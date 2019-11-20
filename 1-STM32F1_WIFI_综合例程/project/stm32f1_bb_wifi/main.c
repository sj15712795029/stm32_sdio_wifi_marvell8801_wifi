#include "board_wrapper.h"
#include "wifi_app.h"
#include "cJSON.h"

uint32_t sys_time = 0;
#define CONF_BSP_TICKS_PER_SEC 100

uint32_t sys_now(void)
{
    return sys_time;
}

void SysTick_Handler(void)
{
    sys_time += 1000/CONF_BSP_TICKS_PER_SEC;
}
static int8_t  nibble_for_char(uint8_t c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

#define OLED_SHOW_SIZE 32
uint8_t func_show[OLED_SHOW_SIZE];
uint8_t operate_show[OLED_SHOW_SIZE];
uint8_t status_show[OLED_SHOW_SIZE];
uint8_t key1_show[OLED_SHOW_SIZE];
uint8_t key2_show[OLED_SHOW_SIZE];
uint8_t key3_show[OLED_SHOW_SIZE];

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

static uint8_t wifi_init_status = 1;/* 0 -> success */
void wifi_init_result(uint8_t status)
{
    wifi_init_status = status;
    uart_send_json("WIFI","WIFI_ON",status==0?(uint8_t*)"SUCCESS":(uint8_t*)"FAIL",0,0,0,0,0);

}
void wifi_scan_result(uint8_t *ssid,uint8_t rssi,uint8_t channel,uint8_t *encryption_mode)
{
    uint8_t rssi_str[8] = {0};
    uint8_t channel_str[8] = {0};
    hw_sprintf((char*)rssi_str,"%d",rssi);
    hw_sprintf((char*)channel_str,"%d",channel);
    uart_send_json("WIFI","WIFI_SCAN","SUCCESS",ssid,rssi_str,channel_str,encryption_mode,0);
}

void wifi_connect_result(uint8_t status)
{
    uart_send_json("WIFI","WIFI_CONNECT",status==0?(uint8_t*)"SUCCESS":(uint8_t*)"FAIL",0,0,0,0,0);
}



void wifi_start_ap_result(uint8_t status)
{
    uart_send_json("WIFI","WIFI_START_AP",status==0?(uint8_t*)"SUCCESS":(uint8_t*)"FAIL",0,0,0,0,0);
}


void wifi_ap_connect_result(uint8_t *name,uint8_t *mac,uint8_t *ip)
{
    uint8_t mac_str[20] = {0};
    sprintf((char*)mac_str,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    HW_DEBUG("wifi_ap_connect_result\n");
    HW_DEBUG("name %s\n",name);
    HW_DEBUG("mac %s\n",mac_str);
    HW_DEBUG("ip %s\n",ip);

    uart_send_json("WIFI","WIFI_AP_CON_IND","SUCCESS",name,mac_str,ip,0,0);

}

void wifi_ap_disconnect_result(uint8_t *mac)
{
    uint8_t mac_str[20] = {0};

    HW_DEBUG("wifi_ap_disconnect_result\n");
    HW_DEBUG("mac %s\n",mac_str);
    sprintf((char*)mac_str,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    uart_send_json("WIFI","WIFI_AP_DISCON_RET","SUCCESS",mac_str,0,0,0,0);
}


static wifi_cb_t wifi_cb =
{
    wifi_init_result,
    wifi_scan_result,
    wifi_connect_result,
    wifi_start_ap_result,
    wifi_ap_connect_result,
    wifi_ap_disconnect_result,
};

void wifi_ping_runing_hook(ip_addr_t *addr,uint32_t time)
{
    uint8_t time_str[8] = {0};
    hw_sprintf((char*)time_str,"%d",time);
    uart_send_json("WIFI","WIFI_PING","SUCCESS",(uint8_t *)ipaddr_ntoa(addr),time_str,0,0,0);
}


void wifi_ping_stop_hook(uint16_t send_count,uint16_t recv_count)
{
    uint8_t send_str[8] = {0};
    uint8_t recv_str[8] = {0};
    hw_sprintf((char*)send_str,"%d",send_count);
    hw_sprintf((char*)recv_str,"%d",recv_count);
    uart_send_json("WIFI","WIFI_STOP_PING","SUCCESS",send_str,recv_str,0,0,0);

}


struct udp_pcb *udp_active_pcb= NULL;
uint16_t udp_local_port = 0;
uint16_t udp_remote_port = 0;
ip_addr_t udp_remote_ipaddr;
uint8_t app_udp_recv_buffer[1600] = {0};
void app_udp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    if (p != NULL)
    {
        uint8_t udp_recv_str[8] = {0};
        hw_sprintf((char*)udp_recv_str,"%d",p->tot_len);
        HW_DEBUG("app_udp_recv len %d\n",p->tot_len);
        memset(app_udp_recv_buffer,0,sizeof(app_udp_recv_buffer));
        pbuf_copy_partial(p, app_udp_recv_buffer, p->tot_len, 0);

        uart_send_json("WIFI","WIFI_UDP_RECV","SUCCESS",app_udp_recv_buffer,udp_recv_str,0,0,0);
        pbuf_free(p);
    }
}



ip_addr_t tcp_server_ip;
uint16_t tcp_remote_server_port = 0;
struct tcp_pcb *tcp_client_active_pcb = NULL;

uint8_t app_tcp_client_recv_buffer[1600] = {0};
err_t app_tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p != NULL)
    {
        uint8_t tcpc_recv_str[8] = {0};
        hw_sprintf((char*)tcpc_recv_str,"%d",p->tot_len);
        HW_DEBUG("app_tcp_client_recv len %d\n",p->tot_len);
        hw_memset(app_tcp_client_recv_buffer,0,sizeof(app_tcp_client_recv_buffer));
        pbuf_copy_partial(p, app_tcp_client_recv_buffer, p->tot_len, 0);

        uart_send_json("WIFI","WIFI_TCPC_RECV","SUCCESS",app_tcp_client_recv_buffer,tcpc_recv_str,0,0,0);

        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
    }
    else
    {
        err = tcp_close(tpcb);
        HW_DEBUG("Connection is closed! err=%d\n", err);
    }
    return ERR_OK;
}

err_t app_tcp_client_connect(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    HW_DEBUG("connected %d\n",err);
    tcp_recv(tpcb, app_tcp_client_recv);

    return ERR_OK;
}



#define TCP_CLIENT_COUNT 8
typedef struct
{
    struct tcp_pcb *tcp_client_pcb;
    ip_addr_t tcp_client_ip;
} tcp_server_client_t;
tcp_server_client_t tcp_client[TCP_CLIENT_COUNT];

uint16_t tcp_local_server_port = 0;
struct tcp_pcb *tcp_server_active_pcb = NULL;
uint8_t app_tcp_server_recv_buffer[1600] = {0};
err_t app_tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p != NULL)
    {
        uint8_t remote_port_str[8] = {0};
        uint8_t tcps_recv_str[8] = {0};
        hw_sprintf((char*)tcps_recv_str,"%d",p->tot_len);
        hw_sprintf((char*)remote_port_str,"%d",tpcb->remote_port);
        HW_DEBUG("TCP tester received %d bytes from %s:%d!\n", p->tot_len, ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);

        hw_memset(app_tcp_server_recv_buffer,0,sizeof(app_tcp_server_recv_buffer));
        pbuf_copy_partial(p, app_tcp_server_recv_buffer, p->tot_len, 0);

        uart_send_json("WIFI","WIFI_TCPS_RECV","SUCCESS",(uint8_t *)ipaddr_ntoa(&tpcb->remote_ip),remote_port_str,app_tcp_server_recv_buffer,tcps_recv_str,0);

        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
    }
    else
    {
        uint8_t index = 0;
        HW_DEBUG("TCP tester client %s:%d closed!\n", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
        for(index = 0; index < TCP_CLIENT_COUNT; index++)
        {
            if(ip4_addr_cmp(&tpcb->remote_ip,&(tcp_client[index].tcp_client_ip)))
            {
                hw_memset(&(tcp_client[index]),0,sizeof(tcp_server_client_t));
                break;
            }
        }
        tcp_close(tpcb);
    }
    return ERR_OK;
}
err_t app_tcp_server_sent(void *arg, struct tcp_pcb *tpcb,u16_t len)
{
    printf("TCP tester client %s:%d send %d byte success!\n", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port,len);

    return ERR_OK;
}

static err_t app_tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    uint8_t index = 0;
    printf("TCP tester accepted %s:%d!\n", ipaddr_ntoa(&newpcb->remote_ip), newpcb->remote_port);
    tcp_recv(newpcb, app_tcp_server_recv);
    tcp_sent(newpcb, app_tcp_server_sent);

    for(index = 0; index < TCP_CLIENT_COUNT; index++)
    {
        if(tcp_client[index].tcp_client_ip.addr == 0)
        {
            ip4_addr_copy(tcp_client[index].tcp_client_ip,newpcb->remote_ip);
            tcp_client[index].tcp_client_pcb = newpcb;
            break;
        }
    }

    return ERR_OK;
}



mqtt_client_t *app_mqtt_client;
uint8_t mqtt_web_address[64] = {0};
uint8_t mqtt_account[32] = {0};
uint8_t mqtt_password[32] = {0};
uint8_t mqtt_subcribe_topic[32] = {0};
uint8_t mqtt_subcribe_data[64] = {0};

static void app_mqtt_sub_request_cb(void *arg, err_t result)
{
    /* Just print the result code here for simplicity,
    normal behaviour would be to take some action if subscribe fails like
    notifying user, retry subscribe or disconnect from server */
    printf("Subscribe result: %d\n", result);
}

static void app_mqtt_unsub_request_cb(void *arg, err_t result)
{
    printf("Subscribe result: %d\n", result);
}

static void app_mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    printf("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);
    /* Decode topic string into a user defined reference */

}

static void app_mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    uint8_t index;
    uint8_t len_str[8] = {0};
    hw_sprintf((char*)len_str,"%d",len);

    printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);



    for(index = 0; index < len; index++)
    {
        printf("%c",data[index]);
    }
    printf("\n");

    memset(mqtt_subcribe_data,0,sizeof(mqtt_subcribe_data));
    memcpy(mqtt_subcribe_data,data,len);


    uart_send_json("WIFI","WIFI_MQTT_SUBCRIBE_RECV","SUCCESS",mqtt_subcribe_data,len_str,0,0,0);


    if(flags & MQTT_DATA_FLAG_LAST)
    {
        printf("MQTT_DATA_FLAG_LAST\n");
    }
    else
    {
        printf("~MQTT_DATA_FLAG_LAST\n");
    }
}


static void app_mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if(status == MQTT_CONNECT_ACCEPTED)
    {
        printf("mqtt_connection_cb: Successfully connected\n");
        /* Setup callback for incoming publish requests */
        mqtt_set_inpub_callback(client, app_mqtt_incoming_publish_cb, app_mqtt_incoming_data_cb, arg);

    }
    else
    {
        printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);
    }
}


static void app_mqtt_server_find(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    if (ipaddr != NULL)
    {
        err_t err;
        struct mqtt_connect_client_info_t client_info = {    "mqtt_id",  NULL, NULL,    10,    NULL, NULL, 0, 0  };
        client_info.client_user = 	(const char*)mqtt_account;
        client_info.client_pass = (const char*)mqtt_password;

        printf("DNS Found IP: %s\n", ip4addr_ntoa(ipaddr));
        err = mqtt_client_connect(app_mqtt_client, ipaddr, MQTT_PORT, app_mqtt_connection_cb, 0, &client_info);
        /* For now just print the result code if something goes wrong */
        if(err != ERR_OK)
        {
            printf("mqtt_connect return %d\n", err);
        }
    }
    else
        printf("DNS Not Found IP!\n");
}

void app_find_mqtt_ip()
{
    ip_addr_t dnsip;
    err_t err = dns_gethostbyname((const char*)mqtt_web_address, &dnsip, app_mqtt_server_find, NULL);
    if (err == ERR_OK)
    {
        printf("In cache! IP: %s\n", ip4addr_ntoa(&dnsip));
    }
    else if (err == ERR_INPROGRESS)
    {
        printf("Not in cache!\n");
    }
    else
    {
        printf("dns_gethostbyname failed! err=%d\n", err);
    }
}

void app_mqtt_connect_server()
{
    app_mqtt_client = mqtt_client_new();


    if(app_mqtt_client != NULL)
    {
        app_find_mqtt_ip();

    }
}


void app_mqtt_disconnect_server()
{
    if(app_mqtt_client != NULL)
    {
        mqtt_disconnect(app_mqtt_client);
        app_mqtt_client = NULL;

    }
}

void app_mqtt_subcribe()
{
    if(app_mqtt_client != NULL)
    {
        err_t err = mqtt_subscribe(app_mqtt_client, (const char*)mqtt_subcribe_topic, 1, app_mqtt_sub_request_cb, NULL);
        if(err != ERR_OK)
        {
            printf("mqtt_subscribe return: %d\n", err);
        }

    }
}

void app_mqtt_unsubcribe()
{
    if(app_mqtt_client != NULL)
    {
        err_t err = mqtt_unsubscribe(app_mqtt_client,(const char*)mqtt_subcribe_topic,app_mqtt_unsub_request_cb,NULL);
        if(err != ERR_OK)
        {
            printf("mqtt_subscribe return: %d\n", err);
        }
    }
}

static void app_mqtt_publish_request_cb(void *arg, err_t result)
{
    printf("publish result: %d\n", result);
}

void app_mqtt_publish(uint8_t *topic,uint8_t *data,uint16_t data_len)
{
    if(app_mqtt_client != NULL)
    {
        err_t err = mqtt_publish(app_mqtt_client,(const char*)topic,data,data_len,1,0,app_mqtt_publish_request_cb,NULL);
        if(err != ERR_OK)
        {
            printf("app_mqtt_publish return: %d\n", err);
        }
    }
}


ip_addr_t ping_ipaddr;
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

    if(strcmp((const char *)func_value,"WIFI") == 0)
    {
        if(hw_strcmp((const char *)operate_value,"WIFI_ON") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_ON\n");
            wifi_start(&wifi_cb);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_OFF") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_OFF\n");
            wifi_stop();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_SCAN") == 0)
        {
            uint8_t index = 0;
            scan_condition_t scan_condition;

            HW_DEBUG("UART PARSE DEBUG:operate WIFI_SCAN\n");

            hw_memset(&scan_condition,0,sizeof(scan_condition));
            for(index = 0; index < 14; index++)
            {
                scan_condition.channel[index] = index+1;
            }
            scan_condition.channel_num = 14;
            scan_condition.scan_max_time = 200;

            wifi_start_scan(&scan_condition);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_CONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_CONNECT\n");
            wifi_connect_ap(para1,strlen((const char*)para1),para2,strlen((const char*)para2));
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_DISCONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_DISCONNECT\n");
            wifi_disconnect_ap();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_SHOW_IP") == 0)
        {
            static uint8_t ip[30] = {0};
            static uint8_t mask[30] = {0};
            static uint8_t gateway[30] = {0};

            HW_DEBUG("UART PARSE DEBUG:operate WIFI_SHOW_IP\n");

            /* WIFI DISCONNECT */
            app_udp_dhcp_show_ip(ip,mask,gateway);
            HW_DEBUG("ip %s,mask %s,gateway %s\n",ip,mask,gateway);

            uart_send_json(func_value,operate_value,"SUCCESS",(uint8_t *)ip,(uint8_t *)mask,(uint8_t *)gateway,0,0);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_START_AP") == 0)
        {
            ap_info_t ap_info;
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_START_AP\n");

            hw_memset(&ap_info,0,sizeof(ap_info_t));
            hw_memcpy(ap_info.ssid,para1,hw_strlen((const char*)para1));
            ap_info.ssid_len= hw_strlen((const char*)para1);

            if(hw_strcmp((const char*)para3,"OPEN") == 0)
                ap_info.security = WIFI_SECURITY_NONE;
            else if(hw_strcmp((const char*)para3,"WPA") == 0)
            {
                hw_memcpy(ap_info.pwd,para2,hw_strlen((const char*)para2));
                ap_info.pwd_len= hw_strlen((const char*)para2);
                ap_info.security = WIFI_SECURITY_WPA;
            }
            else if(hw_strcmp((const char*)para3,"WPA2") == 0)
            {
                hw_memcpy(ap_info.pwd,para2,hw_strlen((const char*)para2));
                ap_info.pwd_len= hw_strlen((const char*)para2);
                ap_info.security = WIFI_SECURITY_WPA2;
            }

            if(hw_strcmp((const char*)para4,"HIDDEN") == 0)
                ap_info.broadcast_ssid = 0;
            else
                ap_info.broadcast_ssid = 1;

            wifi_start_ap(&ap_info);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_STOP_AP") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_STOP_AP\n");
            wifi_stop_ap();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_DISCONNECT_STA") == 0)
        {
            uint8_t index = 0;
            uint8_t mac_address[6] = {0};
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_DISCONNECT_STA\n");

            for(index = 0; index < 6; index++)
                mac_address[index] = (nibble_for_char(*(para1+index*3)) << 4) | nibble_for_char(*(para1+index*3 + 1));
            wifi_disconnect_sta(mac_address);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_PING") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_PING\n");
            ip4addr_aton((const char *)para1,&ping_ipaddr);
            ping_init(&ping_ipaddr,wifi_ping_runing_hook);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_STOP_PING") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_STOP_PING\n");
            ping_deinit(wifi_ping_stop_hook);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_UDP_CONNECT") == 0)
        {
            udp_local_port = atoi((const char*)para2);
            udp_remote_port = atoi((const char*)para3);

            HW_DEBUG("UART PARSE DEBUG:operate WIFI_UDP_CONNECT\n");

            ip4addr_aton((const char *)para1,&udp_remote_ipaddr);
            udp_active_pcb = udp_new();
            udp_bind(udp_active_pcb, IP4_ADDR_ANY, udp_local_port);
            udp_recv(udp_active_pcb, app_udp_recv, NULL);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;
        }

        if(hw_strcmp((const char *)operate_value,"WIFI_UDP_DISCONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_UDP_DISCONNECT\n");
            if(udp_active_pcb)
            {
                udp_remove(udp_active_pcb);
                udp_active_pcb = NULL;
            }
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_UDP_SEND") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_UDP_SEND\n");
            if(udp_active_pcb)
            {
                uint16_t send_len = atoi((const char*)para2);
                struct pbuf *send;
                send = pbuf_alloc(PBUF_TRANSPORT, send_len, PBUF_ROM);
                if (send != NULL)
                {
                    HW_DEBUG("Sending UDP packets...\n");
                    send->payload = para1;
                    udp_sendto(udp_active_pcb, send, &udp_remote_ipaddr, udp_remote_port);
                    pbuf_free(send);
                }
            }
            else
                HW_DEBUG("no activer udp pcb\n");
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_TCPC_CONNECT") == 0)
        {
            err_t err;
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPC_CONNECT\n");

            tcp_remote_server_port = atoi((const char*)para3);

            tcp_client_active_pcb = tcp_new();

            ip4addr_aton((const char*)para1,&tcp_server_ip);
            err = tcp_connect(tcp_client_active_pcb, &tcp_server_ip, tcp_remote_server_port, app_tcp_client_connect);
            if (err != ERR_OK)
            {
                HW_DEBUG("Connection failed! err=%d\n", err);
                tcp_close(tcp_client_active_pcb);
            }
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_TCPC_DISCONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPC_DISCONNECT\n");
            if(tcp_client_active_pcb)
            {
                tcp_close(tcp_client_active_pcb);
                tcp_client_active_pcb = NULL;
            }
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }
        if(hw_strcmp((const char *)operate_value,"WIFI_TCPC_SEND") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPC_SEND\n");
            if(tcp_client_active_pcb)
            {
                uint16_t send_len = atoi((const char*)para2);

                HW_DEBUG("Sending TCP client packets...\n");
                tcp_write(tcp_client_active_pcb, para1, send_len,1);
            }
            else
                HW_DEBUG("no activer tcp client pcb\n");
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_TCPS_CONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPS_CONNECT\n");
            hw_memset(tcp_client,0,sizeof(tcp_server_client_t)*TCP_CLIENT_COUNT);
            tcp_server_active_pcb = tcp_new();
            tcp_local_server_port = atoi((const char*)para2);
            HW_DEBUG("tcp server port %d\n",tcp_local_server_port);
            tcp_bind(tcp_server_active_pcb, IP4_ADDR_ANY, tcp_local_server_port);
            tcp_server_active_pcb = tcp_listen(tcp_server_active_pcb);
            tcp_accept(tcp_server_active_pcb, app_tcp_server_accept);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_TCPS_DISCONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPS_DISCONNECT\n");
            if(tcp_server_active_pcb)
            {
                hw_memset(tcp_client,0,sizeof(tcp_server_client_t)*TCP_CLIENT_COUNT);
                tcp_close(tcp_server_active_pcb);
                tcp_server_active_pcb = NULL;
            }
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }


        if(hw_strcmp((const char *)operate_value,"WIFI_TCPS_SEND") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_TCPS_SEND\n");
            uint8_t index = 0;
            uint16_t send_len = atoi((const char*)para4);
            ip_addr_t tcp_temp_client_ip;
            ip4addr_aton((const char*)para1,&tcp_temp_client_ip);
            for(index = 0; index < TCP_CLIENT_COUNT; index++)
            {
                if(ip4_addr_cmp(&tcp_temp_client_ip,&(tcp_client[index].tcp_client_ip)))
                {
                    HW_DEBUG("tcp server write to client ip %s,port %d\n",(const char*)ipaddr_ntoa(&(tcp_client[index].tcp_client_pcb->remote_ip)),(tcp_client[index].tcp_client_pcb->remote_port));
                    tcp_write(tcp_client[index].tcp_client_pcb, para3, send_len,1);
                    break;
                }
            }
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_MQTT_CONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_MQTT_CONNECT\n");
            memset(mqtt_web_address,0,64);
            memset(mqtt_account,0,32);
            memset(mqtt_password,0,32);

            memcpy(mqtt_web_address,para1,strlen((const char*)para1));
            memcpy(mqtt_account,para2,strlen((const char*)para2));
            memcpy(mqtt_password,para3,strlen((const char*)para3));
            app_mqtt_connect_server();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_MQTT_DISCONNECT") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_MQTT_DISCONNECT\n");
            app_mqtt_disconnect_server();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_MQTT_SUBCRIBE") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_MQTT_SUBCRIBE\n");
            memset(mqtt_subcribe_topic,0,32);
            memcpy(mqtt_subcribe_topic,para1,strlen((const char*)para1));
            app_mqtt_subcribe();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_MQTT_UNSUBCRIBE") == 0)
        {
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_MQTT_UNSUBCRIBE\n");
            app_mqtt_unsubcribe();
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }

        if(hw_strcmp((const char *)operate_value,"WIFI_MQTT_PUBLISH") == 0)
        {
            uint16_t data_len = atoi((const char*)para3);
            HW_DEBUG("UART PARSE DEBUG:operate WIFI_MQTT_PUBLISH\n");

            app_mqtt_publish(para1,para2,data_len);
            operate_stauts_oled_show(func_value,operate_value,"SUCCESS",0,0,0,0,0,0);
            goto exit;

        }
    }

    if(hw_strcmp((const char *)shell_string,"shop220811498.taobao.com") == 0)
        HW_DEBUG("welcome to use our stm32f1 camera wifi board\n");
    else
        HW_DEBUG("UART PARSE ERR:HW_ERR_SHELL_NO_CMD\n");

    result = HW_ERR_SHELL_NO_CMD;
exit:
    cJSON_Delete(parse_json);
    return result;
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
