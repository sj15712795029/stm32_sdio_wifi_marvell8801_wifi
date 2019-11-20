#ifndef LWIPOPTS_H_H_H
#define LWIPOPTS_H_H_H

/** 配置无操作系统 */
#define NO_SYS 1
#define LWIP_NETCONN 0
#define LWIP_SOCKET 0
#define LWIP_STATS 0

/* 4字节对齐 */
#define MEM_ALIGNMENT 4
/* 不进行临界值保护 */
#define SYS_LIGHTWEIGHT_PROT 0

/* 开启DHCP */
#define LWIP_DHCP 1
#define LWIP_NETIF_HOSTNAME 1
/* 开启DNS */
#define LWIP_DNS 1
#define LWIP_RAND() ((u32_t)rand())

#define MEM_SIZE	8*1024

#define LWIP_DEBUG


/* Add 5 num sys timer */
#define MEMP_NUM_SYS_TIMEOUT            (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + (PPP_SUPPORT*6*MEMP_NUM_PPP_PCB) + (LWIP_IPV6 ? (1 + LWIP_IPV6_REASS + LWIP_IPV6_MLD) : 0)+5)


#define LWIP_RAW                        1

#define PBUF_POOL_SIZE 8
#if 0
#define U8_F "c"
#define S8_F "c"
#define X8_F "x"
#define U16_F "u"
#define S16_F "d"
#define X16_F "x"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"
#define LWIP_DEBUG


#define DNS_DEBUG LWIP_DBG_ON
#define AUTOIP_DEBUG LWIP_DBG_ON
#define DHCP_DEBUG LWIP_DBG_ON
#define SLIP_DEBUG LWIP_DBG_ON
#define TCPIP_DEBUG LWIP_DBG_ON
#define UDP_DEBUG LWIP_DBG_ON
#define TCP_QLEN_DEBUG LWIP_DBG_ON
#define TCP_RST_DEBUG LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG LWIP_DBG_ON
#define TCP_WND_DEBUG LWIP_DBG_ON
#define TCP_CWND_DEBUG LWIP_DBG_ON
#define TCP_RTO_DEBUG LWIP_DBG_ON
#define TCP_FR_DEBUG LWIP_DBG_ON
#define TCP_INPUT_DEBUG LWIP_DBG_ON
#define TCP_DEBUG LWIP_DBG_ON
#define IP_DEBUG LWIP_DBG_ON
#define INET_DEBUG LWIP_DBG_ON
#define IGMP_DEBUG LWIP_DBG_ON
#define ICMP_DEBUG LWIP_DBG_ON
#define NETIF_DEBUG LWIP_DBG_ON
#define ETHARP_DEBUG LWIP_DBG_ON
#define MQTT_DEBUG LWIP_DBG_ON
#endif

#endif
