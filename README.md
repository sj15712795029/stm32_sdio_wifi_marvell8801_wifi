# stm32f1_mrvl8801_wifi

## 平台介绍：
**目前我们的STM32F103 RET6分为V1/V2**
<br>MCU我们选用STM32F103RET6,ROM 512K,RAM 64K
<br>Wi-Fi模块我们选用Marvell88w8801,我们采用SDIO接口，完全手写驱动

**一.stm32f103 RET6 + Marvell88w8801 SDIO Wi-Fi V2开发板**
<BR>1）开发板功能图示
<br>[![](https://img-blog.csdnimg.cn/20200627174833624.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1hpYW9YaWFvUGVuZ0Jv,size_16,color_FFFFFF,t_70)](https://shop220811498.taobao.com)
<br>1）TYPE C串口调试接口
<br>2）TYPE C USB Devic，可把spi flash模拟U盘使用
<br>3）复位按键
<br>4）电源按键
<br>5）SWD下载器
<br>6）用户按键
<br>7）ADC接口
<br>8）喇叭左右声道接口
<br>9）WM8960 codec ic
<br>10）耳机接口
<br>11）Line-in接口
<br>12）蓝牙接口
<br>13）OLED接口
<br>14）SDIO Wi-Fi接口，兼容正点原子Linux开发板
<br>15）ESP8266接口，兼容正点原子接口
**二.stm32f103 RET6 + Marvell88w8801 SDIO Wi-Fi V1开发板**
<BR>1）开发板功能图示
<br>[![](https://img-blog.csdnimg.cn/20200627174817882.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1hpYW9YaWFvUGVuZ0Jv,size_16,color_FFFFFF,t_70)](https://shop220811498.taobao.com)
<br>1）BOOT切换跳帽，都接GND是MCU从默认flash启动，也就是0x0800 0000
<br>2）摄像头接口，此接口我们接我们的OV7670摄像头
<br>3）存储芯片，此存储芯片型号为W25Q128，方便用户存储数据
<br>4）LED指示灯，此指示灯在user通过GPIO来控制
<br>5）OLED显示屏，型号为SSD1306,128*64像素
<br>6）WIFI模组，通过插针的方式与MCU通过SDIO交互，型号为Marvell8801]
<br>7）晶振，8M的HSE给MCU提供
<br>8）MCU控制芯片，型号为STM32F103RET6，ROM为512K，RAM为64K
<br>9）SWD下载器，通过我们的ST LINK下载器下载程序
<br>10）电源开关，为6旋自锁开关
<br>11）电源芯片,AMS1117
<br>12）电源指示灯
<br>13）USB设备接口，这个接口是测试USB device的
<br>14）串口芯片，USB转串口
<br>15）USB调试接口，此接口是USB debug
<br>16）复位按键，复位MCU
## 视频说明
[**开发板资料，视频，使用视频说明（点击我，哔哩哔哩视频）**](https://www.bilibili.com/video/BV12t4y1974Q?from=search&seid=11200186700468330596)
## 购买链接
<br>[**淘宝V2购买连接：点击购买Marvell8801 V2开发板**](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w4004-22329603896.26.5aeb41f9sVPcfc&id=623552067826)
<br>[**淘宝V1购买连接：点击购买Marvell8801 V1开发板**](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w4004-22329603896.6.5aeb41f9sVPcfc&id=609729761614)
## 资料预看，购买后可全部查看
<br>[开发手册下载](https://pan.baidu.com/s/1dcE5XYLJh0Z2T6Z5P6z4fQ)