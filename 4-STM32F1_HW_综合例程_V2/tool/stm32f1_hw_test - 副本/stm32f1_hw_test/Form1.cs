#define CONSOLE_DEBUG

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using Newtonsoft.Json;

namespace stm32f1_hw_test
{
    public partial class Form1 : Form
    {
        int Xcount = 0;
        string hw_func = "HW";

        string operate_led_on = "LED_ON";
        string operate_led_off = "LED_OFF";

        string operate_oled_show = "OLED_SHOW";
        string operate_oled_clear = "OLED_CLEAR";
        string operate_oled_normal_display = "OLED_NORMAL_DISPLAY";
        string operate_oled_unnormal_display = "OLED_INVERSE_DISPLAY";
        string operate_oled_entry_ram = "OLED_ENTRY_RAM";
        string operate_oled_entry_noram = "OLED_ENTRY_NORAM";
        string operate_oled_contrast = "OLED_CONTRAST";
        string operate_oled_hscroll_set = "OLED_H_SCROLL_SET";
        string operate_oled_vscroll_set = "OLED_V_SCROLL_SET";
        string operate_oled_scroll_start = "OLED_SCROLL_START";
        string operate_oled_scroll_stop = "OLED_SCROLL_STOP";
        string operate_flash_size = "FLASH_SIZE";
        string operate_flash_id = "FLASH_ID";
        string operate_flash_erase = "FLASH_ERASE_S";
        string operate_fs_write = "FS_WRITE";
        string operate_fs_read = "FS_READ";
        string operate_fs_scan = "FS_DIR_R";
        string operate_camera_start = "CAMERA_START";
        string operate_camera_stop = "CAMERA_STOP";
        string operate_camera_light_mode = "CAMERA_LIGHT";
        string operate_camera_saturation = "CAMERA_SATURATION";
        string operate_camera_brightness = "CAMERA_BRIGHTNESS";
        string operate_camera_contrast = "CAMERA_CONTRAST";
        string operate_camera_effect = "CAMERA_EFFECT";
        string operate_sht20_start_update = "SHT20_START_UPDATE";
        string operate_sht20_stop_update = "SHT20_STOP_UPDATE";

        Bitmap OvImage = new Bitmap(400, 400);


        const int PRINTFING_LOG = 0;
        const int PARSEING_JSON = 1;
        int serial_recv_status = PRINTFING_LOG;
        string recv_json_str;

        public const int WM_DEVICE_CHANGE = 0x219;
        public const int DBT_DEVICEARRIVAL = 0x8000;
        public const int DBT_DEVICE_REMOVE_COMPLETE = 0x8004;


        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            search_add_serial_port();
            oled_tab_init();
            camera_tab_init();
            basic_func_enable(false);
            log_func_enable(false);
            cb_serial_baudrate.SelectedIndex = 1;
        }

        private void b_serial_open_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)//串口处于关闭状态
            {
                try
                {

                    if (cb_serial_port.SelectedIndex == -1)
                    {
                        MessageBox.Show("Error: 无效的端口,请重新选择", "Error");
                        return;
                    }
                    string strSerialName = cb_serial_port.SelectedItem.ToString();

                    serialPort1.PortName = strSerialName;//串口号
                    serialPort1.BaudRate = Convert.ToInt32(cb_serial_baudrate.SelectedItem.ToString());//波特率
                    serialPort1.DataBits = 8;//数据位
                    serialPort1.StopBits = StopBits.One;
                    serialPort1.Parity = Parity.None;

                    //打开串口
                    serialPort1.Open();

                    basic_func_enable(true);
                    log_func_enable(true);
                    b_serial_open.Enabled = false;
                    b_serial_close.Enabled = true;

                    b_start_update_temphump.Enabled = true;
                    b_stop_update_temphump.Enabled = false;

                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("Error:" + ex.Message, "Error");
                    return;
                }
            }
        }

        /* 串口搜索 */
        private void search_add_serial_port()
        {
            /* 更新串口按键状态 */

            /*------串口界面参数设置------*/
            int has_port = 0;
            //检查是否含有串口
            string[] str = SerialPort.GetPortNames();


            //添加串口
            foreach (string s in str)
            {
                has_port++;

                if (!cb_serial_port.Items.Contains(s))
                    cb_serial_port.Items.Add(s);
            }

            if (has_port == 0)
            {
                return;
            }
            //设置默认串口选项
            cb_serial_port.SelectedIndex = 0;

        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_DEVICE_CHANGE)        // 捕获USB设备的拔出消息WM_DEVICECHANGE
            {
                switch (m.WParam.ToInt32())
                {
                    case DBT_DEVICE_REMOVE_COMPLETE:    // USB拔出    
                    {
                        b_serial_open.Enabled = true;
                        b_serial_close.Enabled = false;
                    }
                    break;
                    case DBT_DEVICEARRIVAL:             // USB插入获取对应串口名称      
                    {
                        search_add_serial_port();
                    }
                    break;
                }
            }
            base.WndProc(ref m);

        }

        private void b_serial_close_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)//串口处于关闭状态
            {
                serialPort1.Close();//关闭串口
                
                b_serial_open.Enabled = true;
                b_serial_close.Enabled = false;

                basic_func_enable(false);
                log_func_enable(false);

            }
        }

        private void b_serial_send_Click(object sender, EventArgs e)
        {

            if (t_data_send.Text == "")
                MessageBox.Show("发送内容为空", "错误提示");
            else
            {
                if(serialPort1.IsOpen)
                    serialPort1.Write(t_data_send.Text);
                else
                    MessageBox.Show("先打开串口", "错误提示");
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    string recv_data_string;
                    int recv_data_count = serialPort1.BytesToRead;
                    while (serialPort1.BytesToRead > 0)
                    {
                        recv_data_string = serialPort1.ReadLine();
                        if (recv_data_string.StartsWith("CAML"))
                        {
                            if (recv_data_string.Length >= (320*2*2+4))
                            {
                                Color[] colors;
                                colors = RGBToBitmap(recv_data_string.Substring(4, 1280));

                                
                                for (int Ycount = 0; Ycount < 320; Ycount++)
                                {
                                    OvImage.SetPixel(Xcount, Ycount, colors[Ycount]);
                                }
                                Xcount++;
                                if (Xcount == 240)
                                    Xcount = 0;
                                pcamera_box.Image = OvImage;
                            }
                            else
                                Console.WriteLine("camera len error\n" + recv_data_string.Length);

                        }
                        else if (recv_data_string.Contains("{") || (serial_recv_status == PARSEING_JSON))
                        {
                            serial_recv_status = PARSEING_JSON;
                            recv_json_str += recv_data_string;
                            if (recv_data_string.Contains("}"))
                            {
                                serial_recv_status = PRINTFING_LOG;
#if  CONSOLE_DEBUG
                                Console.WriteLine(recv_json_str);
#endif

                                json_status status = JsonConvert.DeserializeObject<json_status>(recv_json_str);

                                json_status_recv_parse(status);
                                recv_json_str = "";
                                //return;
                            }


                        }
                        else
                        {
                            t_data_recv.AppendText(recv_data_string + '\r' + '\n');
                        }
                    }
                    
                }
                catch (Exception ex)
                {
                    return;
                }
            }
        }

        private void b_led_on_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func,operate_led_on,null,null,null,null,null,null);
        }

        private void b_led_off_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_led_off, null, null, null, null, null, null);
        }

        private void json_construction_send(string func,string operate,string param1,string param2,string param3,string param4,string param5,string param6)
        {
            json_commmand cmd = new json_commmand();
            cmd.FUNC = func;
            cmd.OPERATE = operate;
            cmd.PARAM1 = param1;
            cmd.PARAM2 = param2;
            cmd.PARAM3 = param3;
            cmd.PARAM4 = param4;
            cmd.PARAM5 = param5;
            cmd.PARAM6 = param6;
            string json_cmd = JsonConvert.SerializeObject(cmd);
#if  CONSOLE_DEBUG
            Console.WriteLine(json_cmd);
#endif
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine(json_cmd);
            }
        }

        private void json_status_recv_parse(json_status status)
        {
#if  CONSOLE_DEBUG
            Console.WriteLine("----------json_status_recv_parse-------------");
            Console.WriteLine("json func:" + status.FUNC);
            Console.WriteLine("json operate:" + status.OPERATE);
            Console.WriteLine("json status:" + status.STATUS);
            Console.WriteLine("json param1:" + status.PARAM1);
            Console.WriteLine("json param2:" + status.PARAM2);
            Console.WriteLine("json param3:" + status.PARAM3);
            Console.WriteLine("json param4:" + status.PARAM4);
            Console.WriteLine("json param5:" + status.PARAM5);
            Console.WriteLine("----------json_status_recv_parse  end--------");
#endif
            if (status.FUNC == "HW")
            {

                if (status.OPERATE == "SHT20_UPDATE")
                {
                    l_humi.Text = "";
                    l_humi.Text = status.PARAM1 + "% RH";
                    l_temp.Text = "";
                    l_temp.Text = status.PARAM2 + "℃";
                }


            }
        }

        private void oled_tab_init()
        {
            
            for (int index = 0; index < 128; index++)
                c_oled_col.Items.Add("第" + index + "列");
            c_oled_col.SelectedIndex = 0;
            c_oled_page.SelectedIndex = 0;
            c_oled_format.SelectedIndex = 0;

            for (int index = 0; index <= 0xff; index++)
                c_oled_contrast.Items.Add(index.ToString());
            c_oled_contrast.SelectedIndex = 0;


            ch_start_page.SelectedIndex = 0;
            ch_stop_page.SelectedIndex = 0;
            ch_direct.SelectedIndex = 0;
            ch_inteval.SelectedIndex = 0;

            cv_start_page.SelectedIndex = 0;
            cv_stop_page.SelectedIndex = 0;
            cv_direct.SelectedIndex = 0;
            cv_inteval.SelectedIndex = 0;
            for (int index = 0; index < 64; index++)
                cv_offset.Items.Add(index + "rows");
            cv_offset.SelectedIndex = 0;
        }
        private void camera_tab_init()
        {
            ccamera_brightness.SelectedIndex = 0;
            ccamera_contrast.SelectedIndex = 0;
            ccamera_effect.SelectedIndex = 0;
            ccamera_light.SelectedIndex = 0;
            ccamera_saturation.SelectedIndex = 0;
        }

        private void basic_func_enable(bool enable)
        {
            g_basic_func.Enabled = enable;
        }

        private void log_func_enable(bool enable)
        {
            g_log_func.Enabled = enable;
        }
        

        private void b_oled_show_Click(object sender, EventArgs e)
        {
            int oled_col = c_oled_col.SelectedIndex;
            int oled_page = c_oled_page.SelectedIndex;
            int oled_format = c_oled_format.SelectedIndex;
            if (t_oled_string.Text == "")
            {
                MessageBox.Show("输入要显示的字符串", "错误提示");
                return;
            }
            string oled_show = t_oled_string.Text;
            json_construction_send(hw_func, operate_oled_show, oled_col.ToString(), oled_page.ToString(), oled_format.ToString(), oled_show.Length.ToString(), oled_show, null);
        }

        private void b_oled_clear_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_clear, null, null, null, null, null, null);

        }

        private void b_oled_normal_display_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_normal_display, null, null, null, null, null, null);
        }

        private void b_oled_unnormal_display_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_unnormal_display, null, null, null, null, null, null);
        }

        private void b_oled_entry_ram_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_entry_ram, null, null, null, null, null, null);
            
        }

        private void b_oled_entry_noram_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_entry_noram, null, null, null, null, null, null);
        }

        private void b_oled_contrast_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_contrast, c_oled_contrast.SelectedItem.ToString(), null, null, null, null, null);       
        }

        private void bh_scroll_set_Click(object sender, EventArgs e)
        {
            string h_scroll_start_page = ch_start_page.SelectedIndex.ToString();
            string h_scroll_stop_page = ch_stop_page.SelectedIndex.ToString();
            string h_scroll_dir = ch_direct.SelectedIndex.ToString();
            int h_scroll_inteval = ch_inteval.SelectedIndex;
            int inteval = 0;
            if (h_scroll_inteval == 0)
                inteval = 7;
            if (h_scroll_inteval == 1)
                inteval = 4;
            if (h_scroll_inteval == 1)
                inteval = 4;
            if (h_scroll_inteval == 2)
                inteval = 5;
            if (h_scroll_inteval == 3)
                inteval = 0;
            if (h_scroll_inteval == 4)
                inteval = 6;
            if (h_scroll_inteval == 5)
                inteval = 1;
            if (h_scroll_inteval == 6)
                inteval = 2;
            if (h_scroll_inteval == 7)
                inteval = 3;

            json_construction_send(hw_func, operate_oled_hscroll_set, h_scroll_start_page, h_scroll_stop_page, h_scroll_dir, inteval.ToString(), null, null);       

        }

        private void bv_scroll_set_Click(object sender, EventArgs e)
        {
            string v_scroll_start_page = cv_start_page.SelectedIndex.ToString();
            string v_scroll_stop_page = cv_stop_page.SelectedIndex.ToString();
            int v_scroll_dir = cv_direct.SelectedIndex;
            int scroll_dir = 1;
            if (v_scroll_dir == 0)
                scroll_dir = 2;
            if (v_scroll_dir == 1)
                scroll_dir = 1;

            int v_scroll_inteval = cv_inteval.SelectedIndex;
            string v_scroll_offset = cv_offset.SelectedIndex.ToString();
            int inteval = 0;
            if (v_scroll_inteval == 0)
                inteval = 7;
            if (v_scroll_inteval == 1)
                inteval = 4;
            if (v_scroll_inteval == 1)
                inteval = 4;
            if (v_scroll_inteval == 2)
                inteval = 5;
            if (v_scroll_inteval == 3)
                inteval = 0;
            if (v_scroll_inteval == 4)
                inteval = 6;
            if (v_scroll_inteval == 5)
                inteval = 1;
            if (v_scroll_inteval == 6)
                inteval = 2;
            if (v_scroll_inteval == 7)
                inteval = 3;

            json_construction_send(hw_func, operate_oled_vscroll_set, v_scroll_start_page, v_scroll_stop_page, scroll_dir.ToString(), inteval.ToString(), v_scroll_offset, null);       

        }

        private void bh_scroll_start_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_scroll_start, null, null, null, null, null, null);

        }

        private void bh_sroll_stop_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_oled_scroll_stop, null, null, null, null, null, null);

        }

        private void b_flash_size_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_flash_size, null, null, null, null, null, null);
    
        }

        private void b_flash_id_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_flash_id, null, null, null, null, null, null);
        }

        private void b_flash_erase_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_flash_erase, null, null, null, null, null, null);
        }

        private void b_fs_write_Click(object sender, EventArgs e)
        {
            if (t_fs_name.Text == "")
            {
                MessageBox.Show("输入文件名", "错误提示");
                return;
            }
            string file_name = t_fs_name.Text;
            if(file_name.Length > 16)
            {
                MessageBox.Show("输入小于16字节的文件名字", "错误提示");
                return;
            }

            if (t_fs_text.Text == "")
            {
                MessageBox.Show("输入文件内容", "错误提示");
                return;
            }
            string file_text = t_fs_text.Text;
            if (file_text.Length > 16)
            {
                MessageBox.Show("输入小于16字节的文件内容", "错误提示");
                return;
            }
            json_construction_send(hw_func, operate_fs_write, file_name, file_text, null, null, null, null);


        }

        private void b_fs_read_Click(object sender, EventArgs e)
        {
            if (t_fs_name.Text == "")
            {
                MessageBox.Show("输入文件名", "错误提示");
                return;
            }
            string file_name = t_fs_name.Text;
            if (file_name.Length > 16)
            {
                MessageBox.Show("输入小于16字节的文件名字", "错误提示");
                return;
            }

           
            json_construction_send(hw_func, operate_fs_read, file_name, null, null, null, null, null);
        }

        private void b_fs_scan_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_fs_scan, null, null, null, null, null, null);

        }

        private void bcamera_light_Click(object sender, EventArgs e)
        {
            string light = ccamera_light.SelectedIndex.ToString();
            json_construction_send(hw_func, operate_camera_light_mode, light, null, null, null, null, null);

        }

        private void bcamera_saturation_Click(object sender, EventArgs e)
        {
            string saturation = ccamera_saturation.SelectedIndex.ToString();
            json_construction_send(hw_func, operate_camera_saturation, saturation, null, null, null, null, null);

        }

        private void bcamera_effect_Click(object sender, EventArgs e)
        {
            string effect = ccamera_effect.SelectedIndex.ToString();
            json_construction_send(hw_func, operate_camera_effect, effect, null, null, null, null, null);

        }

        private void bcamera_brightness_Click(object sender, EventArgs e)
        {
            string brightness = ccamera_brightness.SelectedIndex.ToString();
            json_construction_send(hw_func, operate_camera_brightness, brightness, null, null, null, null, null);

        }

        private void bcamera_contrast_Click(object sender, EventArgs e)
        {
            string contrast = ccamera_contrast.SelectedIndex.ToString();
            json_construction_send(hw_func, operate_camera_contrast, contrast, null, null, null, null, null);

        }

        private void bcamera_start_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_camera_start, null, null, null, null, null, null);

        }

        private void bcamera_stop_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_camera_stop, null, null, null, null, null, null);

        }

        private void bsave_camera_Click(object sender, EventArgs e)
        {
            OvImage.Save("OV7670.bmp");
            MessageBox.Show("图片保存成功", "信息");
        }

        private Color[] RGBToBitmap(string data)
        {
            Color[] colors;
            //将十六进制字符串转换为字节数组
            byte[] hexData = hexStringToByte(data);
            //将RGB565转换为RGB三色数值
            colors = RGB565ToColor(hexData);
            return colors;
        }

        private static Color[] RGB565ToColor(byte[] hexArray)
        {
            //两字节代表一个像素，故长度为一半
            Color[] colors = new Color[hexArray.Length / 2];
            //生成Color值
            for (int i = 0; i < hexArray.Length; i += 2)
            {
                //U16(565) to RGB:
                //byte bg_r_color = ((bg_color >> 11) & 0xff) << 3;
                //byte bg_g_color = ((bg_color >> 5) & 0x3f) << 2;
                //byte bg_b_color = (bg_color & 0x1f) << 2;
                byte rr = (byte)(hexArray[i + 1] & 0xf8);//byte和byte相与运算后，结果变为int
                byte gg = (byte)((hexArray[i + 1] << 5) | ((hexArray[i] & 0xe0) >> 3));
                byte bb = (byte)(hexArray[i] << 3);

                // 补偿  
                rr = (byte)(rr | ((rr & 0x38) >> 3));
                gg = (byte)(gg | ((gg & 0x0c) >> 2));
                bb = (byte)(bb | ((bb & 0x38) >> 3));

                //设置Color值
                colors[i / 2] = Color.FromArgb(rr, gg, bb);
            }
            return colors;
        }

        /// <summary>
        /// 把16进制字符串转换成字节数组
        /// </summary>
        /// <param name="hex"></param>
        /// <returns></returns>
        public static byte[] hexStringToByte(String hex)
        {
            int len = (hex.Length / 2);
            byte[] result = new byte[len];
            char[] achar = hex.ToCharArray();
            for (int i = 0; i < len; i++)
            {
                int pos = i * 2;
                result[i] = (byte)(toByte(achar[pos]) << 4 | toByte(achar[pos + 1]));
            }
            return result;
        }

        /// <summary>
        /// 将十六进制的字符转换为字节
        /// </summary>
        /// <param name="c">字符</param>
        /// <returns></returns>
        private static byte toByte(char c)
        {
            byte b = (byte)"0123456789abcdef".IndexOf(c);
            if (b > 16)
                b = (byte)"0123456789ABCDEF".IndexOf(c);
            return b;
        }

        private void b_board_buy_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://shop220811498.taobao.com");
        }

        private void b_log_clear_Click(object sender, EventArgs e)
        {
            t_data_recv.Text = "";
        }

        private void b_start_update_temphump_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_sht20_start_update, null, null, null, null, null, null);
            b_start_update_temphump.Enabled = false;
            b_stop_update_temphump.Enabled = true;
        }

        private void b_stop_update_temphump_Click(object sender, EventArgs e)
        {
            json_construction_send(hw_func, operate_sht20_stop_update, null, null, null, null, null, null);
            b_start_update_temphump.Enabled = true;
            b_stop_update_temphump.Enabled = false;
        }

    
    }


    /* JSON定义 */
    public class json_commmand
    {
        public string FUNC { get; set; }
        public string OPERATE { get; set; }
        public string PARAM1 { get; set; }
        public string PARAM2 { get; set; }
        public string PARAM3 { get; set; }
        public string PARAM4 { get; set; }
        public string PARAM5 { get; set; }
        public string PARAM6 { get; set; }
    }

    public class json_status
    {
        public string FUNC { get; set; }
        public string OPERATE { get; set; }
        public string STATUS { get; set; }
        public string PARAM1 { get; set; }
        public string PARAM2 { get; set; }
        public string PARAM3 { get; set; }
        public string PARAM4 { get; set; }
        public string PARAM5 { get; set; }
        public string PARAM6 { get; set; }
    }
}
