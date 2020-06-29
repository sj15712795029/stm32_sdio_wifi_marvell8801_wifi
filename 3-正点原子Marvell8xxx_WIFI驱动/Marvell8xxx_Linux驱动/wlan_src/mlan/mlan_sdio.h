/** @file mlan_sdio.h
 *
 *  @brief This file contains definitions for SDIO interface.
 *
 *  (C) Copyright 2008-2018 Marvell International Ltd. All Rights Reserved
 *
 *  MARVELL CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Material") are owned by Marvell International Ltd or its
 *  suppliers or licensors. Title to the Material remains with Marvell
 *  International Ltd or its suppliers and licensors. The Material contains
 *  trade secrets and proprietary and confidential information of Marvell or its
 *  suppliers and licensors. The Material is protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Material may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without Marvell's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by Marvell in writing.
 *
 */
/****************************************************
Change log:
****************************************************/

#ifndef	_MLAN_SDIO_H
#define	_MLAN_SDIO_H

/** Block mode */
#ifndef BLOCK_MODE
#define BLOCK_MODE	1
#endif

/** Fixed address mode */
#ifndef FIXED_ADDRESS
#define FIXED_ADDRESS	0
#endif

/* Host Control Registers */
/** Host Control Registers : Host to Card Event */
#define HOST_TO_CARD_EVENT_REG		0x00
/** Host Control Registers : Host terminates Command 53 */
#define HOST_TERM_CMD53			(0x1U << 2)
/** Host Control Registers : Host without Command 53 finish host */
#define HOST_WO_CMD53_FINISH_HOST	(0x1U << 2)
/** Host Control Registers : Host power up */
#define HOST_POWER_UP			(0x1U << 1)
/** Host Control Registers : Host power down */
#define HOST_POWER_DOWN			(0x1U << 0)

/** Host Control Registers : Host interrupt RSR */
#define HOST_INT_RSR_REG		0x01

/** Host Control Registers : Upload host interrupt RSR */
#define UP_LD_HOST_INT_RSR		(0x1U)
#define HOST_INT_RSR_MASK		0xFF

/** Host Control Registers : Host interrupt mask */
#define HOST_INT_MASK_REG		0x02

/** Host Control Registers : Upload host interrupt mask */
#define UP_LD_HOST_INT_MASK		(0x1U)
/** Host Control Registers : Download host interrupt mask */
#define DN_LD_HOST_INT_MASK		(0x2U)
/** Host Control Registers : Cmd port upload interrupt mask */
#define CMD_PORT_UPLD_INT_MASK		(0x1U << 6)
/** Host Control Registers : Cmd port download interrupt mask */
#define CMD_PORT_DNLD_INT_MASK		(0x1U << 7)
/** Enable Host interrupt mask */
#define HIM_ENABLE			(UP_LD_HOST_INT_MASK   | \
					DN_LD_HOST_INT_MASK    | \
					CMD_PORT_UPLD_INT_MASK | \
					CMD_PORT_DNLD_INT_MASK)
/** Disable Host interrupt mask */
#define	HIM_DISABLE			0xff

/** Host Control Registers : Host interrupt status */
#define HOST_INT_STATUS_REG		0x03

/** Host Control Registers : Upload command port host interrupt status */
#define UP_LD_CMD_PORT_HOST_INT_STATUS		(0x40U)
/** Host Control Registers : Download command port host interrupt status */
#define DN_LD_CMD_PORT_HOST_INT_STATUS		(0x80U)

/** Host Control Registers : Upload host interrupt status */
#define UP_LD_HOST_INT_STATUS		(0x1U)
/** Host Control Registers : Download host interrupt status */
#define DN_LD_HOST_INT_STATUS		(0x2U)

/** Port for registers */
#define REG_PORT			0
/** LSB of read bitmap */
#define RD_BITMAP_L			0x04
/** MSB of read bitmap */
#define RD_BITMAP_U			0x05
/** LSB of write bitmap */
#define WR_BITMAP_L			0x06
/** MSB of write bitmap */
#define WR_BITMAP_U			0x07
/** LSB of read length for port 0 */
#define RD_LEN_P0_L			0x08
/** MSB of read length for port 0 */
#define RD_LEN_P0_U			0x09
/** Ctrl port */
#define CTRL_PORT			0
/** Ctrl port mask */
#define CTRL_PORT_MASK			0x0001
/** Data port mask */
#define DATA_PORT_MASK			0xfffe
/** Misc. Config Register : Auto Re-enable interrupts */
#define AUTO_RE_ENABLE_INT		MBIT(4)

/** Host Control Registers : Host transfer status */
#define HOST_RESTART_REG		0x28
/** Host Control Registers : Download CRC error */
#define DN_LD_CRC_ERR			(0x1U << 2)
/** Host Control Registers : Upload restart */
#define UP_LD_RESTART			(0x1U << 1)
/** Host Control Registers : Download restart */
#define DN_LD_RESTART			(0x1U << 0)

/* Card Control Registers */
/** Card Control Registers : Card to host event */
#define CARD_TO_HOST_EVENT_REG		0x30
/** Card Control Registers : Card I/O ready */
#define CARD_IO_READY			(0x1U << 3)
/** Card Control Registers : CIS card ready */
#define CIS_CARD_RDY			(0x1U << 2)
/** Card Control Registers : Upload card ready */
#define UP_LD_CARD_RDY			(0x1U << 1)
/** Card Control Registers : Download card ready */
#define DN_LD_CARD_RDY			(0x1U << 0)

/** Card Control Registers : Host interrupt mask register */
#define HOST_INTERRUPT_MASK_REG		0x34
/** Card Control Registers : Host power interrupt mask */
#define HOST_POWER_INT_MASK		(0x1U << 3)
/** Card Control Registers : Abort card interrupt mask */
#define ABORT_CARD_INT_MASK		(0x1U << 2)
/** Card Control Registers : Upload card interrupt mask */
#define UP_LD_CARD_INT_MASK		(0x1U << 1)
/** Card Control Registers : Download card interrupt mask */
#define DN_LD_CARD_INT_MASK		(0x1U << 0)

/** Card Control Registers : Card interrupt status register */
#define CARD_INTERRUPT_STATUS_REG	0x38
/** Card Control Registers : Power up interrupt */
#define POWER_UP_INT			(0x1U << 4)
/** Card Control Registers : Power down interrupt */
#define POWER_DOWN_INT			(0x1U << 3)

/** Card Control Registers : Card interrupt RSR register */
#define CARD_INTERRUPT_RSR_REG		0x3c
/** Card Control Registers : Power up RSR */
#define POWER_UP_RSR			(0x1U << 4)
/** Card Control Registers : Power down RSR */
#define POWER_DOWN_RSR			(0x1U << 3)

/** Card Control Registers : SQ Read base address 0 register */
#define READ_BASE_0_REG			0x40
/** Card Control Registers : SQ Read base address 1 register */
#define READ_BASE_1_REG			0x41

/** Card Control Registers : Card revision register */
#define CARD_REVISION_REG		0x5c

/** Firmware status 0 register (SCRATCH0_0) */
#define CARD_FW_STATUS0_REG		0x60
/** Firmware status 1 register (SCRATCH0_1) */
#define CARD_FW_STATUS1_REG		0x61
/** Rx length register (SCRATCH0_2) */
#define CARD_RX_LEN_REG			0x62
/** Rx unit register (SCRATCH0_3) */
#define CARD_RX_UNIT_REG		0x63

/** Card Control Registers : Card OCR 0 register */
#define CARD_OCR_0_REG			0x68
/** Card Control Registers : Card OCR 1 register */
#define CARD_OCR_1_REG			0x69
/** Card Control Registers : Card OCR 3 register */
#define CARD_OCR_3_REG			0x6A
/** Card Control Registers : Card config register */
#define CARD_CONFIG_REG			0x6B
/** Card Control Registers : Miscellaneous Configuration Register */
#define CARD_MISC_CFG_REG		0x6C

/** Card Control Registers : Debug 0 register */
#define DEBUG_0_REG			0x70
/** Card Control Registers : SD test BUS 0 */
#define SD_TESTBUS0			(0x1U)
/** Card Control Registers : Debug 1 register */
#define DEBUG_1_REG			0x71
/** Card Control Registers : SD test BUS 1 */
#define SD_TESTBUS1			(0x1U)
/** Card Control Registers : Debug 2 register */
#define DEBUG_2_REG			0x72
/** Card Control Registers : SD test BUS 2 */
#define SD_TESTBUS2			(0x1U)
/** Card Control Registers : Debug 3 register */
#define DEBUG_3_REG			0x73
/** Card Control Registers : SD test BUS 3 */
#define SD_TESTBUS3			(0x1U)

/** Host Control Registers : I/O port 0 */
#define IO_PORT_0_REG			0x78
/** Host Control Registers : I/O port 1 */
#define IO_PORT_1_REG			0x79
/** Host Control Registers : I/O port 2 */
#define IO_PORT_2_REG			0x7A

/** Port for memory */
#define MEM_PORT	                        0x10000
/** Card Control Registers : cmd53 new mode */
#define CMD53_NEW_MODE      (0x1U << 0)
#define CMD_PORT_RD_LEN_EN  (0x1U << 2)
#define CMD_PORT_AUTO_EN              (0x1U << 0)
#define CMD_PORT_SLCT                   0x8000
/** Ctrl port mask */
#define CTRL_PORT_MASK			0x0001
/** Enable GPIO-1 as a duplicated signal of interrupt as appear of SDIO_DAT1*/
#define ENABLE_GPIO_1_INT_MODE  0x88
/** Scratch reg 3 2  :     Configure GPIO-1 INT*/
#define SCRATCH_REG_32          0xEE

/** SD8787 card type */
#define CARD_TYPE_SD8787   0x01
/** SD8777 card type */
#define CARD_TYPE_SD8777   0x02
/** SD8887 card type */
#define CARD_TYPE_SD8887   0x03
/** SD8801 card type */
#define CARD_TYPE_SD8801   0x04
/** SD8897 card type */
#define CARD_TYPE_SD8897   0x05
/** SD8797 card type */
#define CARD_TYPE_SD8797   0x06
/** SD8977 card type */
#define CARD_TYPE_SD8977   0x07
/** SD8997 card type */
#define CARD_TYPE_SD8997   0x08
/** SD8987 card type */
#define CARD_TYPE_SD8987   0x09

#define IS_SD8777(ct) (CARD_TYPE_SD8777 == (ct))
#define IS_SD8787(ct) (CARD_TYPE_SD8787 == (ct))
#define IS_SD8887(ct) (CARD_TYPE_SD8887 == (ct))
#define IS_SD8801(ct) (CARD_TYPE_SD8801 == (ct))
#define IS_SD8897(ct) (CARD_TYPE_SD8897 == (ct))
#define IS_SD8797(ct) (CARD_TYPE_SD8797 == (ct))
#define IS_SD8977(ct) (CARD_TYPE_SD8977 == (ct))
#define IS_SD8997(ct) (CARD_TYPE_SD8997 == (ct))
#define IS_SD8987(ct) (CARD_TYPE_SD8987 == (ct))

/** Event header Len*/
#define MLAN_EVENT_HEADER_LEN           8

/** SDIO byte mode size */
#define MAX_BYTE_MODE_SIZE             512

#if defined(SDIO_MULTI_PORT_TX_AGGR) || defined(SDIO_MULTI_PORT_RX_AGGR)
/** The base address for packet with multiple ports aggregation */
#define SDIO_MPA_ADDR_BASE             0x1000
#endif

#ifdef SDIO_MULTI_PORT_TX_AGGR

/** SDIO Tx aggregation in progress ? */
#define MP_TX_AGGR_IN_PROGRESS(a) (a->mpa_tx.pkt_cnt > 0)

/** SDIO Tx aggregation buffer room for next packet ? */
#define MP_TX_AGGR_BUF_HAS_ROOM(a, mbuf, len) \
			(((a->mpa_tx.buf_len) + len) <= (a->mpa_tx.buf_size))

/** Copy current packet (SDIO Tx aggregation buffer) to SDIO buffer */
#define MP_TX_AGGR_BUF_PUT_NEWMODE(a, mbuf, port) do {                  \
	pmadapter->callbacks.moal_memmove(a->pmoal_handle, \
		&a->mpa_tx.buf[a->mpa_tx.buf_len], \
		mbuf->pbuf+mbuf->data_offset, mbuf->data_len);\
	a->mpa_tx.buf_len += mbuf->data_len;                        \
    a->mpa_tx.mp_wr_info[a->mpa_tx.pkt_cnt] = *(t_u16 *)(mbuf->pbuf+mbuf->data_offset); \
	if (!a->mpa_tx.pkt_cnt) {                                   \
	    a->mpa_tx.start_port = port;                            \
	}                                                           \
	a->mpa_tx.ports |= (1 << port);                             \
	a->mpa_tx.pkt_cnt++;                                        \
} while (0)

#define MP_TX_AGGR_BUF_PUT_SG_NEWMODE(a, mbuf, port) do {               \
	a->mpa_tx.buf_len += mbuf->data_len;                        \
    a->mpa_tx.mp_wr_info[a->mpa_tx.pkt_cnt] = *(t_u16 *)(mbuf->pbuf+mbuf->data_offset); \
    a->mpa_tx.mbuf_arr[a->mpa_tx.pkt_cnt] = mbuf;               \
	if (!a->mpa_tx.pkt_cnt) {                                   \
	    a->mpa_tx.start_port = port;                            \
	}                                                           \
	a->mpa_tx.ports |= (1 << port);                             \
	a->mpa_tx.pkt_cnt++;                                        \
} while (0)
#define MP_TX_AGGR_BUF_PUT_NONEWMODE(a, mbuf, port) do {                  \
	pmadapter->callbacks.moal_memmove(a->pmoal_handle, \
		&a->mpa_tx.buf[a->mpa_tx.buf_len], \
		mbuf->pbuf+mbuf->data_offset, mbuf->data_len);\
	a->mpa_tx.buf_len += mbuf->data_len;                        \
	a->mpa_tx.mp_wr_info[a->mpa_tx.pkt_cnt] = *(t_u16 *)(mbuf->pbuf+mbuf->data_offset); \
	if (!a->mpa_tx.pkt_cnt) {                                   \
	    a->mpa_tx.start_port = port;                            \
	}                                                           \
	if (a->mpa_tx.start_port <= port) {                         \
	    a->mpa_tx.ports |= (1 << (a->mpa_tx.pkt_cnt));			\
	} else {                                                    \
	      a->mpa_tx.ports |= (1 << (a->mpa_tx.pkt_cnt \
			+ 1 + (a->psdio_device->max_ports - a->mp_end_port)));  \
	}                                                           \
	a->mpa_tx.pkt_cnt++;                                       \
} while (0)
#define MP_TX_AGGR_BUF_PUT_SG_NONEWMODE(a, mbuf, port) do {                  \
	a->mpa_tx.buf_len += mbuf->data_len;                        \
    a->mpa_tx.mp_wr_info[a->mpa_tx.pkt_cnt] = *(t_u16 *)(mbuf->pbuf+mbuf->data_offset); \
    a->mpa_tx.mbuf_arr[a->mpa_tx.pkt_cnt] = mbuf;               \
	if (!a->mpa_tx.pkt_cnt) {                                   \
	    a->mpa_tx.start_port = port;                            \
	}                                                           \
	if (a->mpa_tx.start_port <= port) {                         \
	    a->mpa_tx.ports |= (1 << (a->mpa_tx.pkt_cnt));			\
	} else {                                                    \
	      a->mpa_tx.ports |= (1 << (a->mpa_tx.pkt_cnt \
			+ 1 + (a->psdio_device->max_ports - a->mp_end_port)));  \
	}                                                           \
	a->mpa_tx.pkt_cnt++;                                       \
} while (0)
/** SDIO Tx aggregation limit ? */
#define MP_TX_AGGR_PKT_LIMIT_REACHED(a) ((a->mpa_tx.pkt_cnt) \
			== (a->mpa_tx.pkt_aggr_limit))

/** SDIO Tx aggregation port limit ? */

#define MP_TX_AGGR_PORT_LIMIT_REACHED(a) ((a->curr_wr_port < \
                a->mpa_tx.start_port) && (((a->psdio_device->max_ports - \
                a->mpa_tx.start_port) + a->curr_wr_port) >= \
                    a->psdio_device->mp_aggr_pkt_limit))

/** Reset SDIO Tx aggregation buffer parameters */
#define MP_TX_AGGR_BUF_RESET(a) do {         \
	memset(a, a->mpa_tx.mp_wr_info, 0, sizeof(a->mpa_tx.mp_wr_info)); \
	a->mpa_tx.pkt_cnt = 0;                   \
	a->mpa_tx.buf_len = 0;                   \
	a->mpa_tx.ports = 0;                     \
	a->mpa_tx.start_port = 0;                \
} while (0)

#endif /* SDIO_MULTI_PORT_TX_AGGR */

#ifdef SDIO_MULTI_PORT_RX_AGGR

/** SDIO Rx aggregation limit ? */
#define MP_RX_AGGR_PKT_LIMIT_REACHED(a) (a->mpa_rx.pkt_cnt \
		== a->mpa_rx.pkt_aggr_limit)

/** SDIO Rx aggregation port limit ? */
#define MP_RX_AGGR_PORT_LIMIT_REACHED_NEWMODE(a) \
			(((a->curr_rd_port < a->mpa_rx.start_port) && \
			(((a->psdio_device->max_ports - a->mpa_rx.start_port) + a->curr_rd_port) \
			>= (a->mp_end_port >> 1))) || \
			((a->curr_rd_port - a->mpa_rx.start_port) >= \
			(a->mp_end_port >> 1)))
#define MP_RX_AGGR_PORT_LIMIT_REACHED_NONEWMODE(a) ((a->curr_rd_port < \
                a->mpa_rx.start_port) && (((a->psdio_device->max_ports - \
                a->mpa_rx.start_port) + a->curr_rd_port) >= \
                a->psdio_device->mp_aggr_pkt_limit))

/** SDIO Rx aggregation in progress ? */
#define MP_RX_AGGR_IN_PROGRESS(a) (a->mpa_rx.pkt_cnt > 0)

/** SDIO Rx aggregation buffer room for next packet ? */
#define MP_RX_AGGR_BUF_HAS_ROOM(a, rx_len)   \
	((a->mpa_rx.buf_len + rx_len) <= a->mpa_rx.buf_size)

/** Prepare to copy current packet from card to SDIO Rx aggregation buffer */
#define MP_RX_AGGR_SETUP_NEWMODE(a, mbuf, port, rx_len) do {   \
	a->mpa_rx.buf_len += rx_len;                       \
	if (!a->mpa_rx.pkt_cnt) {                          \
	    a->mpa_rx.start_port = port;                   \
	}                                                  \
	a->mpa_rx.ports |= (1 << port);                    \
	a->mpa_rx.mbuf_arr[a->mpa_rx.pkt_cnt] = mbuf;      \
	a->mpa_rx.len_arr[a->mpa_rx.pkt_cnt] = rx_len;     \
	a->mpa_rx.pkt_cnt++;                              \
} while (0);

#define MP_RX_AGGR_SETUP_NONEWMODE(a, mbuf, port, rx_len) do {   \
	a->mpa_rx.buf_len += rx_len;                       \
	if (!a->mpa_rx.pkt_cnt) {                          \
	    a->mpa_rx.start_port = port;                   \
	}                                                  \
	if (a->mpa_rx.start_port <= port) {                  \
	    a->mpa_rx.ports |= (1 << (a->mpa_rx.pkt_cnt)); \
	} else {                                           \
	    a->mpa_rx.ports |= (1 << (a->mpa_rx.pkt_cnt + 1)); \
	}                                                  \
	a->mpa_rx.mbuf_arr[a->mpa_rx.pkt_cnt] = mbuf;      \
	a->mpa_rx.len_arr[a->mpa_rx.pkt_cnt] = rx_len;     \
	a->mpa_rx.pkt_cnt++;                               \
} while (0);

/** Reset SDIO Rx aggregation buffer parameters */
#define MP_RX_AGGR_BUF_RESET(a) do {         \
	a->mpa_rx.pkt_cnt = 0;                   \
	a->mpa_rx.buf_len = 0;                   \
	a->mpa_rx.ports = 0;                     \
	a->mpa_rx.start_port = 0;                \
} while (0)

#endif /* SDIO_MULTI_PORT_RX_AGGR */

/** Register sdio 87xx card structure */
static const struct _mlan_sdio_card_reg mlan_reg_sd87xx = {
     /** start read port */
	.start_rd_port = 1,
    /** start write port */
	.start_wr_port = 1,
    /** base register0 */
	.base_0_reg = 0x40,	//0x0040,
    /** base1 register1 */
	.base_1_reg = 0x41,	//0x0041,
    /** poll register */
	.poll_reg = 0x30,
    /** host interrupt enable */
	.host_int_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK,
    /** host interrupt status*/
	.host_int_status = DN_LD_HOST_INT_STATUS | UP_LD_HOST_INT_STATUS,
     /** status register0 */
	.status_reg_0 = 0x60,
    /** status register 1 */
	.status_reg_1 = 0x61,
    /** sdio interrupt mask */
	.sdio_int_mask = 0x3f,
    /** data port mask */
	.data_port_mask = 0x0000fffe,
    /** maximum mp register */
	.max_mp_regs = 64,
     /** read bitmap lower byte */
	.rd_bitmap_l = 0x04,
    /** read bitmap upper byte */
	.rd_bitmap_u = 0x05,
    /** write bitmap lower byte */
	.wr_bitmap_l = 0x06,
    /** write bitmap upper byte */
	.wr_bitmap_u = 0x07,
    /** read port0 length lower byte */
	.rd_len_p0_l = 0x08,
    /** read port0 length upper byte */
	.rd_len_p0_u = 0x09,
    /** card misc configuration register */
	.card_misc_cfg_reg = 0x6c,
     /** scratch reg used for reset and check SOC wakeup*/
	.reset_reg = 0x64,
    /** reset value, not set for 87xx */
	.reset_val = 0,
};

/** Registeri sdio 8887 card structure */
static const struct _mlan_sdio_card_reg mlan_reg_sd8887 = {
     /** start read port */
	.start_rd_port = 0,
    /** start write port */
	.start_wr_port = 0,
    /** base register0 */
	.base_0_reg = 0x6C,
    /** base register1 */
	.base_1_reg = 0x6D,
    /** poll register */
	.poll_reg = 0x5C,
    /** host interrupt enable */
	.host_int_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
		CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
     /** host interrupt status */
	.host_int_status = DN_LD_HOST_INT_STATUS | UP_LD_HOST_INT_STATUS |
		DN_LD_CMD_PORT_HOST_INT_STATUS | UP_LD_CMD_PORT_HOST_INT_STATUS,
     /** status register0 */
	.status_reg_0 = 0x90,
    /** status register1 */
	.status_reg_1 = 0x91,
     /** sdio interrupt mask */
	.sdio_int_mask = 0xff,
    /** data port mask */
	.data_port_mask = 0xffffffff,
    /** maximum mp register */
	.max_mp_regs = 196,
    /** read bitmap lower byte */
	.rd_bitmap_l = 0x10,
    /** read bitmap upper byte */
	.rd_bitmap_u = 0x11,
    /** read bitmap1 lower byte */
	.rd_bitmap_1l = 0x12,
    /** read bitmap1 upper byte */
	.rd_bitmap_1u = 0x13,
    /** write bitmap lower byte */
	.wr_bitmap_l = 0x14,
    /** write bitmap upper byte */
	.wr_bitmap_u = 0x15,
    /** write bitmap1 lower byte */
	.wr_bitmap_1l = 0x16,
    /** write bitmap1 upper byte */
	.wr_bitmap_1u = 0x17,
    /** read port0 length lower byte */
	.rd_len_p0_l = 0x18,
    /** read port0 length upper byte */
	.rd_len_p0_u = 0x19,
    /** card misc configuration register */
	.card_misc_cfg_reg = 0xD8,
     /** scratch reg used for reset and check SOC wakeup*/
	.reset_reg = 0xB6,
    /** reset value */
	.reset_val = 1,
};

/** Register sdio 8897 card structure */
static const struct _mlan_sdio_card_reg mlan_reg_sd8897 = {
     /** start read port */
	.start_rd_port = 0,
    /** start write port */
	.start_wr_port = 0,
    /** base register0 */
	.base_0_reg = 0x60,
    /** base register1 */
	.base_1_reg = 0x61,
    /** poll register */
	.poll_reg = 0x50,
    /** host interrupt enable */
	.host_int_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
		CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
     /** host interrupt status*/
	.host_int_status = DN_LD_HOST_INT_STATUS | UP_LD_HOST_INT_STATUS |
		DN_LD_CMD_PORT_HOST_INT_STATUS | UP_LD_CMD_PORT_HOST_INT_STATUS,
     /** status register0 */
	.status_reg_0 = 0xC0,
     /** status register1 */
	.status_reg_1 = 0xC1,
     /** sdio interrupt mask */
	.sdio_int_mask = 0xff,
    /** data port mask */
	.data_port_mask = 0xffffffff,
    /** maximum mp register */
	.max_mp_regs = 184,
    /** read bitmap lower byte */
	.rd_bitmap_l = 0x04,
    /** read bitmap upper byte */
	.rd_bitmap_u = 0x05,
    /** read bitmap1 lower byte */
	.rd_bitmap_1l = 0x06,
    /** read bitmap1 upper byte */
	.rd_bitmap_1u = 0x07,
    /** write bitmap lower byte */
	.wr_bitmap_l = 0x08,
    /** write bitmap upper byte */
	.wr_bitmap_u = 0x09,
    /** write bitmap1 lower byte */
	.wr_bitmap_1l = 0x0A,
    /** write bitmapi1 upper byte */
	.wr_bitmap_1u = 0x0B,
    /** read port0 length lower byte */
	.rd_len_p0_l = 0x0C,
    /** read port0 length upper byte */
	.rd_len_p0_u = 0x0D,
    /** card misc configuration register */
	.card_misc_cfg_reg = 0xCC,
     /** scratch reg used for reset and check SOC wakeup*/
	.reset_reg = 0xE8,
    /** reset value */
	.reset_val = 1,
};

/** Register sdio 8997 card structure */
static const struct _mlan_sdio_card_reg mlan_reg_sd8977_sd8997 = {
     /** start read port */
	.start_rd_port = 0,
    /** start write port */
	.start_wr_port = 0,
    /** base register0 */
	.base_0_reg = 0xf8,
    /** base register1 */
	.base_1_reg = 0xf9,
    /** poll register */
	.poll_reg = 0x5C,
    /** host interrupt enable */
	.host_int_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
		CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
     /** host interrupt status*/
	.host_int_status = DN_LD_HOST_INT_STATUS | UP_LD_HOST_INT_STATUS |
		DN_LD_CMD_PORT_HOST_INT_STATUS | UP_LD_CMD_PORT_HOST_INT_STATUS,
    /** status register0 */
	.status_reg_0 = 0xe8,
    /** status register1 */
	.status_reg_1 = 0xe9,
     /** sdio interrupt mask */
	.sdio_int_mask = 0xff,
     /** data port mask */
	.data_port_mask = 0xffffffff,
     /** maximum mp register */
	.max_mp_regs = 196,
    /** read bitmap lower byte */
	.rd_bitmap_l = 0x10,
    /** read bitmap upper byte */
	.rd_bitmap_u = 0x11,
    /** read bitmap1 lower byte */
	.rd_bitmap_1l = 0x12,
    /** read bitmap1 upper byte */
	.rd_bitmap_1u = 0x13,
    /** write bitmap lower byte */
	.wr_bitmap_l = 0x14,
    /** write bitmap upper byte */
	.wr_bitmap_u = 0x15,
    /** write bitmap1 lower byte */
	.wr_bitmap_1l = 0x16,
    /** write bitmap1 upper byte */
	.wr_bitmap_1u = 0x17,
    /** read port0 length lower byte */
	.rd_len_p0_l = 0x18,
    /** read port0 length upper byte */
	.rd_len_p0_u = 0x19,
    /** card misc configuration register */
	.card_misc_cfg_reg = 0xd8,
     /** scratch reg used for reset and check SOC wakeup*/
	.reset_reg = 0xEE,
    /** reset value */
	.reset_val = 0x99,
};

/** ampdu info for general card */
static struct _ampdu_info ampdu_info_nov15 = {
     /** AMPDU station tx window size */
	.ampdu_sta_txwinsize = MLAN_STA_AMPDU_DEF_TXWINSIZE_NOV15,
    /** AMPDU uAP tx window size */
	.ampdu_uap_txwinsize = MLAN_UAP_AMPDU_DEF_TXWINSIZE_NOV15,
    /** AMPDU uAP rx window size */
	.ampdu_uap_rxwinsize = MLAN_UAP_AMPDU_DEF_RXWINSIZE_NOV15,
#ifdef WIFI_DIRECT_SUPPORT
    /** AMPDU wifi direct txrx window size */
	.ampdu_wfd_txrxwinsize = MLAN_WFD_AMPDU_DEF_TXRXWINSIZE_NOV15,
#endif
};

/** ampdu info for sd8887 and sd8897 */
static struct _ampdu_info ampdu_info_v15 = {
     /** AMPDU station tx window size */
	.ampdu_sta_txwinsize = MLAN_STA_AMPDU_DEF_TXWINSIZE,
     /** AMPDU uAP tx window size */
	.ampdu_uap_txwinsize = MLAN_UAP_AMPDU_DEF_TXWINSIZE,
     /** AMPDU uAP rx window size */
	.ampdu_uap_rxwinsize = MLAN_UAP_AMPDU_DEF_RXWINSIZE,
#ifdef WIFI_DIRECT_SUPPORT
     /** AMPDU wifi direct txrx window size */
	.ampdu_wfd_txrxwinsize = MLAN_WFD_AMPDU_DEF_TXRXWINSIZE,
#endif
};

/** aggr buf size 32k  */
#define SDIO_MP_AGGR_BUF_SIZE_32K   (32768)
/** max aggr buf size 64k-256 */
#define SDIO_MP_AGGR_BUF_SIZE_MAX   (65280)

/** Sdio 8777 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8777 = {
     /** register */
	.reg = &mlan_reg_sd87xx,
    /** maximum ports */
	.max_ports = 16,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_8,
    /** sdio new mode support */
	.supports_sdio_new_mode = MFALSE,
    /** control mask */
	.has_control_mask = MTRUE,
     /** io port0 register */
	.io_port_0_reg = 0x78,
     /** io port1 register */
	.io_port_1_reg = 0x79,
     /** io port2 register */
	.io_port_2_reg = 0x7A,
     /** host interrupt rsr register */
	.host_int_rsr_reg = 0x01,
     /** card_rx_len_reg */
	.card_rx_len_reg = 0x62,
     /** card rx unit register */
	.card_rx_unit_reg = 0x63,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x02,
    /** host interrupt status register */
	.host_int_status_reg = 0x03,
     /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 0,
    /** V15 firmware api */
	.v15_fw_api = 0,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 0,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_nov15,
};

/** Sdio 8787 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8787 = {
    /** register */
	.reg = &mlan_reg_sd87xx,
    /** maximum ports */
	.max_ports = 16,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_8,
    /** sdio new mode support */
	.supports_sdio_new_mode = MFALSE,
    /** control mask */
	.has_control_mask = MTRUE,
     /** io port0 register */
	.io_port_0_reg = 0x78,
    /** io port1 register */
	.io_port_1_reg = 0x79,
    /** io port2 register */
	.io_port_2_reg = 0x7A,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x01,
    /** card_rx_len_reg */
	.card_rx_len_reg = 0x62,
    /** card rx unit register */
	.card_rx_unit_reg = 0x63,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x02,
    /** host interrupt status register */
	.host_int_status_reg = 0x03,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 0,
    /** V15 firmware api */
	.v15_fw_api = 0,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 0,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_nov15,
};

/** Sdio 8797 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8797 = {
     /** register */
	.reg = &mlan_reg_sd87xx,
    /** maximum ports */
	.max_ports = 16,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_8,
    /** sdio new mode support */
	.supports_sdio_new_mode = MFALSE,
    /** control mask */
	.has_control_mask = MTRUE,
    /** io port0 register */
	.io_port_0_reg = 0x78,
    /** io port1 register */
	.io_port_1_reg = 0x79,
    /** io port2 register */
	.io_port_2_reg = 0x7A,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x01,
    /** card_rx_len_reg */
	.card_rx_len_reg = 0x62,
    /** card rx unit register */
	.card_rx_unit_reg = 0x63,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x02,
    /** host interrupt status register */
	.host_int_status_reg = 0x03,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 0,
    /** V15 firmware api */
	.v15_fw_api = 0,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 0,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_nov15,
};

/** Sdio 8887 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8887 = {
    /** register */
	.reg = &mlan_reg_sd8887,
    /** maximum ports */
	.max_ports = 32,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_16,
    /** sdio new mode support */
	.supports_sdio_new_mode = MTRUE,
    /** control mask */
	.has_control_mask = MFALSE,
    /** card configuration_2_1 register */
	.card_config_2_1_reg = 0xD9,
     /** command configuration register0 */
	.cmd_config_0 = 0xC4,
    /** command configuration register1 */
	.cmd_config_1 = 0xC5,
    /** command read length 0 */
	.cmd_rd_len_0 = 0xC0,
    /** command read length 1 */
	.cmd_rd_len_1 = 0xC1,
    /** io port0 register */
	.io_port_0_reg = 0xE4,
    /** io port1 register */
	.io_port_1_reg = 0xE5,
    /** io port2 register */
	.io_port_2_reg = 0xE6,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x04,
    /** card rx length register */
	.card_rx_len_reg = 0x92,
    /** card rx unit register */
	.card_rx_unit_reg = 0x93,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x08,
    /** host interrupt status register */
	.host_int_status_reg = 0x0C,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 1,
    /** V15 firmware api */
	.v15_fw_api = 1,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 1,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_v15,
};

/** Sdio 8801 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8801 = {
     /** register */
	.reg = &mlan_reg_sd87xx,
    /** maximum ports */
	.max_ports = 16,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_8,
    /** sdio new mode support */
	.supports_sdio_new_mode = MFALSE,
    /** control mask */
	.has_control_mask = MTRUE,
    /** io port0 register */
	.io_port_0_reg = 0x78,
    /** io port1 register */
	.io_port_1_reg = 0x79,
    /** io port0 register */
	.io_port_2_reg = 0x7A,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x01,
    /** card rx length register */
	.card_rx_len_reg = 0x62,
    /** card rx unit register */
	.card_rx_unit_reg = 0x63,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x02,
    /** host interrupt status register */
	.host_int_status_reg = 0x03,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_32K,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 0,
    /** V15 firmware api */
	.v15_fw_api = 0,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 0,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_nov15,
};

/** Sdio 8897 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8897 = {
     /** register */
	.reg = &mlan_reg_sd8897,
     /** maximum ports */
	.max_ports = 32,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_16,
    /** sdio new mode support */
	.supports_sdio_new_mode = MTRUE,
    /** control mask */
	.has_control_mask = MFALSE,
    /** card configuration_2_1 register */
	.card_config_2_1_reg = 0xCD,
    /** command configuration register0 */
	.cmd_config_0 = 0xB8,
    /** command configuration register1 */
	.cmd_config_1 = 0xB9,
    /** command read length 0 */
	.cmd_rd_len_0 = 0xB4,
    /** command read length 1 */
	.cmd_rd_len_1 = 0xB5,
    /** io port0 register */
	.io_port_0_reg = 0xD8,
    /** io port1 register */
	.io_port_1_reg = 0xD9,
    /** io port2 register */
	.io_port_2_reg = 0xDA,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x01,
    /** card rx length register */
	.card_rx_len_reg = 0xC2,
    /** card rx unit register */
	.card_rx_unit_reg = 0xC3,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x02,
    /** host interrupt status register */
	.host_int_status_reg = 0x03,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_4K,
    /** V15 update */
	.v15_update = 1,
    /** V15 firmware api */
	.v15_fw_api = 1,
    /** V16 firmware api */
	.v16_fw_api = 0,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 1,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_v15,
};

/** Sdio 8977 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8977 = {
     /** register */
	.reg = &mlan_reg_sd8977_sd8997,
     /** maximum ports */
	.max_ports = 32,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_16,
    /** sdio new mode support */
	.supports_sdio_new_mode = MTRUE,
    /** control mask */
	.has_control_mask = MFALSE,
    /** card configuration_2_1 register */
	.card_config_2_1_reg = 0xD9,
    /** command configuration register0 */
	.cmd_config_0 = 0xC4,
    /** command configuration register1 */
	.cmd_config_1 = 0xC5,
    /** command read length 0 */
	.cmd_rd_len_0 = 0xC0,
    /** command read length 1 */
	.cmd_rd_len_1 = 0xC1,
    /** io port0 register */
	.io_port_0_reg = 0xE4,
    /** io port1 register */
	.io_port_1_reg = 0xE5,
    /** io port2 register */
	.io_port_2_reg = 0xE6,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x04,
    /** card rx length register */
	.card_rx_len_reg = 0xEA,
    /** card rx unit register */
	.card_rx_unit_reg = 0xEB,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x08,
    /** host interrupt status register */
	.host_int_status_reg = 0x0C,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 1,
    /** V15 firmware api */
	.v15_fw_api = 1,
    /** V16 firmware api */
	.v16_fw_api = 1,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 1,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_v15,
};

/** Sdio 8997 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8997 = {
    /** register */
	.reg = &mlan_reg_sd8977_sd8997,
    /** maximum ports */
	.max_ports = 32,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_16,
    /** sdio new mode support */
	.supports_sdio_new_mode = MTRUE,
    /** control mask */
	.has_control_mask = MFALSE,
    /** card configuration_2_1 register */
	.card_config_2_1_reg = 0xD9,
    /** command configuration register0 */
	.cmd_config_0 = 0xC4,
    /** command configuration register1 */
	.cmd_config_1 = 0xC5,
    /** command read length 0 */
	.cmd_rd_len_0 = 0xC0,
    /** command read length 1 */
	.cmd_rd_len_1 = 0xC1,
    /** io port0 register */
	.io_port_0_reg = 0xE4,
    /** io port1 register */
	.io_port_1_reg = 0xE5,
    /** io port2 register */
	.io_port_2_reg = 0xE6,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x04,
    /** card rx length register */
	.card_rx_len_reg = 0xEA,
    /** card rx unit register */
	.card_rx_unit_reg = 0xEB,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x08,
    /** host interrupt status register */
	.host_int_status_reg = 0x0C,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_4K,
    /** V15 update */
	.v15_update = 1,
    /** V15 firmware api */
	.v15_fw_api = 1,
    /** V16 firmware api */
	.v16_fw_api = 1,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 1,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_v15,
};

/** Sdio 8987 device structure */
static const struct _mlan_sdio_device mlan_sdio_sd8987 = {
    /** register */
	.reg = &mlan_reg_sd8977_sd8997,
    /** maximum ports */
	.max_ports = 32,
    /** mp aggregation packet limit */
	.mp_aggr_pkt_limit = SDIO_MP_AGGR_DEF_PKT_LIMIT_16,
    /** sdio new mode support */
	.supports_sdio_new_mode = MTRUE,
    /** control mask */
	.has_control_mask = MFALSE,
    /** card configuration_2_1 register */
	.card_config_2_1_reg = 0xD9,
    /** command configuration register0 */
	.cmd_config_0 = 0xC4,
    /** command configuration register1 */
	.cmd_config_1 = 0xC5,
    /** command read length 0 */
	.cmd_rd_len_0 = 0xC0,
    /** command read length 1 */
	.cmd_rd_len_1 = 0xC1,
    /** io port0 register */
	.io_port_0_reg = 0xE4,
    /** io port1 register */
	.io_port_1_reg = 0xE5,
    /** io port2 register */
	.io_port_2_reg = 0xE6,
    /** host interrupt rsr register */
	.host_int_rsr_reg = 0x04,
    /** card rx length register */
	.card_rx_len_reg = 0xEA,
    /** card rx unit register */
	.card_rx_unit_reg = 0xEB,
    /** host interrupt mask register */
	.host_int_mask_reg = 0x08,
    /** host interrupt mask register */
	.host_int_status_reg = 0x0C,
    /** mp tx aggregation buffer size */
	.mp_tx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** mp rx aggregation buffer size */
	.mp_rx_aggr_buf_size = SDIO_MP_AGGR_BUF_SIZE_MAX,
    /** maximum tx buffer size */
	.max_tx_buf_size = MLAN_TX_DATA_BUF_SIZE_2K,
    /** V15 update */
	.v15_update = 1,
    /** V15 firmware api */
	.v15_fw_api = 1,
    /** V16 firmware api */
	.v16_fw_api = 1,
    /** extend scan */
	.ext_scan = 1,
    /** firmware relaod */
	.fw_reload = 1,
    /** AMPDU information */
	.ampdu_info = &ampdu_info_v15,
};

/** Enable host interrupt */
mlan_status wlan_enable_host_int(pmlan_adapter pmadapter);
/** Probe and initialization function */
mlan_status wlan_sdio_probe(pmlan_adapter pmadapter);
mlan_status wlan_get_sdio_device(pmlan_adapter pmadapter);
/** multi interface download check */
mlan_status wlan_check_winner_status(mlan_adapter *pmadapter, t_u32 *val);

#ifdef SDIO_MULTI_PORT_TX_AGGR
mlan_status wlan_send_mp_aggr_buf(mlan_adapter *pmadapter);
#endif

/** Firmware status check */
mlan_status wlan_check_fw_status(mlan_adapter *pmadapter, t_u32 pollnum);
/** Read interrupt status */
mlan_status wlan_interrupt(pmlan_adapter pmadapter);
/** Process Interrupt Status */
mlan_status wlan_process_int_status(mlan_adapter *pmadapter);
/** Transfer data to card */
mlan_status wlan_sdio_host_to_card(mlan_adapter *pmadapter, t_u8 type,
				   mlan_buffer *mbuf, mlan_tx_param *tx_param);
mlan_status wlan_set_sdio_gpio_int(IN pmlan_private priv);
mlan_status wlan_cmd_sdio_gpio_int(pmlan_private pmpriv,
				   IN HostCmd_DS_COMMAND *cmd,
				   IN t_u16 cmd_action, IN t_void *pdata_buf);
mlan_status wlan_reset_fw(pmlan_adapter pmadapter);
#endif /* _MLAN_SDIO_H */
