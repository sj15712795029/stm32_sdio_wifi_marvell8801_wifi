/******************************************************************************
  * @file    fs_wrapper.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-12-11
  * @brief   file system source file
******************************************************************************/

#include "fs_wrapper.h"

FATFS file_system;
BYTE file_system_work[FF_MAX_SS];

uint8_t file_system_init(void)
{
	FRESULT result;
        result = f_mount(&file_system, "", 1);
        COMP_DEBUG("file_system_init mount result %d\n",result);
        if(result == FR_NO_FILESYSTEM)
        {
            result=f_mkfs("",FM_ANY,0,file_system_work,sizeof(file_system_work));
            COMP_DEBUG("file_system_init make file system result %d\n",result);
        }
	if(result == FR_OK)
	{
		return COMP_ERR_OK;
	}
	else
	{
		return COMP_ERR_FS_INIT;
	}
        
}
