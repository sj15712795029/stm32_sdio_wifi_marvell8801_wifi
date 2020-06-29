#ifndef IOT_LWOS_COMPONENT_CONF_H_H_H
#define IOT_LWOS_COMPONENT_CONF_H_H_H

#include <stdio.h>
#include <string.h>

#define COMP_DEBUG_ENABLE 1
#if COMP_DEBUG_ENABLE > 0
#define COMP_DEBUG	printf
#else
#define COMP_DEBUG
#endif

#define comp_memset 	memset
#define comp_memcpy	memcpy
#define comp_memcmp	memcmp
#define comp_strlen	strlen
#define comp_strcmp strcmp
#define comp_sprintf sprintf

/** Do nothing */
#define comp_le16_to_cpu(x) x
/** Do nothing */
#define comp_le32_to_cpu(x) x
/** Do nothing */
#define comp_le64_to_cpu(x) x
/** Do nothing */
#define comp_cpu_to_le16(x) x
/** Do nothing */
#define comp_cpu_to_le32(x) x
/** Do nothing */
#define wlan_cpu_to_le64(x) x

/* 1.WI-FI≈‰÷√«¯ */
#define WIFI_CONF_TX_BUFFER_SIZE	2048
#define WIFI_CONF_RX_BUFFER_SIZE	2048
#define WIFI_CONF_SSID_MAX_SIZE	32
#define WIFI_CONF_PWD_MAX_SIZE	64
#define WIFI_CONF_CHANNEL_MAX	14

#define WIFI_CONF_MIN_POLL_TRIES		10
#define WIFI_CONF_MAX_POLL_TRIES		10000
#define WIFI_CONF_MAX_CLIENT_NUM	8


/* 2.¿∂—¿≈‰÷√«¯ */
#define BT_CONF_CLASSICAL_ENABLE 1
#define BT_CONF_BLE_ENABLE 1

typedef enum
{
	COMP_ERR_OK,

	COMP_ERR_FS_INIT,
	
	WIFI_ERR_REQ_INVALID_FW_SIZE,
	WIFI_ERR_INVALID_FW_STATUS,
	WIFI_ERR_NO_MORE_READ_HANDLE,
	WIFI_ERR_INVALID_RESPONSE,
	
}comp_err_e;


#endif
