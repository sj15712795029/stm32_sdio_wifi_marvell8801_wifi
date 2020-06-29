#!/bin/bash
iwpriv wfd0 drvdbg 0x20037
# change the mac address
ifconfig mlan0 hw ether 00:50:43:21:0e:08
ifconfig wfd0 hw ether 00:50:43:21:0e:08
ifconfig uap0 hw ether 00:50:43:21:0e:08

iwpriv wfd0 deepsleep 0
iwconfig wfd0 power off

iwpriv wfd0 bssrole 1
./uaputl.exe -i wfd0 sys_config config/uaputl_wifidirect.conf
iwpriv wfd0 bssrole 0
./wifidirectutl wfd0 wifidirect_config config/wifidirect.conf
./uaputl.exe -i wfd0 sys_cfg_protocol 32
./uaputl.exe -i wfd0 sys_cfg_cipher 8 8
./uaputl.exe -i wfd0 sys_cfg_wpa_passphrase 1234567890
./wifidirectutl wfd0 wifidirect_mode 1
