#include "lwip_test.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include "lwip/dhcp.h"
#include "lwip/apps/httpd.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/http_client.h"


/* UDP dns(done)
 * UDP echo(done)
 * UDP speed(done)
 * UDP hdcp client(done)
 * UDP dhcp server(done)
 * UDP tftp server(not yet)
 * UDP tftp client(not yet)
 * TCP client(done)
 * TCP server(done)
 * TCP http server(done 但是不能被外网访问)
 * TCP http client(not yet)
 * TCP telnet server(not yet)
 * TCP telnet client(not yet)
 * TCP ftp client
 * TCP ftp server
 * MQTT
 */
#include <string.h>
extern struct netif mrvl88w8801_lwip;

#if LWIP_DNS
static void dns_found_func(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    if (ipaddr != NULL)
    {
        printf("DNS Found IP: %s\n", ip4addr_ntoa(ipaddr));
    }
    else
        printf("DNS Not Found IP!\n");
}

void udp_dns_test(const char *name)
{
    ip_addr_t dnsip;
    err_t err = dns_gethostbyname(name, &dnsip, dns_found_func, NULL);
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
#endif


#define UDP_ECHO_PORT 7
void udp_echo_recv(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    udp_sendto(upcb,p,addr,port);
    pbuf_free(p);
}

void udp_echo_test()
{
    struct udp_pcb *upcb = udp_new();
    udp_bind(upcb, IP4_ADDR_ANY, UDP_ECHO_PORT);
    udp_recv(upcb, udp_echo_recv, NULL);
}



uint8_t test_buffer[1500];
void udp_speed_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    struct pbuf *q;
    uint16_t i;

    if (p != NULL)
    {
        pbuf_free(p);

        q = pbuf_alloc(PBUF_TRANSPORT, 1300, PBUF_ROM);
        if (q != NULL)
        {
            printf("Sending UDP packets...\n");
            q->payload = test_buffer;
            for (i = 0; i < 1024; i++)
                udp_sendto(pcb, q, addr, port);
            pbuf_free(q);
        }
    }
}
void udp_speed_test(void)
{
    struct udp_pcb *upcb = udp_new();
    udp_bind(upcb, IP4_ADDR_ANY, 24002);
    udp_recv(upcb, udp_speed_recv, NULL);
}


#if LWIP_DHCP
void udp_dhcp_show_ip(u8_t *ip,u8_t *mask,u8_t *gateway)
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
#endif


void  tcp_server_err_cb(void *arg, err_t err)
{
    printf("TCP tester error! err=%d\n", err);
}

err_t tcp_server_recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p != NULL)
    {
        printf("TCP tester received %d bytes from %s:%d!\n", p->tot_len, ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
    }
    else
    {
        printf("TCP tester client %s:%d closed!\n", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
        tcp_close(tpcb);
    }
    return ERR_OK;
}

err_t tcp_server_sent_cb(void *arg, struct tcp_pcb *tpcb,u16_t len)
{
    printf("TCP tester client %s:%d send %d byte success!\n", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port,len);

    return ERR_OK;
}

static err_t tcp_server_accept_cb(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    printf("TCP tester accepted %s:%d!\n", ipaddr_ntoa(&newpcb->remote_ip), newpcb->remote_port);
    tcp_err(newpcb, tcp_server_err_cb);
    tcp_recv(newpcb, tcp_server_recv_cb);
    tcp_sent(newpcb, tcp_server_sent_cb);
    return ERR_OK;
}

void tcp_server_test(uint16_t port)
{
    struct tcp_pcb *tpcb = tcp_new();
    printf("tcp server port %d\n",port);
    tcp_bind(tpcb, IP4_ADDR_ANY, port);
    tpcb = tcp_listen(tpcb);
    tcp_accept(tpcb, tcp_server_accept_cb);
}


err_t tcp_client_recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p != NULL)
    {
        uint8_t send_buffer[] = "client received";
        printf("%d bytes received!\n", p->tot_len);
        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
        tcp_write(tpcb, send_buffer, sizeof(send_buffer), 1);
    }
    else
    {
        err = tcp_close(tpcb);
        printf("Connection is closed! err=%d\n", err);
    }
    return ERR_OK;
}

err_t tcp_client_connect_cb(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    printf("connected %d\n",err);
    tcp_recv(tpcb, tcp_client_recv_cb);

    return ERR_OK;
}

void tcp_client_test(char *ipaddr_c,uint16_t port)
{
    err_t err;
    ip_addr_t ipaddr;

    struct tcp_pcb *tpcb = tcp_new();

    ip4addr_aton(ipaddr_c,&ipaddr);
    err = tcp_connect(tpcb, &ipaddr, port, tcp_client_connect_cb);
    if (err != ERR_OK)
    {
        printf("Connection failed! err=%d\n", err);
        tcp_close(tpcb);
    }
}

void tcp_http_server_test()
{
    httpd_init();
}

err_t tcp_httpc_recv_fn(void *arg, struct tcp_pcb *tpcb,struct pbuf *p, err_t err)
{
    printf("tcp_httpc_recv_fn %d bytes received!\n", p->tot_len);
    return ERR_OK;
}

void tcp_http_client_test()
{
    //httpc_connection_t setting;
    httpc_get_file_dns("wireless-ota.bj.bcebos.com",80,"http://wireless-ota.bj.bcebos.com/stm32f10x_bb_tiny_driver.hex",\
                       NULL,tcp_httpc_recv_fn,NULL,NULL);
}


mqtt_client_t *mqtt_client;

static void mqtt_sub_request_cb(void *arg, err_t result)
{
    /* Just print the result code here for simplicity,
    normal behaviour would be to take some action if subscribe fails like
    notifying user, retry subscribe or disconnect from server */
    printf("Subscribe result: %d\n", result);
}

static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    printf("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);
    /* Decode topic string into a user defined reference */

}

#include "hw_led.h"
static void mqtt_msg_parse(const u8_t *data, u16_t len)
{
    u8_t index;
    for(index = 0; index < len; index++)
    {
        printf("%c",data[index]);
    }
    printf("\n");

    if(hw_strncmp("LED_ON",(const char*)data,hw_strlen("LED_ON")) == 0)
    {
        LED1_ON;
        LED2_ON;
    }

    if(hw_strncmp("LED_OFF",(const char*)data,hw_strlen("LED_OFF")) == 0)
    {
        LED1_OFF;
        LED2_OFF;
    }
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);

    mqtt_msg_parse(data,len);
    if(flags & MQTT_DATA_FLAG_LAST)
    {
        printf("MQTT_DATA_FLAG_LAST\n");
    }
    else
    {
        printf("~MQTT_DATA_FLAG_LAST\n");
    }
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    err_t err;
    if(status == MQTT_CONNECT_ACCEPTED)
    {
        printf("mqtt_connection_cb: Successfully connected\n");
        /* Setup callback for incoming publish requests */
        mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
        /* Subscribe to a topic named "subtopic" with QoS level 1, call mqtt_sub_request_cb with result */
        err = mqtt_subscribe(client, "wireless_topic", 1, mqtt_sub_request_cb, arg);
        if(err != ERR_OK)
        {
            printf("mqtt_subscribe return: %d\n", err);
        }
    }
    else
    {
        printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);
    }
}

static void mqtt_server_find(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    if (ipaddr != NULL)
    {

        struct mqtt_connect_client_info_t client_info = {    "mqtt_id",  "pc1a2qy/wireless_rtos", "tE7owXEWJ8tusatI",    10,    NULL, NULL, 0, 0  };
        err_t err;
        printf("DNS Found IP: %s\n", ip4addr_ntoa(ipaddr));
        err = mqtt_client_connect(mqtt_client, ipaddr, MQTT_PORT, mqtt_connection_cb, 0, &client_info);
        /* For now just print the result code if something goes wrong */
        if(err != ERR_OK)
        {
            printf("mqtt_connect return %d\n", err);
        }
    }
    else
        printf("DNS Not Found IP!\n");
}

void find_mqtt_ip()
{
    ip_addr_t dnsip;
    err_t err = dns_gethostbyname("pc1a2qy.mqtt.iot.bj.baidubce.com", &dnsip, mqtt_server_find, NULL);
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

void mqtt_connect_server()
{
    mqtt_client = mqtt_client_new();


    if(mqtt_client != NULL)
    {
        /* baidu cloud server */
        find_mqtt_ip();

    }
}

