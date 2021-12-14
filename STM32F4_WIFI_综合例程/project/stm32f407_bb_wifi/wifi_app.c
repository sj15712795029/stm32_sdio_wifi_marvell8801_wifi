#include "wifi_app.h"

uint8_t wifi_start(wifi_cb_t *cb)
{
    hw_sdio_init();
    mrvl88w8801_init(cb);
    return WIFI_ERR_OK;
}

uint8_t wifi_stop()
{
    hw_chip_reset();
    mrvl88w8801_deinit();
    return WIFI_ERR_OK;
}

uint8_t wifi_start_scan(scan_condition_t *scan_condition)
{
    if(scan_condition->ssid_len)
    {
        mrvl88w8801_scan_ssid(scan_condition->ssid,scan_condition->ssid_len,scan_condition->scan_max_time);
    }
    else
    {
        mrvl88w8801_scan(scan_condition->channel,scan_condition->channel_num,scan_condition->scan_max_time);
    }
    return WIFI_ERR_OK;
}

uint8_t wifi_connect_ap(uint8_t *ssid,uint8_t ssid_len,uint8_t *pwd,uint8_t pwd_len)
{
    mrvl88w8801_connect(ssid,ssid_len,pwd,pwd_len);
    return WIFI_ERR_OK;
}

uint8_t wifi_disconnect_ap()
{
    mrvl88w8801_disconnect();
    return WIFI_ERR_OK;
}

uint8_t wifi_start_ap(ap_info_t *ap_info)
{
    mrvl88w8801_cre_ap(ap_info->ssid,ap_info->ssid_len,ap_info->pwd,ap_info->pwd_len,ap_info->security,ap_info->broadcast_ssid);
    return WIFI_ERR_OK;
}

uint8_t wifi_stop_ap(void)
{
    mrvl88w8801_stop_ap();
    return WIFI_ERR_OK;
}

uint8_t wifi_disconnect_sta(uint8_t *mac_address)
{
    mrvl88w8801_disconnect_sta(mac_address);
    return WIFI_ERR_OK;
}

extern struct netif mrvl88w8801_lwip;
void app_udp_dhcp_show_ip(uint8_t *ip,uint8_t *mask,uint8_t *gateway)
{
    struct dhcp *dhcp;

    if (dhcp_supplied_address(&mrvl88w8801_lwip))
    {
        dhcp = netif_dhcp_data(&mrvl88w8801_lwip);
        printf("DHCP supplied address!\n");
        printf("IP address: %s\n", ip4addr_ntoa(&dhcp->offered_ip_addr));
        printf("Subnet mask: %s\n", ip4addr_ntoa(&dhcp->offered_sn_mask));
        printf("Default gateway: %s\n", ip4addr_ntoa(&dhcp->offered_gw_addr));
        memcpy(ip,ip4addr_ntoa(&dhcp->offered_ip_addr),strlen(ip4addr_ntoa(&dhcp->offered_ip_addr)));
        memcpy(mask,ip4addr_ntoa(&dhcp->offered_sn_mask),strlen(ip4addr_ntoa(&dhcp->offered_sn_mask)));
        memcpy(gateway,ip4addr_ntoa(&dhcp->offered_gw_addr),strlen(ip4addr_ntoa(&dhcp->offered_gw_addr)));
#if LWIP_DNS
        printf("DNS Server: %s\n", ip4addr_ntoa(dns_getserver(0)));
#endif
    }
}

