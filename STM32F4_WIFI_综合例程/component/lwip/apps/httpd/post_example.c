/**
 * @file
 * HTTPD example for simple POST
 */

/*
* Copyright (c) 2017 Simon Goldschmidt
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
* Author: Simon Goldschmidt <goldsimon@gmx.de>
*
*/

#include "marvell88w8801_core.h"
#include "lwip/opt.h"

#include "lwip/apps/httpd.h"
#include "lwip/def.h"
#include "lwip/mem.h"

#include <stdio.h>
#include <string.h>

#define LWIP_HTTPD_EXAMPLE_SIMPLEPOST 1
#define LWIP_HTTPD_SUPPORT_POST 1
/** define LWIP_HTTPD_EXAMPLE_GENERATEDFILES to 1 to enable this file system */
#ifndef LWIP_HTTPD_EXAMPLE_SIMPLEPOST
#define LWIP_HTTPD_EXAMPLE_SIMPLEPOST 0
#endif

#if LWIP_HTTPD_EXAMPLE_SIMPLEPOST

#if !LWIP_HTTPD_SUPPORT_POST
#error This needs LWIP_HTTPD_SUPPORT_POST
#endif

uint8_t wifi_config_ssid[32] = {0};
uint8_t wifi_config_pwd[32] = {0};
uint8_t wifi_config = 0;

static void *current_connection;

err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                       u16_t http_request_len, int content_len, char *response_uri,
                       u16_t response_uri_len, u8_t *post_auto_wnd)
{
    LWIP_UNUSED_ARG(connection);
    LWIP_UNUSED_ARG(http_request);
    LWIP_UNUSED_ARG(http_request_len);
    LWIP_UNUSED_ARG(content_len);
    LWIP_UNUSED_ARG(post_auto_wnd);

    if (!memcmp(uri, "/index.html", strlen("/index.html")))
    {
        if (current_connection != connection)
        {
            current_connection = connection;
            snprintf(response_uri, response_uri_len, "/success.html");
            /* e.g. for large uploads to slow flash over a fast connection, you should
               manually update the rx window. That way, a sender can only send a full
               tcp window at a time. If this is required, set 'post_aut_wnd' to 0.
               We do not need to throttle upload speed here, so: */
            *post_auto_wnd = 1;
            return ERR_OK;
        }
    }
    return ERR_VAL;
}

err_t
httpd_post_receive_data(void *connection, struct pbuf *p)
{
    char *ssid_start = strstr(p->payload,"ssid=") + strlen("ssid=");
    char *ssid_end = strstr((char *)ssid_start,"&");

    char *pwd_start = strstr(p->payload,"pwd=") + strlen("pwd=") ;
    //char *pwd_end =  strstr((char *)pwd_start," ");

    memset(wifi_config_ssid,0,sizeof(wifi_config_ssid));
    memset(wifi_config_pwd,0,sizeof(wifi_config_pwd));

    memcpy(wifi_config_ssid,ssid_start,ssid_end-ssid_start);
    memcpy(wifi_config_pwd,pwd_start,strlen(pwd_start));

    printf("wifi_config_ssid:%s\n",wifi_config_ssid);
    printf("wifi_config_pwd:%s\n",wifi_config_pwd);
	wifi_config = 1;


    return ERR_OK;
}

void
httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len)
{
    snprintf(response_uri, response_uri_len, "/success.html");
	 
}

#endif /* LWIP_HTTPD_EXAMPLE_SIMPLEPOST*/
