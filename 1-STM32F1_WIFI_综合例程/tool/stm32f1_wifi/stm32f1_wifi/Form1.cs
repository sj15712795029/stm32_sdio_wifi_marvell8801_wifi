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

namespace stm32f1_wifi
{
    public partial class Form1 : Form
    {
        string wifi_func = "WIFI";

        string operate_wifi_on = "WIFI_ON";
        string operate_wifi_off = "WIFI_OFF";
        string operate_wifi_scan = "WIFI_SCAN";
        string operate_wifi_connect = "WIFI_CONNECT";
        string operate_wifi_disconnect = "WIFI_DISCONNECT";
        string operate_wifi_showip = "WIFI_SHOW_IP";
        string operate_wifi_start_ap = "WIFI_START_AP";
        string operate_wifi_stop_ap = "WIFI_STOP_AP";
        string operate_wifi_ap_disconnect_sta = "WIFI_DISCONNECT_STA";
        string operate_wifi_start_ping = "WIFI_PING";
        string operate_wifi_stop_ping = "WIFI_STOP_PING";
        string operate_wifi_udp_connect = "WIFI_UDP_CONNECT";
        string operate_wifi_udp_disconnect = "WIFI_UDP_DISCONNECT";
        string operate_wifi_udp_send = "WIFI_UDP_SEND";
        string operate_wifi_tcpc_connect = "WIFI_TCPC_CONNECT";
        string operate_wifi_tcpc_disconnect = "WIFI_TCPC_DISCONNECT";
        string operate_wifi_tcpc_send = "WIFI_TCPC_SEND";
        string operate_wifi_tcps_connect = "WIFI_TCPS_CONNECT";
        string operate_wifi_tcps_disconnect = "WIFI_TCPS_DISCONNECT";
        string operate_wifi_tcps_send = "WIFI_TCPS_SEND";
        string operate_wifi_mqtt_connect = "WIFI_MQTT_CONNECT";
        string operate_wifi_mqtt_disconnect = "WIFI_MQTT_DISCONNECT";
        string operate_wifi_mqtt_subcribe = "WIFI_MQTT_SUBCRIBE";
        string operate_wifi_mqtt_unsubcribe = "WIFI_MQTT_UNSUBCRIBE";
        string operate_wifi_mqtt_publish = "WIFI_MQTT_PUBLISH";

        string ap_disconnect_sta = "";

        public const int WM_DEVICE_CHANGE = 0x219;
        public const int DBT_DEVICEARRIVAL = 0x8000;
        public const int DBT_DEVICE_REMOVE_COMPLETE = 0x8004;

        const int PRINTFING_LOG = 0;
        const int PARSEING_JSON = 1;
        int serial_recv_status = PRINTFING_LOG;
        string recv_json_str;

        const int TCP_ROLE_NONE = -1;
        const int TCP_ROLE_CLIENT = 0;
        const int TCP_ROLE_SERVER = 1;
        int tcp_rule = TCP_ROLE_NONE;
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            bwifi_start.Enabled = false;
            bwifi_stop.Enabled = false;
            log_func_enable(false);
            search_add_serial_port();
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

                    bwifi_start.Enabled = true;
                    bwifi_stop.Enabled = false;
                    
                    log_func_enable(true);
                    b_serial_open.Enabled = false;
                    b_serial_close.Enabled = true;

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
                            bwifi_start.Enabled = false;
                            bwifi_stop.Enabled = false;
                            log_func_enable(false);
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

                bwifi_start.Enabled = false;
                bwifi_stop.Enabled = false;
                b_serial_open.Enabled = true;
                b_serial_close.Enabled = false;

                basic_func_enable(false);
                log_func_enable(false);

            }
        }

        private void b_board_buy_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://shop220811498.taobao.com");
        }

        private void log_func_enable(bool enable)
        {
            g_log_func.Enabled = enable;
        }

        private void json_construction_send(string func, string operate, string param1, string param2, string param3, string param4, string param5, string param6)
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
                        if (recv_data_string.Contains("{") || (serial_recv_status == PARSEING_JSON))
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

                        t_data_recv.AppendText(recv_data_string + '\r' + '\n');
                    }

                }
                catch (Exception ex)
                {
                    return;
                }
            }
        }

        private void b_serial_send_Click(object sender, EventArgs e)
        {
            if (t_data_send.Text == "")
                MessageBox.Show("发送内容为空", "错误提示");
            else
            {
                if (serialPort1.IsOpen)
                    serialPort1.Write(t_data_send.Text);
                else
                    MessageBox.Show("先打开串口", "错误提示");
            }
        }

        private void bwifi_start_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_on, null, null, null, null, null, null);
        }

        private void bwifi_stop_Click(object sender, EventArgs e)
        {
            bwifi_start.Enabled = true;
            bwifi_stop.Enabled = false;
            json_construction_send(wifi_func, operate_wifi_off, null, null, null, null, null, null);
        }

        private void bshow_ip_Click_1(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_showip, null, null, null, null, null, null);
        }

        private void bwifi_scan_Click(object sender, EventArgs e)
        {
            dgwifi_scan_result.Rows.Clear();
            json_construction_send(wifi_func, operate_wifi_scan, null, null, null, null, null, null);
        }

        private void bwifi_connect_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_connect, tsta_ssid.Text, tsta_pwd.Text, null, null, null, null);

        }

        private void bwifi_disconnect_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_disconnect, null, null, null, null, null, null);

        }

        private void bwifi_start_ap_Click(object sender, EventArgs e)
        {
            string security = "OPEN";
            string hidden;
            string ssid = tap_ssid.Text;

            if (ssid == "")
            {
                MessageBox.Show("请填入热点名称", "错误提示");
                return;
            }
            string pwd = tap_pwd.Text;

            if (rsec_open.Checked)
                security = "OPEN";
            else if (rsec_wap.Checked)
                security = "WPA";
            else if (rsec_wpa2.Checked)
                security = "WPA2";

            if (security != "OPEN" && (pwd == ""))
            {
                MessageBox.Show("请填入热点密码", "错误提示");
                return;
            }

            if (cap_hidden.Checked)
                hidden = "HIDDEN";
            else
                hidden = "";

            json_construction_send(wifi_func, operate_wifi_start_ap, ssid, pwd, security, hidden, null, null);

            
        }

        private void bwifi_stop_ap_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_stop_ap, null, null, null, null, null, null);
            bwifi_start_ap.Enabled = true;
            bwifi_stop_ap.Enabled = false;

        }

        private void bwifi_disconnect_sta_Click(object sender, EventArgs e)
        {
            if (ap_disconnect_sta == "")
            {
                MessageBox.Show("请选择要断开的STA", "错误提示");
                return;
            }

            json_construction_send(wifi_func, operate_wifi_ap_disconnect_sta, ap_disconnect_sta, null, null, null, null, null);
            ap_disconnect_sta = "";
        }

        private void bping_Click(object sender, EventArgs e)
        {
            if (tping_ip.Text == "")
            {
                MessageBox.Show("请填入IP地址", "错误提示");
                return;
            }
            json_construction_send(wifi_func, operate_wifi_start_ping, tping_ip.Text, null, null, null, null, null);

        }

        private void bping_stop_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_stop_ping, null, null, null, null, null, null);

        }

        private void dgwifi_ap_con_result_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (dgwifi_ap_con_result.CurrentRow.Cells[1].Value != null)
                ap_disconnect_sta = dgwifi_ap_con_result.CurrentRow.Cells[1].Value.ToString();
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
            if (status.FUNC == "WIFI")
            {
                if (status.OPERATE == "WIFI_ON")
                {
                    if (status.STATUS == "SUCCESS")
                    {
                        //linfo_status.Text = "初始化成功";
                        bwifi_start.Enabled = false;
                        bwifi_stop.Enabled = true;
                        /* STA角色按钮状态 */
                        bwifi_scan.Enabled = true;
                        bwifi_connect.Enabled = true;

                        /* AP角色按钮状态 */
                        bwifi_start_ap.Enabled = true;
                        basic_func_enable(true);
                    }
                }

                if (status.OPERATE == "WIFI_SCAN")
                {
                    int index = dgwifi_scan_result.Rows.Add();
                    dgwifi_scan_result.Rows[index].Cells[0].Value = status.PARAM1;
                    dgwifi_scan_result.Rows[index].Cells[1].Value = status.PARAM2;
                    dgwifi_scan_result.Rows[index].Cells[2].Value = status.PARAM3;
                    dgwifi_scan_result.Rows[index].Cells[3].Value = status.PARAM4;
                }

                if (status.OPERATE == "WIFI_CONNECT")
                {
                    if (status.STATUS == "SUCCESS")
                    {
                        //linfo_status.Text = "连接成功";
                        bwifi_connect.Enabled = false;
                        bwifi_disconnect.Enabled = true;

                        bshow_ip.Enabled = true;

                    }
                }

                if (status.OPERATE == "WIFI_SHOW_IP")
                {
                    lshow_ip.Text = "IP地址：" + status.PARAM1 + "  子网掩码: " + status.PARAM2 + "  网关: " + status.PARAM3;
                }

                if (status.OPERATE == "WIFI_START_AP")
                {
                    if (status.STATUS == "SUCCESS")
                    {
                        //linfo_role.Text = "AP";
                        //linfo_status.Text = "开启热点成功";
                        bwifi_start_ap.Enabled = false;
                        bwifi_stop_ap.Enabled = true;
                        bshow_ip.Enabled = false;

                    }
                }

                if (status.OPERATE == "WIFI_AP_CON_IND")
                {

                    int count = dgwifi_ap_con_result.Rows.Count;
                    for (int index = 0; index < count - 1; index++)
                    {
                        if (dgwifi_ap_con_result.Rows[index].Cells[0].Value.ToString() == status.PARAM1)
                        {
#if  CONSOLE_DEBUG
                            Console.WriteLine("数据存在");
#endif
                            return;
                        }
                    }

                    int data_index = dgwifi_ap_con_result.Rows.Add();
                    dgwifi_ap_con_result.Rows[data_index].Cells[0].Value = status.PARAM1;
                    dgwifi_ap_con_result.Rows[data_index].Cells[1].Value = status.PARAM2;
                    dgwifi_ap_con_result.Rows[data_index].Cells[2].Value = status.PARAM3;

                    if (dgwifi_ap_con_result.Rows.Count > 0)
                    {
                        bwifi_disconnect_sta.Enabled = true;
                    }

                }

                if (status.OPERATE == "WIFI_AP_DISCON_RET")
                {
                    int count = dgwifi_ap_con_result.Rows.Count;
                    for (int index = 0; index < count - 1; index++)
                    {
                        string mac = dgwifi_ap_con_result.Rows[index].Cells[1].Value.ToString();
                        if (mac == status.PARAM1)
                        {
                            dgwifi_ap_con_result.Rows.RemoveAt(index);
                        }
                    }

                    if (dgwifi_ap_con_result.Rows.Count > 1)
                    {
                        bwifi_disconnect_sta.Enabled = true;
                    }
                    else
                    {
                        bwifi_disconnect_sta.Enabled = false;
                    }

                }

                if (status.OPERATE == "WIFI_PING")
                {
               
                    if (Convert.ToInt32(status.PARAM2) == 0)
                        tping_result.AppendText("receive from " + status.PARAM1 + " time< 1ms" + '\r' + '\n');
                    else
                        tping_result.AppendText("receive from " + status.PARAM1 + " time=" + status.PARAM2 + " ms" + '\r' + '\n');
                }

                if (status.OPERATE == "WIFI_STOP_PING")
                {
                    Int32 loss_all = 0;
                    double packet_loss = 0;
                    if (Convert.ToInt32(status.PARAM2) == 0)
                        loss_all = 1;
                    else
                        packet_loss = (Convert.ToDouble(status.PARAM1) - Convert.ToDouble(status.PARAM2)) / Convert.ToDouble(status.PARAM2);
                    tping_result.AppendText("" + '\r' + '\n');
                    tping_result.AppendText("--- ping statistics ---" + '\r' + '\n');
                    tping_result.AppendText(status.PARAM1 + " packets transmitted, " + status.PARAM2 + " received, ");

                    if(loss_all == 1)
                        tping_result.AppendText("100%packet loss" + '\r' + '\n');
                    else
                        tping_result.AppendText(packet_loss.ToString() + "%packet loss" + '\r' + '\n');
                }

                if (status.OPERATE == "WIFI_UDP_RECV")
                {
                    /* PARAM1:DATA PARAM2:LENGTH */
                    int udp_recv_count = Convert.ToInt32(ludp_recv_count.Text) + Convert.ToInt32(status.PARAM2);
                    ludp_recv_count.Text = udp_recv_count.ToString();

                    tudp_recv.AppendText(status.PARAM1 + '\r' + '\n');
                }

                if (status.OPERATE == "WIFI_TCPC_RECV")
                {
                    /* PARAM1:DATA PARAM2:LENGTH */
                    int tcp_recv_count = Convert.ToInt32(ltcp_recv_count.Text) + Convert.ToInt32(status.PARAM2);
                    ltcp_recv_count.Text = tcp_recv_count.ToString();

                    ttcp_recv.AppendText(status.PARAM1 + '\r' + '\n');
                }

                if (status.OPERATE == "WIFI_TCPS_RECV")
                {
                    /* PARAM1:IP PARAM2:PORT PARMA3:DATA PARAM4:LENGTH */
                    int tcp_recv_count = Convert.ToInt32(ltcp_recv_count.Text) + Convert.ToInt32(status.PARAM4);
                    ltcp_recv_count.Text = tcp_recv_count.ToString();

                    ttcp_recv.AppendText("收到IP:" + status.PARAM1 + " 端口:" + status.PARAM2 + " 数据:" + status.PARAM3 + '\r' + '\n');
                }

                if (status.OPERATE == "WIFI_MQTT_SUBCRIBE_RECV")
                {
                    tcloud_subcribe_data.AppendText(status.PARAM1 + '\r' + '\n');
                }


            }
        }

        private void dgwifi_scan_result_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (dgwifi_scan_result.CurrentRow.Cells[0].Value != null)
                tsta_ssid.Text = dgwifi_scan_result.CurrentRow.Cells[0].Value.ToString();
        }

        private void bping_result_clear_Click(object sender, EventArgs e)
        {
            tping_result.Text = "";
        }

        private void budp_connect_Click(object sender, EventArgs e)
        {
            if (tlocal_udp_port.Text == "")
            {
                MessageBox.Show("请填入要开启的本地端口", "错误提示");
                return;
            }

            if (tremote_udp_port.Text == "")
            {
                MessageBox.Show("请填入要开启的远端端口", "错误提示");
                return;
            }

            if (tremote_udp_ip.Text == "")
            {
                MessageBox.Show("请填入要开启的远端IP", "错误提示");
                return;
            }
            budp_connect.Enabled = false;
            budp_disconnect.Enabled = true;

            json_construction_send(wifi_func, operate_wifi_udp_connect, tremote_udp_ip.Text, tlocal_udp_port.Text, tremote_udp_port.Text, null, null, null);

        }

        private void budp_disconnect_Click(object sender, EventArgs e)
        {
            budp_connect.Enabled = true;
            budp_disconnect.Enabled = false;
            json_construction_send(wifi_func, operate_wifi_udp_disconnect, null, null, null, null, null, null);
        }

        private void budp_clear_recv_data_Click(object sender, EventArgs e)
        {
            tudp_recv.Text = "";
        }

        private void budp_clear_send_data_Click(object sender, EventArgs e)
        {
            tudp_send.Text = "";
        }

        private void budp_send_Click(object sender, EventArgs e)
        {
            if (tudp_send.Text == "")
            {
                MessageBox.Show("请填入要发送的内容", "错误提示");
                return;
            }

            json_construction_send(wifi_func, operate_wifi_udp_send, tudp_send.Text, tudp_send.Text.Length.ToString(), null, null, null, null);

            int udp_send_count = Convert.ToInt32(ludp_send_count.Text) + tudp_send.Text.Length;
            ludp_send_count.Text = udp_send_count.ToString();
            
        }

        private void budp_clear_statistics_Click(object sender, EventArgs e)
        {
            ludp_recv_count.Text = "0";
            ludp_send_count.Text = "0";
        }

        private void btcp_connect_Click(object sender, EventArgs e)
        {
            if (tcp_rule == TCP_ROLE_NONE)
            {
                MessageBox.Show("请填入TCP协议类型", "错误提示");
                return;
            }     

            if (tremote_tcp_port.Text == "" && tcp_rule == TCP_ROLE_CLIENT)
            {
                MessageBox.Show("请填入远端端口", "错误提示");
                return;
            }

            if (tlocal_tcp_port.Text == "" && tcp_rule == TCP_ROLE_SERVER)
            {
                MessageBox.Show("请填入本地端口", "错误提示");
                return;
            }

            btcp_connect.Enabled = false;
            btcp_disconnect.Enabled = true;

            if (tcp_rule == TCP_ROLE_CLIENT)
            {
                if (tremote_tcp_ip.Text == "")
                {
                    MessageBox.Show("请填入远端IP", "错误提示");
                    return;
                }
                json_construction_send(wifi_func, operate_wifi_tcpc_connect, tremote_tcp_ip.Text, null, tremote_tcp_port.Text, null, null, null);

            }
            else if (tcp_rule == TCP_ROLE_SERVER)
            {
                json_construction_send(wifi_func, operate_wifi_tcps_connect, null, tlocal_tcp_port.Text, null, null, null, null);
                tremote_tcp_ip.Enabled = true;

            }

        }

        private void btcp_disconnect_Click(object sender, EventArgs e)
        {
            btcp_connect.Enabled = true;
            btcp_disconnect.Enabled = false;

            if (tcp_rule == TCP_ROLE_CLIENT)
            {
                json_construction_send(wifi_func, operate_wifi_tcpc_disconnect, null, null, null, null, null, null);

            }
            else if (tcp_rule == TCP_ROLE_SERVER)
            {
                json_construction_send(wifi_func, operate_wifi_tcps_disconnect, null, null, null, null, null, null);

            }
        }

        private void btcp_clear_recv_data_Click(object sender, EventArgs e)
        {
            ttcp_recv.Text = "";
        }

        private void btcp_clear_send_data_Click(object sender, EventArgs e)
        {
            ttcp_send.Text = "";
        }

        private void btcp_send_Click(object sender, EventArgs e)
        {
            if (ttcp_send.Text == "")
            {
                MessageBox.Show("请填入要发送的内容", "错误提示");
                return;
            }

            

            if (tcp_rule == TCP_ROLE_CLIENT)
            {
                json_construction_send(wifi_func, operate_wifi_tcpc_send, ttcp_send.Text, ttcp_send.Text.Length.ToString(), null, null, null, null);

            }
            else if (tcp_rule == TCP_ROLE_SERVER)
            {

                if (tremote_tcp_ip.Text == "")
                {
                    MessageBox.Show("请填入远端IP", "错误提示");
                    return;
                }
                json_construction_send(wifi_func, operate_wifi_tcps_send, tremote_tcp_ip.Text, null, ttcp_send.Text, ttcp_send.Text.Length.ToString(), null, null);

            }
        }

        private void btcp1_clear_statistics_Click(object sender, EventArgs e)
        {
            ltcp_recv_count.Text = "0";
            ltcp_send_count.Text = "0";
        }

        private void ctcp_func_SelectedIndexChanged(object sender, EventArgs e)
        {
            tcp_rule = ctcp_func.SelectedIndex;
            if (ctcp_func.SelectedIndex == 0)//客户端
            {
                tlocal_tcp_port.Enabled = false;
                tremote_tcp_port.Enabled = true;
                tremote_tcp_ip.Enabled = true;
            }
            else if (ctcp_func.SelectedIndex == 1)//服务端
            {
                tlocal_tcp_port.Enabled = true;
                tremote_tcp_port.Enabled = false;
                tremote_tcp_ip.Enabled = false;
            }
            
        }

        private void bwifi_cloud_mqtt_con_Click(object sender, EventArgs e)
        {
            if (tcloud_web_address.Text == "")
            {
                MessageBox.Show("请填入要连接的云服务器网址", "错误提示");
                return;
            }

            if (tcloud_acount.Text == "")
            {
                MessageBox.Show("请填入云服务器账号", "错误提示");
                return;
            }

            if (tcloud_password.Text == "")
            {
                MessageBox.Show("请填入云服务器密码", "错误提示");
                return;
            }

            json_construction_send(wifi_func, operate_wifi_mqtt_connect, tcloud_web_address.Text, tcloud_acount.Text, tcloud_password.Text, null, null, null);

        }

        private void bwifi_cloud_mqtt_discon_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_mqtt_disconnect, null, null, null, null, null, null);

        }

        private void bwifi_cloud_mqtt_subcribe_Click(object sender, EventArgs e)
        {
            if (tcloud_subcribe.Text == "")
            {
                MessageBox.Show("请填入要订阅的主题", "错误提示");
                return;
            }
            json_construction_send(wifi_func, operate_wifi_mqtt_subcribe, tcloud_subcribe.Text, null, null, null, null, null);

        }

        private void bwifi_cloud_mqtt_unsubcribe_Click(object sender, EventArgs e)
        {
            json_construction_send(wifi_func, operate_wifi_mqtt_unsubcribe, tcloud_subcribe.Text, null, null, null, null, null);

        }

        private void bcloud_publish_Click(object sender, EventArgs e)
        {
            if (tcloud_publish_topic.Text == "")
            {
                MessageBox.Show("请填入要推送的主题", "错误提示");
                return;
            }
            if (tcloud_publish_data.Text == "")
            {
                MessageBox.Show("请填入要推送的内容", "错误提示");
                return;
            }
            json_construction_send(wifi_func, operate_wifi_mqtt_publish, tcloud_publish_topic.Text, tcloud_publish_data.Text, tcloud_publish_data.Text.Length.ToString(), null, null, null);

        }

        private void basic_func_enable(bool enable)
        {
            func_opt.Enabled = enable;
        }

        private void b_log_clear_Click(object sender, EventArgs e)
        {
            t_data_recv.Text = "";
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
