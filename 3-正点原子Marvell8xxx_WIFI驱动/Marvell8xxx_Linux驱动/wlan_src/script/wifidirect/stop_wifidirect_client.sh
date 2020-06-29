#!/bin/bash
# deauth the GO first
./wifidirectutl wfd0 wifidirect_mode 0
# IE clear assume index 0, 1
./uaputl.exe -i wfd0 sys_cfg_custom_ie 0 0
./uaputl.exe -i wfd0 sys_cfg_custom_ie 1 0
