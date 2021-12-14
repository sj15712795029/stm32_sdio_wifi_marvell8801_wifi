/**
 * @file
 * Dynamic Host Configuration Protocol server
 *
 * @defgroup dhcp4 DHCPv4
 * @ingroup ip4
 * DHCP (IPv4) related functions
 * This is a DHCP server for the lwIP TCP/IP stack. It aims to conform
 * with RFC 2131 and RFC 2132.
 *
 * @todo:
 * - Support for interfaces other than Ethernet (SLIP, PPP, ...)
 *
 *
 * dhcpd_start() starts a DHCP server instance which
 * configures the interface by obtaining an IP address lease and maintaining it.
 *
 * Use dhcp_stop() to remove the DHCP client.
 *
 */

/*
 * Copyright (c) 2018-2025 Zhongjun Yu <124756828@qq.com>
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
 * The Swedish Institute of Computer Science and Adam Dunkels
 * are specifically granted permission to redistribute this
 * source code.
 *
 * Author: Zhongjun Yu <124756828@qq.com>
 *
 */


#include "lwip/opt.h"

#if LWIP_IPV4 && LWIP_DHCP /* don't build if not configured for use in lwipopts.h */

#include "lwip/netif.h"
#include "lwip/def.h"
#include "lwip/dhcpd.h"
#include "lwip/dns.h"
#include "lwip/etharp.h"
#include "lwip/prot/dhcp.h"

#include <string.h>

/* TODO:
 * 1.����option database��������(���õ��Ѿ���ȫ)
 * 2.����message type�Ĵ���(��ʱֻ�ǽ�������ʹ���˼��ַ��:DISCOVER,OFFSET,REQUEST,ACK,NACK)
 	DHCP_RELEASE DHCP_DECLINE DHCP_INFORM 3�ַ���Ѿ�Ԥ����������ʱ���ò�Ӱ������ʹ��
 * 3.����release,renew,rebind�Ĵ���(DONE)
 */


struct dhcpd* pdhcpd_core;
hook_func_ptr dhcpd_hook = NULL;

static void dhcpd_recv(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
static err_t dhcpd_init(struct netif *netif);
static err_t dhcp_parse_request_list(struct dhcpd*dhcpd, struct pbuf *p);
static err_t dhcpd_opt_db_append(u8_t type,u8_t len,void *value);
static err_t dhcpd_opt_cre_db(struct netif *netif);
static err_t dhcpd_opt_clr_db(void);
static u8_t dhcpd_find_db(u8_t req_id,void *value);
static err_t dhcpd_create_msg(struct dhcpd *dhcpd, u8_t message_type);
static void dhcpd_delete_msg(struct dhcpd *dhcpd);
static err_t dhcpd_clr_map(void);
static err_t dhcpd_add_option(struct dhcpd *dhcpd,u8_t message_type,addr_map_ip_t *map);

err_t dhcpd_start(struct netif *netif,hook_func_ptr hook)
{
    dhcpd_hook = hook;
    dhcpd_init(netif);
    pdhcpd_core->dhcpd_pcb = udp_new();
    udp_bind(pdhcpd_core->dhcpd_pcb, IP4_ADDR_ANY, DHCP_SERVER_PORT);
    udp_recv(pdhcpd_core->dhcpd_pcb, dhcpd_recv, NULL);
    return ERR_OK;
}

void dhcpd_stop()
{
    if(pdhcpd_core->dhcpd_pcb != NULL)
    {
        udp_remove(pdhcpd_core->dhcpd_pcb);
        pdhcpd_core->dhcpd_pcb = NULL;
    }
    dhcpd_opt_clr_db();
    dhcpd_clr_map();
    if(pdhcpd_core)
    {
        mem_free(pdhcpd_core);
        pdhcpd_core = NULL;
    }

}


static err_t dhcp_parse_request_list(struct dhcpd*dhcpd, struct pbuf *p)
{
    u8_t *option;
    u16_t remain_len = 0;
    /* check that beginning of dhcp_msg (up to and including chaddr) is in first pbuf */
    if (p->len < DHCP_OPTIONS_OFS)
    {
        return ERR_BUF;
    }

    dhcpd->req_opt_cnt = 0;
    dhcpd->msg_in = (struct dhcp_msg *)p->payload;
    option = dhcpd->msg_in->options;

    remain_len = p->len - DHCP_OPTIONS_OFS;
    while(remain_len)
    {
        option_data_t *opt = (option_data_t *)option;
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("opt type= %"U16_F",len %"U16_F"\n", opt->type,opt->len));

        if(opt->type == DHCP_OPTION_PARAMETER_REQUEST_LIST)
        {
            dhcpd->req_opt_cnt = opt->len;
            memcpy(dhcpd->req_opt_id,&(opt->data),opt->len);

            //printf("DHCPD request list:\n");
            //hw_hex_dump(dhcpd->req_opt_id,opt->len);
        }

        if(opt->type == DHCP_OPTION_HOSTNAME)
        {
            dhcpd->has_host_name = 1;
            dhcpd->remote_host_name_len = opt->len;
            memcpy(dhcpd->remote_host_name,&(opt->data),opt->len);
        }

        if(opt->type == DHCP_OPTION_MESSAGE_TYPE)
        {
            dhcpd->msg_type = *opt->data;
        }

        if(opt->type == DHCP_OPTION_END)
        {
            break;
        }
        option += opt->len + 2;
        remain_len -= (opt->len + 2);
    }

    return ERR_OK;

}


static void dhcpd_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    struct dhcp_msg *request_msg = (struct dhcp_msg *)p->payload;

    LWIP_UNUSED_ARG(arg);

    LWIP_ASSERT("invalid server address type", IP_IS_V4(addr));

    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_recv(pbuf = %p) from DHCP client %"U16_F".%"U16_F".%"U16_F".%"U16_F" port %"U16_F"\n", (void*)p,
                ip4_addr1_16(ip_2_ip4(addr)), ip4_addr2_16(ip_2_ip4(addr)), ip4_addr3_16(ip_2_ip4(addr)), ip4_addr4_16(ip_2_ip4(addr)), port));
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("pbuf->len = %"U16_F"\n", p->len));
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("pbuf->tot_len = %"U16_F"\n", p->tot_len));
    /* prevent warnings about unused arguments */
    LWIP_UNUSED_ARG(pcb);
    LWIP_UNUSED_ARG(addr);
    LWIP_UNUSED_ARG(port);


    if (request_msg->op != DHCP_BOOTREQUEST)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("not a DHCP request message, but type %"U16_F"\n", (u16_t)request_msg->op));
        goto free_pbuf_and_return;
    }

    if (dhcp_parse_request_list(pdhcpd_core, p) != ERR_OK)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
                    ("problem unfolding DHCP message - too short on memory?\n"));
        goto free_pbuf_and_return;
    }

    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,("msg type = %"U16_F"\n",pdhcpd_core->msg_type));
    dhcpd_create_msg(pdhcpd_core,pdhcpd_core->msg_type);

    //udp_sendto(pcb,pdhcpd_core->p_out,(const ip_addr_t *)&pdhcpd_core->msg_out->yiaddr,DHCP_CLIENT_PORT);

    udp_sendto(pcb,pdhcpd_core->p_out,(const ip_addr_t *)IP_ADDR_BROADCAST,DHCP_CLIENT_PORT);
    dhcpd_delete_msg(pdhcpd_core);

free_pbuf_and_return:
    pbuf_free(p);
}


static err_t dhcpd_add_option(struct dhcpd *dhcpd,u8_t message_type,addr_map_ip_t *map)
{
    u8_t req_list_cnt = dhcpd->req_opt_cnt;
    u8_t req_id;
    u8_t index;
    option_data_t *opt_data = (option_data_t *)dhcpd->msg_out->options;
    u8_t req_value[32];
    u8_t req_value_len;
    u8_t offset = 0;

    if(message_type == DHCP_DISCOVER)
    {
        opt_data->type = DHCP_OPTION_MESSAGE_TYPE;
        opt_data->len = 1;
        *(opt_data->data) = DHCP_OFFER;
        map->status = DHCPD_W4_REQUEST;

    }
    else if(message_type == DHCP_REQUEST)
    {
        if(map->status == DHCPD_W4_REQUEST)
        {
            opt_data->type = DHCP_OPTION_MESSAGE_TYPE;
            opt_data->len = 1;
            *(opt_data->data) = DHCP_ACK;
            map->status = DHCPD_W4_DISCOVERY;

		if(dhcpd_hook != NULL)
			dhcpd_hook(map->remote_host_name,map->mac_addr,(u8_t *)ip4addr_ntoa(&(map->ip)));
        }
        else
        {
            opt_data->type = DHCP_OPTION_MESSAGE_TYPE;
            opt_data->len = 1;
            *(opt_data->data) = DHCP_NAK;
            map->status = DHCPD_W4_DISCOVERY;
        }
    }
    else if(message_type == DHCP_RELEASE)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,("dhcpd_add_option(): receive DHCP_RELEASE\n"));
    }
    else if(message_type == DHCP_DECLINE)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,("dhcpd_add_option(): receive DHCP_DECLINE\n"));
    }
    else if(message_type == DHCP_INFORM)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,("dhcpd_add_option(): receive DHCP_INFORM\n"));
        opt_data->type = DHCP_OPTION_MESSAGE_TYPE;
        opt_data->len = 1;
        *(opt_data->data) = DHCP_ACK;
    }
    else
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
                    ("dhcpd_add_option(): message type is err\n"));

        return ERR_BUF;
    }
    offset = 3*sizeof(u8_t);

    opt_data = (option_data_t *)((u8_t *)opt_data + offset);
    opt_data->type = DHCP_OPTION_T1;
    opt_data->len = sizeof(u32_t);
    *((u32_t *)opt_data->data) = PP_HTONL(dhcpd->renew_t1);
    offset = sizeof(u32_t) + 2*sizeof(u8_t);

    opt_data = (option_data_t *)((u8_t *)opt_data + offset);
    opt_data->type = DHCP_OPTION_T2;
    opt_data->len = sizeof(u32_t);
    *((u32_t *)opt_data->data) = PP_HTONL(dhcpd->rebind_t2);
    offset = sizeof(u32_t) + 2*sizeof(u8_t);

    opt_data = (option_data_t *)((u8_t *)opt_data + offset);
    opt_data->type = DHCP_OPTION_LEASE_TIME;
    opt_data->len = sizeof(u32_t);
    *((u32_t *)opt_data->data) = PP_HTONL(dhcpd->realease_time);
    offset = sizeof(u32_t) + 2*sizeof(u8_t);


    opt_data = (option_data_t *)((u8_t *)opt_data + offset);
    opt_data->type = DHCP_OPTION_SERVER_ID;
    opt_data->len = sizeof(u32_t);
    *((u32_t *)opt_data->data) = dhcpd->server.addr;
    offset = sizeof(u32_t) + 2*sizeof(u8_t);

    opt_data = (option_data_t *)((u8_t *)opt_data + offset);
    for(index = 0; index < req_list_cnt; index++)
    {
        req_id = dhcpd->req_opt_id[index];
        req_value_len = dhcpd_find_db(req_id,(void *)req_value);
        if(req_value_len != 0)
        {
            opt_data->type = req_id;
            opt_data->len = req_value_len;
            memcpy(opt_data->data,req_value,req_value_len);

            offset = 2*sizeof(u8_t) + req_value_len;
            opt_data = (option_data_t *)((u8_t *)opt_data + offset);
        }

    }

    opt_data->type = DHCP_OPTION_END;

    return ERR_OK;

}

static err_t dhcpd_create_msg(struct dhcpd *dhcpd, u8_t message_type)
{
    u32_t addr_temp;
    addr_map_ip_t *map = NULL;

    /* ������˵��64�ֽڵ�option����������������APPEND_OPT_SIZE�ֽ� */
    dhcpd->p_out = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct dhcp_msg) + APPEND_OPT_SIZE, PBUF_RAM);

    if (dhcpd->p_out == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
                    ("dhcp_create_msg(): could not allocate pbuf\n"));
        return ERR_MEM;
    }
    LWIP_ASSERT("dhcp_create_msg: check that first pbuf can hold struct dhcp_msg",
                (dhcpd->p_out->len >= sizeof(struct dhcp_msg)));

    memset(dhcpd->p_out->payload,0,dhcpd->p_out->tot_len);
    dhcpd->msg_out = (struct dhcp_msg *)dhcpd->p_out->payload;

    dhcpd->msg_out->op = DHCP_BOOTREPLY;
    /* @todo: make link layer independent */
    dhcpd->msg_out->htype = DHCP_HTYPE_ETH;
    dhcpd->msg_out->hlen = NETIF_MAX_HWADDR_LEN;
    dhcpd->msg_out->hops = 0;
    dhcpd->msg_out->xid = dhcpd->msg_in->xid;
    dhcpd->msg_out->secs = 0;
    dhcpd->msg_out->flags = dhcpd->msg_in->flags;
    ip4_addr_copy(dhcpd->msg_out->ciaddr,dhcpd->msg_in->ciaddr);

    if(dhcpd->addr_map_ip)
    {
        u8_t find_map = 0;
        addr_map_ip_t *map_temp = dhcpd->addr_map_ip;

        while(map_temp)
        {
            if(memcmp(map_temp->mac_addr,dhcpd->msg_in->chaddr,NETIF_MAX_HWADDR_LEN) == 0)
            {
                map = map_temp;
                ip4_addr_copy(dhcpd->msg_out->yiaddr,map_temp->ip);

                if(dhcpd->has_host_name == 1)
                {
                    memset(map->remote_host_name,0,sizeof(map->remote_host_name));
                    memcpy(map->remote_host_name,dhcpd->remote_host_name,dhcpd->remote_host_name_len);
                    dhcpd->has_host_name = 0;
                }
                find_map = 1;
                break;
            }
            map_temp = map_temp->next;
        }

        if(find_map == 0)
        {
            addr_map_ip_t *addr_map_ip = (addr_map_ip_t *)mem_malloc(sizeof(addr_map_ip_t));
            if (addr_map_ip == NULL)
            {
                LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_create_msg(): could not allocate addr_map_ip\n"));
                return ERR_MEM;
            }
            map = addr_map_ip;
            memcpy(addr_map_ip->mac_addr,dhcpd->msg_in->chaddr, NETIF_MAX_HWADDR_LEN);
            ip4_addr_copy(addr_map_ip->ip,dhcpd->start);
            if(dhcpd->has_host_name == 1)
            {
                memset(map->remote_host_name,0,sizeof(map->remote_host_name));
                memcpy(map->remote_host_name,dhcpd->remote_host_name,dhcpd->remote_host_name_len);
                dhcpd->has_host_name = 0;
            }
            addr_map_ip->status = DHCPD_W4_DISCOVERY;

            addr_map_ip->next = dhcpd->addr_map_ip;
            dhcpd->addr_map_ip = addr_map_ip;

            ip4_addr_copy(dhcpd->msg_out->yiaddr,dhcpd->start);
            //etharp_add_static_entry((const ip4_addr_t*)&dhcpd->msg_out->yiaddr,(struct eth_addr *)dhcpd->msg_in->chaddr);
            addr_temp = lwip_ntohl(dhcpd->start.addr);
            addr_temp += 1;
            dhcpd->start.addr = lwip_htonl(addr_temp);
            LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_create_msg(): assign IP %s, next IP %s\n",
                        ipaddr_ntoa((const ip4_addr_t*)&dhcpd->msg_out->yiaddr),
                        ipaddr_ntoa((const ip4_addr_t*)&dhcpd->start)));

        }

    }
    else
    {
        addr_map_ip_t *addr_map_ip = (addr_map_ip_t *)mem_malloc(sizeof(addr_map_ip_t));

        if (addr_map_ip == NULL)
        {
            LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_create_msg(): could not allocate addr_map_ip\n"));
            return ERR_MEM;
        }

        map = addr_map_ip;
        memcpy(addr_map_ip->mac_addr,dhcpd->msg_in->chaddr, NETIF_MAX_HWADDR_LEN);
        ip4_addr_copy(addr_map_ip->ip,dhcpd->start);
        if(dhcpd->has_host_name == 1)
        {
            memset(map->remote_host_name,0,sizeof(map->remote_host_name));
            memcpy(map->remote_host_name,dhcpd->remote_host_name,dhcpd->remote_host_name_len);
            dhcpd->has_host_name = 0;
        }
        addr_map_ip->status = DHCPD_W4_DISCOVERY;

        pdhcpd_core->addr_map_ip =  addr_map_ip;
        addr_map_ip->next = NULL;

        ip4_addr_copy(dhcpd->msg_out->yiaddr,dhcpd->start);
        //etharp_add_static_entry((const ip4_addr_t*)&dhcpd->msg_out->yiaddr,(struct eth_addr *)dhcpd->msg_in->chaddr);

        addr_temp = lwip_ntohl(dhcpd->start.addr);
        addr_temp += 1;
        dhcpd->start.addr = lwip_htonl(addr_temp);
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_create_msg(): assign IP %s, next IP %s\n",
                    ipaddr_ntoa((const ip4_addr_t*)&dhcpd->msg_out->yiaddr),
                    ipaddr_ntoa((const ip4_addr_t*)&dhcpd->start)));

    }

    ip4_addr_set_zero(&dhcpd->msg_out->siaddr);
    ip4_addr_set_zero(&dhcpd->msg_out->giaddr);

    memcpy(dhcpd->msg_out->chaddr, dhcpd->msg_in->chaddr, NETIF_MAX_HWADDR_LEN);
    memset(dhcpd->msg_out->sname,0,DHCP_SNAME_LEN);
    memset(dhcpd->msg_out->file,0,DHCP_FILE_LEN);

    dhcpd->msg_out->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);

    dhcpd_add_option(dhcpd,message_type,map);

    //printf("-----------dhcpd->msg_out--------------:\n");
    //hw_hex_dump(dhcpd->msg_out,308);
    //printf("-----------dhcpd->p_out->payload--------------:\n");
    //extern void hw_hex_dump(uint8_t *data,int len);
    //hw_hex_dump((uint8_t *)dhcpd->p_out->payload,308);
    return ERR_OK;
}


static void dhcpd_delete_msg(struct dhcpd *dhcpd)
{
    LWIP_ERROR("dhcp_delete_msg: dhcp != NULL", (dhcpd != NULL), return;);
    LWIP_ASSERT("dhcp_delete_msg: dhcp->p_out != NULL", dhcpd->p_out != NULL);
    LWIP_ASSERT("dhcp_delete_msg: dhcp->msg_out != NULL", dhcpd->msg_out != NULL);
    if (dhcpd->p_out != NULL)
    {
        pbuf_free(dhcpd->p_out);
    }
    dhcpd->p_out = NULL;
    dhcpd->msg_out = NULL;
}

static err_t dhcpd_clr_map(void)
{
    addr_map_ip_t  *map_ptr = pdhcpd_core->addr_map_ip;
    addr_map_ip_t *map_ptr_next = map_ptr->next;
    if(map_ptr)
    {
        mem_free((void*)map_ptr);
        map_ptr = map_ptr_next;
        map_ptr_next = map_ptr_next->next;
    }
    pdhcpd_core->addr_map_ip = NULL;
    return ERR_OK;
}


static err_t dhcpd_opt_db_append(u8_t type,u8_t len,void *value)
{
    option_set_t *opt_item = (option_set_t *)mem_malloc(sizeof(option_set_t) + len - sizeof(u8_t));
    if (opt_item == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcpd_opt_db_append(): could not allocate opt_item\n"));
        return ERR_MEM;
    }

    opt_item->opt.type = type;
    opt_item->opt.len = len;
    memcpy(opt_item->opt.data,value,len);

    if(pdhcpd_core->opt_hdr)
    {
        opt_item->next = pdhcpd_core->opt_hdr;
        pdhcpd_core->opt_hdr = opt_item;
    }
    else
    {
        pdhcpd_core->opt_hdr =  opt_item;
        opt_item->next = NULL;
    }

    return ERR_OK;
}

static err_t dhcpd_opt_cre_db(struct netif *netif)
{
    dhcpd_opt_db_append(DHCP_OPTION_SUBNET_MASK,4,(void*)&pdhcpd_core->submask.addr);
    dhcpd_opt_db_append(DHCP_OPTION_ROUTER,4,(void*)&pdhcpd_core->router.addr);
    dhcpd_opt_db_append(DHCP_OPTION_BROADCAST,4,(void*)&pdhcpd_core->broadcast.addr);
    dhcpd_opt_db_append(DHCP_OPTION_SERVER_ID,4,(void*)&pdhcpd_core->server.addr);
    dhcpd_opt_db_append(DHCP_OPTION_DNS_SERVER,4,(void*)dns_getserver(0));
    dhcpd_opt_db_append(DHCP_OPTION_HOSTNAME,strlen(netif->hostname),(void*)netif->hostname);
    dhcpd_opt_db_append(DHCP_OPTION_DOMAIN_NAME,strlen("xxx.IoT_lwos.com"),(void*)"xxx.IoT_lwos.com");



    return ERR_OK;
}

static err_t dhcpd_opt_clr_db(void)
{
    option_set_t *opt_ptr = pdhcpd_core->opt_hdr;
    option_set_t *opt_ptr_next = opt_ptr->next;
    if(opt_ptr)
    {
        mem_free((void*)opt_ptr);
        opt_ptr = opt_ptr_next;
        opt_ptr_next = opt_ptr_next->next;
    }
    pdhcpd_core->opt_hdr = NULL;
    return ERR_OK;
}

static u8_t dhcpd_find_db(u8_t req_id,void *value)
{
    option_set_t *temp = pdhcpd_core->opt_hdr;

    while(temp)
    {
        if(temp->opt.type == req_id)
        {
            memcpy(value,temp->opt.data,temp->opt.len);
            return (temp->opt.len);
        }
        temp = temp->next;
    }
    return 0;
}
static err_t dhcpd_init(struct netif *netif)
{
    pdhcpd_core = (struct dhcpd *)mem_malloc(sizeof(struct dhcpd));
    if (pdhcpd_core == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_start(): could not allocate dhcp\n"));
        return ERR_MEM;
    }
    memset(pdhcpd_core, 0, sizeof(struct dhcpd));

    ip4addr_aton("192.168.1.100",(ip4_addr_t *)&pdhcpd_core->start);
    ip4addr_aton("192.168.1.254",(ip4_addr_t *)&pdhcpd_core->end);
    ip4addr_aton("192.168.1.1",(ip4_addr_t *)&pdhcpd_core->server);
    ip4addr_aton("192.168.1.1",(ip4_addr_t *)&pdhcpd_core->router);
    ip4addr_aton("255.255.255.0",(ip4_addr_t *)&pdhcpd_core->submask);
    ip4addr_aton("192.168.1.255",(ip4_addr_t *)&pdhcpd_core->broadcast);

    /* realease time is T, renew time is T1, rebind timer is T2,In general T1 = T/2 ,T2 = 7*T/8 */
    pdhcpd_core->realease_time = REALEASE_TIME;
    pdhcpd_core->renew_t1 = REALEASE_TIME/2;
    pdhcpd_core->rebind_t2 = REALEASE_TIME/8*7;


    pdhcpd_core->addr_map_ip = NULL;
    pdhcpd_core->opt_hdr = NULL;
    dhcpd_opt_cre_db(netif);
    return ERR_OK;
}

#endif /* LWIP_IPV4 && LWIP_DHCP */


