/** @file  timestamp.h
*
* @brief This file contains definitions used for timestamp feature
*
* (C) Copyright 2011-2018 Marvell International Ltd. All Rights Reserved
*
* MARVELL CONFIDENTIAL
* The source code contained or described herein and all documents related to
* the source code ("Material") are owned by Marvell International Ltd or its
* suppliers or licensors. Title to the Material remains with Marvell International Ltd
* or its suppliers and licensors. The Material contains trade secrets and
* proprietary and confidential information of Marvell or its suppliers and
* licensors. The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used, copied,
* reproduced, modified, published, uploaded, posted, transmitted, distributed,
* or disclosed in any way without Marvell's prior express written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel or
* otherwise. Any license under such intellectual property rights must be
* express and approved by Marvell in writing.
*
*/

#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include  "mlanutl.h"
#include  <linux/if_packet.h>
#include  <netinet/ether.h>
#include  <linux/net_tstamp.h>

#define BUF_SIZ         1024
#define ARP_FORMAT      "%s %*s %*s %s %*s %s"
#define ARP_FILE_BUFFER_LEN  (1024)

struct interface_data {
	char ip[20];
	int mac[20];
	char interface[20];
};

/**
 * 802.1 Local Experimental 1.
 */
#ifndef ETH_P_802_EX1
#define ETH_P_802_EX1   0x88B5
#endif

void receive_timestamp(int argc, char *argv[]);
int send_timestamp(int argc, char *argv[]);
void get_mac(char *ifc, char *ip);
void recvpacket(int sock, int recvmsg_flags, int siocgstamp, int siocgstampns);
void printpacket(struct msghdr *msg, int res, int sock,
		 int recvmsg_flags, int siocgstamp, int siocgstampns);

#endif //_TIMESTAMP_H_
