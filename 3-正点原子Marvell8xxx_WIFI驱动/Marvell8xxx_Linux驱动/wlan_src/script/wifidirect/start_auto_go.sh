#!/bin/bash
# iwpriv mlan0 drvdbg 0x20037
# change the mac address
./wifidirect/update_mac.sh
echo "wfd0 Mac address updated in config/wifidirect.conf"


./wifidirectutl wfd0 wifidirect_config config/wifidirect.conf
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
# iwpriv wfd0 bssrole 1
# change the group owner parameters
# either in uaputl_wifidirect.conf or using CLI below
#./uaputl.exe -i wfd0 sys_cfg_wpa_passphrase 1234567890
#./uaputl.exe -i wfd0 sys_cfg_eapol_gwk_hsk 2000 3
#./uaputl.exe -i wfd0 sys_cfg_eapol_pwk_hsk 2000 3
# iwpriv wfd0 bssrole 0
./wifidirectutl wfd0 wifidirect_mode 1
iwpriv wfd0 bssrole 1
./wifidirectutl wfd0 wifidirect_mode 2
./uaputl.exe -i wfd0 bss_start
