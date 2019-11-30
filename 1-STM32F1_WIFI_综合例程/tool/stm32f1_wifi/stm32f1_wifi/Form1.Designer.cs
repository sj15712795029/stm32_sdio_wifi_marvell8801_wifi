namespace stm32f1_wifi
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.b_board_buy = new System.Windows.Forms.Button();
            this.b_serial_close = new System.Windows.Forms.Button();
            this.b_serial_open = new System.Windows.Forms.Button();
            this.cb_serial_baudrate = new System.Windows.Forms.ComboBox();
            this.cb_serial_port = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.g_log_func = new System.Windows.Forms.GroupBox();
            this.b_serial_send = new System.Windows.Forms.Button();
            this.t_data_send = new System.Windows.Forms.TextBox();
            this.t_data_recv = new System.Windows.Forms.TextBox();
            this.b_log_clear = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.func_opt = new System.Windows.Forms.GroupBox();
            this.btcp_clear_statistics = new System.Windows.Forms.TabControl();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.lshow_ip = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tsta_ssid = new System.Windows.Forms.TextBox();
            this.bshow_ip = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.bwifi_disconnect = new System.Windows.Forms.Button();
            this.dgwifi_scan_result = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bwifi_scan = new System.Windows.Forms.Button();
            this.tsta_pwd = new System.Windows.Forms.TextBox();
            this.bwifi_connect = new System.Windows.Forms.Button();
            this.tabPage10 = new System.Windows.Forms.TabPage();
            this.dgwifi_ap_con_result = new System.Windows.Forms.DataGridView();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.cap_hidden = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.rsec_wpa2 = new System.Windows.Forms.RadioButton();
            this.tap_ssid = new System.Windows.Forms.TextBox();
            this.rsec_wap = new System.Windows.Forms.RadioButton();
            this.tap_pwd = new System.Windows.Forms.TextBox();
            this.rsec_open = new System.Windows.Forms.RadioButton();
            this.bwifi_disconnect_sta = new System.Windows.Forms.Button();
            this.bwifi_start_ap = new System.Windows.Forms.Button();
            this.bwifi_stop_ap = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label10 = new System.Windows.Forms.Label();
            this.bping_result_clear = new System.Windows.Forms.Button();
            this.bping_stop = new System.Windows.Forms.Button();
            this.tping_result = new System.Windows.Forms.TextBox();
            this.tping_ip = new System.Windows.Forms.TextBox();
            this.bping = new System.Windows.Forms.Button();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.label22 = new System.Windows.Forms.Label();
            this.btcp_clear_send_data = new System.Windows.Forms.Button();
            this.btcp_clear_recv_data = new System.Windows.Forms.Button();
            this.btcp1_clear_statistics = new System.Windows.Forms.Button();
            this.btcp_send = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.ttcp_send = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.ttcp_recv = new System.Windows.Forms.TextBox();
            this.ltcp_recv_count = new System.Windows.Forms.Label();
            this.ltcp_send_count = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.tremote_tcp_ip = new System.Windows.Forms.TextBox();
            this.tremote_tcp_port = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.tlocal_tcp_port = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.btcp_disconnect = new System.Windows.Forms.Button();
            this.btcp_connect = new System.Windows.Forms.Button();
            this.ctcp_func = new System.Windows.Forms.ComboBox();
            this.tabPage8 = new System.Windows.Forms.TabPage();
            this.budp_clear_send_data = new System.Windows.Forms.Button();
            this.budp_clear_recv_data = new System.Windows.Forms.Button();
            this.budp_clear_statistics = new System.Windows.Forms.Button();
            this.budp_send = new System.Windows.Forms.Button();
            this.gudp_send = new System.Windows.Forms.GroupBox();
            this.tudp_send = new System.Windows.Forms.TextBox();
            this.gudp_recv = new System.Windows.Forms.GroupBox();
            this.tudp_recv = new System.Windows.Forms.TextBox();
            this.ludp_recv_count = new System.Windows.Forms.Label();
            this.ludp_send_count = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.tremote_udp_ip = new System.Windows.Forms.TextBox();
            this.tremote_udp_port = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.tlocal_udp_port = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.budp_disconnect = new System.Windows.Forms.Button();
            this.budp_connect = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label27 = new System.Windows.Forms.Label();
            this.tcloud_publish_data = new System.Windows.Forms.TextBox();
            this.bcloud_publish = new System.Windows.Forms.Button();
            this.tcloud_publish_topic = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.bwifi_cloud_mqtt_unsubcribe = new System.Windows.Forms.Button();
            this.label24 = new System.Windows.Forms.Label();
            this.tcloud_subcribe_data = new System.Windows.Forms.TextBox();
            this.tcloud_subcribe = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.bwifi_cloud_mqtt_subcribe = new System.Windows.Forms.Button();
            this.tcloud_password = new System.Windows.Forms.TextBox();
            this.tcloud_acount = new System.Windows.Forms.TextBox();
            this.tcloud_web_address = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.bwifi_cloud_mqtt_discon = new System.Windows.Forms.Button();
            this.bwifi_cloud_mqtt_con = new System.Windows.Forms.Button();
            this.bwifi_stop = new System.Windows.Forms.Button();
            this.bwifi_start = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.groupBox1.SuspendLayout();
            this.g_log_func.SuspendLayout();
            this.func_opt.SuspendLayout();
            this.btcp_clear_statistics.SuspendLayout();
            this.tabPage9.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgwifi_scan_result)).BeginInit();
            this.tabPage10.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgwifi_ap_con_result)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.tabPage7.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.tabPage8.SuspendLayout();
            this.gudp_send.SuspendLayout();
            this.gudp_recv.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.b_board_buy);
            this.groupBox1.Controls.Add(this.b_serial_close);
            this.groupBox1.Controls.Add(this.b_serial_open);
            this.groupBox1.Controls.Add(this.cb_serial_baudrate);
            this.groupBox1.Controls.Add(this.cb_serial_port);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(586, 100);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口配置区";
            // 
            // b_board_buy
            // 
            this.b_board_buy.BackgroundImage = global::stm32f1_wifi.Properties.Resources.购买;
            this.b_board_buy.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.b_board_buy.Location = new System.Drawing.Point(450, 25);
            this.b_board_buy.Name = "b_board_buy";
            this.b_board_buy.Size = new System.Drawing.Size(130, 65);
            this.b_board_buy.TabIndex = 6;
            this.toolTip1.SetToolTip(this.b_board_buy, "购买开发板");
            this.b_board_buy.UseVisualStyleBackColor = true;
            this.b_board_buy.Click += new System.EventHandler(this.b_board_buy_Click);
            // 
            // b_serial_close
            // 
            this.b_serial_close.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.b_serial_close.Enabled = false;
            this.b_serial_close.Image = global::stm32f1_wifi.Properties.Resources.串口关闭;
            this.b_serial_close.Location = new System.Drawing.Point(333, 25);
            this.b_serial_close.Name = "b_serial_close";
            this.b_serial_close.Size = new System.Drawing.Size(95, 65);
            this.b_serial_close.TabIndex = 5;
            this.toolTip1.SetToolTip(this.b_serial_close, "关闭串口");
            this.b_serial_close.UseVisualStyleBackColor = true;
            this.b_serial_close.Click += new System.EventHandler(this.b_serial_close_Click);
            // 
            // b_serial_open
            // 
            this.b_serial_open.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.b_serial_open.Image = global::stm32f1_wifi.Properties.Resources.串口打开;
            this.b_serial_open.Location = new System.Drawing.Point(220, 25);
            this.b_serial_open.Name = "b_serial_open";
            this.b_serial_open.Size = new System.Drawing.Size(95, 65);
            this.b_serial_open.TabIndex = 4;
            this.toolTip1.SetToolTip(this.b_serial_open, "打开串口");
            this.b_serial_open.UseVisualStyleBackColor = true;
            this.b_serial_open.Click += new System.EventHandler(this.b_serial_open_Click);
            // 
            // cb_serial_baudrate
            // 
            this.cb_serial_baudrate.AutoCompleteCustomSource.AddRange(new string[] {
            "115200",
            "921600"});
            this.cb_serial_baudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cb_serial_baudrate.FormattingEnabled = true;
            this.cb_serial_baudrate.Items.AddRange(new object[] {
            "115200",
            "921600"});
            this.cb_serial_baudrate.Location = new System.Drawing.Point(73, 66);
            this.cb_serial_baudrate.Name = "cb_serial_baudrate";
            this.cb_serial_baudrate.Size = new System.Drawing.Size(121, 23);
            this.cb_serial_baudrate.TabIndex = 3;
            // 
            // cb_serial_port
            // 
            this.cb_serial_port.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cb_serial_port.FormattingEnabled = true;
            this.cb_serial_port.Location = new System.Drawing.Point(73, 25);
            this.cb_serial_port.Name = "cb_serial_port";
            this.cb_serial_port.Size = new System.Drawing.Size(121, 23);
            this.cb_serial_port.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "波特率：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "串口号：";
            // 
            // g_log_func
            // 
            this.g_log_func.Controls.Add(this.b_serial_send);
            this.g_log_func.Controls.Add(this.t_data_send);
            this.g_log_func.Controls.Add(this.t_data_recv);
            this.g_log_func.Controls.Add(this.b_log_clear);
            this.g_log_func.Location = new System.Drawing.Point(809, 16);
            this.g_log_func.Name = "g_log_func";
            this.g_log_func.Size = new System.Drawing.Size(541, 690);
            this.g_log_func.TabIndex = 2;
            this.g_log_func.TabStop = false;
            this.g_log_func.Text = "串口调试区";
            // 
            // b_serial_send
            // 
            this.b_serial_send.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.b_serial_send.Image = global::stm32f1_wifi.Properties.Resources.发送;
            this.b_serial_send.Location = new System.Drawing.Point(412, 614);
            this.b_serial_send.Name = "b_serial_send";
            this.b_serial_send.Size = new System.Drawing.Size(114, 67);
            this.b_serial_send.TabIndex = 3;
            this.toolTip1.SetToolTip(this.b_serial_send, "发送数据");
            this.b_serial_send.UseVisualStyleBackColor = true;
            this.b_serial_send.Click += new System.EventHandler(this.b_serial_send_Click);
            // 
            // t_data_send
            // 
            this.t_data_send.Location = new System.Drawing.Point(18, 614);
            this.t_data_send.Multiline = true;
            this.t_data_send.Name = "t_data_send";
            this.t_data_send.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.t_data_send.Size = new System.Drawing.Size(388, 66);
            this.t_data_send.TabIndex = 2;
            this.t_data_send.Text = "shop220811498.taobao.com";
            // 
            // t_data_recv
            // 
            this.t_data_recv.Location = new System.Drawing.Point(16, 23);
            this.t_data_recv.Multiline = true;
            this.t_data_recv.Name = "t_data_recv";
            this.t_data_recv.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.t_data_recv.Size = new System.Drawing.Size(510, 542);
            this.t_data_recv.TabIndex = 1;
            // 
            // b_log_clear
            // 
            this.b_log_clear.Location = new System.Drawing.Point(18, 571);
            this.b_log_clear.Name = "b_log_clear";
            this.b_log_clear.Size = new System.Drawing.Size(508, 37);
            this.b_log_clear.TabIndex = 0;
            this.b_log_clear.Text = "清空调试日志";
            this.b_log_clear.UseVisualStyleBackColor = true;
            this.b_log_clear.Click += new System.EventHandler(this.b_log_clear_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // func_opt
            // 
            this.func_opt.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.func_opt.Controls.Add(this.btcp_clear_statistics);
            this.func_opt.Enabled = false;
            this.func_opt.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.func_opt.Location = new System.Drawing.Point(12, 127);
            this.func_opt.Name = "func_opt";
            this.func_opt.Size = new System.Drawing.Size(791, 585);
            this.func_opt.TabIndex = 3;
            this.func_opt.TabStop = false;
            this.func_opt.Text = "功能区";
            // 
            // btcp_clear_statistics
            // 
            this.btcp_clear_statistics.Controls.Add(this.tabPage9);
            this.btcp_clear_statistics.Controls.Add(this.tabPage10);
            this.btcp_clear_statistics.Controls.Add(this.tabPage2);
            this.btcp_clear_statistics.Controls.Add(this.tabPage7);
            this.btcp_clear_statistics.Controls.Add(this.tabPage8);
            this.btcp_clear_statistics.Controls.Add(this.tabPage4);
            this.btcp_clear_statistics.Location = new System.Drawing.Point(7, 17);
            this.btcp_clear_statistics.Name = "btcp_clear_statistics";
            this.btcp_clear_statistics.SelectedIndex = 0;
            this.btcp_clear_statistics.Size = new System.Drawing.Size(778, 562);
            this.btcp_clear_statistics.TabIndex = 1;
            // 
            // tabPage9
            // 
            this.tabPage9.Controls.Add(this.lshow_ip);
            this.tabPage9.Controls.Add(this.label7);
            this.tabPage9.Controls.Add(this.tsta_ssid);
            this.tabPage9.Controls.Add(this.bshow_ip);
            this.tabPage9.Controls.Add(this.label6);
            this.tabPage9.Controls.Add(this.bwifi_disconnect);
            this.tabPage9.Controls.Add(this.dgwifi_scan_result);
            this.tabPage9.Controls.Add(this.bwifi_scan);
            this.tabPage9.Controls.Add(this.tsta_pwd);
            this.tabPage9.Controls.Add(this.bwifi_connect);
            this.tabPage9.Location = new System.Drawing.Point(4, 29);
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage9.Size = new System.Drawing.Size(770, 529);
            this.tabPage9.TabIndex = 8;
            this.tabPage9.Text = "STA调试区";
            this.tabPage9.UseVisualStyleBackColor = true;
            // 
            // lshow_ip
            // 
            this.lshow_ip.AutoSize = true;
            this.lshow_ip.Location = new System.Drawing.Point(12, 388);
            this.lshow_ip.Name = "lshow_ip";
            this.lshow_ip.Size = new System.Drawing.Size(52, 20);
            this.lshow_ip.TabIndex = 9;
            this.lshow_ip.Text = "IP地址";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 337);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(39, 20);
            this.label7.TabIndex = 2;
            this.label7.Text = "密码";
            // 
            // tsta_ssid
            // 
            this.tsta_ssid.Location = new System.Drawing.Point(75, 304);
            this.tsta_ssid.Name = "tsta_ssid";
            this.tsta_ssid.Size = new System.Drawing.Size(488, 27);
            this.tsta_ssid.TabIndex = 7;
            // 
            // bshow_ip
            // 
            this.bshow_ip.Image = global::stm32f1_wifi.Properties.Resources.ip;
            this.bshow_ip.Location = new System.Drawing.Point(280, 428);
            this.bshow_ip.Name = "bshow_ip";
            this.bshow_ip.Size = new System.Drawing.Size(70, 70);
            this.bshow_ip.TabIndex = 5;
            this.toolTip1.SetToolTip(this.bshow_ip, "显示IP地址");
            this.bshow_ip.UseVisualStyleBackColor = true;
            this.bshow_ip.Click += new System.EventHandler(this.bshow_ip_Click_1);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 311);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(46, 20);
            this.label6.TabIndex = 6;
            this.label6.Text = "SSID:";
            // 
            // bwifi_disconnect
            // 
            this.bwifi_disconnect.Image = global::stm32f1_wifi.Properties.Resources.断开连接;
            this.bwifi_disconnect.Location = new System.Drawing.Point(190, 428);
            this.bwifi_disconnect.Name = "bwifi_disconnect";
            this.bwifi_disconnect.Size = new System.Drawing.Size(70, 70);
            this.bwifi_disconnect.TabIndex = 5;
            this.toolTip1.SetToolTip(this.bwifi_disconnect, "断开连接");
            this.bwifi_disconnect.UseVisualStyleBackColor = true;
            this.bwifi_disconnect.Click += new System.EventHandler(this.bwifi_disconnect_Click);
            // 
            // dgwifi_scan_result
            // 
            this.dgwifi_scan_result.BackgroundColor = System.Drawing.SystemColors.ButtonHighlight;
            this.dgwifi_scan_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgwifi_scan_result.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column3,
            this.Column6,
            this.Column4});
            this.dgwifi_scan_result.Location = new System.Drawing.Point(19, 27);
            this.dgwifi_scan_result.Name = "dgwifi_scan_result";
            this.dgwifi_scan_result.RowTemplate.Height = 27;
            this.dgwifi_scan_result.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgwifi_scan_result.Size = new System.Drawing.Size(556, 262);
            this.dgwifi_scan_result.TabIndex = 4;
            this.dgwifi_scan_result.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgwifi_scan_result_CellClick);
            // 
            // Column1
            // 
            this.Column1.HeaderText = "SSID";
            this.Column1.Name = "Column1";
            // 
            // Column3
            // 
            this.Column3.HeaderText = "RSSI";
            this.Column3.Name = "Column3";
            // 
            // Column6
            // 
            this.Column6.HeaderText = "通道";
            this.Column6.Name = "Column6";
            // 
            // Column4
            // 
            this.Column4.HeaderText = "加密模式";
            this.Column4.Name = "Column4";
            // 
            // bwifi_scan
            // 
            this.bwifi_scan.Image = global::stm32f1_wifi.Properties.Resources.搜索;
            this.bwifi_scan.Location = new System.Drawing.Point(16, 428);
            this.bwifi_scan.Name = "bwifi_scan";
            this.bwifi_scan.Size = new System.Drawing.Size(70, 70);
            this.bwifi_scan.TabIndex = 0;
            this.toolTip1.SetToolTip(this.bwifi_scan, "搜索");
            this.bwifi_scan.UseVisualStyleBackColor = true;
            this.bwifi_scan.Click += new System.EventHandler(this.bwifi_scan_Click);
            // 
            // tsta_pwd
            // 
            this.tsta_pwd.Location = new System.Drawing.Point(75, 337);
            this.tsta_pwd.Name = "tsta_pwd";
            this.tsta_pwd.Size = new System.Drawing.Size(488, 27);
            this.tsta_pwd.TabIndex = 3;
            // 
            // bwifi_connect
            // 
            this.bwifi_connect.Image = global::stm32f1_wifi.Properties.Resources.连接;
            this.bwifi_connect.Location = new System.Drawing.Point(101, 428);
            this.bwifi_connect.Name = "bwifi_connect";
            this.bwifi_connect.Size = new System.Drawing.Size(70, 70);
            this.bwifi_connect.TabIndex = 1;
            this.toolTip1.SetToolTip(this.bwifi_connect, "连接");
            this.bwifi_connect.UseVisualStyleBackColor = true;
            this.bwifi_connect.Click += new System.EventHandler(this.bwifi_connect_Click);
            // 
            // tabPage10
            // 
            this.tabPage10.Controls.Add(this.dgwifi_ap_con_result);
            this.tabPage10.Controls.Add(this.label5);
            this.tabPage10.Controls.Add(this.label3);
            this.tabPage10.Controls.Add(this.cap_hidden);
            this.tabPage10.Controls.Add(this.label4);
            this.tabPage10.Controls.Add(this.rsec_wpa2);
            this.tabPage10.Controls.Add(this.tap_ssid);
            this.tabPage10.Controls.Add(this.rsec_wap);
            this.tabPage10.Controls.Add(this.tap_pwd);
            this.tabPage10.Controls.Add(this.rsec_open);
            this.tabPage10.Controls.Add(this.bwifi_disconnect_sta);
            this.tabPage10.Controls.Add(this.bwifi_start_ap);
            this.tabPage10.Controls.Add(this.bwifi_stop_ap);
            this.tabPage10.Location = new System.Drawing.Point(4, 29);
            this.tabPage10.Name = "tabPage10";
            this.tabPage10.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage10.Size = new System.Drawing.Size(770, 529);
            this.tabPage10.TabIndex = 9;
            this.tabPage10.Text = "AP调试区";
            this.tabPage10.UseVisualStyleBackColor = true;
            // 
            // dgwifi_ap_con_result
            // 
            this.dgwifi_ap_con_result.BackgroundColor = System.Drawing.SystemColors.ButtonHighlight;
            this.dgwifi_ap_con_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgwifi_ap_con_result.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column2,
            this.Column7,
            this.Column5});
            this.dgwifi_ap_con_result.Location = new System.Drawing.Point(26, 245);
            this.dgwifi_ap_con_result.Name = "dgwifi_ap_con_result";
            this.dgwifi_ap_con_result.RowTemplate.Height = 27;
            this.dgwifi_ap_con_result.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgwifi_ap_con_result.Size = new System.Drawing.Size(433, 278);
            this.dgwifi_ap_con_result.TabIndex = 14;
            this.dgwifi_ap_con_result.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgwifi_ap_con_result_CellClick);
            // 
            // Column2
            // 
            this.Column2.HeaderText = "名称";
            this.Column2.Name = "Column2";
            // 
            // Column7
            // 
            this.Column7.HeaderText = "MAC";
            this.Column7.Name = "Column7";
            // 
            // Column5
            // 
            this.Column5.HeaderText = "IP地址";
            this.Column5.Name = "Column5";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 23);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(73, 20);
            this.label5.TabIndex = 0;
            this.label5.Text = "热点名称:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 20);
            this.label3.TabIndex = 1;
            this.label3.Text = "热点密码:";
            // 
            // cap_hidden
            // 
            this.cap_hidden.AutoSize = true;
            this.cap_hidden.Location = new System.Drawing.Point(109, 94);
            this.cap_hidden.Name = "cap_hidden";
            this.cap_hidden.Size = new System.Drawing.Size(91, 24);
            this.cap_hidden.TabIndex = 10;
            this.cap_hidden.Text = "隐藏热点";
            this.cap_hidden.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(22, 95);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 20);
            this.label4.TabIndex = 2;
            this.label4.Text = "加密模式";
            // 
            // rsec_wpa2
            // 
            this.rsec_wpa2.AutoSize = true;
            this.rsec_wpa2.Location = new System.Drawing.Point(180, 131);
            this.rsec_wpa2.Name = "rsec_wpa2";
            this.rsec_wpa2.Size = new System.Drawing.Size(74, 24);
            this.rsec_wpa2.TabIndex = 9;
            this.rsec_wpa2.Text = "WAP2";
            this.rsec_wpa2.UseVisualStyleBackColor = true;
            // 
            // tap_ssid
            // 
            this.tap_ssid.Location = new System.Drawing.Point(109, 16);
            this.tap_ssid.Name = "tap_ssid";
            this.tap_ssid.Size = new System.Drawing.Size(166, 27);
            this.tap_ssid.TabIndex = 4;
            // 
            // rsec_wap
            // 
            this.rsec_wap.AutoSize = true;
            this.rsec_wap.Location = new System.Drawing.Point(109, 131);
            this.rsec_wap.Name = "rsec_wap";
            this.rsec_wap.Size = new System.Drawing.Size(65, 24);
            this.rsec_wap.TabIndex = 8;
            this.rsec_wap.Text = "WPA";
            this.rsec_wap.UseVisualStyleBackColor = true;
            // 
            // tap_pwd
            // 
            this.tap_pwd.Location = new System.Drawing.Point(109, 55);
            this.tap_pwd.Name = "tap_pwd";
            this.tap_pwd.Size = new System.Drawing.Size(166, 27);
            this.tap_pwd.TabIndex = 5;
            // 
            // rsec_open
            // 
            this.rsec_open.AutoSize = true;
            this.rsec_open.Checked = true;
            this.rsec_open.Location = new System.Drawing.Point(32, 131);
            this.rsec_open.Name = "rsec_open";
            this.rsec_open.Size = new System.Drawing.Size(71, 24);
            this.rsec_open.TabIndex = 7;
            this.rsec_open.TabStop = true;
            this.rsec_open.Text = "OPEN";
            this.rsec_open.UseVisualStyleBackColor = true;
            // 
            // bwifi_disconnect_sta
            // 
            this.bwifi_disconnect_sta.Image = global::stm32f1_wifi.Properties.Resources.断开连接;
            this.bwifi_disconnect_sta.Location = new System.Drawing.Point(196, 170);
            this.bwifi_disconnect_sta.Name = "bwifi_disconnect_sta";
            this.bwifi_disconnect_sta.Size = new System.Drawing.Size(55, 55);
            this.bwifi_disconnect_sta.TabIndex = 13;
            this.toolTip1.SetToolTip(this.bwifi_disconnect_sta, "断开STA连接");
            this.bwifi_disconnect_sta.UseVisualStyleBackColor = true;
            this.bwifi_disconnect_sta.Click += new System.EventHandler(this.bwifi_disconnect_sta_Click);
            // 
            // bwifi_start_ap
            // 
            this.bwifi_start_ap.Image = global::stm32f1_wifi.Properties.Resources.wifi热点开启;
            this.bwifi_start_ap.Location = new System.Drawing.Point(26, 170);
            this.bwifi_start_ap.Name = "bwifi_start_ap";
            this.bwifi_start_ap.Size = new System.Drawing.Size(55, 55);
            this.bwifi_start_ap.TabIndex = 11;
            this.toolTip1.SetToolTip(this.bwifi_start_ap, "开启热点");
            this.bwifi_start_ap.UseVisualStyleBackColor = true;
            this.bwifi_start_ap.Click += new System.EventHandler(this.bwifi_start_ap_Click);
            // 
            // bwifi_stop_ap
            // 
            this.bwifi_stop_ap.Image = global::stm32f1_wifi.Properties.Resources.wifi热点关闭;
            this.bwifi_stop_ap.Location = new System.Drawing.Point(109, 170);
            this.bwifi_stop_ap.Name = "bwifi_stop_ap";
            this.bwifi_stop_ap.Size = new System.Drawing.Size(55, 55);
            this.bwifi_stop_ap.TabIndex = 12;
            this.toolTip1.SetToolTip(this.bwifi_stop_ap, "关闭热点");
            this.bwifi_stop_ap.UseVisualStyleBackColor = true;
            this.bwifi_stop_ap.Click += new System.EventHandler(this.bwifi_stop_ap_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Controls.Add(this.bping_result_clear);
            this.tabPage2.Controls.Add(this.bping_stop);
            this.tabPage2.Controls.Add(this.tping_result);
            this.tabPage2.Controls.Add(this.tping_ip);
            this.tabPage2.Controls.Add(this.bping);
            this.tabPage2.Location = new System.Drawing.Point(4, 29);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(770, 529);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "PING";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 12);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 20);
            this.label10.TabIndex = 5;
            this.label10.Text = "IP地址:";
            // 
            // bping_result_clear
            // 
            this.bping_result_clear.Location = new System.Drawing.Point(138, 51);
            this.bping_result_clear.Name = "bping_result_clear";
            this.bping_result_clear.Size = new System.Drawing.Size(351, 55);
            this.bping_result_clear.TabIndex = 4;
            this.bping_result_clear.Text = "清空";
            this.toolTip1.SetToolTip(this.bping_result_clear, "清空PING结果");
            this.bping_result_clear.UseVisualStyleBackColor = true;
            this.bping_result_clear.Click += new System.EventHandler(this.bping_result_clear_Click);
            // 
            // bping_stop
            // 
            this.bping_stop.Image = global::stm32f1_wifi.Properties.Resources.ping结束;
            this.bping_stop.Location = new System.Drawing.Point(77, 51);
            this.bping_stop.Name = "bping_stop";
            this.bping_stop.Size = new System.Drawing.Size(55, 55);
            this.bping_stop.TabIndex = 3;
            this.toolTip1.SetToolTip(this.bping_stop, "停止PING");
            this.bping_stop.UseVisualStyleBackColor = true;
            this.bping_stop.Click += new System.EventHandler(this.bping_stop_Click);
            // 
            // tping_result
            // 
            this.tping_result.Location = new System.Drawing.Point(16, 123);
            this.tping_result.Multiline = true;
            this.tping_result.Name = "tping_result";
            this.tping_result.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tping_result.Size = new System.Drawing.Size(473, 385);
            this.tping_result.TabIndex = 2;
            // 
            // tping_ip
            // 
            this.tping_ip.Location = new System.Drawing.Point(74, 9);
            this.tping_ip.Name = "tping_ip";
            this.tping_ip.Size = new System.Drawing.Size(415, 27);
            this.tping_ip.TabIndex = 1;
            // 
            // bping
            // 
            this.bping.Image = global::stm32f1_wifi.Properties.Resources.ping开始;
            this.bping.Location = new System.Drawing.Point(16, 51);
            this.bping.Name = "bping";
            this.bping.Size = new System.Drawing.Size(55, 55);
            this.bping.TabIndex = 0;
            this.toolTip1.SetToolTip(this.bping, "开始PING");
            this.bping.UseVisualStyleBackColor = true;
            this.bping.Click += new System.EventHandler(this.bping_Click);
            // 
            // tabPage7
            // 
            this.tabPage7.Controls.Add(this.label22);
            this.tabPage7.Controls.Add(this.btcp_clear_send_data);
            this.tabPage7.Controls.Add(this.btcp_clear_recv_data);
            this.tabPage7.Controls.Add(this.btcp1_clear_statistics);
            this.tabPage7.Controls.Add(this.btcp_send);
            this.tabPage7.Controls.Add(this.groupBox2);
            this.tabPage7.Controls.Add(this.groupBox6);
            this.tabPage7.Controls.Add(this.ltcp_recv_count);
            this.tabPage7.Controls.Add(this.ltcp_send_count);
            this.tabPage7.Controls.Add(this.label20);
            this.tabPage7.Controls.Add(this.label21);
            this.tabPage7.Controls.Add(this.tremote_tcp_ip);
            this.tabPage7.Controls.Add(this.tremote_tcp_port);
            this.tabPage7.Controls.Add(this.label15);
            this.tabPage7.Controls.Add(this.label16);
            this.tabPage7.Controls.Add(this.tlocal_tcp_port);
            this.tabPage7.Controls.Add(this.label17);
            this.tabPage7.Controls.Add(this.btcp_disconnect);
            this.tabPage7.Controls.Add(this.btcp_connect);
            this.tabPage7.Controls.Add(this.ctcp_func);
            this.tabPage7.Location = new System.Drawing.Point(4, 29);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Size = new System.Drawing.Size(770, 529);
            this.tabPage7.TabIndex = 6;
            this.tabPage7.Text = "TCP测试";
            this.tabPage7.UseVisualStyleBackColor = true;
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(15, 23);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(73, 20);
            this.label22.TabIndex = 28;
            this.label22.Text = "协议类型:";
            // 
            // btcp_clear_send_data
            // 
            this.btcp_clear_send_data.Location = new System.Drawing.Point(657, 379);
            this.btcp_clear_send_data.Name = "btcp_clear_send_data";
            this.btcp_clear_send_data.Size = new System.Drawing.Size(85, 31);
            this.btcp_clear_send_data.TabIndex = 27;
            this.btcp_clear_send_data.Text = "清除发送";
            this.btcp_clear_send_data.UseVisualStyleBackColor = true;
            this.btcp_clear_send_data.Click += new System.EventHandler(this.btcp_clear_send_data_Click);
            // 
            // btcp_clear_recv_data
            // 
            this.btcp_clear_recv_data.Location = new System.Drawing.Point(567, 379);
            this.btcp_clear_recv_data.Name = "btcp_clear_recv_data";
            this.btcp_clear_recv_data.Size = new System.Drawing.Size(84, 31);
            this.btcp_clear_recv_data.TabIndex = 26;
            this.btcp_clear_recv_data.Text = "清除接收";
            this.btcp_clear_recv_data.UseVisualStyleBackColor = true;
            this.btcp_clear_recv_data.Click += new System.EventHandler(this.btcp_clear_recv_data_Click);
            // 
            // btcp1_clear_statistics
            // 
            this.btcp1_clear_statistics.Location = new System.Drawing.Point(567, 451);
            this.btcp1_clear_statistics.Name = "btcp1_clear_statistics";
            this.btcp1_clear_statistics.Size = new System.Drawing.Size(175, 30);
            this.btcp1_clear_statistics.TabIndex = 25;
            this.btcp1_clear_statistics.Text = "清除统计";
            this.btcp1_clear_statistics.UseVisualStyleBackColor = true;
            this.btcp1_clear_statistics.Click += new System.EventHandler(this.btcp1_clear_statistics_Click);
            // 
            // btcp_send
            // 
            this.btcp_send.Location = new System.Drawing.Point(567, 416);
            this.btcp_send.Name = "btcp_send";
            this.btcp_send.Size = new System.Drawing.Size(175, 29);
            this.btcp_send.TabIndex = 24;
            this.btcp_send.Text = "发送";
            this.btcp_send.UseVisualStyleBackColor = true;
            this.btcp_send.Click += new System.EventHandler(this.btcp_send_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ttcp_send);
            this.groupBox2.Location = new System.Drawing.Point(19, 358);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(526, 163);
            this.groupBox2.TabIndex = 23;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "发送区";
            // 
            // ttcp_send
            // 
            this.ttcp_send.Location = new System.Drawing.Point(8, 23);
            this.ttcp_send.Multiline = true;
            this.ttcp_send.Name = "ttcp_send";
            this.ttcp_send.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.ttcp_send.Size = new System.Drawing.Size(509, 134);
            this.ttcp_send.TabIndex = 0;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.ttcp_recv);
            this.groupBox6.Location = new System.Drawing.Point(19, 97);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(748, 261);
            this.groupBox6.TabIndex = 22;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "接收区";
            // 
            // ttcp_recv
            // 
            this.ttcp_recv.Location = new System.Drawing.Point(6, 26);
            this.ttcp_recv.Multiline = true;
            this.ttcp_recv.Name = "ttcp_recv";
            this.ttcp_recv.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.ttcp_recv.Size = new System.Drawing.Size(726, 229);
            this.ttcp_recv.TabIndex = 0;
            // 
            // ltcp_recv_count
            // 
            this.ltcp_recv_count.AutoSize = true;
            this.ltcp_recv_count.Location = new System.Drawing.Point(612, 493);
            this.ltcp_recv_count.Name = "ltcp_recv_count";
            this.ltcp_recv_count.Size = new System.Drawing.Size(18, 20);
            this.ltcp_recv_count.TabIndex = 21;
            this.ltcp_recv_count.Text = "0";
            // 
            // ltcp_send_count
            // 
            this.ltcp_send_count.AutoSize = true;
            this.ltcp_send_count.Location = new System.Drawing.Point(715, 493);
            this.ltcp_send_count.Name = "ltcp_send_count";
            this.ltcp_send_count.Size = new System.Drawing.Size(18, 20);
            this.ltcp_send_count.TabIndex = 20;
            this.ltcp_send_count.Text = "0";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(666, 493);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(43, 20);
            this.label20.TabIndex = 19;
            this.label20.Text = "发送:";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(563, 493);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(43, 20);
            this.label21.TabIndex = 18;
            this.label21.Text = "接收:";
            // 
            // tremote_tcp_ip
            // 
            this.tremote_tcp_ip.Location = new System.Drawing.Point(94, 64);
            this.tremote_tcp_ip.Name = "tremote_tcp_ip";
            this.tremote_tcp_ip.Size = new System.Drawing.Size(183, 27);
            this.tremote_tcp_ip.TabIndex = 15;
            // 
            // tremote_tcp_port
            // 
            this.tremote_tcp_port.Location = new System.Drawing.Point(397, 64);
            this.tremote_tcp_port.Name = "tremote_tcp_port";
            this.tremote_tcp_port.Size = new System.Drawing.Size(113, 27);
            this.tremote_tcp_port.TabIndex = 14;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(18, 68);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(56, 20);
            this.label15.TabIndex = 13;
            this.label15.Text = "目标IP:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(318, 67);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(73, 20);
            this.label16.TabIndex = 12;
            this.label16.Text = "目标端口:";
            // 
            // tlocal_tcp_port
            // 
            this.tlocal_tcp_port.Location = new System.Drawing.Point(397, 20);
            this.tlocal_tcp_port.Name = "tlocal_tcp_port";
            this.tlocal_tcp_port.Size = new System.Drawing.Size(113, 27);
            this.tlocal_tcp_port.TabIndex = 11;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(318, 23);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(73, 20);
            this.label17.TabIndex = 10;
            this.label17.Text = "本地端口:";
            // 
            // btcp_disconnect
            // 
            this.btcp_disconnect.Image = global::stm32f1_wifi.Properties.Resources.断开连接;
            this.btcp_disconnect.Location = new System.Drawing.Point(676, 20);
            this.btcp_disconnect.Name = "btcp_disconnect";
            this.btcp_disconnect.Size = new System.Drawing.Size(75, 75);
            this.btcp_disconnect.TabIndex = 9;
            this.toolTip1.SetToolTip(this.btcp_disconnect, "TCP断开");
            this.btcp_disconnect.UseVisualStyleBackColor = true;
            this.btcp_disconnect.Click += new System.EventHandler(this.btcp_disconnect_Click);
            // 
            // btcp_connect
            // 
            this.btcp_connect.Image = global::stm32f1_wifi.Properties.Resources.连接;
            this.btcp_connect.Location = new System.Drawing.Point(576, 23);
            this.btcp_connect.Name = "btcp_connect";
            this.btcp_connect.Size = new System.Drawing.Size(75, 75);
            this.btcp_connect.TabIndex = 8;
            this.toolTip1.SetToolTip(this.btcp_connect, "TCP建立");
            this.btcp_connect.UseVisualStyleBackColor = true;
            this.btcp_connect.Click += new System.EventHandler(this.btcp_connect_Click);
            // 
            // ctcp_func
            // 
            this.ctcp_func.FormattingEnabled = true;
            this.ctcp_func.Items.AddRange(new object[] {
            "TCP客户端",
            "TCP服务器"});
            this.ctcp_func.Location = new System.Drawing.Point(94, 20);
            this.ctcp_func.Name = "ctcp_func";
            this.ctcp_func.Size = new System.Drawing.Size(117, 28);
            this.ctcp_func.TabIndex = 1;
            this.ctcp_func.SelectedIndexChanged += new System.EventHandler(this.ctcp_func_SelectedIndexChanged);
            // 
            // tabPage8
            // 
            this.tabPage8.Controls.Add(this.budp_clear_send_data);
            this.tabPage8.Controls.Add(this.budp_clear_recv_data);
            this.tabPage8.Controls.Add(this.budp_clear_statistics);
            this.tabPage8.Controls.Add(this.budp_send);
            this.tabPage8.Controls.Add(this.gudp_send);
            this.tabPage8.Controls.Add(this.gudp_recv);
            this.tabPage8.Controls.Add(this.ludp_recv_count);
            this.tabPage8.Controls.Add(this.ludp_send_count);
            this.tabPage8.Controls.Add(this.label14);
            this.tabPage8.Controls.Add(this.label13);
            this.tabPage8.Controls.Add(this.tremote_udp_ip);
            this.tabPage8.Controls.Add(this.tremote_udp_port);
            this.tabPage8.Controls.Add(this.label12);
            this.tabPage8.Controls.Add(this.label11);
            this.tabPage8.Controls.Add(this.tlocal_udp_port);
            this.tabPage8.Controls.Add(this.label18);
            this.tabPage8.Controls.Add(this.budp_disconnect);
            this.tabPage8.Controls.Add(this.budp_connect);
            this.tabPage8.Location = new System.Drawing.Point(4, 29);
            this.tabPage8.Name = "tabPage8";
            this.tabPage8.Size = new System.Drawing.Size(770, 529);
            this.tabPage8.TabIndex = 7;
            this.tabPage8.Text = "UDP测试";
            this.tabPage8.UseVisualStyleBackColor = true;
            // 
            // budp_clear_send_data
            // 
            this.budp_clear_send_data.Location = new System.Drawing.Point(635, 376);
            this.budp_clear_send_data.Name = "budp_clear_send_data";
            this.budp_clear_send_data.Size = new System.Drawing.Size(98, 31);
            this.budp_clear_send_data.TabIndex = 17;
            this.budp_clear_send_data.Text = "清除发送";
            this.budp_clear_send_data.UseVisualStyleBackColor = true;
            this.budp_clear_send_data.Click += new System.EventHandler(this.budp_clear_send_data_Click);
            // 
            // budp_clear_recv_data
            // 
            this.budp_clear_recv_data.Location = new System.Drawing.Point(545, 376);
            this.budp_clear_recv_data.Name = "budp_clear_recv_data";
            this.budp_clear_recv_data.Size = new System.Drawing.Size(84, 31);
            this.budp_clear_recv_data.TabIndex = 16;
            this.budp_clear_recv_data.Text = "清除接收";
            this.budp_clear_recv_data.UseVisualStyleBackColor = true;
            this.budp_clear_recv_data.Click += new System.EventHandler(this.budp_clear_recv_data_Click);
            // 
            // budp_clear_statistics
            // 
            this.budp_clear_statistics.Location = new System.Drawing.Point(545, 448);
            this.budp_clear_statistics.Name = "budp_clear_statistics";
            this.budp_clear_statistics.Size = new System.Drawing.Size(188, 30);
            this.budp_clear_statistics.TabIndex = 15;
            this.budp_clear_statistics.Text = "清除统计";
            this.budp_clear_statistics.UseVisualStyleBackColor = true;
            this.budp_clear_statistics.Click += new System.EventHandler(this.budp_clear_statistics_Click);
            // 
            // budp_send
            // 
            this.budp_send.Location = new System.Drawing.Point(545, 413);
            this.budp_send.Name = "budp_send";
            this.budp_send.Size = new System.Drawing.Size(188, 29);
            this.budp_send.TabIndex = 14;
            this.budp_send.Text = "发送";
            this.budp_send.UseVisualStyleBackColor = true;
            this.budp_send.Click += new System.EventHandler(this.budp_send_Click);
            // 
            // gudp_send
            // 
            this.gudp_send.Controls.Add(this.tudp_send);
            this.gudp_send.Location = new System.Drawing.Point(24, 355);
            this.gudp_send.Name = "gudp_send";
            this.gudp_send.Size = new System.Drawing.Size(504, 163);
            this.gudp_send.TabIndex = 13;
            this.gudp_send.TabStop = false;
            this.gudp_send.Text = "发送区";
            // 
            // tudp_send
            // 
            this.tudp_send.Location = new System.Drawing.Point(8, 23);
            this.tudp_send.Multiline = true;
            this.tudp_send.Name = "tudp_send";
            this.tudp_send.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tudp_send.Size = new System.Drawing.Size(484, 134);
            this.tudp_send.TabIndex = 0;
            // 
            // gudp_recv
            // 
            this.gudp_recv.Controls.Add(this.tudp_recv);
            this.gudp_recv.Location = new System.Drawing.Point(24, 77);
            this.gudp_recv.Name = "gudp_recv";
            this.gudp_recv.Size = new System.Drawing.Size(743, 272);
            this.gudp_recv.TabIndex = 12;
            this.gudp_recv.TabStop = false;
            this.gudp_recv.Text = "接收区";
            // 
            // tudp_recv
            // 
            this.tudp_recv.Location = new System.Drawing.Point(6, 26);
            this.tudp_recv.Multiline = true;
            this.tudp_recv.Name = "tudp_recv";
            this.tudp_recv.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tudp_recv.Size = new System.Drawing.Size(731, 240);
            this.tudp_recv.TabIndex = 0;
            // 
            // ludp_recv_count
            // 
            this.ludp_recv_count.AutoSize = true;
            this.ludp_recv_count.Location = new System.Drawing.Point(590, 490);
            this.ludp_recv_count.Name = "ludp_recv_count";
            this.ludp_recv_count.Size = new System.Drawing.Size(18, 20);
            this.ludp_recv_count.TabIndex = 11;
            this.ludp_recv_count.Text = "0";
            // 
            // ludp_send_count
            // 
            this.ludp_send_count.AutoSize = true;
            this.ludp_send_count.Location = new System.Drawing.Point(702, 490);
            this.ludp_send_count.Name = "ludp_send_count";
            this.ludp_send_count.Size = new System.Drawing.Size(18, 20);
            this.ludp_send_count.TabIndex = 10;
            this.ludp_send_count.Text = "0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(653, 490);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(43, 20);
            this.label14.TabIndex = 9;
            this.label14.Text = "发送:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(541, 490);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(43, 20);
            this.label13.TabIndex = 8;
            this.label13.Text = "接收:";
            // 
            // tremote_udp_ip
            // 
            this.tremote_udp_ip.Location = new System.Drawing.Point(419, 30);
            this.tremote_udp_ip.Name = "tremote_udp_ip";
            this.tremote_udp_ip.Size = new System.Drawing.Size(150, 27);
            this.tremote_udp_ip.TabIndex = 7;
            // 
            // tremote_udp_port
            // 
            this.tremote_udp_port.Location = new System.Drawing.Point(262, 30);
            this.tremote_udp_port.Name = "tremote_udp_port";
            this.tremote_udp_port.Size = new System.Drawing.Size(72, 27);
            this.tremote_udp_port.TabIndex = 6;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(361, 33);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(56, 20);
            this.label12.TabIndex = 5;
            this.label12.Text = "目标IP:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(183, 33);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(73, 20);
            this.label11.TabIndex = 4;
            this.label11.Text = "目标端口:";
            // 
            // tlocal_udp_port
            // 
            this.tlocal_udp_port.Location = new System.Drawing.Point(98, 30);
            this.tlocal_udp_port.Name = "tlocal_udp_port";
            this.tlocal_udp_port.Size = new System.Drawing.Size(69, 27);
            this.tlocal_udp_port.TabIndex = 3;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(23, 33);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(73, 20);
            this.label18.TabIndex = 2;
            this.label18.Text = "本地端口:";
            // 
            // budp_disconnect
            // 
            this.budp_disconnect.Image = global::stm32f1_wifi.Properties.Resources.断开连接;
            this.budp_disconnect.Location = new System.Drawing.Point(673, 16);
            this.budp_disconnect.Name = "budp_disconnect";
            this.budp_disconnect.Size = new System.Drawing.Size(55, 55);
            this.budp_disconnect.TabIndex = 1;
            this.toolTip1.SetToolTip(this.budp_disconnect, "UDP断开");
            this.budp_disconnect.UseVisualStyleBackColor = true;
            this.budp_disconnect.Click += new System.EventHandler(this.budp_disconnect_Click);
            // 
            // budp_connect
            // 
            this.budp_connect.Image = global::stm32f1_wifi.Properties.Resources.连接;
            this.budp_connect.Location = new System.Drawing.Point(591, 16);
            this.budp_connect.Name = "budp_connect";
            this.budp_connect.Size = new System.Drawing.Size(55, 55);
            this.budp_connect.TabIndex = 0;
            this.toolTip1.SetToolTip(this.budp_connect, "UDP建立");
            this.budp_connect.UseVisualStyleBackColor = true;
            this.budp_connect.Click += new System.EventHandler(this.budp_connect_Click);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.groupBox7);
            this.tabPage4.Controls.Add(this.groupBox8);
            this.tabPage4.Controls.Add(this.tcloud_password);
            this.tabPage4.Controls.Add(this.tcloud_acount);
            this.tabPage4.Controls.Add(this.tcloud_web_address);
            this.tabPage4.Controls.Add(this.label23);
            this.tabPage4.Controls.Add(this.label19);
            this.tabPage4.Controls.Add(this.label28);
            this.tabPage4.Controls.Add(this.bwifi_cloud_mqtt_discon);
            this.tabPage4.Controls.Add(this.bwifi_cloud_mqtt_con);
            this.tabPage4.Location = new System.Drawing.Point(4, 29);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(770, 529);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Cloud";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label27);
            this.groupBox7.Controls.Add(this.tcloud_publish_data);
            this.groupBox7.Controls.Add(this.bcloud_publish);
            this.groupBox7.Controls.Add(this.tcloud_publish_topic);
            this.groupBox7.Controls.Add(this.label25);
            this.groupBox7.Location = new System.Drawing.Point(419, 144);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(348, 382);
            this.groupBox7.TabIndex = 15;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Publish";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(7, 78);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(88, 20);
            this.label27.TabIndex = 18;
            this.label27.Text = "推送的数据:";
            // 
            // tcloud_publish_data
            // 
            this.tcloud_publish_data.Location = new System.Drawing.Point(11, 109);
            this.tcloud_publish_data.Multiline = true;
            this.tcloud_publish_data.Name = "tcloud_publish_data";
            this.tcloud_publish_data.Size = new System.Drawing.Size(331, 267);
            this.tcloud_publish_data.TabIndex = 17;
            // 
            // bcloud_publish
            // 
            this.bcloud_publish.Location = new System.Drawing.Point(244, 71);
            this.bcloud_publish.Name = "bcloud_publish";
            this.bcloud_publish.Size = new System.Drawing.Size(98, 34);
            this.bcloud_publish.TabIndex = 17;
            this.bcloud_publish.Text = "推送数据";
            this.bcloud_publish.UseVisualStyleBackColor = true;
            this.bcloud_publish.Click += new System.EventHandler(this.bcloud_publish_Click);
            // 
            // tcloud_publish_topic
            // 
            this.tcloud_publish_topic.Location = new System.Drawing.Point(56, 24);
            this.tcloud_publish_topic.Multiline = true;
            this.tcloud_publish_topic.Name = "tcloud_publish_topic";
            this.tcloud_publish_topic.Size = new System.Drawing.Size(286, 34);
            this.tcloud_publish_topic.TabIndex = 18;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(7, 31);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(43, 20);
            this.label25.TabIndex = 17;
            this.label25.Text = "策略:";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.bwifi_cloud_mqtt_unsubcribe);
            this.groupBox8.Controls.Add(this.label24);
            this.groupBox8.Controls.Add(this.tcloud_subcribe_data);
            this.groupBox8.Controls.Add(this.tcloud_subcribe);
            this.groupBox8.Controls.Add(this.label26);
            this.groupBox8.Controls.Add(this.bwifi_cloud_mqtt_subcribe);
            this.groupBox8.Location = new System.Drawing.Point(16, 144);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(397, 382);
            this.groupBox8.TabIndex = 14;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Subscriptions";
            // 
            // bwifi_cloud_mqtt_unsubcribe
            // 
            this.bwifi_cloud_mqtt_unsubcribe.Location = new System.Drawing.Point(287, 71);
            this.bwifi_cloud_mqtt_unsubcribe.Name = "bwifi_cloud_mqtt_unsubcribe";
            this.bwifi_cloud_mqtt_unsubcribe.Size = new System.Drawing.Size(104, 34);
            this.bwifi_cloud_mqtt_unsubcribe.TabIndex = 16;
            this.bwifi_cloud_mqtt_unsubcribe.Text = "取消订阅";
            this.bwifi_cloud_mqtt_unsubcribe.UseVisualStyleBackColor = true;
            this.bwifi_cloud_mqtt_unsubcribe.Click += new System.EventHandler(this.bwifi_cloud_mqtt_unsubcribe_Click);
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(8, 77);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(88, 20);
            this.label24.TabIndex = 15;
            this.label24.Text = "收到的数据:";
            // 
            // tcloud_subcribe_data
            // 
            this.tcloud_subcribe_data.Location = new System.Drawing.Point(12, 109);
            this.tcloud_subcribe_data.Multiline = true;
            this.tcloud_subcribe_data.Name = "tcloud_subcribe_data";
            this.tcloud_subcribe_data.Size = new System.Drawing.Size(379, 267);
            this.tcloud_subcribe_data.TabIndex = 14;
            // 
            // tcloud_subcribe
            // 
            this.tcloud_subcribe.Location = new System.Drawing.Point(55, 30);
            this.tcloud_subcribe.Multiline = true;
            this.tcloud_subcribe.Name = "tcloud_subcribe";
            this.tcloud_subcribe.Size = new System.Drawing.Size(336, 34);
            this.tcloud_subcribe.TabIndex = 11;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(6, 37);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(43, 20);
            this.label26.TabIndex = 10;
            this.label26.Text = "策略:";
            // 
            // bwifi_cloud_mqtt_subcribe
            // 
            this.bwifi_cloud_mqtt_subcribe.Location = new System.Drawing.Point(177, 71);
            this.bwifi_cloud_mqtt_subcribe.Name = "bwifi_cloud_mqtt_subcribe";
            this.bwifi_cloud_mqtt_subcribe.Size = new System.Drawing.Size(104, 34);
            this.bwifi_cloud_mqtt_subcribe.TabIndex = 13;
            this.bwifi_cloud_mqtt_subcribe.Text = "订阅主题";
            this.bwifi_cloud_mqtt_subcribe.UseVisualStyleBackColor = true;
            this.bwifi_cloud_mqtt_subcribe.Click += new System.EventHandler(this.bwifi_cloud_mqtt_subcribe_Click);
            // 
            // tcloud_password
            // 
            this.tcloud_password.Location = new System.Drawing.Point(69, 100);
            this.tcloud_password.Name = "tcloud_password";
            this.tcloud_password.Size = new System.Drawing.Size(446, 27);
            this.tcloud_password.TabIndex = 8;
            // 
            // tcloud_acount
            // 
            this.tcloud_acount.Location = new System.Drawing.Point(69, 56);
            this.tcloud_acount.Name = "tcloud_acount";
            this.tcloud_acount.Size = new System.Drawing.Size(446, 27);
            this.tcloud_acount.TabIndex = 7;
            // 
            // tcloud_web_address
            // 
            this.tcloud_web_address.Location = new System.Drawing.Point(69, 17);
            this.tcloud_web_address.Name = "tcloud_web_address";
            this.tcloud_web_address.Size = new System.Drawing.Size(446, 27);
            this.tcloud_web_address.TabIndex = 6;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(12, 59);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(43, 20);
            this.label23.TabIndex = 4;
            this.label23.Text = "账号:";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(12, 103);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(43, 20);
            this.label19.TabIndex = 3;
            this.label19.Text = "密码:";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(12, 20);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(43, 20);
            this.label28.TabIndex = 2;
            this.label28.Text = "网址:";
            // 
            // bwifi_cloud_mqtt_discon
            // 
            this.bwifi_cloud_mqtt_discon.Image = global::stm32f1_wifi.Properties.Resources.断开连接;
            this.bwifi_cloud_mqtt_discon.Location = new System.Drawing.Point(640, 28);
            this.bwifi_cloud_mqtt_discon.Name = "bwifi_cloud_mqtt_discon";
            this.bwifi_cloud_mqtt_discon.Size = new System.Drawing.Size(75, 75);
            this.bwifi_cloud_mqtt_discon.TabIndex = 1;
            this.toolTip1.SetToolTip(this.bwifi_cloud_mqtt_discon, "断开云服务器");
            this.bwifi_cloud_mqtt_discon.UseVisualStyleBackColor = true;
            this.bwifi_cloud_mqtt_discon.Click += new System.EventHandler(this.bwifi_cloud_mqtt_discon_Click);
            // 
            // bwifi_cloud_mqtt_con
            // 
            this.bwifi_cloud_mqtt_con.Image = global::stm32f1_wifi.Properties.Resources.连接;
            this.bwifi_cloud_mqtt_con.Location = new System.Drawing.Point(542, 28);
            this.bwifi_cloud_mqtt_con.Name = "bwifi_cloud_mqtt_con";
            this.bwifi_cloud_mqtt_con.Size = new System.Drawing.Size(75, 75);
            this.bwifi_cloud_mqtt_con.TabIndex = 0;
            this.toolTip1.SetToolTip(this.bwifi_cloud_mqtt_con, "连接云服务器");
            this.bwifi_cloud_mqtt_con.UseVisualStyleBackColor = true;
            this.bwifi_cloud_mqtt_con.Click += new System.EventHandler(this.bwifi_cloud_mqtt_con_Click);
            // 
            // bwifi_stop
            // 
            this.bwifi_stop.Enabled = false;
            this.bwifi_stop.Image = global::stm32f1_wifi.Properties.Resources.wifi_off;
            this.bwifi_stop.Location = new System.Drawing.Point(718, 30);
            this.bwifi_stop.Name = "bwifi_stop";
            this.bwifi_stop.Size = new System.Drawing.Size(85, 75);
            this.bwifi_stop.TabIndex = 1;
            this.toolTip1.SetToolTip(this.bwifi_stop, "关闭Wi-Fi");
            this.bwifi_stop.UseVisualStyleBackColor = true;
            this.bwifi_stop.Click += new System.EventHandler(this.bwifi_stop_Click);
            // 
            // bwifi_start
            // 
            this.bwifi_start.Enabled = false;
            this.bwifi_start.Image = global::stm32f1_wifi.Properties.Resources.wifi_on;
            this.bwifi_start.Location = new System.Drawing.Point(614, 30);
            this.bwifi_start.Name = "bwifi_start";
            this.bwifi_start.Size = new System.Drawing.Size(85, 75);
            this.bwifi_start.TabIndex = 0;
            this.toolTip1.SetToolTip(this.bwifi_start, "开启Wi-Fi");
            this.bwifi_start.UseVisualStyleBackColor = true;
            this.bwifi_start.Click += new System.EventHandler(this.bwifi_start_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1363, 728);
            this.Controls.Add(this.func_opt);
            this.Controls.Add(this.bwifi_stop);
            this.Controls.Add(this.g_log_func);
            this.Controls.Add(this.bwifi_start);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "https://shop220811498.taobao.com | Wireless link STM32 F1 Wi-Fi test  ";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.g_log_func.ResumeLayout(false);
            this.g_log_func.PerformLayout();
            this.func_opt.ResumeLayout(false);
            this.btcp_clear_statistics.ResumeLayout(false);
            this.tabPage9.ResumeLayout(false);
            this.tabPage9.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgwifi_scan_result)).EndInit();
            this.tabPage10.ResumeLayout(false);
            this.tabPage10.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgwifi_ap_con_result)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage7.ResumeLayout(false);
            this.tabPage7.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.tabPage8.ResumeLayout(false);
            this.tabPage8.PerformLayout();
            this.gudp_send.ResumeLayout(false);
            this.gudp_send.PerformLayout();
            this.gudp_recv.ResumeLayout(false);
            this.gudp_recv.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button b_board_buy;
        private System.Windows.Forms.Button b_serial_close;
        private System.Windows.Forms.Button b_serial_open;
        private System.Windows.Forms.ComboBox cb_serial_baudrate;
        private System.Windows.Forms.ComboBox cb_serial_port;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox g_log_func;
        private System.Windows.Forms.Button b_serial_send;
        private System.Windows.Forms.TextBox t_data_send;
        private System.Windows.Forms.TextBox t_data_recv;
        private System.Windows.Forms.Button b_log_clear;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.GroupBox func_opt;
        private System.Windows.Forms.TabControl btcp_clear_statistics;
        private System.Windows.Forms.Button bwifi_stop;
        private System.Windows.Forms.Button bwifi_start;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button bping_result_clear;
        private System.Windows.Forms.Button bping_stop;
        private System.Windows.Forms.TextBox tping_result;
        private System.Windows.Forms.TextBox tping_ip;
        private System.Windows.Forms.Button bping;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Button btcp_clear_send_data;
        private System.Windows.Forms.Button btcp_clear_recv_data;
        private System.Windows.Forms.Button btcp1_clear_statistics;
        private System.Windows.Forms.Button btcp_send;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox ttcp_send;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.TextBox ttcp_recv;
        private System.Windows.Forms.Label ltcp_recv_count;
        private System.Windows.Forms.Label ltcp_send_count;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.TextBox tremote_tcp_ip;
        private System.Windows.Forms.TextBox tremote_tcp_port;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox tlocal_tcp_port;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button btcp_disconnect;
        private System.Windows.Forms.Button btcp_connect;
        private System.Windows.Forms.ComboBox ctcp_func;
        private System.Windows.Forms.TabPage tabPage8;
        private System.Windows.Forms.Button budp_clear_send_data;
        private System.Windows.Forms.Button budp_clear_recv_data;
        private System.Windows.Forms.Button budp_clear_statistics;
        private System.Windows.Forms.Button budp_send;
        private System.Windows.Forms.GroupBox gudp_send;
        private System.Windows.Forms.TextBox tudp_send;
        private System.Windows.Forms.GroupBox gudp_recv;
        private System.Windows.Forms.TextBox tudp_recv;
        private System.Windows.Forms.Label ludp_recv_count;
        private System.Windows.Forms.Label ludp_send_count;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox tremote_udp_ip;
        private System.Windows.Forms.TextBox tremote_udp_port;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tlocal_udp_port;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Button budp_disconnect;
        private System.Windows.Forms.Button budp_connect;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.TextBox tcloud_publish_data;
        private System.Windows.Forms.Button bcloud_publish;
        private System.Windows.Forms.TextBox tcloud_publish_topic;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Button bwifi_cloud_mqtt_unsubcribe;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox tcloud_subcribe_data;
        private System.Windows.Forms.TextBox tcloud_subcribe;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Button bwifi_cloud_mqtt_subcribe;
        private System.Windows.Forms.TextBox tcloud_password;
        private System.Windows.Forms.TextBox tcloud_acount;
        private System.Windows.Forms.TextBox tcloud_web_address;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Button bwifi_cloud_mqtt_discon;
        private System.Windows.Forms.Button bwifi_cloud_mqtt_con;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.TabPage tabPage10;
        private System.Windows.Forms.TextBox tsta_ssid;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button bwifi_disconnect;
        private System.Windows.Forms.DataGridView dgwifi_scan_result;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column6;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.TextBox tsta_pwd;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button bwifi_connect;
        private System.Windows.Forms.Button bwifi_scan;
        private System.Windows.Forms.DataGridView dgwifi_ap_con_result;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column7;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column5;
        private System.Windows.Forms.Button bwifi_disconnect_sta;
        private System.Windows.Forms.Button bwifi_stop_ap;
        private System.Windows.Forms.Button bwifi_start_ap;
        private System.Windows.Forms.CheckBox cap_hidden;
        private System.Windows.Forms.RadioButton rsec_wpa2;
        private System.Windows.Forms.RadioButton rsec_wap;
        private System.Windows.Forms.RadioButton rsec_open;
        private System.Windows.Forms.TextBox tap_pwd;
        private System.Windows.Forms.TextBox tap_ssid;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button bshow_ip;
        private System.Windows.Forms.Label lshow_ip;
        private System.Windows.Forms.ToolTip toolTip1;
    }
}

