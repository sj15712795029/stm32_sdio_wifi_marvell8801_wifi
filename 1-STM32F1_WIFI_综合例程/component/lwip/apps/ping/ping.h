#ifndef LWIP_PING_H
#define LWIP_PING_H

#include "lwip/ip_addr.h"

/**
 * PING_USE_SOCKETS: Set to 1 to use sockets, otherwise the raw api is used
 */
#ifndef PING_USE_SOCKETS
#define PING_USE_SOCKETS    LWIP_SOCKET
#endif

typedef void (*ping_runing_hook)(ip_addr_t *addr,u32_t time);
typedef void (*ping_stop_hook)(u16_t send_count,u16_t recv_count);
void ping_init(ip_addr_t* ping_addr,ping_runing_hook hook);
void ping_deinit(ping_stop_hook hook);

#if !PING_USE_SOCKETS
void ping_send_now(void);
#endif /* !PING_USE_SOCKETS */

#endif /* LWIP_PING_H */
