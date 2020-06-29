#include "board_wrapper.h"
#include "fs_wrapper.h"
#include "cJSON.h"

#define OLED_SHOW_SIZE 32
uint8_t func_show[OLED_SHOW_SIZE];
uint8_t operate_show[OLED_SHOW_SIZE];
uint8_t status_show[OLED_SHOW_SIZE];
uint8_t key1_show[OLED_SHOW_SIZE];
uint8_t key2_show[OLED_SHOW_SIZE];
uint8_t key3_show[OLED_SHOW_SIZE];

uint8_t sht20_update = 0;

void operate_stauts_oled_show(uint8_t *func,uint8_t *operate,uint8_t *status,uint8_t *key1,uint8_t *value1,uint8_t *key2,uint8_t *value2,uint8_t * key3,uint8_t *value3)
{
    hw_memset(func_show,0,OLED_SHOW_SIZE);
    hw_memset(operate_show,0,OLED_SHOW_SIZE);
    hw_memset(status_show,0,OLED_SHOW_SIZE);
    hw_memset(key1_show,0,OLED_SHOW_SIZE);
    hw_memset(key2_show,0,OLED_SHOW_SIZE);
    hw_memset(key3_show,0,OLED_SHOW_SIZE);

    hw_sprintf((char*)func_show,"FUC:%s",func);
    hw_sprintf((char*)operate_show,"OPERATE:%s",operate);
    hw_sprintf((char*)status_show,"STATUS:%s",status);

    hw_oled_clear();
    hw_oled_show_string(0,0,func_show,8);
    hw_oled_show_string(0,1,operate_show,8);
    hw_oled_show_string(0,2,status_show,8);

    if(key1 && value1)
    {
        hw_sprintf((char*)key1_show,"%s:%s",key1,value1);
        hw_oled_show_string(0,3,key1_show,8);
    }

    if(key2 && value2)
    {
        hw_sprintf((char*)key2_show,"%s:%s",key2,value2);
        hw_oled_show_string(0,4,key2_show,8);
    }

    if(key3 && value3)
    {
        hw_sprintf((char*)key3_show,"%s:%s",key3,value3);
        hw_oled_show_string(0,4,key3_show,8);
    }
}

uint8_t scan_path[512] = {0};
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK)
    {
        for (;;)
        {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR)                      /* It is a directory */
            {
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            }
            else                                           /* It is a file. */
            {
                printf("%s/%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}




uint8_t uart_send_json(uint8_t *func,uint8_t *operate,uint8_t *status,uint8_t *para1,uint8_t *para2,uint8_t *para3,uint8_t *para4,uint8_t *para5)
{
    uint8_t *wifi_status_string;
    cJSON *wifi_json_status = cJSON_CreateObject();

    cJSON_AddStringToObject(wifi_json_status, "FUNC", (const char*)func);
    cJSON_AddStringToObject(wifi_json_status, "OPERATE", (const char*)operate);
    cJSON_AddStringToObject(wifi_json_status, "STATUS", (const char*)status);

    if(para1)
        cJSON_AddStringToObject(wifi_json_status, "PARAM1", (const char*)para1);
    if(para2)
        cJSON_AddStringToObject(wifi_json_status, "PARAM2", (const char*)para2);
    if(para3)
        cJSON_AddStringToObject(wifi_json_status, "PARAM3", (const char*)para3);
    if(para4)
        cJSON_AddStringToObject(wifi_json_status, "PARAM4", (const char*)para4);
    if(para5)
        cJSON_AddStringToObject(wifi_json_status, "PARAM5", (const char*)para5);
    wifi_status_string = (uint8_t *)cJSON_Print(wifi_json_status);

    HW_DEBUG("%s\n",wifi_status_string);
    cJSON_Delete(wifi_json_status);
    free(wifi_status_string);

    return 0;
}

uint8_t get_wav_buffer[512] = {0};
uint8_t wav_music_name[64] = {0};
FRESULT get_wav_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK)
    {
        for (;;)
        {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR)                      /* It is a directory */
            {
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = get_wav_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            }
            else                                           /* It is a file. */
            {
                hw_memset(wav_music_name,0,sizeof(wav_music_name));
                hw_sprintf((char*)wav_music_name,"%s/%s",path,fno.fname);
                if(hw_strstr((const char*)wav_music_name,".wav") || hw_strstr((const char*)wav_music_name,".WAV"))
                {
                    printf("music name:%s\n",wav_music_name);
                }
            }

        }
        f_closedir(&dir);
    }

    return res;
}

uint8_t uart_receive_parse(uint8_t *shell_string)
{
    uint8_t result = HW_ERR_OK;

    cJSON* parse_json = cJSON_Parse((const char *)shell_string);
    uint8_t* func_value = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"FUNC"))->valuestring;
    uint8_t* operate_value = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"OPERATE"))->valuestring;
    uint8_t* para1 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM1"))->valuestring;
    uint8_t* para2 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM2"))->valuestring;
    uint8_t* para3 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM3"))->valuestring;
    uint8_t* para4 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM4"))->valuestring;
    uint8_t* para5 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM5"))->valuestring;
    uint8_t* para6 = (uint8_t*)((cJSON *)cJSON_GetObjectItem(parse_json,"PARAM6"))->valuestring;


    if(hw_strcmp((const char *)func_value,"HW") == 0)
    {
        if(hw_strcmp((const char *)operate_value,"LED_ON") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate LED_ON\n");
            LED1_ON;
            LED2_ON;
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"LED_OFF") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate LED_OFF\n");
            LED1_OFF;
            LED2_OFF;
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_SHOW") == 0)
        {
            uint8_t col,page,format,string_len;
            uint8_t show_string[32] = {0};

            HW_DEBUG("UART PARSE DEBUG:operate OLED_SHOW\n");
            col = atoi((const char*)para1);
            page = atoi((const char*)para2);
            format = atoi((const char*)para3);
            string_len = atoi((const char*)para4);
            hw_memcpy(show_string,(const char*)para5,string_len);
            hw_oled_show_string(col,page,show_string,format == 0?8:16);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_CLEAR") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_CLEAR\n");
            hw_oled_clear();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_CONTRAST") == 0)
        {
            uint8_t contrast_value;

            HW_DEBUG("UART PARSE DEBUG:operate OLED_CONTRAST\n");
            contrast_value = atoi((const char*)para1);

            hw_oled_set_contrast(contrast_value);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_ENTRY_RAM") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_ENTRY_RAM\n");
            hw_oled_entry_display_with_ram();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_ENTRY_NORAM") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_ENTRY_NORAM\n");
            hw_oled_entry_display_without_ram();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_NORMAL_DISPLAY") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_NORMAL_DISPLAY\n");
            hw_oled_set_normal_display();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_INVERSE_DISPLAY") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_INVERSE_DISPLAY\n");
            hw_oled_set_inverse_display();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_H_SCROLL_SET") == 0)
        {
            uint8_t start_page,stop_page,dir,interval;

            HW_DEBUG("UART PARSE DEBUG:operate OLED_H_SCROLL_SET\n");
            start_page = atoi((const char*)para1);
            stop_page = atoi((const char*)para2);
            dir = atoi((const char*)para3);
            interval = atoi((const char*)para4);

            hw_oled_set_horizontal_scroll(dir,start_page,stop_page,interval);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_V_SCROLL_SET") == 0)
        {
            uint8_t start_page,stop_page,dir,interval,offset;

            HW_DEBUG("UART PARSE DEBUG:operate OLED_V_SCROLL_SET\n");
            start_page = atoi((const char*)para1);
            stop_page = atoi((const char*)para2);
            dir = atoi((const char*)para3);
            interval = atoi((const char*)para4);
            offset = atoi((const char*)para5);

            hw_oled_set_vertical_scroll(dir,start_page,stop_page,interval,offset);
            goto exit;
        }


        if(hw_strcmp((const char *)operate_value,"OLED_SCROLL_START") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_SCROLL_START\n");
            hw_oled_scroll_active();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"OLED_SCROLL_STOP") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate OLED_SCROLL_START\n");
            hw_oled_scroll_deactive();
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FLASH_SIZE") == 0)
        {
            uint8_t flash_size_buf[16] = {0};
            HW_DEBUG("UART PARSE DEBUG:operate FLASH_SIZE\n");
            uint32_t flash_size = hw_spi_flash_get_size();
            hw_sprintf((char*)flash_size_buf,"%d",flash_size);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS","SIZE",flash_size_buf,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FLASH_ID") == 0)
        {
            uint8_t manuf_id,device_id;
            uint8_t flash_manufid_buf[16] = {0};
            uint8_t flash_deviceid_buf[16] = {0};
            HW_DEBUG("UART PARSE DEBUG:operate FLASH_ID\n");

            hw_spi_flash_read_manu_dev_id(&manuf_id,&device_id);
            hw_sprintf((char*)flash_manufid_buf,"0x%02x",manuf_id);
            hw_sprintf((char*)flash_deviceid_buf,"0x%02x",device_id);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS","MANUF_ID",flash_manufid_buf,"DEVICE_ID",flash_deviceid_buf,0,0);

            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FLASH_ERASE_S") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate FLASH_ERASE_S\n");
            hw_oled_clear();
            hw_spi_flash_erase_chip();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);

            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FS_WRITE") == 0)
        {
            FIL file;
            FRESULT fr;
            UINT writed_len = 0;
            HW_DEBUG("UART PARSE DEBUG:operate FS_WRITE\n");

            /* Opens an existing file. If not exist, creates a new file. */
            fr = f_open(&file, (const TCHAR*)para1, FA_WRITE | FA_OPEN_ALWAYS);
            if (fr == FR_OK)
            {
                HW_DEBUG("open %s success\n",para1);
                f_write(&file,para2,hw_strlen((char*)para2),&writed_len);
                HW_DEBUG("write len %d\n",writed_len);
                f_close(&file);
                operate_stauts_oled_show(func_value,operate_value,"SUCCESS","NAME",para1,"TEXT",para2,0,0);

                goto exit;
            }
            operate_stauts_oled_show(func_value,operate_value,"FAIL",0,0,0,0,0,0);

            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FS_READ") == 0)
        {
            FIL file;
            FRESULT fr;
            uint8_t buffer[32] = {0};
            UINT read_len = 0;
            HW_DEBUG("UART PARSE DEBUG:operate FS_READ\n");

            /* Opens an existing file. If not exist, creates a new file. */
            fr = f_open(&file, (const TCHAR*)para1, FA_READ);
            if (fr == FR_OK)
            {
                HW_DEBUG("open success\n");
                f_read(&file,buffer,sizeof(buffer),&read_len);
                HW_DEBUG("read len %d\n",read_len);
                f_close(&file);
                operate_stauts_oled_show(func_value,operate_value,"SUCCESS","NAME",para1,"TEXT",buffer,0,0);

                goto exit;
            }

            operate_stauts_oled_show(func_value,operate_value,"FAIL",0,0,0,0,0,0);

            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"FS_DIR_R") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate FS_DIR_R\n");

            scan_files((char*)scan_path);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);


            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"SHT20_START_UPDATE") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate SHT20_START_UPDATE\n");
            sht20_update = 1;
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);

            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"SHT20_STOP_UPDATE") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate SHT20_STOP_UPDATE\n");
            sht20_update = 0;
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"SPI_WAV_UPDATE") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate SPI_WAV_UPDATE\n");
            get_wav_files((char*)get_wav_buffer);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"SPI_WAV_PLAY") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate SPI_WAV_PLAY\n");
            hw_wm8960_play_wav(para1);

            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"SPI_WAV_STOP") == 0)
        {

            HW_DEBUG("UART PARSE DEBUG:operate SPI_WAV_STOP\n");
            wm8960_stop_play();

            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }


        result = HW_ERR_SHELL_NO_CMD;
    }

    if(hw_strcmp((const char *)shell_string,"shop220811498.taobao.com") == 0)
        HW_DEBUG("welcome to use our stm32f1 camera wifi board\n");
    else
        HW_DEBUG("UART PARSE ERR:HW_ERR_SHELL_NO_CMD %s\n",shell_string);

    result = HW_ERR_SHELL_NO_CMD;
exit:
    cJSON_Delete(parse_json);
    return result;
}


uint8_t humi_buffer[16] = {0};
uint8_t temp_buffer[16] = {0};
int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    hw_uart_debug_init(921600);
    hw_led_init();
    hw_button_init();
    hw_oled_init();
    hw_sht2x_init();
    hw_wm8960_init();
    hw_spi_flash_init();
    hw_usb_init();
    file_system_init();

    printf("hardware test runing...\n");

    while(1)
    {
        if(sht20_update == 1)
        {

            hw_memset(humi_buffer,0,sizeof(humi_buffer));
            hw_memset(temp_buffer,0,sizeof(temp_buffer));
            hw_sprintf((char*)humi_buffer,"%.2f",hw_sht2x_get_humi_poll());
            hw_sprintf((char*)temp_buffer,"%.2f",hw_sht2x_get_temp_poll());
            printf("humi_buffer:%s\n",humi_buffer);
            printf("temp_buffer:%s\n",temp_buffer);
            hw_oled_show_string(0,0,humi_buffer,8);
            hw_oled_show_string(0,1,temp_buffer,8);
            uart_send_json("HW","SHT20_UPDATE","SUCCESS",humi_buffer,temp_buffer,0,0,0);
        }
        hw_delay_ms(500);
    }
}
