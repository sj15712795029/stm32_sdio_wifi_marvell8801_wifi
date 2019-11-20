#ifndef LWIP_TEST_H_H_H
#define LWIP_TEST_H_H_H

#include "lwip/opt.h"

#if LWIP_DNS
void udp_dns_test(const char *name);
#endif
#if LWIP_DHCP
void udp_dhcp_show_ip(u8_t *ip,u8_t *mask,u8_t *gateway);
#endif
void udp_echo_test(void);
void udp_speed_test(void);

void tcp_client_test(char *ipaddr_c,uint16_t port);
void tcp_server_test(uint16_t port);
void tcp_user_https_test(void);
void tcp_http_server_test(void);
void tcp_http_client_test(void);
void mqtt_connect_server(void);

#endif
