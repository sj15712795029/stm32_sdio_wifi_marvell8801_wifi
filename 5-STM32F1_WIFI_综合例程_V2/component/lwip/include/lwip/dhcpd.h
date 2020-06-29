/**
 * @file
 * DHCP server API
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
 *
 * Author: Zhongjun Yu <124756828@qq.com>
 *
 */
#ifndef LWIP_HDR_DHCPD_H
#define LWIP_HDR_DHCPD_H

#include "lwip/opt.h"

#if LWIP_DHCP /* don't build if not configured for use in lwipopts.h */

#include "lwip/netif.h"
#include "lwip/udp.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_OPTION_SIZE 32
#define APPEND_OPT_SIZE 32

/* realease time 5 days */
#define REALEASE_TIME (5*24*60*60)

#define DHCP_OPTION_DOMAIN_NAME 15

typedef enum
{
    DHCPD_W4_DISCOVERY,
    DHCPD_W4_REQUEST,
} dhcpd_status_e;


PACK_STRUCT_BEGIN
typedef struct
{
    u8_t type;
    u8_t len;
    u8_t data[1];
} option_data_t;
PACK_STRUCT_END

typedef struct _option_set_t
{
    struct _option_set_t *next;
    option_data_t opt;
} option_set_t;

typedef struct _addr_map_ip_t
{
    struct _addr_map_ip_t *next;
    u8_t mac_addr[NETIF_MAX_HWADDR_LEN];
    u8_t remote_host_name[MAX_OPTION_SIZE];
    ip_addr_t ip;
    u8_t status;
} addr_map_ip_t;

struct dhcpd
{
    struct udp_pcb *dhcpd_pcb;
    ip4_addr_p_t server;		/* Our IP, in network order */
    ip4_addr_p_t start;		/* Start address of leases, network order */
    ip4_addr_p_t end;			/* End of leases, network order */
    ip4_addr_p_t submask;
    ip4_addr_p_t router;
    ip4_addr_p_t broadcast;

    u32_t renew_t1;
    u32_t rebind_t2;
    u32_t realease_time;

    u8_t has_host_name;
    u8_t remote_host_name_len;
    u8_t remote_host_name[MAX_OPTION_SIZE];

    addr_map_ip_t *addr_map_ip;
    option_set_t *opt_hdr;	/* List of DHCP options loaded from the config file */

    u8_t msg_type;
    u8_t req_opt_cnt;
    u8_t req_opt_id[MAX_OPTION_SIZE];

    struct pbuf *p_out; /* pbuf of outcoming msg */
    struct dhcp_msg *msg_out; /* outgoing msg */
    /** incoming msg */
    struct dhcp_msg *msg_in;

};


typedef void (* hook_func_ptr)(u8_t *name,u8_t *mac,u8_t *ip);
err_t dhcpd_start(struct netif *netif,hook_func_ptr hook);
void dhcpd_stop(void);


#ifdef __cplusplus
}
#endif

#endif /* LWIP_DHCP */

#endif /*LWIP_HDR_DHCP_H*/

