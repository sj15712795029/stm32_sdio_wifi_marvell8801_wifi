/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "marvell88w8801_core.h"
#include <string.h>
#include "lwip/dhcp.h"
#include "lwip/dhcpd.h"
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/apps/netbiosns.h"
#include "lwip/dns.h"
#include "lwip/apps/httpd.h"

#if 1 /* don't build, this is only a skeleton, see previous comment */

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "netif/ppp/pppoe.h"

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif
{
    struct eth_addr *ethaddr;
    /* Add whatever per-interface state that is needed here. */
};

/* Forward declarations. */
void  ethernetif_input(struct netif *netif);


/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void
low_level_init(struct netif *netif)
{
    //struct ethernetif *ethernetif = netif->state;

    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    printf("low_level_init MAC Addr: %02X:%02X:%02X:%02X:%02X:%02X\n", netif->hwaddr[0], netif->hwaddr[1],\
           netif->hwaddr[2], netif->hwaddr[3], netif->hwaddr[4], netif->hwaddr[5]);

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

#if LWIP_IPV6 && LWIP_IPV6_MLD
    /*
     * For hardware/netifs that implement MAC filtering.
     * All-nodes link-local is handled by default, so we must let the hardware know
     * to allow multicast packets in.
     * Should set mld_mac_filter previously. */
    if (netif->mld_mac_filter != NULL)
    {
        ip6_addr_t ip6_allnodes_ll;
        ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
        netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
    }
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

    /* Do whatever else is needed to initialize interface. */
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become available since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
    //struct ethernetif *ethernetif = netif->state;
    //struct pbuf *q;
    u8_t*buffer;

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    buffer = mrvl88w8801_get_send_data_buf();
    pbuf_copy_partial(p, buffer, p->tot_len, 0);

    //printf("low_level_output dump\n ");
    //extern void hw_hex_dump(uint8_t *data,int len);
    //hw_hex_dump(buffer,p->tot_len);

    mrvl88w8801_send_date(buffer,p->tot_len);

    MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
    if (((u8_t*)p->payload)[0] & 1)
    {
        /* broadcast or multicast packet*/
        MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
    }
    else
    {
        /* unicast packet */
        MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
    }
    /* increase ifoutdiscards or ifouterrors on error */

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.xmit);
    return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{
    //struct ethernetif *ethernetif = netif->state;
    struct pbuf *p;
    u16_t len;


    RxPD *rx_packet = (RxPD *)netif->state;
    rx_packet->payload = (u8_t *)((u8_t *)rx_packet + rx_packet->rx_pkt_offset + 4);

    /* Obtain the size of the packet and put it into the "len"
       variable. */
    len = rx_packet->rx_pkt_length;
    //printf("low_level_input dump\n ");
    //extern void hw_hex_dump(uint8_t *data,int len);
    //hw_hex_dump(rx_packet->payload,len);
#if ETH_PAD_SIZE
    len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

    /* We allocate a pbuf chain of pbufs from the pool. */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

    if (p != NULL)
    {

#if ETH_PAD_SIZE
        pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

        pbuf_take(p, rx_packet->payload, len); // 将数据帧内容复制到pbuf中


        MIB2_STATS_NETIF_ADD(netif, ifinoctets, p->tot_len);
        if (((u8_t*)p->payload)[0] & 1)
        {
            /* broadcast or multicast packet*/
            MIB2_STATS_NETIF_INC(netif, ifinnucastpkts);
        }
        else
        {
            /* unicast packet*/
            MIB2_STATS_NETIF_INC(netif, ifinucastpkts);
        }
#if ETH_PAD_SIZE
        pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

        LINK_STATS_INC(link.recv);
    }
    else
    {
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
        MIB2_STATS_NETIF_INC(netif, ifindiscards);
    }
    return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(struct netif *netif)
{
    //struct ethernetif *ethernetif;
    //struct eth_hdr *ethhdr;
    struct pbuf *p;

    //ethernetif = netif->state;

    /* move received packet into a new pbuf */
    p = low_level_input(netif);
    /* if no packet could be read, silently ignore this */
    if (p != NULL)
    {
        /* pass all packets to ethernet_input, which decides what packets it supports */
        if (netif->input(p, netif) != ERR_OK)
        {
            LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
            pbuf_free(p);
            p = NULL;
        }
    }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{

    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "IoT_lwos_Wi-Fi";
#endif /* LWIP_NETIF_HOSTNAME */

    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
    MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    return ERR_OK;
}

struct netif mrvl88w8801_lwip;
extern err_t ethernet_input(struct pbuf *p, struct netif *netif);
void ethernet_sta_driver_init(uint8_t *mac_address)
{
    struct ip4_addr ipaddr, netmask, gw;

    memcpy(mrvl88w8801_lwip.hwaddr, mac_address, MAC_ADDR_LENGTH); // 将获得的MAC地址复制到全局变量中

    printf("LWIP:STATIC IP start\n");
    IP4_ADDR(&ipaddr, 192, 168, 1, 1); // IP地址
    IP4_ADDR(&netmask, 255, 255, 255, 0); // 子网掩码
    IP4_ADDR(&gw, 192, 168, 1, 1); // 网关
    netif_add(&mrvl88w8801_lwip, &ipaddr, &netmask, &gw, NULL, ethernetif_init, ethernet_input); // 添加WiFi模块到lwip中

#if LWIP_DNS
    IP4_ADDR(&ipaddr, 8, 8, 8, 8); // 首选DNS服务器
    dns_setserver(0, &ipaddr);
    IP4_ADDR(&ipaddr, 114, 114, 114, 114); // 备用DNS服务器
    dns_setserver(1, &ipaddr);
#endif

    netif_set_default(&mrvl88w8801_lwip); // 设为默认网卡
    netif_set_up(&mrvl88w8801_lwip); // 允许lwip使用该网卡

    lwip_init();
    netbiosns_init();
    netbiosns_set_name("IoT_lwos_wifi");
    //httpd_init();
}

void ethernet_ap_driver_init(uint8_t *mac_address)
{

}

void ethernet_link_up()
{
    netif_set_link_up(&mrvl88w8801_lwip);
}

void ethernet_link_down()
{
    netif_set_link_down(&mrvl88w8801_lwip);
}

void ethernet_dhcp_start()
{
    printf("ethernet_dhcp_start\n");
#if LWIP_DHCP
    if (netif_dhcp_data(&mrvl88w8801_lwip) == NULL)
        dhcp_start(&mrvl88w8801_lwip);
#endif
}

void ethernet_dhcpd_start(hook_func_ptr hook)
{
    dhcpd_start(&mrvl88w8801_lwip,hook);
}

void ethernet_dhcpd_stop()
{
    dhcpd_stop();
}

void ethernet_lwip_process(uint8_t *rx,uint16_t rx_len)
{
    mrvl88w8801_lwip.state = (void *)rx;
    ethernetif_input(&mrvl88w8801_lwip);
}

#endif /* 0 */
