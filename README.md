# stm32f1_mrvl8801_wifi

## 平台介绍：
**stm32f103 RET6 + Marvell88w8801 SDIO Wi-Fi**
<br>MCU我们选用STM32F103RET6,ROM 512K,RAM 64K
<br>Wi-Fi模块我们选用Marvell88w8801,我们采用SDIO接口，完全手写驱动
<br>另外，我们还提供丰富的外设，SPI FLASH(W25Q128)，USB device,OLED(SSD1306),OV7670(FIFO)
<br>![STM32F103+Marvell8801板子](https://img-blog.csdn.net/20160616143012974?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center ''STM32F103板子'')
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
## 测试例程
**此开发板一共分为两个综合测试例程**
<br>1) 硬件测试例程（需要bilibili视频链接以及上位机图片）
<br>![STM32F103+Marvell8801板子](https://img-blog.csdn.net/20160616143012974?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center ''STM32F103板子'')
<br>2) Wi-Fi测试例程（需要bilibili视频链接以及上位机图片）
<br>![STM32F103+Marvell8801板子](https://img-blog.csdn.net/20160616143012974?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center ''STM32F103板子'')
## 购买链接
<br>[淘宝购买连接：https://shop220811498.taobao.com/](https://shop220811498.taobao.com/)

