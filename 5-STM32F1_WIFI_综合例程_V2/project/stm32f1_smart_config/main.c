#include "board_wrapper.h"
#include "wifi_app.h"
#include "cJSON.h"

uint32_t sys_time = 0;
extern uint8_t wifi_config_ssid[32];
extern uint8_t wifi_config_pwd[32];
extern uint8_t wifi_config;
#define CONF_BSP_TICKS_PER_SEC 100

uint32_t sys_now(void)
{
    return sys_time;
}

void SysTick_Handler(void)
{
    sys_time += 1000/CONF_BSP_TICKS_PER_SEC;
}


#define AP_SSID "SMART_CONFIG"
#define AP_PWD "12345678"
static uint8_t wifi_init_status = 1;/* 0 -> success */
void wifi_init_result(uint8_t status)
{
    ap_info_t ap_info;
    wifi_init_status = status;
    HW_DEBUG("wifi_init_result %d\n",status);

    hw_memset(&ap_info,0,sizeof(ap_info_t));
    hw_memcpy(ap_info.ssid,AP_SSID,hw_strlen((const char*)AP_SSID));
    ap_info.ssid_len= hw_strlen((const char*)AP_SSID);


    hw_memcpy(ap_info.pwd,AP_PWD,hw_strlen((const char*)AP_PWD));
    ap_info.pwd_len= hw_strlen((const char*)AP_PWD);
    ap_info.security = WIFI_SECURITY_WPA2;

    ap_info.broadcast_ssid = 1;

    wifi_start_ap(&ap_info);


}


void wifi_scan_result(uint8_t *ssid,uint8_t rssi,uint8_t channel,uint8_t *encryption_mode)
{

}

void wifi_connect_result(uint8_t status)
{

}



void wifi_start_ap_result(uint8_t status)
{
    HW_DEBUG("wifi_start_ap_result %d\n",status);
}

void wifi_stop_ap_result(uint8_t status)
{
    HW_DEBUG("wifi_stop_ap_result %d\n",status);
    mrvl88w8801_connect(wifi_config_ssid,strlen((const char*)wifi_config_ssid),wifi_config_pwd,strlen((const char*)wifi_config_pwd));
}


void wifi_ap_connect_result(uint8_t *name,uint8_t *mac,uint8_t *ip)
{
    uint8_t mac_str[20] = {0};
    sprintf((char*)mac_str,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    HW_DEBUG("wifi_ap_connect_result\n");
    HW_DEBUG("name %s\n",name);
    HW_DEBUG("mac %s\n",mac_str);
    HW_DEBUG("ip %s\n",ip);


}

void wifi_ap_disconnect_result(uint8_t *mac)
{
    uint8_t mac_str[20] = {0};

    HW_DEBUG("wifi_ap_disconnect_result\n");
    HW_DEBUG("mac %s\n",mac_str);
    if(wifi_config == 1)
    {
        mrvl88w8801_stop_ap();

        wifi_config = 0;
    }
}


static wifi_cb_t wifi_cb =
{
    wifi_init_result,
    wifi_scan_result,
    wifi_connect_result,
    wifi_start_ap_result,
    wifi_stop_ap_result,
    wifi_ap_connect_result,
    wifi_ap_disconnect_result,
};


uint8_t uart_receive_parse(uint8_t *shell_string)
{

    return HW_ERR_OK;
}


extern void sys_check_timeouts(void);
int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    hw_uart_debug_init(921600);
    hw_led_init();
    hw_oled_init();
    hw_systick_init(SystemCoreClock/CONF_BSP_TICKS_PER_SEC);
    HW_DEBUG("stm32f1 mrvl8801 testing...\n");

    wifi_start(&wifi_cb);
    while(1)
    {
        if(SDIO_GetITStatus(SDIO_IT_SDIOIT) == SET)
        {
            SDIO_ClearITPendingBit(SDIO_IT_SDIOIT);
            mrvl88w8801_process_packet();
        }


        if(!wifi_init_status)
            sys_check_timeouts();
    }
}
