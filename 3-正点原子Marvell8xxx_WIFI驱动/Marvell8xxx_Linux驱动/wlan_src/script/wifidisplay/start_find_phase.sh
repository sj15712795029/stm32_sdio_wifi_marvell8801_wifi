#!/bin/bash
# iwpriv wfd0 drvdbg 0x20037
#change the mac address
./wifidirect/update_mac.sh
echo "wfd0 Mac address updated in config/wifidirect.conf"

#ifdef STREAM_2X2
iwpriv wfd0 bssrole 1
#else
# iwpriv wfd0 bssrole 1
#endif
./uaputl.exe -i wfd0 sys_config config/uaputl_wifidirect.conf
#ifdef STREAM_2X2
iwpriv wfd0 bssrole 0
#else
# iwpriv wfd0 bssrole 0
#endif
./wifidirectutl wfd0 wifidirect_config config/wifidirect.conf
# change the passphrase
# either in uaputl_wifidirect.conf or using CLI below
#./uaputl.exe -i wfd0 sys_cfg_wpa_passphrase 1234567890
./wifidirectutl wfd0 wifidirect_mode 1
./wifidirectutl wfd0 wifidirect_params_config config/wifidirect.conf
./mlanconfig wfd0 hostcmd config/bg_scan_wifidirect.conf bgscfg
./wifidirectutl wfd0 wifidirect_mode 4

#enable wifi-display
./wifidirectutl wfd0 wifidisplay_mode 1
./wifidirectutl wfd0 wifidisplay_config config/wifidisplay.conf

