#!/bin/bash
./uaputl.exe -i wfd0 bss_stop
sleep 1
iwpriv wfd0 bssrole 0
./wifidirectutl wfd0 wifidirect_mode 0
# IE clear assume index 0, 1
./uaputl.exe -i wfd0 sys_cfg_custom_ie 0 0
./uaputl.exe -i wfd0 sys_cfg_custom_ie 1 0
