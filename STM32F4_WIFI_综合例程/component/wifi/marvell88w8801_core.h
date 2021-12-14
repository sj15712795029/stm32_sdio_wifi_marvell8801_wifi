#ifndef MARVELL88W8801_H_H_H
#define MARVELL88W8801_H_H_H

#include <stdint.h>
#include "wireless_link_components_conf.h"
#define MBIT(x)    (((uint32_t)1) << (x))


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
#define HOST_INT_RSR_MASK		0x3F

/** Host Control Registers : Host interrupt mask */
#define HOST_INT_MASK_REG		0x02

/** Host Control Registers : Upload host interrupt mask */
#define UP_LD_HOST_INT_MASK		(0x1U)
/** Host Control Registers : Download host interrupt mask */
#define DN_LD_HOST_INT_MASK		(0x2U)
/** Enable Host interrupt mask */
#define HIM_ENABLE			(UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK)
/** Disable Host interrupt mask */
#define	HIM_DISABLE			0xff

/** Host Control Registers : Host interrupt status */
#define HOST_INT_STATUS_REG		0x03

/** Host Control Registers : Upload host interrupt status */
#define UP_LD_HOST_INT_STATUS		(0x1U)
/** Host Control Registers : Download host interrupt status */
#define DN_LD_HOST_INT_STATUS		(0x2U)
/** Host Control Registers : Download and Upload host interrupt status */
#define INT_STATUS_ALL	(UP_LD_HOST_INT_STATUS | DN_LD_HOST_INT_STATUS)

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
#define MAX_PORT			16
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
/** Firmware ready */
#define FIRMWARE_READY          0xfedc
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


/** TLV  type ID definition */
#define PROPRIETARY_TLV_BASE_ID                 0x0100

/** Terminating TLV Type */
#define MRVL_TERMINATE_TLV_ID                   0xffff

/** TLV type : SSID */
#define TLV_TYPE_SSID                           0x0000
/** TLV type : Rates */
#define TLV_TYPE_RATES                          0x0001
/** TLV type : PHY FH */
#define TLV_TYPE_PHY_FH                         0x0002
/** TLV type : PHY DS */
#define TLV_TYPE_PHY_DS                         0x0003
/** TLV type : CF */
#define TLV_TYPE_CF                             0x0004
/** TLV type : IBSS */
#define TLV_TYPE_IBSS                           0x0006
/** TLV type : Domain */
#define TLV_TYPE_DOMAIN                         0x0007
/** TLV type : Power constraint */
#define TLV_TYPE_POWER_CONSTRAINT               0x0020
/** TLV type : Power capability */
#define TLV_TYPE_POWER_CAPABILITY               0x0021
/** TLV type : TLV_TYPE_RSN_PARAMSET*/
#define TLV_TYPE_RSN_PARAMSET				0x0030
/** TLV type : Vendor Specific IE */
#define TLV_TYPE_VENDOR_SPECIFIC_IE             0xdd

/** TLV type : Key material */
#define TLV_TYPE_KEY_MATERIAL       (PROPRIETARY_TLV_BASE_ID + 0x00)    // 0x0100
/** TLV type : Channel list */
#define TLV_TYPE_CHANLIST           (PROPRIETARY_TLV_BASE_ID + 0x01)    // 0x0101
/** TLV type : Number of probes */
#define TLV_TYPE_NUMPROBES          (PROPRIETARY_TLV_BASE_ID + 0x02)    // 0x0102
/** TLV type : Beacon RSSI low */
#define TLV_TYPE_RSSI_LOW           (PROPRIETARY_TLV_BASE_ID + 0x04)    // 0x0104
/** TLV type : Beacon SNR low */
#define TLV_TYPE_SNR_LOW            (PROPRIETARY_TLV_BASE_ID + 0x05)    // 0x0105
/** TLV type : Fail count */
#define TLV_TYPE_FAILCOUNT          (PROPRIETARY_TLV_BASE_ID + 0x06)    // 0x0106
/** TLV type : BCN miss */
#define TLV_TYPE_BCNMISS            (PROPRIETARY_TLV_BASE_ID + 0x07)    // 0x0107
/** TLV type : LED behavior */
#define TLV_TYPE_LEDBEHAVIOR        (PROPRIETARY_TLV_BASE_ID + 0x09)    // 0x0109
/** TLV type : Passthrough */
#define TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 0x0a)    // 0x010a
/** TLV type : Power TBL 2.4 Ghz */
#define TLV_TYPE_POWER_TBL_2_4GHZ   (PROPRIETARY_TLV_BASE_ID + 0x0c)    // 0x010c
/** TLV type : Power TBL 5 GHz */
#define TLV_TYPE_POWER_TBL_5GHZ     (PROPRIETARY_TLV_BASE_ID + 0x0d)    // 0x010d
/** TLV type : WMM queue status */
#define TLV_TYPE_WMMQSTATUS         (PROPRIETARY_TLV_BASE_ID + 0x10)    // 0x0110
/** TLV type : Wildcard SSID */
#define TLV_TYPE_WILDCARDSSID       (PROPRIETARY_TLV_BASE_ID + 0x12)    // 0x0112
/** TLV type : TSF timestamp */
#define TLV_TYPE_TSFTIMESTAMP       (PROPRIETARY_TLV_BASE_ID + 0x13)    // 0x0113
/** TLV type : ARP filter */
#define TLV_TYPE_ARP_FILTER         (PROPRIETARY_TLV_BASE_ID + 0x15)    // 0x0115
/** TLV type : Beacon RSSI high */
#define TLV_TYPE_RSSI_HIGH          (PROPRIETARY_TLV_BASE_ID + 0x16)    // 0x0116
/** TLV type : Beacon SNR high */
#define TLV_TYPE_SNR_HIGH           (PROPRIETARY_TLV_BASE_ID + 0x17)    // 0x0117
/** TLV type : Start BG scan later */
#define TLV_TYPE_STARTBGSCANLATER   (PROPRIETARY_TLV_BASE_ID + 0x1e)    // 0x011e
/** TLV type: BG scan repeat count */
#define TLV_TYPE_REPEAT_COUNT       (PROPRIETARY_TLV_BASE_ID + 0xb0)    // 0x01b0
/** TLV type : Authentication type */
#define TLV_TYPE_AUTH_TYPE          (PROPRIETARY_TLV_BASE_ID + 0x1f)    // 0x011f
/** TLV type : BSSID */
#define TLV_TYPE_BSSID              (PROPRIETARY_TLV_BASE_ID + 0x23)    // 0x0123

/** TLV type : Link Quality */
#define TLV_TYPE_LINK_QUALITY       (PROPRIETARY_TLV_BASE_ID + 0x24)    // 0x0124

/** TLV type : Data RSSI low */
#define TLV_TYPE_RSSI_LOW_DATA      (PROPRIETARY_TLV_BASE_ID + 0x26)    // 0x0126
/** TLV type : Data SNR low */
#define TLV_TYPE_SNR_LOW_DATA       (PROPRIETARY_TLV_BASE_ID + 0x27)    // 0x0127
/** TLV type : Data RSSI high */
#define TLV_TYPE_RSSI_HIGH_DATA     (PROPRIETARY_TLV_BASE_ID + 0x28)    // 0x0128
/** TLV type : Data SNR high */
#define TLV_TYPE_SNR_HIGH_DATA      (PROPRIETARY_TLV_BASE_ID + 0x29)    // 0x0129

/** TLV type : Channel band list */
#define TLV_TYPE_CHANNELBANDLIST    (PROPRIETARY_TLV_BASE_ID + 0x2a)    // 0x012a

/** TLV type : Passphrase */
#define TLV_TYPE_PASSPHRASE         (PROPRIETARY_TLV_BASE_ID + 0x3c)    // 0x013c

/** TLV type : Encryption Protocol TLV */
#define TLV_TYPE_ENCRYPTION_PROTO   (PROPRIETARY_TLV_BASE_ID + 0x40)    // 0x0140
/** TLV type : Cipher TLV */
#define TLV_TYPE_CIPHER             (PROPRIETARY_TLV_BASE_ID + 0x42)    // 0x0142
/** TLV type : PMK */
#define TLV_TYPE_PMK                (PROPRIETARY_TLV_BASE_ID + 0x44)    // 0x0144

/** TLV type : BCN miss */
#define TLV_TYPE_PRE_BCNMISS         (PROPRIETARY_TLV_BASE_ID + 0x49)   // 0x0149

/** TLV type: WAPI IE */
#define TLV_TYPE_WAPI_IE             (PROPRIETARY_TLV_BASE_ID + 0x5e)   // 0x015e

/** TLV type: MGMT IE */
#define TLV_TYPE_MGMT_IE             (PROPRIETARY_TLV_BASE_ID + 0x69)   // 0x0169
/** TLV type: MAX_MGMT_IE */
#define TLV_TYPE_MAX_MGMT_IE         (PROPRIETARY_TLV_BASE_ID + 0xaa)   // 0x01aa

/** TLV type : HT Capabilities */
#define TLV_TYPE_HT_CAP                  (PROPRIETARY_TLV_BASE_ID + 0x4a)       // 0x014a
/** TLV type : HT Information */
#define TLV_TYPE_HT_INFO                 (PROPRIETARY_TLV_BASE_ID + 0x4b)       // 0x014b
/** TLV type : Secondary Channel Offset */
#define TLV_SECONDARY_CHANNEL_OFFSET     (PROPRIETARY_TLV_BASE_ID + 0x4c)       // 0x014c
/** TLV type : 20/40 BSS Coexistence */
#define TLV_TYPE_2040BSS_COEXISTENCE     (PROPRIETARY_TLV_BASE_ID + 0x4d)       // 0x014d
/** TLV type : Overlapping BSS Scan Parameters */
#define TLV_TYPE_OVERLAP_BSS_SCAN_PARAM  (PROPRIETARY_TLV_BASE_ID + 0x4e)       // 0x014e
/** TLV type : Extended capabilities */
#define TLV_TYPE_EXTCAP                  (PROPRIETARY_TLV_BASE_ID + 0x4f)       // 0x014f
/** TLV type : Set of MCS values that STA desires to use within the BSS */
#define TLV_TYPE_HT_OPERATIONAL_MCS_SET  (PROPRIETARY_TLV_BASE_ID + 0x50)       // 0x0150
/** TLV type : RXBA_SYNC */
#define TLV_TYPE_RXBA_SYNC               (PROPRIETARY_TLV_BASE_ID + 0x99)       // 0x0199
/** ADDBA TID mask */
#define ADDBA_TID_MASK   (MBIT(2) | MBIT(3) | MBIT(4) | MBIT(5))
/** DELBA TID mask */
#define DELBA_TID_MASK   (MBIT(12) | MBIT(13) | MBIT(14) | MBIT(15))
/** ADDBA Starting Sequence Number Mask */
#define SSN_MASK         0xfff0
/** TLV type : AP Channel band Config */
#define TLV_TYPE_UAP_CHAN_BAND_CONFIG (PROPRIETARY_TLV_BASE_ID + 0x2a)  // 0x012a
/** TLV type : AP Mac address */
#define TLV_TYPE_UAP_MAC_ADDRESS      (PROPRIETARY_TLV_BASE_ID + 0x2b)  // 0x012b
/** TLV type : AP Beacon period */
#define TLV_TYPE_UAP_BEACON_PERIOD    (PROPRIETARY_TLV_BASE_ID + 0x2c)  // 0x012c
/** TLV type : AP DTIM period */
#define TLV_TYPE_UAP_DTIM_PERIOD      (PROPRIETARY_TLV_BASE_ID + 0x2d)  // 0x012d
/** TLV type : AP Tx power */
#define TLV_TYPE_UAP_TX_POWER         (PROPRIETARY_TLV_BASE_ID + 0x2f)  // 0x012f
/** TLV type : AP SSID broadcast control */
#define TLV_TYPE_UAP_BCAST_SSID_CTL   (PROPRIETARY_TLV_BASE_ID + 0x30)  // 0x0130
/** TLV type : AP Preamble control */
#define TLV_TYPE_UAP_PREAMBLE_CTL     (PROPRIETARY_TLV_BASE_ID + 0x31)  // 0x0131
/** TLV type : AP Antenna control */
#define TLV_TYPE_UAP_ANTENNA_CTL      (PROPRIETARY_TLV_BASE_ID + 0x32)  // 0x0132
/** TLV type : AP RTS threshold */
#define TLV_TYPE_UAP_RTS_THRESHOLD    (PROPRIETARY_TLV_BASE_ID + 0x33)  // 0x0133
/** TLV type : AP Tx data rate */
#define TLV_TYPE_UAP_TX_DATA_RATE     (PROPRIETARY_TLV_BASE_ID + 0x35)  // 0x0135
/** TLV type: AP Packet forwarding control */
#define TLV_TYPE_UAP_PKT_FWD_CTL      (PROPRIETARY_TLV_BASE_ID + 0x36)  // 0x0136
/** TLV type: STA information */
#define TLV_TYPE_UAP_STA_INFO         (PROPRIETARY_TLV_BASE_ID + 0x37)  // 0x0137
/** TLV type: AP STA MAC address filter */
#define TLV_TYPE_UAP_STA_MAC_ADDR_FILTER (PROPRIETARY_TLV_BASE_ID + 0x38)       // 0x0138
/** TLV type: AP STA ageout timer */
#define TLV_TYPE_UAP_STA_AGEOUT_TIMER (PROPRIETARY_TLV_BASE_ID + 0x39)  // 0x0139
/** TLV type: AP WEP keys */
#define TLV_TYPE_UAP_WEP_KEY          (PROPRIETARY_TLV_BASE_ID + 0x3b)  // 0x013b
/** TLV type: AP WPA passphrase */
#define TLV_TYPE_UAP_WPA_PASSPHRASE   (PROPRIETARY_TLV_BASE_ID + 0x3c)  // 0x013c
/** TLV type: AP protocol */
#define TLV_TYPE_UAP_ENCRYPT_PROTOCOL (PROPRIETARY_TLV_BASE_ID + 0x40)  // 0x0140
/** TLV type: AP AKMP */
#define TLV_TYPE_UAP_AKMP             (PROPRIETARY_TLV_BASE_ID + 0x41)  // 0x0141
/** TLV type: AP Fragment threshold */
#define TLV_TYPE_UAP_FRAG_THRESHOLD   (PROPRIETARY_TLV_BASE_ID + 0x46)  // 0x0146
/** TLV type: AP Group rekey timer */
#define TLV_TYPE_UAP_GRP_REKEY_TIME   (PROPRIETARY_TLV_BASE_ID + 0x47)  // 0x0147
/**TLV type : AP Max Station number */
#define TLV_TYPE_UAP_MAX_STA_CNT      (PROPRIETARY_TLV_BASE_ID + 0x55)  // 0x0155
/**TLV type : AP Retry limit */
#define TLV_TYPE_UAP_RETRY_LIMIT      (PROPRIETARY_TLV_BASE_ID + 0x5d)  // 0x015d
/** TLV type : AP MCBC data rate */
#define TLV_TYPE_UAP_MCBC_DATA_RATE   (PROPRIETARY_TLV_BASE_ID + 0x62)  // 0x0162
/**TLV type: AP RSN replay protection */
#define TLV_TYPE_UAP_RSN_REPLAY_PROTECT  (PROPRIETARY_TLV_BASE_ID + 0x64)       // 0x0164
/** TLV ID : Management Frame */
#define TLV_TYPE_UAP_MGMT_FRAME          (PROPRIETARY_TLV_BASE_ID + 0x68)       // 0x0168
/**TLV type: AP mgmt IE passthru mask */
#define TLV_TYPE_UAP_MGMT_IE_PASSTHRU_MASK  (PROPRIETARY_TLV_BASE_ID + 0x70)    // 0x0170
/** TLV : 20/40 coex config */
#define TLV_TYPE_2040_BSS_COEX_CONTROL      (PROPRIETARY_TLV_BASE_ID + 0x98)    // 0x0198
/**TLV type: AP pairwise handshake timeout */
#define TLV_TYPE_UAP_EAPOL_PWK_HSK_TIMEOUT  (PROPRIETARY_TLV_BASE_ID + 0x75)    // 0x0175
/**TLV type: AP pairwise handshake retries */
#define TLV_TYPE_UAP_EAPOL_PWK_HSK_RETRIES  (PROPRIETARY_TLV_BASE_ID + 0x76)    // 0x0176
/**TLV type: AP groupwise handshake timeout */
#define TLV_TYPE_UAP_EAPOL_GWK_HSK_TIMEOUT  (PROPRIETARY_TLV_BASE_ID + 0x77)    // 0x0177
/**TLV type: AP groupwise handshake retries */
#define TLV_TYPE_UAP_EAPOL_GWK_HSK_RETRIES  (PROPRIETARY_TLV_BASE_ID + 0x78)    // 0x0178
/** TLV type: AP PS STA ageout timer */
#define TLV_TYPE_UAP_PS_STA_AGEOUT_TIMER (PROPRIETARY_TLV_BASE_ID + 0x7b)       // 0x017b
/** TLV type : Pairwise Cipher */
#define TLV_TYPE_PWK_CIPHER              (PROPRIETARY_TLV_BASE_ID + 0x91)       // 0x0191
/** TLV type : Group Cipher */
#define TLV_TYPE_GWK_CIPHER              (PROPRIETARY_TLV_BASE_ID + 0x92)       // 0x0192
/** TLV type : BSS Status */
#define TLV_TYPE_BSS_STATUS              (PROPRIETARY_TLV_BASE_ID + 0x93)       // 0x0193


/** Block Ack result status */
/** Block Ack Result : Success */
#define BA_RESULT_SUCCESS        0x0
/** Block Ack Result : Execution failure */
#define BA_RESULT_FAILURE        0x1
/** Block Ack Result : Timeout */
#define BA_RESULT_TIMEOUT        0x2
/** Block Ack Result : Data invalid */
#define BA_RESULT_DATA_INVALID   0x3

/** Get the baStatus (NOT_SETUP, COMPLETE, IN_PROGRESS)
 *  in Tx BA stream table */
#define IS_BASTREAM_SETUP(ptr)  (ptr->ba_status)

/** An AMPDU/AMSDU could be disallowed for certain TID. 0xff means
 *  no aggregation is enabled for the assigned TID */
#define BA_STREAM_NOT_ALLOWED   0xff
#define BAND_B       (1U << 0)
#define BAND_G       (1U << 1)
#define BAND_A       (1U << 2)
#define BAND_GN      (1U << 3)
#define BAND_AN      (1U << 4)
/** Position of INITIATOR in DelBA Param set */
#define DELBA_INITIATOR_POS		11
/** Test if 11n is enabled by checking the HTCap IE */
#define IS_11N_ENABLED(priv) ((priv->config_bands & BAND_GN ||priv->config_bands & BAND_AN) \
        && priv->curr_bss_params.bss_descriptor.pht_cap)
/** Find out if we are the initiator or not */
#define INITIATOR_BIT(DelBAParamSet) (((DelBAParamSet) & \
                        MBIT(DELBA_INITIATOR_POS)) >> DELBA_INITIATOR_POS)

/** 4K buf size */
#define MLAN_TX_DATA_BUF_SIZE_4K        4096
/** 8K buf size */
#define MLAN_TX_DATA_BUF_SIZE_8K        8192
/** Max Rx AMPDU Size */
#define MAX_RX_AMPDU_SIZE_64K   0x03
/** Non green field station */
#define NON_GREENFIELD_STAS     0x04

/** Greenfield support */
#define HWSPEC_GREENFIELD_SUPP	 MBIT(29)
/** RX STBC support */
#define HWSPEC_RXSTBC_SUPP	 MBIT(26)
/** ShortGI @ 40Mhz support */
#define HWSPEC_SHORTGI40_SUPP	 MBIT(24)
/** ShortGI @ 20Mhz support */
#define HWSPEC_SHORTGI20_SUPP	 MBIT(23)
/** Channel width 40Mhz support */
#define HWSPEC_CHANBW40_SUPP	 MBIT(17)
/** 40Mhz intolarent enable */
#define CAPINFO_40MHZ_INTOLARENT MBIT(8)

/** Default 11n capability mask for 2.4GHz */
#define DEFAULT_11N_CAP_MASK_BG (HWSPEC_SHORTGI20_SUPP | HWSPEC_RXSTBC_SUPP)
/** Default 11n capability mask for 5GHz */
#define DEFAULT_11N_CAP_MASK_A  (HWSPEC_CHANBW40_SUPP | HWSPEC_SHORTGI20_SUPP | \
                                 HWSPEC_SHORTGI40_SUPP | HWSPEC_RXSTBC_SUPP)
/** Bits to ignore in hw_dev_cap as these bits are set in get_hw_spec */
#define IGN_HW_DEV_CAP		(CAPINFO_40MHZ_INTOLARENT)

/** HW_SPEC FwCapInfo */
#define ISSUPP_11NENABLED(FwCapInfo) (FwCapInfo & MBIT(11))

/** HW_SPEC Dot11nDevCap : MAX AMSDU supported */
#define ISSUPP_MAXAMSDU(Dot11nDevCap) (Dot11nDevCap & MBIT(31))
/** HW_SPEC Dot11nDevCap : Beamforming support */
#define ISSUPP_BEAMFORMING(Dot11nDevCap) (Dot11nDevCap & MBIT(30))
/** HW_SPEC Dot11nDevCap : Green field support */
#define ISSUPP_GREENFIELD(Dot11nDevCap) (Dot11nDevCap & MBIT(29))
/** HW_SPEC Dot11nDevCap : AMPDU support */
#define ISSUPP_AMPDU(Dot11nDevCap) (Dot11nDevCap & MBIT(28))
/** HW_SPEC Dot11nDevCap : MIMO PS support  */
#define ISSUPP_MIMOPS(Dot11nDevCap) (Dot11nDevCap & MBIT(27))
/** HW_SPEC Dot11nDevCap : Rx STBC support */
#define ISSUPP_RXSTBC(Dot11nDevCap) (Dot11nDevCap & MBIT(26))
/** HW_SPEC Dot11nDevCap : Tx STBC support */
#define ISSUPP_TXSTBC(Dot11nDevCap) (Dot11nDevCap & MBIT(25))
/** HW_SPEC Dot11nDevCap : Short GI @ 40Mhz support */
#define ISSUPP_SHORTGI40(Dot11nDevCap) (Dot11nDevCap & MBIT(24))
/** HW_SPEC Dot11nDevCap : Short GI @ 20Mhz support */
#define ISSUPP_SHORTGI20(Dot11nDevCap) (Dot11nDevCap & MBIT(23))
/** HW_SPEC Dot11nDevCap : Rx LDPC support */
#define ISSUPP_RXLDPC(Dot11nDevCap) (Dot11nDevCap & MBIT(22))
/** HW_SPEC Dot11nDevCap : Delayed ACK */
#define GET_DELAYEDBACK(Dot11nDevCap) (((Dot11nDevCap >> 20) & 0x03))
/** HW_SPEC Dot11nDevCap : Immediate ACK */
#define GET_IMMEDIATEBACK(Dot11nDevCap) (((Dot11nDevCap >> 18) & 0x03))
/** HW_SPEC Dot11nDevCap : Channel BW support @ 40Mhz  support */
#define ISSUPP_CHANWIDTH40(Dot11nDevCap) (Dot11nDevCap & MBIT(17))
/** HW_SPEC Dot11nDevCap : Channel BW support @ 20Mhz  support */
#define ISSUPP_CHANWIDTH20(Dot11nDevCap) (Dot11nDevCap & MBIT(16))
/** HW_SPEC Dot11nDevCap : Channel BW support @ 10Mhz  support */
#define ISSUPP_CHANWIDTH10(Dot11nDevCap) (Dot11nDevCap & MBIT(15))
/** Dot11nUsrCap : 40Mhz intolarance enabled */
#define ISENABLED_40MHZ_INTOLARENT(Dot11nDevCap) (Dot11nDevCap & MBIT(8))
/** HW_SPEC Dot11nDevCap : Rx AntennaD support */
#define ISSUPP_RXANTENNAD(Dot11nDevCap) (Dot11nDevCap & MBIT(7))
/** HW_SPEC Dot11nDevCap : Rx AntennaC support */
#define ISSUPP_RXANTENNAC(Dot11nDevCap) (Dot11nDevCap & MBIT(6))
/** HW_SPEC Dot11nDevCap : Rx AntennaB support */
#define ISSUPP_RXANTENNAB(Dot11nDevCap) (Dot11nDevCap & MBIT(5))
/** HW_SPEC Dot11nDevCap : Rx AntennaA support */
#define ISSUPP_RXANTENNAA(Dot11nDevCap) (Dot11nDevCap & MBIT(4))
/** HW_SPEC Dot11nDevCap : Tx AntennaD support */
#define ISSUPP_TXANTENNAD(Dot11nDevCap) (Dot11nDevCap & MBIT(3))
/** HW_SPEC Dot11nDevCap : Tx AntennaC support */
#define ISSUPP_TXANTENNAC(Dot11nDevCap) (Dot11nDevCap & MBIT(2))
/** HW_SPEC Dot11nDevCap : Tx AntennaB support */
#define ISSUPP_TXANTENNAB(Dot11nDevCap) (Dot11nDevCap & MBIT(1))
/** HW_SPEC Dot11nDevCap : Tx AntennaA support */
#define ISSUPP_TXANTENNAA(Dot11nDevCap) (Dot11nDevCap & MBIT(0))

/** HW_SPEC Dot11nDevCap : Set support of channel bw @ 40Mhz */
#define SETSUPP_CHANWIDTH40(Dot11nDevCap) (Dot11nDevCap |= MBIT(17))
/** HW_SPEC Dot11nDevCap : Reset support of channel bw @ 40Mhz */
#define RESETSUPP_CHANWIDTH40(Dot11nDevCap) (Dot11nDevCap &= ~MBIT(17))

/** DevMCSSupported : Tx MCS supported */
#define GET_TXMCSSUPP(DevMCSSupported) (DevMCSSupported >> 4)
/** DevMCSSupported : Rx MCS supported */
#define GET_RXMCSSUPP(DevMCSSupported) (DevMCSSupported & 0x0f)

/** GET HTCapInfo : Supported Channel BW */
#define GETHT_SUPPCHANWIDTH(HTCapInfo) (HTCapInfo & MBIT(1))
/** GET HTCapInfo : Support for Greenfield */
#define GETHT_GREENFIELD(HTCapInfo) (HTCapInfo & MBIT(4))
/** GET HTCapInfo : Support for Short GI @ 20Mhz */
#define GETHT_SHORTGI20(HTCapInfo) (HTCapInfo & MBIT(5))
/** GET HTCapInfo : Support for Short GI @ 40Mhz */
#define GETHT_SHORTGI40(HTCapInfo) (HTCapInfo & MBIT(6))
/** GET HTCapInfo : Support for Tx STBC */
#define GETHT_TXSTBC(HTCapInfo) (HTCapInfo & MBIT(7))

/** GET HTCapInfo : Support for Rx STBC */
#define GETHT_RXSTBC(HTCapInfo) ((HTCapInfo >> 8) & 0x03)
/** GET HTCapInfo : Support for Delayed ACK */
#define GETHT_DELAYEDBACK(HTCapInfo) (HTCapInfo & MBIT(10))
/** GET HTCapInfo : Support for Max AMSDU */
#define GETHT_MAXAMSDU(HTCapInfo) (HTCapInfo & MBIT(11))

/** SET HTCapInfo : Set support for LDPC coding capability */
#define SETHT_LDPCCODINGCAP(HTCapInfo) (HTCapInfo |= MBIT(0))
/** SET HTCapInfo : Set support for Channel BW */
#define SETHT_SUPPCHANWIDTH(HTCapInfo) (HTCapInfo |= MBIT(1))
/** SET HTCapInfo : Set support for Greenfield */
#define SETHT_GREENFIELD(HTCapInfo) (HTCapInfo |= MBIT(4))
/** SET HTCapInfo : Set support for Short GI @ 20Mhz */
#define SETHT_SHORTGI20(HTCapInfo) (HTCapInfo |= MBIT(5))
/** SET HTCapInfo : Set support for Short GI @ 40Mhz */
#define SETHT_SHORTGI40(HTCapInfo) (HTCapInfo |= MBIT(6))
/** SET HTCapInfo : Set support for Tx STBC */
#define SETHT_TXSTBC(HTCapInfo) (HTCapInfo |= MBIT(7))
/** SET HTCapInfo : Set support for Rx STBC */
#define SETHT_RXSTBC(HTCapInfo, value) (HTCapInfo |= (value << 8))
/** SET HTCapInfo : Set support for delayed block ack */
#define SETHT_DELAYEDBACK(HTCapInfo) (HTCapInfo |= MBIT(10))
/** SET HTCapInfo : Set support for Max size AMSDU */
#define SETHT_MAXAMSDU(HTCapInfo) (HTCapInfo |= MBIT(11))
/** SET HTCapInfo : Set support for DSSS/CCK Rates @ 40Mhz */
#define SETHT_DSSSCCK40(HTCapInfo) (HTCapInfo |= MBIT(12))
/** SET HTCapInfo : Enable 40Mhz Intolarence */
#define SETHT_40MHZ_INTOLARANT(HTCapInfo) (HTCapInfo |= MBIT(14))

/** RESET HTCapInfo : Set support for LDPC coding capability */
#define RESETHT_LDPCCODINGCAP(HTCapInfo) (HTCapInfo &= ~MBIT(0))
/** RESET HTCapInfo : Set support for Channel BW */
#define RESETHT_SUPPCHANWIDTH(HTCapInfo) (HTCapInfo &= ~MBIT(1))
/** RESET HTCapInfo : Set support for Greenfield */
#define RESETHT_GREENFIELD(HTCapInfo) (HTCapInfo &= ~MBIT(4))
/** RESET HTCapInfo : Set support for Short GI @ 20Mhz */
#define RESETHT_SHORTGI20(HTCapInfo) (HTCapInfo &= ~MBIT(5))
/** RESET HTCapInfo : Set support for Short GI @ 40Mhz */
#define RESETHT_SHORTGI40(HTCapInfo) (HTCapInfo &= ~MBIT(6))
/** RESET HTCapInfo : Set support for Tx STBC */
#define RESETHT_TXSTBC(HTCapInfo) (HTCapInfo &= ~MBIT(7))
/** RESET HTCapInfo : Set support for Rx STBC */
#define RESETHT_RXSTBC(HTCapInfo) (HTCapInfo &= ~(0x03 << 8))
/** RESET HTCapInfo : Set support for delayed block ack */
#define RESETHT_DELAYEDBACK(HTCapInfo) (HTCapInfo &= ~MBIT(10))
/** RESET HTCapInfo : Set support for Max size AMSDU */
#define RESETHT_MAXAMSDU(HTCapInfo) (HTCapInfo &= ~MBIT(11))
/** RESET HTCapInfo : Disable 40Mhz Intolarence */
#define RESETHT_40MHZ_INTOLARANT(HTCapInfo) (HTCapInfo &= ~MBIT(14))
/** RESET HTExtCap : Clear RD Responder bit */
#define RESETHT_EXTCAP_RDG(HTExtCap) (HTExtCap &= ~MBIT(11))
/** SET MCS32 */
#define SETHT_MCS32(x) (x[4] |= 1)
/** Set mcs set defined bit */
#define SETHT_MCS_SET_DEFINED(x) (x[12] |= 1)
/** Set the highest Rx data rate */
#define SETHT_RX_HIGHEST_DT_SUPP(x, y) ((*(uint16_t *) (x + 10)) = y)
/** AMPDU factor size */
#define AMPDU_FACTOR_64K	0x03
/** Set AMPDU size in A-MPDU paramter field */
#define SETAMPDU_SIZE(x, y) do { \
	x = x & ~0x03; \
	x |= y & 0x03; \
} while (0) \
/** Set AMPDU spacing in A-MPDU paramter field */
#define SETAMPDU_SPACING(x, y) do { \
	x = x & ~0x1c; \
	x |= (y & 0x07) << 2; \
} while (0) \

/** RadioType : Support for Band A */
#define ISSUPP_BANDA(FwCapInfo) (FwCapInfo & MBIT(10))
/** RadioType : Support for 40Mhz channel BW */
#define ISALLOWED_CHANWIDTH40(Field2) (Field2 & MBIT(2))
/** RadioType : Set support 40Mhz channel */
#define SET_CHANWIDTH40(Field2) (Field2 |= MBIT(2))
/** RadioType : Reset support 40Mhz channel */
#define RESET_CHANWIDTH40(Field2) (Field2 &= ~(MBIT(0) | MBIT(1) | MBIT(2)))
/** RadioType : Get secondary channel */
#define GET_SECONDARYCHAN(Field2) (Field2 & (MBIT(0) | MBIT(1)))
/** RadioType : Set secondary channel */
#define SET_SECONDARYCHAN(RadioType, SECCHAN) (RadioType |= (SECCHAN << 4))

/* WiFi命令字段位定义 */
// Capability information
#define WIFI_CAPABILITY_ESS MBIT(0)
#define WIFI_CAPABILITY_IBSS MBIT(1)
#define WIFI_CAPABILITY_CF_POLLABLE MBIT(2)
#define WIFI_CAPABILITY_CF_POLL_REQUEST MBIT(3)
#define WIFI_CAPABILITY_PRIVACY MBIT(4)
#define WIFI_CAPABILITY_SHORT_PREAMBLE MBIT(5)
#define WIFI_CAPABILITY_PBCC MBIT(6)
#define WIFI_CAPABILITY_CHANNEL_AGILITY MBIT(7)
#define WIFI_CAPABILITY_SPECTRUM_MGMT MBIT(8)
#define WIFI_CAPABILITY_SHORT_SLOT MBIT(10)
#define WIFI_CAPABILITY_DSSS_OFDM MBIT(13)

/** LLC/SNAP header len   */
#define LLC_SNAP_LEN    8

/** TLV type : Rate scope */
#define TLV_TYPE_RATE_DROP_PATTERN  (PROPRIETARY_TLV_BASE_ID + 0x51)    // 0x0151
/** TLV type : Rate drop pattern */
#define TLV_TYPE_RATE_DROP_CONTROL  (PROPRIETARY_TLV_BASE_ID + 0x52)    // 0x0152
/** TLV type : Rate scope */
#define TLV_TYPE_RATE_SCOPE         (PROPRIETARY_TLV_BASE_ID + 0x53)    // 0x0153

/** TLV type : Power group */
#define TLV_TYPE_POWER_GROUP        (PROPRIETARY_TLV_BASE_ID + 0x54)    // 0x0154

/** Modulation class for DSSS Rates */
#define MOD_CLASS_HR_DSSS       0x03
/** Modulation class for OFDM Rates */
#define MOD_CLASS_OFDM          0x07
/** Modulation class for HT Rates */
#define MOD_CLASS_HT            0x08
/** HT bandwidth 20 MHz */
#define HT_BW_20    0
/** HT bandwidth 40 MHz */
#define HT_BW_40    1

/** TLV type : Scan Response */
#define TLV_TYPE_BSS_SCAN_RSP        (PROPRIETARY_TLV_BASE_ID + 0x56)   // 0x0156
/** TLV type : Scan Response Stats */
#define TLV_TYPE_BSS_SCAN_INFO       (PROPRIETARY_TLV_BASE_ID + 0x57)   // 0x0157

/** TLV type : 11h Basic Rpt */
#define TLV_TYPE_CHANRPT_11H_BASIC   (PROPRIETARY_TLV_BASE_ID + 0x5b)   // 0x015b

/** TLV type : Action frame */
#define TLV_TYPE_IEEE_ACTION_FRAME   (PROPRIETARY_TLV_BASE_ID + 0x8c)   // 0x018c



/* 2. 命令ID */
/** Firmware Host Command ID Constants */
/** Host Command ID : Get hardware specifications */
#define HostCmd_CMD_GET_HW_SPEC               0x0003
/** Host Command ID : 802.11 scan */
#define HostCmd_CMD_802_11_SCAN               0x0006
/** Host Command ID : 802.11 get log */
#define HostCmd_CMD_802_11_GET_LOG            0x000b
/** Host Command ID : MAC multicast address */
#define HostCmd_CMD_MAC_MULTICAST_ADR         0x0010
/** Host Command ID : 802.11 EEPROM access */
#define HostCmd_CMD_802_11_EEPROM_ACCESS      0x0059
/** Host Command ID : 802.11 associate */
#define HostCmd_CMD_802_11_ASSOCIATE          0x0012

/** Host Command ID : 802.11 SNMP MIB */
#define HostCmd_CMD_802_11_SNMP_MIB           0x0016
/** Host Command ID : MAC register access */
#define HostCmd_CMD_MAC_REG_ACCESS            0x0019
/** Host Command ID : BBP register access */
#define HostCmd_CMD_BBP_REG_ACCESS            0x001a
/** Host Command ID : RF register access */
#define HostCmd_CMD_RF_REG_ACCESS             0x001b

/** Host Command ID : 802.11 radio control */
#define HostCmd_CMD_802_11_RADIO_CONTROL      0x001c
/** Host Command ID : 802.11 RF channel */
#define HostCmd_CMD_802_11_RF_CHANNEL         0x001d
/** Host Command ID : 802.11 RF Tx power */
#define HostCmd_CMD_802_11_RF_TX_POWER        0x001e

/** Host Command ID : 802.11 RF antenna */
#define HostCmd_CMD_802_11_RF_ANTENNA         0x0020

/** Host Command ID : 802.11 deauthenticate */
#define HostCmd_CMD_802_11_DEAUTHENTICATE     0x0024
/** Host Command ID: 802.11 disassoicate */
#define HostCmd_CMD_802_11_DISASSOCIATE       0x0026
/** Host Command ID : MAC control */
#define HostCmd_CMD_MAC_CONTROL               0x0028
/** Host Command ID : 802.11 Ad-Hoc start */
#define HostCmd_CMD_802_11_AD_HOC_START       0x002b
/** Host Command ID : 802.11 Ad-Hoc join */
#define HostCmd_CMD_802_11_AD_HOC_JOIN        0x002c

/** Host Command ID : 802.11 key material */
#define HostCmd_CMD_802_11_KEY_MATERIAL       0x005e

/** Host Command ID : 802.11 Ad-Hoc stop */
#define HostCmd_CMD_802_11_AD_HOC_STOP        0x0040

/** Host Command ID : 802.22 MAC address */
#define HostCmd_CMD_802_11_MAC_ADDRESS        0x004d

/** Host Command ID : WMM Traffic Stream Status */
#define HostCmd_CMD_WMM_TS_STATUS             0x005d

/** Host Command ID : 802.11 D domain information */
#define HostCmd_CMD_802_11D_DOMAIN_INFO       0x005b

/** Host Command ID : 802.11 sleep parameters */
#define HostCmd_CMD_802_11_SLEEP_PARAMS       0x0066

/** Host Command ID : 802.11 sleep period */
#define HostCmd_CMD_802_11_SLEEP_PERIOD       0x0068

/** Host Command ID: 802.11 BG scan config */
#define HostCmd_CMD_802_11_BG_SCAN_CONFIG     0x006b
/** Host Command ID : 802.11 BG scan query */
#define HostCmd_CMD_802_11_BG_SCAN_QUERY      0x006c

/** Host Command ID : WMM ADDTS req */
#define HostCmd_CMD_WMM_ADDTS_REQ             0x006E
/** Host Command ID : WMM DELTS req */
#define HostCmd_CMD_WMM_DELTS_REQ             0x006F
/** Host Command ID : WMM queue configuration */
#define HostCmd_CMD_WMM_QUEUE_CONFIG          0x0070
/** Host Command ID : 802.11 get status */
#define HostCmd_CMD_WMM_GET_STATUS            0x0071

/** Host Command ID : 802.11 subscribe event */
#define HostCmd_CMD_802_11_SUBSCRIBE_EVENT    0x0075

/** Host Command ID : 802.11 Tx rate query */
#define HostCmd_CMD_802_11_TX_RATE_QUERY      0x007f

/** Host Command ID : WMM queue stats */
#define HostCmd_CMD_WMM_QUEUE_STATS           0x0081

/** Host Command ID : 802.11 IBSS coalescing status */
#define HostCmd_CMD_802_11_IBSS_COALESCING_STATUS 0x0083

/** Host Command ID : Memory access */
#define HostCmd_CMD_MEM_ACCESS                0x0086

/** Host Command ID : SDIO GPIO interrupt configuration */
#define HostCmd_CMD_SDIO_GPIO_INT_CONFIG      0x0088

/** Host Command ID : Mfg command */
#define HostCmd_CMD_MFG_COMMAND               0x0089

/** Host Command ID : Inactivity timeout ext */
#define HostCmd_CMD_INACTIVITY_TIMEOUT_EXT    0x008a

/** Host Command ID : DBGS configuration */
#define HostCmd_CMD_DBGS_CFG                  0x008b
/** Host Command ID : Get memory */
#define HostCmd_CMD_GET_MEM                   0x008c

/** Host Command ID : Cal data dnld */
#define HostCmd_CMD_CFG_DATA                  0x008f

/** Host Command ID : SDIO pull control */
#define HostCmd_CMD_SDIO_PULL_CTRL            0x0093

/** Host Command ID : ECL system clock configuration */
#define HostCmd_CMD_ECL_SYSTEM_CLOCK_CONFIG   0x0094

/** Host Command ID : Extended version */
#define HostCmd_CMD_VERSION_EXT               0x0097

/** Host Command ID : MEF configuration */
#define HostCmd_CMD_MEF_CFG                   0x009a

/** Host Command ID : 802.11 RSSI INFO*/
#define HostCmd_CMD_RSSI_INFO                 0x00a4

/** Host Command ID : Function initialization */
#define HostCmd_CMD_FUNC_INIT                 0x00a9
/** Host Command ID : Function shutdown */
#define HostCmd_CMD_FUNC_SHUTDOWN             0x00aa

/** Host Command ID :EAPOL PKT */
#define HostCmd_CMD_802_11_EAPOL_PKT    			0x012e

/** Host Command ID: SUPPLICANT_PMK */
#define HostCmd_CMD_SUPPLICANT_PMK            0x00c4
/** Host Command ID: SUPPLICANT_PROFILE */
#define HostCmd_CMD_SUPPLICANT_PROFILE        0x00c5

/** Host Command ID : Add Block Ack Request */
#define HostCmd_CMD_11N_ADDBA_REQ             0x00ce
/** Host Command ID : Delete a Block Ack Request */
#define HostCmd_CMD_11N_CFG                   0x00cd
/** Host Command ID : Add Block Ack Response */
#define HostCmd_CMD_11N_ADDBA_RSP             0x00cf
/** Host Command ID : Delete a Block Ack Request */
#define HostCmd_CMD_11N_DELBA                 0x00d0
/** Host Command ID: Configure Tx Buf size */
#define HostCmd_CMD_RECONFIGURE_TX_BUFF       0x00d9
/** Host Command ID: AMSDU Aggr Ctrl */
#define HostCmd_CMD_AMSDU_AGGR_CTRL           0x00df

/** Host Command ID : 802.11 TX power configuration */
#define HostCmd_CMD_TXPWR_CFG                 0x00d1

/** Host Command ID : Soft Reset */
#define  HostCmd_CMD_SOFT_RESET               0x00d5

/** Host Command ID : 802.11 b/g/n rate configration */
#define HostCmd_CMD_TX_RATE_CFG               0x00d6

/** Host Command ID : Enhanced PS mode */
#define HostCmd_CMD_802_11_PS_MODE_ENH        0x00e4

/** Host command action : Host sleep configuration */
#define HostCmd_CMD_802_11_HS_CFG_ENH         0x00e5

/** Host Command ID : CAU register access */
#define HostCmd_CMD_CAU_REG_ACCESS            0x00ed

/** Host Command ID : mgmt IE list */
#define  HostCmd_CMD_MGMT_IE_LIST             0x00f2

/** Host Command ID : Rx packet coalescing configuration */
#define HostCmd_CMD_RX_PKT_COALESCE_CFG       0x012c

/** Host Command ID : Forward mgmt frame */
#define HostCmd_CMD_RX_MGMT_IND               0x010c

/** Host Command ID : Set BSS_MODE */
#define HostCmd_CMD_SET_BSS_MODE               0x00f7

/**  Host Command id: SYS_INFO */
#define HOST_CMD_APCMD_SYS_INFO                0x00ae
/** Host Command id: sys_reset */
#define HOST_CMD_APCMD_SYS_RESET               0x00af
/** Host Command id: SYS_CONFIGURE  */
#define HOST_CMD_APCMD_SYS_CONFIGURE           0x00b0
/** Host Command id: BSS_START */
#define HOST_CMD_APCMD_BSS_START               0x00b1
/** Host Command id: BSS_STOP  */
#define HOST_CMD_APCMD_BSS_STOP                0x00b2
/** Host Command id: sta_list */
#define HOST_CMD_APCMD_STA_LIST                0x00b3
/** Host Command id: STA_DEAUTH */
#define HOST_CMD_APCMD_STA_DEAUTH              0x00b5

/** Host Command ID: Tx data pause */
#define HostCmd_CMD_CFG_TX_DATA_PAUSE           0x0103

/** Host Command ID: P2P PARAMS CONFIG */
#define HOST_CMD_P2P_PARAMS_CONFIG              0x00ea
/** Host Command ID: WIFI_DIRECT_MODE_CONFIG */
#define HOST_CMD_WIFI_DIRECT_MODE_CONFIG    0x00eb
/** Host Command ID: Remain On Channel */
#define HostCmd_CMD_802_11_REMAIN_ON_CHANNEL     0x010d

#define HostCmd_CMD_COALESCE_CFG                 0x010a

/** Host Command ID : OTP user data */
#define HostCmd_CMD_OTP_READ_USER_DATA          0x0114

/** Host Command ID: HS wakeup reason */
#define HostCmd_CMD_HS_WAKEUP_REASON         0x0116

/** Host Command ID: reject addba request */
#define HostCmd_CMD_REJECT_ADDBA_REQ         0x0119

#define HostCMD_CONFIG_LOW_POWER_MODE   0x0128

/** Host Command ID : Target device access */
#define HostCmd_CMD_TARGET_ACCESS            0x012a

/** Enhanced PS modes */
typedef enum _ENH_PS_MODES
{
    GET_PS = 0,
    SLEEP_CONFIRM = 5,
    DIS_AUTO_PS = 0xfe,
    EN_AUTO_PS = 0xff,
} ENH_PS_MODES;

/** Command RET code, MSB is set to 1 */
#define HostCmd_RET_BIT                       0x8000

/** General purpose action : Get */
#define HostCmd_ACT_GEN_GET                   0x0000
/** General purpose action : Set */
#define HostCmd_ACT_GEN_SET                   0x0001
/** General purpose action : Get_Current */
#define HostCmd_ACT_GEN_GET_CURRENT           0x0003
/** General purpose action : Remove */
#define HostCmd_ACT_GEN_REMOVE                0x0004

/** Host command action : Set Rx */
#define HostCmd_ACT_SET_RX                    0x0001
/** Host command action : Set Tx */
#define HostCmd_ACT_SET_TX                    0x0002
/** Host command action : Set both Rx and Tx */
#define HostCmd_ACT_SET_BOTH                  0x0003
/** Host command action : Get Rx */
#define HostCmd_ACT_GET_RX                    0x0004
/** Host command action : Get Tx */
#define HostCmd_ACT_GET_TX                    0x0008
/** Host command action : Get both Rx and Tx */
#define HostCmd_ACT_GET_BOTH                  0x000c

/** General Result Code*/
/** General result code OK */
#define HostCmd_RESULT_OK                     0x0000
/** Genenral error */
#define HostCmd_RESULT_ERROR                  0x0001
/** Command is not valid */
#define HostCmd_RESULT_NOT_SUPPORT            0x0002
/** Command is pending */
#define HostCmd_RESULT_PENDING                0x0003
/** System is busy (command ignored) */
#define HostCmd_RESULT_BUSY                   0x0004
/** Data buffer is not big enough */
#define HostCmd_RESULT_PARTIAL_DATA           0x0005

/* Define action or option for HostCmd_CMD_MAC_CONTROL */
/** MAC action : Rx on */
#define HostCmd_ACT_MAC_RX_ON                 0x0001
/** MAC action : Tx on */
#define HostCmd_ACT_MAC_TX_ON                 0x0002
/** MAC action : WEP enable */
#define HostCmd_ACT_MAC_WEP_ENABLE            0x0008
/** MAC action : EthernetII enable */
#define HostCmd_ACT_MAC_ETHERNETII_ENABLE     0x0010
/** MAC action : Promiscous mode enable */
#define HostCmd_ACT_MAC_PROMISCUOUS_ENABLE    0x0080
/** MAC action : All multicast enable */
#define HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE  0x0100
/** MAC action : RTS/CTS enable */
#define HostCmd_ACT_MAC_RTS_CTS_ENABLE        0x0200
/** MAC action : Strict protection enable */
#define HostCmd_ACT_MAC_STRICT_PROTECTION_ENABLE  0x0400
/** MAC action : Force 11n protection disable */
#define HostCmd_ACT_MAC_FORCE_11N_PROTECTION_OFF  0x0800
/** MAC action : Ad-Hoc G protection on */
#define HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON     0x2000

/* Define action or option for HostCmd_CMD_802_11_SCAN */
/** Scan type : BSS */
#define HostCmd_BSS_MODE_BSS                0x0001
/** Scan type : IBSS */
#define HostCmd_BSS_MODE_IBSS               0x0002
/** Scan type : Any */
#define HostCmd_BSS_MODE_ANY                0x0003

/* Radio type definitions for the channel TLV */
/** Radio type BG */
#define HostCmd_SCAN_RADIO_TYPE_BG          0
/** Radio type A */
#define HostCmd_SCAN_RADIO_TYPE_A           1

/** Define bitmap conditions for HOST_SLEEP_CFG : GPIO FF */
#define HOST_SLEEP_CFG_GPIO_FF              0xff
/** Define bitmap conditions for HOST_SLEEP_CFG : GAP FF */
#define HOST_SLEEP_CFG_GAP_FF               0xff

/** Buffer Constants */
/** Number of command buffers */
#define MRVDRV_NUM_OF_CMD_BUFFER        15
/** Size of command buffer */
#define MRVDRV_SIZE_OF_CMD_BUFFER       (2 * 1024)

/** Maximum number of BSS Descriptors */
#define MRVDRV_MAX_BSSID_LIST           64

/** Host command flag in command */
#define CMD_F_HOSTCMD           (1 << 0)
/** command cancel flag in command */
#define CMD_F_CANCELED          (1 << 1)
/** scan command flag */
#define CMD_F_SCAN              (1 << 2)

/** Host Command ID bit mask (bit 11:0) */
#define HostCmd_CMD_ID_MASK             0x0fff

/** Host Command Sequence number mask (bit 7:0) */
#define HostCmd_SEQ_NUM_MASK            0x00ff

/** Host Command BSS number mask (bit 11:8) */
#define HostCmd_BSS_NUM_MASK            0x0f00

/** Host Command BSS type mask (bit 15:12) */
#define HostCmd_BSS_TYPE_MASK           0xf000

/** Set BSS information to Host Command */
#define HostCmd_SET_SEQ_NO_BSS_INFO(seq, num, type)    \
	((((seq) & 0x00ff) |         \
		(((num) & 0x000f) << 8)) | \
		(((type) & 0x000f) << 12))

/** Get Sequence Number from Host Command (bit 7:0) */
#define HostCmd_GET_SEQ_NO(seq)       \
	((seq) & HostCmd_SEQ_NUM_MASK)

/** Get BSS number from Host Command (bit 11:8) */
#define HostCmd_GET_BSS_NO(seq)         \
	(((seq) & HostCmd_BSS_NUM_MASK) >> 8)

/** Get BSS type from Host Command (bit 15:12) */
#define HostCmd_GET_BSS_TYPE(seq)       \
	(((seq) & HostCmd_BSS_TYPE_MASK) >> 12)


/* 3. EVENT */
/** Card Event definition : Dummy host wakeup signal */
#define EVENT_DUMMY_HOST_WAKEUP_SIGNAL  0x00000001
/** Card Event definition : Link lost */
#define EVENT_LINK_LOST                 0x00000003
/** Card Event definition : Link sensed */
#define EVENT_LINK_SENSED               0x00000004
/** Card Event definition : MIB changed */
#define EVENT_MIB_CHANGED               0x00000006
/** Card Event definition : Init done */
#define EVENT_INIT_DONE                 0x00000007
/** Card Event definition : Deauthenticated */
#define EVENT_DEAUTHENTICATED           0x00000008
/** Card Event definition : Disassociated */
#define EVENT_DISASSOCIATED             0x00000009
/** Card Event definition : Power save awake */
#define EVENT_PS_AWAKE                  0x0000000a
/** Card Event definition : Power save sleep */
#define EVENT_PS_SLEEP                  0x0000000b
/** Card Event definition : MIC error multicast */
#define EVENT_MIC_ERR_MULTICAST         0x0000000d
/** Card Event definition : MIC error unicast */
#define EVENT_MIC_ERR_UNICAST           0x0000000e

/** Card Event definition : Ad-Hoc BCN lost */
#define EVENT_ADHOC_BCN_LOST            0x00000011

/** Card Event definition : WMM status change */
#define EVENT_WMM_STATUS_CHANGE         0x00000017

/** Card Event definition : BG scan report */
#define EVENT_BG_SCAN_REPORT            0x00000018
/** Card Event definition : BG scan stopped */
#define EVENT_BG_SCAN_STOPPED       0x00000065

/** Card Event definition : Beacon RSSI low */
#define EVENT_RSSI_LOW                  0x00000019
/** Card Event definition : Beacon SNR low */
#define EVENT_SNR_LOW                   0x0000001a
/** Card Event definition : Maximum fail */
#define EVENT_MAX_FAIL                  0x0000001b
/** Card Event definition : Beacon RSSI high */
#define EVENT_RSSI_HIGH                 0x0000001c
/** Card Event definition : Beacon SNR high */
#define EVENT_SNR_HIGH                  0x0000001d

/** Card Event definition : IBSS coalsced */
#define EVENT_IBSS_COALESCED            0x0000001e

/** Card Event definition : Data RSSI low */
#define EVENT_DATA_RSSI_LOW             0x00000024
/** Card Event definition : Data SNR low */
#define EVENT_DATA_SNR_LOW              0x00000025
/** Card Event definition : Data RSSI high */
#define EVENT_DATA_RSSI_HIGH            0x00000026
/** Card Event definition : Data SNR high */
#define EVENT_DATA_SNR_HIGH             0x00000027

/** Card Event definition : Link Quality */
#define EVENT_LINK_QUALITY              0x00000028

/** Card Event definition : Port release event */
#define EVENT_PORT_RELEASE              0x0000002b

/** Card Event definition : Pre-Beacon Lost */
#define EVENT_PRE_BEACON_LOST           0x00000031

/** Card Event definition : Add BA event */
#define EVENT_ADDBA                     0x00000033
/** Card Event definition : Del BA event */
#define EVENT_DELBA                     0x00000034
/** Card Event definition: BA stream timeout*/
#define EVENT_BA_STREAM_TIMEOUT         0x00000037

/** Card Event definition : AMSDU aggr control */
#define EVENT_AMSDU_AGGR_CTRL           0x00000042

/** Card Event definition: WEP ICV error */
#define EVENT_WEP_ICV_ERR               0x00000046

/** Card Event definition : Host sleep enable */
#define EVENT_HS_ACT_REQ                0x00000047

/** Card Event definition : BW changed */
#define EVENT_BW_CHANGE                 0x00000048

/** WIFIDIRECT generic event */
#define EVENT_WIFIDIRECT_GENERIC_EVENT         0x00000049
/** WIFIDIRECT service discovery event */
#define EVENT_WIFIDIRECT_SERVICE_DISCOVERY     0x0000004a
/** Remain on Channel expired event */
#define EVENT_REMAIN_ON_CHANNEL_EXPIRED        0x0000005f

/** Event definition : FW debug information */
#define EVENT_FW_DEBUG_INFO             0x00000063

/** Event definition: RXBA_SYNC */
#define EVENT_RXBA_SYNC                 0x00000059

/** Event ID: STA deauth */
#define EVENT_MICRO_AP_STA_DEAUTH       0x0000002c
/** Event ID: STA assoicated */
#define EVENT_MICRO_AP_STA_ASSOC        0x0000002d
/** Event ID: BSS started */
#define EVENT_MICRO_AP_BSS_START        0x0000002e
/** Event ID: BSS idle event */
#define EVENT_MICRO_AP_BSS_IDLE         0x00000043
/** Event ID: BSS active event */
#define EVENT_MICRO_AP_BSS_ACTIVE       0x00000044
/** Event ID: RSN Connect event */
#define MICRO_AP_EV_RSN_CONNECT             0x00000051

/** Event ID: TX data pause event */
#define EVENT_TX_DATA_PAUSE                  0x00000055

/** Event ID: SAD Report */
#define EVENT_SAD_REPORT                     0x00000066

/** Event ID: Tx status */
#define EVENT_TX_STATUS_REPORT               0x00000074

#define EVENT_BT_COEX_WLAN_PARA_CHANGE	 0x00000076

/**  MAC Address Length */
#define MAC_ADDR_LENGTH            6
#define MAX_SSID_LENGTH			32
#define MAX_PHRASE_LENGTH			64
/** Setup the number of rates passed in the driver/firmware API */
#define HOSTCMD_SUPPORTED_RATES         14
/** country code length  used for 802.11D */
#define COUNTRY_CODE_LEN    3
/** Maximum number of AC QOS queues available in the driver/firmware */
#define MAX_AC_QUEUES               4
/** Size of a TSPEC.  Used to allocate necessary buffer space in commands */
#define WMM_TSPEC_SIZE              63
/** Extra IE bytes allocated in messages for appended IEs after a TSPEC */
#define WMM_ADDTS_EXTRA_IE_BYTES    256
/** Extra TLV bytes allocated in messages for configuring WMM Queues */
#define WMM_QUEUE_CONFIG_EXTRA_TLV_BYTES 64
/** Number of bins in the histogram for the HostCmd_DS_WMM_QUEUE_STATS */
#define WMM_STATS_PKTS_HIST_BINS  7
/** Max IE index to FW */
#define MAX_MGMT_IE_INDEX_TO_FW         4
/** Max IE index per BSS */
#define MAX_MGMT_IE_INDEX       12



#define MLAN_PACK_END	__attribute__ ((packed))

typedef enum
{
    WIFI_SECURITYTYPE_NONE = 0,
    WIFI_SECURITYTYPE_WEP = 1,
    WIFI_SECURITYTYPE_WPA = 2,
    WIFI_SECURITYTYPE_WPA2 = 3
} WiFi_SecurityType;

/**  BSS type */
typedef enum _mlan_bss_type
{
    BSS_TYPE_STA = 0,
    BSS_TYPE_UAP = 1,
    BSS_TYPE_WIFIDIRECT = 2,
    BSS_TYPE_ANY = 0xff,
} mlan_bss_type;


typedef enum
{
    WIFI_AUTH_MODE_OPEN = 0x00,
    WIFI_AUTH_MODE_SHARED = 0x01,
    WIFI_AUTH_MODE_NETWORK_EAP = 0x80
} WiFi_AuthenticationType;

typedef  struct
{
    uint8_t oui[3];
    uint8_t oui_type;
    uint16_t version;
    uint8_t multicast_oui[4];
    uint16_t unicast_num;
    uint8_t unicast_oui[1][4];
    uint16_t auth_num; 
    uint8_t auth_oui[1][4];
} MLAN_PACK_END WiFi_Vendor;

/** MrvlIEtypesHeader_t */
typedef struct MrvlIEtypesHeader
{
    /** Header type */
    uint16_t type;
    /** Header length */
    uint16_t len;
} MLAN_PACK_END  MrvlIEtypesHeader_t;

typedef  struct
{
    MrvlIEtypesHeader_t header;
    uint8_t channel;
} MLAN_PACK_END  MrvlIETypes_PhyParamDSSet_t;

typedef struct _MrvlIETypes_Vendor_context_t
{
    /** OUI */
    uint8_t oui[3];
    /** OUI type */
    uint8_t oui_type;
    /** OUI subtype */
    uint8_t oui_subtype;
    /** Version */
    uint8_t version;
}  MLAN_PACK_END MrvlIETypes_Vendor_context_t;

/** Vendor specific IE header */
typedef struct _MrvlIETypes_Vendor_t
{
    MrvlIEtypesHeader_t header;
    uint8_t vendor[64];
}  MLAN_PACK_END MrvlIETypes_Vendor_t;

/** Vendor specific IE header */
typedef struct _MrvlIETypes_RSN_t
{
    MrvlIEtypesHeader_t header;
    uint8_t rsn[64];
}  MLAN_PACK_END MrvlIETypes_RSN_t;

typedef  struct
{
    MrvlIEtypesHeader_t header;
    uint8_t rate[1];
} MLAN_PACK_END  MrvlIETypes_OpRateSet_t;

typedef  struct
{
    MrvlIEtypesHeader_t header;
    uint8_t count;
    uint8_t period;
    uint16_t max_duration;
    uint16_t duration_remaining;
} MLAN_PACK_END MrvlIETypes_CfParamSet_t;

typedef  struct
{
    MrvlIEtypesHeader_t header;
    uint16_t auth_type;
} MLAN_PACK_END MrvlIETypes_AuthType_t;

typedef  struct
{
    MrvlIEtypesHeader_t header;
    uint8_t mac_address[MAC_ADDR_LENGTH];
} MLAN_PACK_END MrvlIETypes_BSSIDList_t;

typedef struct _IEEEtypes_CapInfo_t
{
    /** Capability Bit Map : ESS */
    uint8_t ess:1;
    /** Capability Bit Map : IBSS */
    uint8_t ibss:1;
    /** Capability Bit Map : CF pollable */
    uint8_t cf_pollable:1;
    /** Capability Bit Map : CF poll request */
    uint8_t cf_poll_rqst:1;
    /** Capability Bit Map : privacy */
    uint8_t privacy:1;
    /** Capability Bit Map : Short preamble */
    uint8_t short_preamble:1;
    /** Capability Bit Map : PBCC */
    uint8_t pbcc:1;
    /** Capability Bit Map : Channel agility */
    uint8_t chan_agility:1;
    /** Capability Bit Map : Spectrum management */
    uint8_t spectrum_mgmt:1;
    /** Capability Bit Map : Reserved */
    uint8_t rsrvd3:1;
    /** Capability Bit Map : Short slot time */
    uint8_t short_slot_time:1;
    /** Capability Bit Map : APSD */
    uint8_t apsd:1;
    /** Capability Bit Map : Reserved */
    uint8_t rsvrd2:1;
    /** Capability Bit Map : DSS OFDM */
    uint8_t dsss_ofdm:1;
    /** Capability Bit Map : Reserved */
    uint8_t rsrvd1:2;
} MLAN_PACK_END IEEEtypes_CapInfo_t, *pIEEEtypes_CapInfo_t;

/** 16 bit unsigned integer */
typedef uint16_t IEEEtypes_AId_t;
/** 16 bit unsigned integer */
typedef uint16_t IEEEtypes_StatusCode_t;


/** Data structure for subband set */
typedef  struct _IEEEtypes_SubbandSet_t
{
    /** First channel */
    uint8_t first_chan;
    /** Number of channels */
    uint8_t no_of_chan;
    /** Maximum Tx power in dBm */
    uint8_t max_tx_pwr;
}  MLAN_PACK_END IEEEtypes_SubbandSet_t, *pIEEEtypes_SubbandSet_t;

typedef struct
{
    /** Capability information */
    //IEEEtypes_CapInfo_t Capability;
    uint16_t Capability;
    /** Association response status code */
    IEEEtypes_StatusCode_t StatusCode;
    /** Association ID */
    IEEEtypes_AId_t AId;
    /** IE data buffer */
    uint8_t IEBuffer[1];
}  MLAN_PACK_END IEEEtypes_AssocRsp_t;

/** IEEEtypes_CfParamSet_t */
typedef  struct _IEEEtypes_CfParamSet_t
{
    /** CF peremeter : Element ID */
    uint8_t element_id;
    /** CF peremeter : Length */
    uint8_t len;
    /** CF peremeter : Count */
    uint8_t cfp_cnt;
    /** CF peremeter : Period */
    uint8_t cfp_period;
    /** CF peremeter : Maximum duration */
    uint16_t cfp_max_duration;
    /** CF peremeter : Remaining duration */
    uint16_t cfp_duration_remaining;
}  MLAN_PACK_END IEEEtypes_CfParamSet_t, *pIEEEtypes_CfParamSet_t;

/** IEEEtypes_IbssParamSet_t */
typedef  struct _IEEEtypes_IbssParamSet_t
{
    /** Element ID */
    uint8_t element_id;
    /** Length */
    uint8_t len;
    /** ATIM window value in milliseconds */
    uint16_t atim_window;
}  MLAN_PACK_END IEEEtypes_IbssParamSet_t, *pIEEEtypes_IbssParamSet_t;

/** IEEEtypes_SsParamSet_t */
typedef  union _IEEEtypes_SsParamSet_t
{
    /** SS parameter : CF parameter set */
    IEEEtypes_CfParamSet_t cf_param_set;
    /** SS parameter : IBSS parameter set */
    IEEEtypes_IbssParamSet_t ibss_param_set;
} MLAN_PACK_END  IEEEtypes_SsParamSet_t, *pIEEEtypes_SsParamSet_t;

/** IEEEtypes_FhParamSet_t */
typedef  struct _IEEEtypes_FhParamSet_t
{
    /** FH parameter : Element ID */
    uint8_t element_id;
    /** FH parameter : Length */
    uint8_t len;
    /** FH parameter : Dwell time in milliseconds */
    uint16_t dwell_time;
    /** FH parameter : Hop set */
    uint8_t hop_set;
    /** FH parameter : Hop pattern */
    uint8_t hop_pattern;
    /** FH parameter : Hop index */
    uint8_t hop_index;
}  MLAN_PACK_END IEEEtypes_FhParamSet_t, *pIEEEtypes_FhParamSet_t;

/** IEEEtypes_DsParamSet_t */
typedef  struct _IEEEtypes_DsParamSet_t
{
    /** DS parameter : Element ID */
    uint8_t element_id;
    /** DS parameter : Length */
    uint8_t len;
    /** DS parameter : Current channel */
    uint8_t current_chan;
}  MLAN_PACK_END IEEEtypes_DsParamSet_t, *pIEEEtypes_DsParamSet_t;

/** IEEEtypes_PhyParamSet_t */
typedef  union _IEEEtypes_PhyParamSet_t
{
    /** FH parameter set */
    IEEEtypes_FhParamSet_t fh_param_set;
    /** DS parameter set */
    IEEEtypes_DsParamSet_t ds_param_set;
}  MLAN_PACK_END IEEEtypes_PhyParamSet_t, *pIEEEtypes_PhyParamSet_t;

/** Vendor specific IE header */
typedef struct _IEEEtypes_VendorHeader_t
{
    /** Element ID */
    uint8_t element_id;
    /** Length */
    uint8_t len;
    /** OUI */
    uint8_t oui[3];
    /** OUI type */
    uint8_t oui_type;
    /** OUI subtype */
    uint8_t oui_subtype;
    /** Version */
    uint8_t version;
}  MLAN_PACK_END IEEEtypes_VendorHeader_t, *pIEEEtypes_VendorHeader_t;

/** Data structure of WMM QoS information */
typedef struct _IEEEtypes_WmmQosInfo_t
{

    /** Parameter set count */
    uint8_t para_set_count:4;
    /** Reserved */
    uint8_t reserved:3;
    /** QoS UAPSD */
    uint8_t qos_uapsd:1;
}  MLAN_PACK_END IEEEtypes_WmmQosInfo_t, *pIEEEtypes_WmmQosInfo_t;

/** Data structure of WMM Aci/Aifsn */
typedef struct _IEEEtypes_WmmAciAifsn_t
{

    /** Aifsn */
    uint8_t aifsn:4;
    /** Acm */
    uint8_t acm:1;
    /** Aci */
    uint8_t aci:2;
    /** Reserved */
    uint8_t reserved:1;

} MLAN_PACK_END  IEEEtypes_WmmAciAifsn_t, *pIEEEtypes_WmmAciAifsn_t;

/** Data structure of WMM ECW */
typedef struct _IEEEtypes_WmmEcw_t
{

    /** Minimum Ecw */
    uint8_t ecw_min:4;
    /** Maximum Ecw */
    uint8_t ecw_max:4;

} MLAN_PACK_END  IEEEtypes_WmmEcw_t, *pIEEEtypes_WmmEcw_t;

/** Data structure of WMM AC parameters  */
typedef struct _IEEEtypes_WmmAcParameters_t
{
    IEEEtypes_WmmAciAifsn_t aci_aifsn;  /**< AciAifSn */
    IEEEtypes_WmmEcw_t ecw;		    /**< Ecw */
    uint16_t tx_op_limit;		    /**< Tx op limit */
} MLAN_PACK_END  IEEEtypes_WmmAcParameters_t, *pIEEEtypes_WmmAcParameters_t;


/** Data structure of WMM parameter IE  */
typedef struct _IEEEtypes_WmmParameter_t
{
    /**
     * WMM Parameter IE - Vendor Specific Header:
     *   element_id  [221/0xdd]
     *   Len         [24]
     *   Oui         [00:50:f2]
     *   OuiType     [2]
     *   OuiSubType  [1]
     *   Version     [1]
     */
    IEEEtypes_VendorHeader_t vend_hdr;

    /** QoS information */
    IEEEtypes_WmmQosInfo_t qos_info;
    /** Reserved */
    uint8_t reserved;

    /** AC Parameters Record WMM_AC_BE, WMM_AC_BK, WMM_AC_VI, WMM_AC_VO */
    IEEEtypes_WmmAcParameters_t ac_params[MAX_AC_QUEUES];

} MLAN_PACK_END  IEEEtypes_WmmParameter_t, *pIEEEtypes_WmmParameter_t;

/* TLV (Tag Length Value) of IEEE IE Type Format */
typedef  struct
{
    uint8_t type;
    uint8_t length; // 数据域的大小
} MLAN_PACK_END IEEEHeader;

// information element parameter
// 所有IEEETypes_*类型的基类型
typedef  struct
{
    IEEEHeader header;
    uint8_t data[1];
} MLAN_PACK_END IEEEType;

typedef  struct _bss_desc_set
{
    uint16_t ie_length; // Total information element length (不含sizeof(ie_length))
    uint8_t bssid[6]; // BSSID
    uint8_t rssi; // RSSI value as received from peer

    // Probe Response/Beacon Payload
    uint64_t pkt_time_stamp; // Timestamp
    uint16_t bcn_interval; // Beacon interval
    uint16_t cap_info; // Capabilities information
    IEEEType ie_parameters; // 存放的是一些IEEE类型的数据
} MLAN_PACK_END bss_desc_set_t,*pbss_desc_set_t;


// 已知数据域大小, 求整个结构体的大小
// 例如定义一个很大的buffer, 然后定义一个IEEEType *的指针p指向该buffer
// buffer接收到数据后, 要求出接收到的IEEEType数据的实际大小显然不能用sizeof(IEEEType), 因为定义IEEEType结构体时data的长度定义的是1
// 此时就应该使用TLV_STRUCTLEN(*p)
#define TLV_STRUCTLEN(tlv) (sizeof((tlv).header) + (tlv).header.length)

// 已知本TLV的地址和大小, 求下一个TLV的地址
#define TLV_NEXT(tlv) ((uint8_t *)(tlv) + TLV_STRUCTLEN(*(tlv)))

/** HostCmd_DS_GET_HW_SPEC */
typedef struct _HostCmd_DS_GET_HW_SPEC
{
    /** HW Interface version number */
    uint16_t hw_if_version;
    /** HW version number */
    uint16_t version;
    /** Reserved field */
    uint16_t reserved;
    /** Max no of Multicast address  */
    uint16_t num_of_mcast_adr;
    /** MAC address */
    uint8_t permanent_addr[MAC_ADDR_LENGTH];
    /** Region Code */
    uint16_t region_code;
    /** Number of antenna used */
    uint16_t number_of_antenna;
    /** FW release number, example 0x1234=1.2.3.4 */
    uint32_t fw_release_number;
    /** Reserved field */
    uint32_t reserved_1;
    /** Reserved field */
    uint32_t reserved_2;
    /** Reserved field */
    uint32_t reserved_3;
    /** FW/HW Capability */
    uint32_t fw_cap_info;
    /** 802.11n Device Capabilities */
    uint32_t dot_11n_dev_cap;
    /** MIMO abstraction of MCSs supported by device */
    uint8_t dev_mcs_support;
    /** Valid end port at init */
    uint16_t mp_end_port;
    /** mgmt IE buffer count */
    uint16_t mgmt_buf_count;
} MLAN_PACK_END  HostCmd_DS_GET_HW_SPEC;

/**  HostCmd_DS_802_11_CFG_DATA */
typedef struct _HostCmd_DS_802_11_CFG_DATA
{
    /** Action */
    uint16_t action;
    /** Type */
    uint16_t type;
    /** Data length */
    uint16_t data_len;
    /** Data */
} MLAN_PACK_END HostCmd_DS_802_11_CFG_DATA;

/** HostCmd_DS_MAC_CONTROL */
typedef  struct _HostCmd_DS_MAC_CONTROL
{
    /** Action */
    uint32_t action;
} MLAN_PACK_END HostCmd_DS_MAC_CONTROL;


/** HostCmd_DS_802_11_MAC_ADDRESS */
typedef  struct _HostCmd_DS_802_11_MAC_ADDRESS
{
    /** Action */
    uint16_t action;
    /** MAC address */
    uint8_t mac_addr[MAC_ADDR_LENGTH];
} MLAN_PACK_END  HostCmd_DS_802_11_MAC_ADDRESS;

#define MAX_MULTICAST_LIST_SIZE	32
/**  HostCmd_CMD_MAC_MULTICAST_ADR */
typedef  struct _HostCmd_DS_MAC_MULTICAST_ADR
{
    /** Action */
    uint16_t action;
    /** Number of addresses */
    uint16_t num_of_adrs;
    /** List of MAC */
    uint8_t mac_list[MAC_ADDR_LENGTH * MAX_MULTICAST_LIST_SIZE];
} MLAN_PACK_END  HostCmd_DS_MAC_MULTICAST_ADR;

/** HostCmd_DS_802_11_GET_LOG */
typedef  struct _HostCmd_DS_802_11_GET_LOG
{
    /** Number of multicast transmitted frames */
    uint32_t mcast_tx_frame;
    /** Number of failures */
    uint32_t failed;
    /** Number of retries */
    uint32_t retry;
    /** Number of multiretries */
    uint32_t multiretry;
    /** Number of duplicate frames */
    uint32_t frame_dup;
    /** Number of RTS success */
    uint32_t rts_success;
    /** Number of RTS failure */
    uint32_t rts_failure;
    /** Number of acknowledgement failure */
    uint32_t ack_failure;
    /** Number of fragmented packets received */
    uint32_t rx_frag;
    /** Number of multicast frames received */
    uint32_t mcast_rx_frame;
    /** FCS error */
    uint32_t fcs_error;
    /** Number of transmitted frames */
    uint32_t tx_frame;
    /** Reserved field */
    uint32_t reserved;
    /** Number of WEP icv error for each key */
    uint32_t wep_icv_err_cnt[4];
    /** Beacon received count */
    uint32_t bcn_rcv_cnt;
    /** Beacon missed count */
    uint32_t bcn_miss_cnt;
} MLAN_PACK_END  HostCmd_DS_802_11_GET_LOG;

/**  HostCmd_DS_CMD_802_11_RSSI_INFO */
typedef  struct _HostCmd_DS_802_11_RSSI_INFO
{
    /** Action */
    uint16_t action;
    /** Parameter used for exponential averaging for Data */
    uint16_t ndata;
    /** Parameter used for exponential averaging for Beacon */
    uint16_t nbcn;
    /** Reserved field 0 */
    uint16_t reserved[9];
    /** Reserved field 1 */
    uint64_t reserved_1;
} MLAN_PACK_END  HostCmd_DS_802_11_RSSI_INFO;

/** HostCmd_DS_802_11_RSSI_INFO_RSP */
typedef  struct _HostCmd_DS_802_11_RSSI_INFO_RSP
{
    /** Action */
    uint16_t action;
    /** Parameter used for exponential averaging for Data */
    uint16_t ndata;
    /** Parameter used for exponential averaging for beacon */
    uint16_t nbcn;
    /** Last Data RSSI in dBm */
    int16_t data_rssi_last;
    /** Last Data NF in dBm */
    int16_t data_nf_last;
    /** AVG DATA RSSI in dBm */
    int16_t data_rssi_avg;
    /** AVG DATA NF in dBm */
    int16_t data_nf_avg;
    /** Last BEACON RSSI in dBm */
    int16_t bcn_rssi_last;
    /** Last BEACON NF in dBm */
    int16_t bcn_nf_last;
    /** AVG BEACON RSSI in dBm */
    int16_t bcn_rssi_avg;
    /** AVG BEACON NF in dBm */
    int16_t bcn_nf_avg;
    /** Last RSSI Beacon TSF */
    uint64_t tsf_bcn;
} MLAN_PACK_END  HostCmd_DS_802_11_RSSI_INFO_RSP;

/**  HostCmd_CMD_802_11_SNMP_MIB */
typedef  struct _HostCmd_DS_802_11_SNMP_MIB
{
    /** SNMP query type */
    uint16_t query_type;
    /** SNMP object ID */
    uint16_t oid;
    /** SNMP buffer size */
    uint16_t buf_size;
    /** Value */
    uint8_t value[1];
} MLAN_PACK_END  HostCmd_DS_802_11_SNMP_MIB;

/** HostCmd_CMD_802_11_RADIO_CONTROL */
typedef  struct _HostCmd_DS_802_11_RADIO_CONTROL
{
    /** Action */
    uint16_t action;
    /** Control */
    uint16_t control;
} MLAN_PACK_END  HostCmd_DS_802_11_RADIO_CONTROL;

/** HostCmd_CMD_802_11_RF_CHANNEL */
typedef  struct _HostCmd_DS_802_11_RF_CHANNEL
{
    /** Action */
    uint16_t action;
    /** Current channel */
    uint16_t current_channel;
    /** RF type */
    uint16_t rf_type;
    /** Reserved field */
    uint16_t reserved;
    /** List of channels */
    uint8_t channel_list[32];

} MLAN_PACK_END  HostCmd_DS_802_11_RF_CHANNEL;

/**_HostCmd_TX_RATE_QUERY */
typedef  struct _HostCmd_TX_RATE_QUERY
{
    /** Tx rate */
    uint8_t tx_rate;
    /** Ht Info [Bit 0] RxRate format: LG=0, HT=1
     * [Bit 1]  HT Bandwidth: BW20 = 0, BW40 = 1
     * [Bit 2]  HT Guard Interval: LGI = 0, SGI = 1 */
    uint8_t ht_info;
} MLAN_PACK_END  HostCmd_TX_RATE_QUERY;

/** HostCmd_DS_TX_RATE_CFG */
typedef  struct _HostCmd_DS_TX_RATE_CFG
{
    /** Action */
    uint16_t action;
    /** Tx Rate Configuration Index */
    uint16_t cfg_index;
    /* MrvlRateScope_t RateScope; MrvlRateDropPattern_t RateDrop; */
} MLAN_PACK_END  HostCmd_DS_TX_RATE_CFG;

/** HostCmd_CMD_TXPWR_CFG */
typedef  struct _HostCmd_DS_TXPWR_CFG
{
    /** Action */
    uint16_t action;
    /** Power group configuration index */
    uint16_t cfg_index;
    /** Power group configuration mode */
    uint32_t mode;
    /* MrvlTypes_Power_Group_t PowerGrpCfg[0] */
} MLAN_PACK_END  HostCmd_DS_TXPWR_CFG;

/** HostCmd_CMD_802_11_RF_TX_POWER */
typedef  struct _HostCmd_DS_802_11_RF_TX_POWER
{
    /** Action */
    uint16_t action;
    /** Current power level */
    int16_t current_level;
    /** Maximum power */
    int8_t max_power;
    /** Minimum power */
    int8_t min_power;
} MLAN_PACK_END  HostCmd_DS_802_11_RF_TX_POWER;

/** HostCmd_CMD_802_11_RF_ANTENNA */
typedef  struct _HostCmd_DS_802_11_RF_ANTENNA
{
    /** Action */
    uint16_t action;
    /**  Antenna or 0xffff (diversity) */
    uint16_t antenna_mode;
} MLAN_PACK_END  HostCmd_DS_802_11_RF_ANTENNA;


/** Structure definition for the new ieee power save parameters*/
typedef  struct __ps_param
{
    /** Null packet interval */
    uint16_t null_pkt_interval;
    /** Num dtims */
    uint16_t multiple_dtims;
    /** becaon miss interval */
    uint16_t bcn_miss_timeout;
    /** local listen interval */
    uint16_t local_listen_interval;
    /** Adhoc awake period */
    uint16_t adhoc_wake_period;
    /** mode - (0x01 - firmware to automatically choose PS_POLL or NULL mode,
     *  0x02 - PS_POLL, 0x03 - NULL mode )
     */
    uint16_t mode;
    /** Delay to PS in milliseconds */
    uint16_t delay_to_ps;
} MLAN_PACK_END  ps_param;

/** Structure definition for the new auto deep sleep command */
typedef  struct __auto_ds_param
{
    /** Deep sleep inactivity timeout */
    uint16_t deep_sleep_timeout;
} MLAN_PACK_END auto_ds_param;

/** Structure definition for sleep confirmation in the new ps command */
typedef  struct __sleep_confirm_param
{
    /** response control 0x00 - response not needed, 0x01 - response needed */
    uint16_t resp_ctrl;
} MLAN_PACK_END  sleep_confirm_param;

/** bitmap for get auto deepsleep */
#define BITMAP_AUTO_DS         0x01
/** bitmap for sta power save */
#define BITMAP_STA_PS          0x10
/** bitmap for uap inactivity based PS */
#define BITMAP_UAP_INACT_PS    0x100
/** bitmap for uap DTIM PS */
#define BITMAP_UAP_DTIM_PS     0x200
/** Structure definition for the new ieee power save parameters*/
typedef  struct _auto_ps_param
{
    /** bitmap for enable power save mode */
    uint16_t ps_bitmap;
    /* auto deep sleep parameter, sta power save parameter uap inactivity
       parameter uap DTIM parameter */
} MLAN_PACK_END  auto_ps_param;

/** Structure definition for new power save command */
typedef  struct _HostCmd_DS_PS_MODE_ENH
{
    /** Action */
    uint16_t action;
    /** Data speciifc to action */
    /* For IEEE power save data will be as UINT16 mode (0x01 - firmware to
       automatically choose PS_POLL or NULL mode, 0x02 - PS_POLL, 0x03 -
       NULL mode ) UINT16 NullpacketInterval UINT16 NumDtims UINT16
       BeaconMissInterval UINT16 locallisteninterval UINT16
       adhocawakeperiod */

    /* For auto deep sleep */
    /* UINT16 Deep sleep inactivity timeout */

    /* For PS sleep confirm UINT16 responeCtrl - 0x00 - reponse from fw not
       needed, 0x01 - response from fw is needed */

    union
    {
        /** PS param definition */
        ps_param opt_ps;
        /** Auto ds param definition */
        auto_ds_param auto_ds;
        /** Sleep comfirm param definition */
        sleep_confirm_param sleep_cfm;
        /** bitmap for get PS info and Disable PS mode */
        uint16_t ps_bitmap;
        /** auto ps param */
        auto_ps_param auto_ps;
    } params;
} MLAN_PACK_END  HostCmd_DS_802_11_PS_MODE_ENH;

typedef  struct _hs_config_param
{
    /** bit0=1: broadcast data
      * bit1=1: unicast data
      * bit2=1: mac events
      * bit3=1: multicast data
      */
    uint32_t conditions;
    /** GPIO pin or 0xff for interface */
    uint8_t gpio;
    /** gap in milliseconds or or 0xff for special setting when
     *  GPIO is used to wakeup host
     */
    uint8_t gap;
} MLAN_PACK_END hs_config_param;

/** HS Action 0x0001 - Configure enhanced host sleep mode,
 * 0x0002 - Activate enhanced host sleep mode
 */
typedef enum _Host_Sleep_Action
{
    HS_CONFIGURE = 0x0001,
    HS_ACTIVATE = 0x0002,
} MLAN_PACK_END Host_Sleep_Action;

/** Structure definition for activating enhanced hs */
typedef  struct __hs_activate_param
{
    /** response control 0x00 - response not needed, 0x01 - response needed */
    uint16_t resp_ctrl;
} MLAN_PACK_END  hs_activate_param;

/** HostCmd_DS_802_11_HS_CFG_ENH */
typedef  struct _HostCmd_DS_802_11_HS_CFG_ENH
{
    /** Action 0x0001 - Configure enhanced host sleep mode,
     *  0x0002 - Activate enhanced host sleep mode
     */
    uint16_t action;

    union
    {
        /** Configure enhanced hs */
        hs_config_param hs_config;
        /** Activate enhanced hs */
        hs_activate_param hs_activate;
    } params;
} MLAN_PACK_END  HostCmd_DS_802_11_HS_CFG_ENH;


/** ChanScanMode_t */
typedef  struct _ChanScanMode_t
{
    /** Channel scan mode passive flag */
    uint8_t passive_scan:1;
    /** Disble channel filtering flag */
    uint8_t disable_chan_filt:1;
    /** Multidomain scan mode */
    uint8_t multidomain_scan:1;
    /** Enable probe response timeout */
    uint8_t rsp_timeout_en:1;
    /** Enable hidden ssid report */
    uint8_t hidden_ssid_report:1;
    /** First channel in scan */
    uint8_t first_chan:1;
    /** Reserved */
    uint8_t reserved_6_7:2;
} MLAN_PACK_END ChanScanMode_t;

/** secondary channel is below */
#define SECOND_CHANNEL_BELOW    0x30
/** secondary channel is above */
#define SECOND_CHANNEL_ABOVE    0x10
/** channel offset */
enum
{
    SEC_CHAN_NONE = 0,
    SEC_CHAN_ABOVE = 1,
    SEC_CHAN_BELOW = 3
};
/** channel bandwidth */
enum
{
    CHAN_BW_20MHZ = 0,
    CHAN_BW_10MHZ,
    CHAN_BW_40MHZ,
};
/** ChanScanParamSet_t */
typedef  struct _ChanScanParamSet_t
{
    /** Channel scan parameter : Radio type */
    uint8_t radio_type;
    /** Channel scan parameter : Channel number */
    uint8_t chan_number;
    /** Channel scan parameter : Channel scan mode */
    uint8_t chan_scan_mode;
    /** Channel scan parameter : Minimum scan time */
    uint16_t min_scan_time;
    /** Channel scan parameter : Maximum scan time */
    uint16_t max_scan_time;
} MLAN_PACK_END ChanScanParamSet_t;

/** MrvlIEtypes_ChanListParamSet_t */
typedef  struct _MrvlIEtypes_ChanListParamSet_t
{
    /** Header */
    MrvlIEtypesHeader_t header;
    /** Channel scan parameters */
    ChanScanParamSet_t chan_scan_param[1];
} MLAN_PACK_END MrvlIEtypes_ChanListParamSet_t;

typedef  struct _MrvlIEtypes_SSIDParamSet_t
{
    MrvlIEtypesHeader_t header;
    uint8_t ssid[MAX_SSID_LENGTH];
} MLAN_PACK_END MrvlIEtypes_SSIDParamSet_t;

typedef  struct _MrvlIEtypes_PASSPhrase_t
{
    MrvlIEtypesHeader_t header;
    uint8_t phrase[MAX_PHRASE_LENGTH];
} MLAN_PACK_END MrvlIEtypes_PASSPhrase_t;

typedef  struct _MrvlIEtypes_Enc_Protocol_t
{
    MrvlIEtypesHeader_t header;
    uint16_t enc_protocol;
} MLAN_PACK_END MrvlIEtypes_Enc_Protocol_t;

typedef  struct _MrvlIEtypes_AKMP_t
{
    MrvlIEtypesHeader_t header;
    uint16_t key_mgmt;
    uint16_t operation;
} MLAN_PACK_END MrvlIEtypes_AKMP_t;

#define WPA_CIPHER_WEP40 MBIT(0)
#define WPA_CIPHER_WEP104 MBIT(1)
#define WPA_CIPHER_TKIP MBIT(2)
#define WPA_CIPHER_CCMP MBIT(3)

typedef  struct _MrvlIEtypes_PTK_cipher_t
{
    MrvlIEtypesHeader_t header;
    uint16_t protocol;
    uint16_t cipher;
} MLAN_PACK_END MrvlIEtypes_PTK_cipher_t;

typedef  struct _MrvlIEtypes_GTK_cipher_t
{
    MrvlIEtypesHeader_t header;
    uint16_t cipher;
} MLAN_PACK_END MrvlIEtypes_GTK_cipher_t;


typedef  struct _MrvlIETypes_ApBCast_SSID_Ctrl_t
{
    MrvlIEtypesHeader_t header;
    uint8_t broadcast_ssid;
} MLAN_PACK_END MrvlIETypes_ApBCast_SSID_Ctrl_t;
/*
 * This scan handle Country Information IE(802.11d compliant)
 * Define data structure for HostCmd_CMD_802_11_SCAN
 */
/** HostCmd_DS_802_11_SCAN */
typedef  struct _HostCmd_DS_802_11_SCAN
{
    /** BSS mode */
    uint8_t bss_mode;
    /** BSSID */
    uint8_t bssid[MAC_ADDR_LENGTH];
    /** TLV buffer */
    uint8_t tlv_buffer[1];
    /** MrvlIEtypes_SsIdParamSet_t      SsIdParamSet;
     *  MrvlIEtypes_ChanListParamSet_t  ChanListParamSet;
     *  MrvlIEtypes_RatesParamSet_t     OpRateSet;
     */
} MLAN_PACK_END  HostCmd_DS_802_11_SCAN;

/** HostCmd_DS_RX_MGMT_IND */
typedef  struct _HostCmd_DS_RX_MGMT_IND
{
    /** Action */
    uint16_t action;
    /** Mgmt frame subtype mask */
    uint32_t mgmt_subtype_mask;
} MLAN_PACK_END  HostCmd_DS_RX_MGMT_IND;

/** HostCmd_DS_802_11_SCAN_RSP */
typedef  struct _HostCmd_DS_802_11_SCAN_RSP
{
    /** Size of BSS descriptor */
    uint16_t bss_descript_size;
    /** Numner of sets */
    uint8_t number_of_sets;
    /** BSS descriptor and TLV buffer */
    uint8_t bss_desc_and_tlv_buffer[1];
} MLAN_PACK_END  HostCmd_DS_802_11_SCAN_RSP;

/** HostCmd_DS_802_11_BG_SCAN_CONFIG */
typedef  struct _HostCmd_DS_802_11_BG_SCAN_CONFIG
{
    /** action */
    uint16_t action;
    /** 0: disable, 1: enable */
    uint8_t enable;
    /** bss type */
    uint8_t bss_type;
    /** num of channel per scan */
    uint8_t chan_per_scan;
    /** reserved field */
    uint8_t reserved;
    /** reserved field */
    uint16_t reserved1;
    /** interval between consecutive scans */
    uint32_t scan_interval;
    /** reserved field */
    uint32_t reserved2;
    /** condition to trigger report to host */
    uint32_t report_condition;
    /** reserved field */
    uint16_t reserved3;
} MLAN_PACK_END  HostCmd_DS_802_11_BG_SCAN_CONFIG;

/** HostCmd_DS_802_11_BG_SCAN_QUERY */
typedef  struct _HostCmd_DS_802_11_BG_SCAN_QUERY
{
    /** Flush */
    uint8_t flush;
} MLAN_PACK_END  HostCmd_DS_802_11_BG_SCAN_QUERY;

/** HostCmd_DS_802_11_BG_SCAN_QUERY_RSP */
typedef  struct _HostCmd_DS_802_11_BG_SCAN_QUERY_RSP
{
    /** Report condition */
    uint32_t report_condition;
    /** Scan response */
    HostCmd_DS_802_11_SCAN_RSP scan_resp;
} MLAN_PACK_END  HostCmd_DS_802_11_BG_SCAN_QUERY_RSP;

/** HostCmd_DS_SUBSCRIBE_EVENT */
typedef  struct _HostCmd_DS_SUBSCRIBE_EVENT
{
    /** Action */
    uint16_t action;
    /** Bitmap of subscribed events */
    uint16_t event_bitmap;
} MLAN_PACK_END  HostCmd_DS_SUBSCRIBE_EVENT;

/** HostCmd_DS_OTP_USER_DATA */
typedef  struct _HostCmd_DS_OTP_USER_DATA
{
    /** Action */
    uint16_t action;
    /** Reserved field */
    uint16_t reserved;
    /** User data length */
    uint16_t user_data_length;
    /** User data */
    uint8_t user_data[1];
} MLAN_PACK_END  HostCmd_DS_OTP_USER_DATA;

/** HostCmd_DS_802_11_ASSOCIATE */
typedef  struct _HostCmd_DS_802_11_ASSOCIATE
{
    /** Peer STA address */
    uint8_t peer_sta_addr[MAC_ADDR_LENGTH];
    /** Capability information */
    uint16_t cap_info;
    //IEEEtypes_CapInfo_t cap_info;
    /** Listen interval */
    uint16_t listen_interval;
    /** Beacon period */
    uint16_t beacon_period;
    /** DTIM period */
    uint8_t dtim_period;
    uint8_t tlv_buffer[1];
    /**
     *  MrvlIEtypes_SsIdParamSet_t  SsIdParamSet;
     *  MrvlIEtypes_PhyParamSet_t   PhyParamSet;
     *  MrvlIEtypes_SsParamSet_t    SsParamSet;
     *  MrvlIEtypes_RatesParamSet_t RatesParamSet;
     */
} MLAN_PACK_END  HostCmd_DS_802_11_ASSOCIATE;

/** HostCmd_CMD_802_11_ASSOCIATE response */
typedef  struct _HostCmd_DS_802_11_ASSOCIATE_RSP
{
    /** Association response structure */
    IEEEtypes_AssocRsp_t assoc_rsp;
} MLAN_PACK_END  HostCmd_DS_802_11_ASSOCIATE_RSP;

/**  HostCmd_CMD_802_11_DEAUTHENTICATE */
typedef  struct _HostCmd_DS_802_11_DEAUTHENTICATE
{
    /** MAC address */
    uint8_t mac_addr[MAC_ADDR_LENGTH];
    /** Deauthentication resaon code */
    uint16_t reason_code;
} MLAN_PACK_END  HostCmd_DS_802_11_DEAUTHENTICATE;

/** HostCmd_DS_802_11_AD_HOC_START*/
typedef  struct _HostCmd_DS_802_11_AD_HOC_START
{
    /** AdHoc SSID */
    uint8_t ssid[MAX_SSID_LENGTH];
    /** BSS mode */
    uint8_t bss_mode;
    /** Beacon period */
    uint16_t beacon_period;
    /** DTIM period */
    uint8_t dtim_period;
    /** SS parameter set */
    IEEEtypes_SsParamSet_t ss_param_set;
    /** PHY parameter set */
    IEEEtypes_PhyParamSet_t phy_param_set;
    /** Reserved field */
    uint16_t reserved1;
    /** Capability information */
    IEEEtypes_CapInfo_t cap;
    /** Supported data rates */
    uint8_t DataRate[HOSTCMD_SUPPORTED_RATES];
} MLAN_PACK_END  HostCmd_DS_802_11_AD_HOC_START;

/**  HostCmd_CMD_802_11_AD_HOC_START response */
typedef  struct _HostCmd_DS_802_11_AD_HOC_START_RESULT
{
    /** Padding */
    uint8_t pad[3];
    /** AdHoc BSSID */
    uint8_t bssid[MAC_ADDR_LENGTH];
    /** Padding to sync with FW structure*/
    uint8_t pad2[2];
    /** Result */
    uint8_t result;
} MLAN_PACK_END  HostCmd_DS_802_11_AD_HOC_START_RESULT;

/**  HostCmd_CMD_802_11_AD_HOC_START response */
typedef  struct _HostCmd_DS_802_11_AD_HOC_JOIN_RESULT
{
    /** Result */
    uint8_t result;
} MLAN_PACK_END  HostCmd_DS_802_11_AD_HOC_JOIN_RESULT;

/** AdHoc_BssDesc_t */
typedef  struct _AdHoc_BssDesc_t
{
    /** BSSID */
    uint8_t bssid[MAC_ADDR_LENGTH];
    /** SSID */
    uint8_t ssid[MAX_SSID_LENGTH];
    /** BSS mode */
    uint8_t bss_mode;
    /** Beacon period */
    uint16_t beacon_period;
    /** DTIM period */
    uint8_t dtim_period;
    /** Timestamp */
    uint8_t time_stamp[8];
    /** Local time */
    uint8_t local_time[8];
    /** PHY parameter set */
    IEEEtypes_PhyParamSet_t phy_param_set;
    /** SS parameter set */
    IEEEtypes_SsParamSet_t ss_param_set;
    /** Capability information */
    IEEEtypes_CapInfo_t cap;
    /** Supported data rates */
    uint8_t data_rates[HOSTCMD_SUPPORTED_RATES];

    /*
     *  DO NOT ADD ANY FIELDS TO THIS STRUCTURE.
     *  It is used in the Adhoc join command and will cause a
     *  binary layout mismatch with the firmware
     */
} MLAN_PACK_END  AdHoc_BssDesc_t;

/** HostCmd_DS_802_11_AD_HOC_JOIN */
typedef  struct _HostCmd_DS_802_11_AD_HOC_JOIN
{
    /** AdHoc BSS descriptor */
    AdHoc_BssDesc_t bss_descriptor;
    /** Reserved field */
    uint16_t reserved1;
    /** Reserved field */
    uint16_t reserved2;
} MLAN_PACK_END  HostCmd_DS_802_11_AD_HOC_JOIN;

/** MrvlIEtypes_DomainParamSet_t */
typedef  struct _MrvlIEtypes_DomainParamSet
{
    /** Header */
    MrvlIEtypesHeader_t header;
    /** Country code */
    uint8_t country_code[COUNTRY_CODE_LEN];
    /** Set of subbands */
    IEEEtypes_SubbandSet_t sub_band[1];
} MLAN_PACK_END  MrvlIEtypes_DomainParamSet_t;

/** HostCmd_DS_802_11D_DOMAIN_INFO */
typedef  struct _HostCmd_DS_802_11D_DOMAIN_INFO
{
    /** Action */
    uint16_t action;
    /** Domain parameter set */
    MrvlIEtypes_DomainParamSet_t domain;
} MLAN_PACK_END  HostCmd_DS_802_11D_DOMAIN_INFO;

/** HostCmd_DS_802_11D_DOMAIN_INFO_RSP */
typedef  struct _HostCmd_DS_802_11D_DOMAIN_INFO_RSP
{
    /** Action */
    uint16_t action;
    /** Domain parameter set */
    MrvlIEtypes_DomainParamSet_t domain;
} MLAN_PACK_END  HostCmd_DS_802_11D_DOMAIN_INFO_RSP;

/** HostCmd_DS_11N_ADDBA_REQ */
typedef  struct _HostCmd_DS_11N_ADDBA_REQ
{
    /** Result of the ADDBA Request Operation */
    uint8_t add_req_result;
    /** Peer MAC address */
    uint8_t peer_mac_addr[MAC_ADDR_LENGTH];
    /** Dialog Token */
    uint8_t dialog_token;
    /** Block Ack Parameter Set */
    uint16_t block_ack_param_set;
    /** Block Act Timeout Value */
    uint16_t block_ack_tmo;
    /** Starting Sequence Number */
    uint16_t ssn;
} MLAN_PACK_END  HostCmd_DS_11N_ADDBA_REQ;

/** HostCmd_DS_11N_ADDBA_RSP */
typedef  struct _HostCmd_DS_11N_ADDBA_RSP
{
    /** Result of the ADDBA Response Operation */
    uint8_t add_rsp_result;
    /** Peer MAC address */
    uint8_t peer_mac_addr[MAC_ADDR_LENGTH];
    /** Dialog Token */
    uint8_t dialog_token;
    /** Status Code */
    uint16_t status_code;
    /** Block Ack Parameter Set */
    uint16_t block_ack_param_set;
    /** Block Act Timeout Value */
    uint16_t block_ack_tmo;
    /** Starting Sequence Number */
    uint16_t ssn;
} MLAN_PACK_END  HostCmd_DS_11N_ADDBA_RSP;

/** HostCmd_DS_11N_DELBA */
typedef  struct _HostCmd_DS_11N_DELBA
{
    /** Result of the ADDBA Request Operation */
    uint8_t del_result;
    /** Peer MAC address */
    uint8_t peer_mac_addr[MAC_ADDR_LENGTH];
    /** Delete Block Ack Parameter Set */
    uint16_t del_ba_param_set;
    /** Reason Code sent for DELBA */
    uint16_t reason_code;
    /** Reserved */
    uint8_t reserved;
} MLAN_PACK_END  HostCmd_DS_11N_DELBA;

/** HostCmd_DS_TXBUF_CFG*/
typedef  struct _HostCmd_DS_TXBUF_CFG
{
    /** Action */
    uint16_t action;
    /** Buffer Size */
    uint16_t buff_size;
    /** End Port_for Multiport */
    uint16_t mp_end_port;
    /** Reserved */
    uint16_t reserved3;
}  HostCmd_DS_TXBUF_CFG;

/** HostCmd_DS_AMSDU_AGGR_CTRL */
typedef  struct _HostCmd_DS_AMSDU_AGGR_CTRL
{
    /** Action */
    uint16_t action;
    /** Enable */
    uint16_t enable;
    /** Get the current Buffer Size valid */
    uint16_t curr_buf_size;
} MLAN_PACK_END  HostCmd_DS_AMSDU_AGGR_CTRL;

/** HostCmd_DS_11N_CFG */
typedef  struct _HostCmd_DS_11N_CFG
{
    /** Action */
    uint16_t action;
    /** HTTxCap */
    uint16_t ht_tx_cap;
    /** HTTxInfo */
    uint16_t ht_tx_info;
    /** Misc configuration */
    uint16_t misc_config;
} MLAN_PACK_END  HostCmd_DS_11N_CFG;

/** HostCmd_DS_11N_CFG */
typedef  struct _HostCmd_DS_REJECT_ADDBA_REQ
{
    /** Action */
    uint16_t action;
    /** Bit0    : host sleep activated
     *  Bit1    : auto reconnect enabled
     *  Others  : reserved
     */
    uint32_t conditions;
} MLAN_PACK_END  HostCmd_DS_REJECT_ADDBA_REQ;


/** MrvlIEtypes_WmmQueueStatus_t */
typedef  struct
{
    /** Header */
    MrvlIEtypesHeader_t header;
    /** Queue index */
    uint8_t queue_index;
    /** Disabled flag */
    uint8_t disabled;
    /** Medium time allocation in 32us units*/
    uint16_t medium_time;
    /** Flow required flag */
    uint8_t flow_required;
    /** Flow created flag */
    uint8_t flow_created;
    /** Reserved */
    uint32_t reserved;
} MLAN_PACK_END  MrvlIEtypes_WmmQueueStatus_t;

/**
 *  @brief Firmware command structure to retrieve the firmware WMM status.
 *
 *  Used to retrieve the status of each WMM AC Queue in TLV
 *    format (MrvlIEtypes_WmmQueueStatus_t) as well as the current WMM
 *    parameter IE advertised by the AP.
 *
 *  Used in response to a EVENT_WMM_STATUS_CHANGE event signaling
 *    a QOS change on one of the ACs or a change in the WMM Parameter in
 *    the Beacon.
 *
 *  TLV based command, byte arrays used for max sizing purpose. There are no
 *    arguments sent in the command, the TLVs are returned by the firmware.
 */
typedef  struct
{
    /** Queue status TLV */
    uint8_t queue_status_tlv[sizeof(MrvlIEtypes_WmmQueueStatus_t)
                             * MAX_AC_QUEUES];
    /** WMM parameter TLV */
    uint8_t wmm_param_tlv[sizeof(IEEEtypes_WmmParameter_t) + 2];
} MLAN_PACK_END  HostCmd_DS_WMM_GET_STATUS;

/** Type enumeration for the command result */
typedef  enum _mlan_cmd_result_e
{
    MLAN_CMD_RESULT_SUCCESS = 0,
    MLAN_CMD_RESULT_FAILURE = 1,
    MLAN_CMD_RESULT_TIMEOUT = 2,
    MLAN_CMD_RESULT_INVALID_DATA = 3
} MLAN_PACK_END  mlan_cmd_result_e;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_ADDTS_REQ firmware command
 */
typedef  struct
{
    mlan_cmd_result_e command_result;/**< Command result */
    uint32_t timeout_ms;		 /**< Timeout value in milliseconds */
    uint8_t dialog_token;		 /**< Dialog token */
    uint8_t ieee_status_code;		 /**< IEEE status code */
    uint8_t tspec_data[WMM_TSPEC_SIZE]; /**< TSPEC data */
    uint8_t addts_extra_ie_buf[WMM_ADDTS_EXTRA_IE_BYTES];
    /**< Extra IE buffer */
} MLAN_PACK_END  HostCmd_DS_WMM_ADDTS_REQ;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_DELTS_REQ firmware command
 */
typedef  struct
{
    mlan_cmd_result_e command_result;
    /**< Command result */
    uint8_t dialog_token;		/**< Dialog token */
    uint8_t ieee_reason_code;		/**< IEEE reason code */
    uint8_t tspec_data[WMM_TSPEC_SIZE];/**< TSPEC data */
} MLAN_PACK_END  HostCmd_DS_WMM_DELTS_REQ;

/**
 *  @brief Enumeration for the action field in the Queue configure command
 */
typedef enum
{
    WMM_QUEUE_CONFIG_ACTION_GET = 0,
    WMM_QUEUE_CONFIG_ACTION_SET = 1,
    WMM_QUEUE_CONFIG_ACTION_DEFAULT = 2,

    WMM_QUEUE_CONFIG_ACTION_MAX
} MLAN_PACK_END  mlan_wmm_queue_config_action_e;

/** Type enumeration of WMM AC_QUEUES */
typedef enum _mlan_wmm_ac_e
{
    WMM_AC_BK,
    WMM_AC_BE,
    WMM_AC_VI,
    WMM_AC_VO
} MLAN_PACK_END  mlan_wmm_ac_e;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_QUEUE_CONFIG firmware cmd
 *
 *  Set/Get/Default the Queue parameters for a specific AC in the firmware.
 */
typedef  struct
{
    mlan_wmm_queue_config_action_e action;
    /**< Set, Get, or Default */
    mlan_wmm_ac_e access_category;	   /**< WMM_AC_BK(0) to WMM_AC_VO(3) */
    /** @brief MSDU lifetime expiry per 802.11e
     *
     *   - Ignored if 0 on a set command
     *   - Set to the 802.11e specified 500 TUs when defaulted
     */
    uint16_t msdu_lifetime_expiry;
    uint8_t tlv_buffer[WMM_QUEUE_CONFIG_EXTRA_TLV_BYTES];
    /**< Not supported */
} MLAN_PACK_END  HostCmd_DS_WMM_QUEUE_CONFIG;

/** Type enumeration for the action field in the queue stats command */
typedef  enum _mlan_wmm_queue_stats_action_e
{
    MLAN_WMM_STATS_ACTION_START = 0,
    MLAN_WMM_STATS_ACTION_STOP = 1,
    MLAN_WMM_STATS_ACTION_GET_CLR = 2,
    MLAN_WMM_STATS_ACTION_SET_CFG = 3,	/* Not currently used */
    MLAN_WMM_STATS_ACTION_GET_CFG = 4,	/* Not currently used */
    MLAN_WMM_STATS_ACTION_MAX
} MLAN_PACK_END  mlan_wmm_queue_stats_action_e;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_QUEUE_STATS firmware cmd
 *
 *  Turn statistical collection on/off for a given AC or retrieve the
 *    accumulated stats for an AC and clear them in the firmware.
 */
typedef  struct
{
    mlan_wmm_queue_stats_action_e action;
    /**< Start, Stop, or Get */

    uint8_t select_is_userpri:1;
    /**< Set if select_bin is UP, Clear for AC */
    uint8_t select_bin:7;	/**< WMM_AC_BK(0) to WMM_AC_VO(3), or TID */
    uint16_t pkt_count;    /**< Number of successful packets transmitted */
    uint16_t pkt_loss;	    /**< Packets lost; not included in pktCount */
    uint32_t avg_queue_delay;
    /**< Average Queue delay in microsec */
    uint32_t avg_tx_delay; /**< Average Transmission delay in microsec */
    uint16_t used_time;    /**< Calc used time - units of 32 microsec */
    uint16_t policed_time; /**< Calc policed time - units of 32 microsec */
    /** @brief Queue Delay Histogram; number of packets per queue delay range
     *
     *  [0] -  0ms <= delay < 5ms
     *  [1] -  5ms <= delay < 10ms
     *  [2] - 10ms <= delay < 20ms
     *  [3] - 20ms <= delay < 30ms
     *  [4] - 30ms <= delay < 40ms
     *  [5] - 40ms <= delay < 50ms
     *  [6] - 50ms <= delay < msduLifetime (TUs)
     */
    uint16_t delay_histogram[WMM_STATS_PKTS_HIST_BINS];
    /** Reserved */
    uint16_t reserved_1;
} MLAN_PACK_END HostCmd_DS_WMM_QUEUE_STATS;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_TS_STATUS firmware cmd
 *
 *  Query the firmware to get the status of the WMM Traffic Streams
 */
typedef  struct
{
    /** TSID: Range: 0->7 */
    uint8_t tid;
    /** TSID specified is valid */
    uint8_t valid;
    /** AC TSID is active on */
    uint8_t access_category;
    /** UP specified for the TSID */
    uint8_t user_priority;
    /** Power save mode for TSID: 0 (legacy), 1 (UAPSD) */
    uint8_t psb;
    /** Uplink(1), Downlink(2), Bidirectional(3) */
    uint8_t flow_dir;
    /** Medium time granted for the TSID */
    uint16_t medium_time;
} MLAN_PACK_END  HostCmd_DS_WMM_TS_STATUS;


/** Key Info flag for multicast key */
#define KEY_INFO_MCAST_KEY      0x01
/** Key Info flag for unicast key */
#define KEY_INFO_UCAST_KEY      0x02
/** Key Info flag for enable key */
#define KEY_INFO_ENABLE_KEY     0x04
/** Key Info flag for default key */
#define KEY_INFO_DEFAULT_KEY    0x08
/** Key Info flag for TX key */
#define KEY_INFO_TX_KEY         0x10
/** Key Info flag for RX key */
#define KEY_INFO_RX_KEY         0x20
#define KEY_INFO_CMAC_AES_KEY   0x400
/** PN size for WPA/WPA2 */
#define WPA_PN_SIZE             8
/** PN size for PMF IGTK */
#define IGTK_PN_SIZE            8
/** WAPI KEY size */
#define WAPI_KEY_SIZE           32
/** key params fix size */
#define KEY_PARAMS_FIXED_LEN    10
/** key index mask */
#define KEY_INDEX_MASK          0xf
/* A few details needed for WEP (Wireless Equivalent Privacy) */
/** 104 bits */
#define MAX_WEP_KEY_SIZE	13
/** 40 bits RC4 - WEP */
#define MIN_WEP_KEY_SIZE	5
/** packet number size */
#define PN_SIZE			16
/** max seq size of wpa/wpa2 key */
#define SEQ_MAX_SIZE        8
/** WPA AES key length */
#define WPA_AES_KEY_LEN                 16
/** WPA TKIP key length */
#define WPA_TKIP_KEY_LEN                32
/** WPA AES IGTK key length */
#define CMAC_AES_KEY_LEN                16
/** IGTK key length */
#define WPA_IGTK_KEY_LEN                16
/** wep_param */
typedef  struct _wep_param_t
{
    /** key_len */
    uint16_t key_len;
    /** wep key */
    uint8_t key[MAX_WEP_KEY_SIZE];
} MLAN_PACK_END  wep_param_t;

/** tkip_param */
typedef  struct _tkip_param
{
    /** Rx packet num */
    uint8_t pn[WPA_PN_SIZE];
    /** key_len */
    uint16_t key_len;
    /** tkip key */
    uint8_t key[WPA_TKIP_KEY_LEN];
} MLAN_PACK_END tkip_param;

/** aes_param */
typedef  struct _aes_param
{
    /** Rx packet num */
    uint8_t pn[WPA_PN_SIZE];
    /** key_len */
    uint16_t key_len;
    /** aes key */
    uint8_t key[WPA_AES_KEY_LEN];
} MLAN_PACK_END aes_param;

/** wapi_param */
typedef  struct _wapi_param
{
    /** Rx packet num */
    uint8_t pn[PN_SIZE];
    /** key_len */
    uint16_t key_len;
    /** wapi key */
    uint8_t key[WAPI_KEY_SIZE];
} MLAN_PACK_END  wapi_param;

/** cmac_aes_param */
typedef  struct _cmac_aes_param
{
    /** IGTK pn */
    uint8_t ipn[IGTK_PN_SIZE];
    /** key_len */
    uint16_t key_len;
    /** aes key */
    uint8_t key[CMAC_AES_KEY_LEN];
} MLAN_PACK_END  cmac_aes_param;

/** MrvlIEtype_KeyParamSet_t */
typedef  struct _MrvlIEtype_KeyParamSetV2_t
{
    /** Type ID */
    uint16_t type;
    /** Length of Payload */
    uint16_t length;
    /** mac address */
    uint8_t mac_addr[MAC_ADDR_LENGTH];
    /** key index */
    uint8_t key_idx;
    /** Type of Key: WEP=0, TKIP=1, AES=2, WAPI=3 AES_CMAC=4 */
    uint8_t key_type;
    /** Key Control Info specific to a key_type_id */
    uint16_t key_info;
    union
    {
        /** wep key param */
        wep_param_t wep;
        /** tkip key param */
        tkip_param tkip;
        /** aes key param */
        aes_param aes;
        /** wapi key param */
        wapi_param wapi;
        /** IGTK key param */
        cmac_aes_param cmac_aes;
    } key_params;
} MLAN_PACK_END MrvlIEtype_KeyParamSetV2_t;

/** HostCmd_DS_802_11_KEY_MATERIAL */
typedef  struct _HostCmd_DS_802_11_KEY_MATERIAL
{
    /** Action */
    uint16_t action;
    /** Key parameter set */
    MrvlIEtype_KeyParamSetV2_t key_param_set;
} MLAN_PACK_END HostCmd_DS_802_11_KEY_MATERIAL;

/** HostCmd_DS_802_11_SUPPLICANT_PMK */
typedef  struct _HostCmd_DS_802_11_SUPPLICANT_PMK
{
    /** CMD Action GET/SET/CLEAR */
    uint16_t action;
    /** CacheResult initialized to 0 */
    uint16_t cache_result;
    /** TLV Buffer */
    uint8_t tlv_buffer[1];
    /** MrvlIEtypes_SsidParamSet_t  SsidParamSet;
      * MrvlIEtypes_PMK_t           Pmk;
      * MrvlIEtypes_Passphrase_t    Passphrase;
      * MrvlIEtypes_Bssid_t         Bssid;
      **/
} MLAN_PACK_END HostCmd_DS_802_11_SUPPLICANT_PMK;

/*
 * This struct will GET the Supplicant supported bitmaps
 * The GET_CURRENT action will get the network profile used
 * for the current assocation.
 * Define data structure for HostCmd_CMD_802_11_SUPPLICANT_PROFILE
 */
typedef  struct _HostCmd_DS_802_11_SUPPLICANT_PROFILE
{
    /** GET/SET/GET_CURRENT */
    uint16_t action;
    /** Reserved */
    uint16_t reserved;
    /** TLVBuffer */
    uint8_t tlv_buf[1];
    /* MrvlIEtypes_EncrProto_t */
} MLAN_PACK_END  HostCmd_DS_802_11_SUPPLICANT_PROFILE;

/** HostCmd_DS_VERSION_EXT */
typedef  struct _HostCmd_DS_VERSION_EXT
{
    /** Selected version string */
    uint8_t version_str_sel;
    /** Version string */
    char version_str[128];
} MLAN_PACK_END  HostCmd_DS_VERSION_EXT;

/** HostCmd_DS_802_11_IBSS_STATUS */
typedef  struct _HostCmd_DS_802_11_IBSS_STATUS
{
    /** Action */
    uint16_t action;
    /** Enable */
    uint16_t enable;
    /** BSSID */
    uint8_t bssid[MAC_ADDR_LENGTH];
    /** Beacon interval */
    uint16_t beacon_interval;
    /** ATIM window interval */
    uint16_t atim_window;
    /** User G rate protection */
    uint16_t use_g_rate_protect;
} MLAN_PACK_END HostCmd_DS_802_11_IBSS_STATUS;

/** custom IE info */
typedef struct _custom_ie_info
{
    /** size of buffer */
    uint16_t buf_size;
    /** no of buffers of buf_size */
    uint16_t buf_count;
} MLAN_PACK_END custom_ie_info;

/** TLV buffer : Max Mgmt IE */
typedef  struct _tlvbuf_max_mgmt_ie
{
    /** Type */
    uint16_t type;
    /** Length */
    uint16_t len;
    /** No of tuples */
    uint16_t count;
    /** custom IE info tuples */
    custom_ie_info info[MAX_MGMT_IE_INDEX];
} MLAN_PACK_END  tlvbuf_max_mgmt_ie;

/** custom IE */
typedef struct _custom_ie
{
    /** IE Index */
    uint16_t ie_index;
    /** Mgmt Subtype Mask */
    uint16_t mgmt_subtype_mask;
    /** IE Length */
    uint16_t ie_length;
    /** IE buffer */
    uint8_t ie_buffer[0];
} MLAN_PACK_END  custom_ie;

/** TLV buffer : custom IE */
typedef  struct _tlvbuf_custom_ie
{
    /** Type */
    uint16_t type;
    /** Length */
    uint16_t len;
    /** IE data */
    custom_ie ie_data_list[MAX_MGMT_IE_INDEX_TO_FW];
    /** Max mgmt IE TLV */
    tlvbuf_max_mgmt_ie max_mgmt_ie;
} MLAN_PACK_END  mlan_ds_misc_custom_ie;

/** HostCmd_DS_MGMT_IE_LIST_CFG */
typedef  struct _HostCmd_DS_MGMT_IE_LIST
{
    /** Action */
    uint16_t action;
    /** Get/Set mgmt IE */
    mlan_ds_misc_custom_ie ds_mgmt_ie;
} MLAN_PACK_END  HostCmd_DS_MGMT_IE_LIST_CFG;



/** HostCmd_DS_ECL_SYSTEM_CLOCK_CONFIG */
typedef  struct _HostCmd_DS_ECL_SYSTEM_CLOCK_CONFIG
{
    /** Action */
    uint16_t action;
    /** Current system clock */
    uint16_t cur_sys_clk;
    /** Clock type */
    uint16_t sys_clk_type;
    /** Length of clocks */
    uint16_t sys_clk_len;
    /** System clocks */
    uint16_t sys_clk[16];
} MLAN_PACK_END  HostCmd_DS_ECL_SYSTEM_CLOCK_CONFIG;

/** HostCmd_CMD_MAC_REG_ACCESS */
typedef  struct _HostCmd_DS_MAC_REG_ACCESS
{
    /** Action */
    uint16_t action;
    /** MAC register offset */
    uint16_t offset;
    /** MAC register value */
    uint32_t value;
} MLAN_PACK_END  HostCmd_DS_MAC_REG_ACCESS;

/** HostCmd_CMD_BBP_REG_ACCESS */
typedef  struct _HostCmd_DS_BBP_REG_ACCESS
{
    /** Acion */
    uint16_t action;
    /** BBP register offset */
    uint16_t offset;
    /** BBP register value */
    uint8_t value;
    /** Reserved field */
    uint8_t reserved[3];
} MLAN_PACK_END  HostCmd_DS_BBP_REG_ACCESS;

/**  HostCmd_CMD_RF_REG_ACCESS */
typedef  struct _HostCmd_DS_RF_REG_ACCESS
{
    /** Action */
    uint16_t action;
    /** RF register offset */
    uint16_t offset;
    /** RF register value */
    uint8_t value;
    /** Reserved field */
    uint8_t reserved[3];
} MLAN_PACK_END  HostCmd_DS_RF_REG_ACCESS;

/** HostCmd_DS_802_11_EEPROM_ACCESS */
typedef  struct _HostCmd_DS_802_11_EEPROM_ACCESS
{
    /** Action */
    uint16_t action;

    /** multiple 4 */
    uint16_t offset;
    /** Number of bytes */
    uint16_t byte_count;
    /** Value */
    uint8_t value;
} MLAN_PACK_END HostCmd_DS_802_11_EEPROM_ACCESS;

/** HostCmd_DS_MEM_ACCESS */
typedef  struct _HostCmd_DS_MEM_ACCESS
{
    /** Action */
    uint16_t action;
    /** Reserved field */
    uint16_t reserved;
    /** Address */
    uint32_t addr;
    /** Value */
    uint32_t value;
} MLAN_PACK_END  HostCmd_DS_MEM_ACCESS;

/** HostCmd_DS_TARGET_ACCESS */
typedef  struct _HostCmd_DS_TARGET_ACCESS
{
    /** Action */
    uint16_t action;
    /** CSU Target Device. 1: CSU, 2: PSU */
    uint16_t csu_target;
    /** Target Device Address */
    uint16_t address;
    /** Data */
    uint8_t data;
} MLAN_PACK_END  HostCmd_DS_TARGET_ACCESS;

/** HostCmd_DS_INACTIVITY_TIMEOUT_EXT */
typedef  struct _HostCmd_DS_INACTIVITY_TIMEOUT_EXT
{
    /** ACT_GET/ACT_SET */
    uint16_t action;
    /** uS, 0 means 1000uS(1ms) */
    uint16_t timeout_unit;
    /** Inactivity timeout for unicast data */
    uint16_t unicast_timeout;
    /** Inactivity timeout for multicast data */
    uint16_t mcast_timeout;
    /** Timeout for additional RX traffic after Null PM1 packet exchange */
    uint16_t ps_entry_timeout;
    /** Reserved to further expansion */
    uint16_t reserved;
} MLAN_PACK_END  HostCmd_DS_INACTIVITY_TIMEOUT_EXT;

/** HostCmd_SYS_CONFIG */
typedef  struct _HostCmd_DS_SYS_CONFIG
{
    /** CMD Action GET/SET*/
    uint16_t action;
    /** Tlv buffer */
    uint8_t tlv_buffer[1];
} MLAN_PACK_END  HostCmd_DS_SYS_CONFIG;

/** HostCmd_SYS_CONFIG */
typedef  struct _HostCmd_DS_SYS_INFO
{
    /** sys info */
    uint8_t sys_info[64];
} MLAN_PACK_END  HostCmd_DS_SYS_INFO;

/** HostCmd_DS_STA_DEAUTH */
typedef  struct _HostCmd_DS_STA_DEAUTH
{
    /** mac address */
    uint8_t mac[MAC_ADDR_LENGTH];
    /** reason code */
    uint16_t reason;
} MLAN_PACK_END  HostCmd_DS_STA_DEAUTH;

/** HostCmd_DS_STA_LIST */
typedef  struct _HostCmd_DS_STA_LIST
{
    /** Number of STAs */
    uint16_t sta_count;
    /* MrvlIEtypes_sta_info_t sta_info[0]; */
} MLAN_PACK_END  HostCmd_DS_STA_LIST;

/** HostCmd_DS_POWER_MGMT */
typedef  struct _HostCmd_DS_POWER_MGMT_EXT
{
    /** CMD Action Get/Set*/
    uint16_t action;
    /** power mode */
    uint16_t power_mode;
} MLAN_PACK_END HostCmd_DS_POWER_MGMT_EXT;

/* HostCmd_DS_802_11_SLEEP_PERIOD */
typedef  struct _HostCmd_DS_802_11_SLEEP_PERIOD
{
    /** ACT_GET/ACT_SET */
    uint16_t action;

    /** Sleep Period in msec */
    uint16_t sleep_pd;
} MLAN_PACK_END HostCmd_DS_802_11_SLEEP_PERIOD;

/* HostCmd_DS_802_11_SLEEP_PARAMS */
typedef  struct _HostCmd_DS_802_11_SLEEP_PARAMS
{
    /** ACT_GET/ACT_SET */
    uint16_t action;
    /** Sleep clock error in ppm */
    uint16_t error;
    /** Wakeup offset in usec */
    uint16_t offset;
    /** Clock stabilization time in usec */
    uint16_t stable_time;
    /** Control periodic calibration */
    uint8_t cal_control;
    /** Control the use of external sleep clock */
    uint8_t external_sleep_clk;
    /** Reserved field, should be set to zero */
    uint16_t reserved;
} MLAN_PACK_END  HostCmd_DS_802_11_SLEEP_PARAMS;

typedef  struct _HostCmd_DS_SDIO_GPIO_INT_CONFIG
{
    /** Action */
    uint16_t action;
    /** GPIO interrupt pin */
    uint16_t gpio_pin;
    /** GPIO interrupt edge, 1: failing edge; 0: raising edge */
    uint16_t gpio_int_edge;
    /** GPIO interrupt pulse widthin usec units */
    uint16_t gpio_pulse_width;
} MLAN_PACK_END  HostCmd_DS_SDIO_GPIO_INT_CONFIG;

typedef  struct _HostCmd_DS_SDIO_PULL_CTRL
{
    /** Action */
    uint16_t action;
    /** The delay of pulling up in us */
    uint16_t pull_up;
    /** The delay of pulling down in us */
    uint16_t pull_down;
} MLAN_PACK_END HostCmd_DS_SDIO_PULL_CTRL;

/** HostCmd_DS_SET_BSS_MODE */
typedef  struct _HostCmd_DS_SET_BSS_MODE
{
    /** connection type */
    uint8_t con_type;
} MLAN_PACK_END  HostCmd_DS_SET_BSS_MODE;

/** HostCmd_DS_CMD_TX_DATA_PAUSE */
typedef  struct _HostCmd_DS_CMD_TX_DATA_PAUSE
{
    /** Action */
    uint16_t action;
    /** Enable/disable Tx data pause */
    uint8_t enable_tx_pause;
    /** Max number of TX buffers allowed for all PS clients*/
    uint8_t pause_tx_count;
} MLAN_PACK_END HostCmd_DS_CMD_TX_DATA_PAUSE;

/** HostCmd_DS_REMAIN_ON_CHANNEL */
typedef  struct _HostCmd_DS_REMAIN_ON_CHANNEL
{
    /** Action 0-GET, 1-SET, 4 CLEAR*/
    uint16_t action;
    /** Not used set to zero */
    uint8_t status;
    /** Not used set to zero */
    uint8_t reserved;
    /** Band cfg */
    uint8_t bandcfg;
    /** channel */
    uint8_t channel;
    /** remain time: Unit ms*/
    uint32_t remain_period;
} MLAN_PACK_END HostCmd_DS_REMAIN_ON_CHANNEL;

/** HostCmd_DS_WIFI_DIRECT_MODE */
typedef  struct _HostCmd_DS_WIFI_DIRECT_MODE
{
    /** Action 0-GET, 1-SET*/
    uint16_t action;
    /**0:disable 1:listen 2:GO 3:p2p client 4:find 5:stop find*/
    uint16_t mode;
} MLAN_PACK_END  HostCmd_DS_WIFI_DIRECT_MODE;

/** HostCmd_DS_REMAIN_ON_CHANNEL */
typedef  struct _HostCmd_DS_WIFI_DIRECT_PARAM_CONFIG
{
    /** Action 0-GET, 1-SET */
    uint16_t action;
    /** MrvlIEtypes_NoA_setting_t
     *  MrvlIEtypes_OPP_PS_setting_t
     */
} MLAN_PACK_END  HostCmd_DS_WIFI_DIRECT_PARAM_CONFIG;

struct coalesce_filt_field_param
{
    uint8_t operation;
    uint8_t operand_len;
    uint16_t offset;
    uint8_t operand_byte_stream[4];
} MLAN_PACK_END ;

struct coalesce_receive_filt_rule
{
    MrvlIEtypesHeader_t header;
    uint8_t num_of_fields;
    uint8_t pkt_type;
    uint16_t max_coalescing_delay;
    struct coalesce_filt_field_param params[0];
} MLAN_PACK_END ;

/** HostCmd_DS_COALESCE_CONFIG */
typedef  struct _HostCmd_DS_COALESCE_CONFIG
{
    /** Action 0-GET, 1-SET */
    uint16_t action;
    uint16_t num_of_rules;
    struct coalesce_receive_filt_rule rule[0];
} MLAN_PACK_END  HostCmd_DS_COALESCE_CONFIG;

/** HostCmd_CMD_HS_WAKEUP_REASON */
typedef  struct _HostCmd_DS_HS_WAKEUP_REASON
{
    /** wakeupReason:
      * 0: unknown
      * 1: Broadcast data matched
      * 2: Multicast data matched
      * 3: Unicast data matched
      * 4: Maskable event matched
      * 5. Non-maskable event matched
      * 6: Non-maskable condition matched (EAPoL rekey)
      * 7: Magic pattern matched
      * Others: reserved. (set to 0) */
    uint16_t wakeup_reason;
} MLAN_PACK_END HostCmd_DS_HS_WAKEUP_REASON;

/** HostCmd_CONFIG_LOW_PWR_MODE */
typedef  struct _HostCmd_CONFIG_LOW_PWR_MODE
{
    /** Enable LPM */
    uint8_t enable;
} MLAN_PACK_END  HostCmd_CONFIG_LOW_PWR_MODE;

typedef  struct _HostCmd_DS_RX_PKT_COAL_CFG
{
    /** Action */
    uint16_t action;
    /** Packet threshold */
    uint32_t packet_threshold;
    /** Timeout */
    uint16_t delay;
} MLAN_PACK_END HostCmd_DS_RX_PKT_COAL_CFG;

/** MrvlIEtypes_eapol_pkt_t */
typedef  struct _MrvlIEtypes_eapol_pkt_t
{
    /** Header */
    MrvlIEtypesHeader_t header;
    /** eapol pkt buf */
    uint8_t pkt_buf[0];
} MLAN_PACK_END  MrvlIEtypes_eapol_pkt_t;

/** HostCmd_DS_EAPOL_PKT */
typedef  struct _HostCmd_DS_EAPOL_PKT
{
    /** Action */
    uint16_t action;
    /** TLV buffer */
    MrvlIEtypes_eapol_pkt_t tlv_eapol;
} MLAN_PACK_END  HostCmd_DS_EAPOL_PKT;

/** Ethernet header */
typedef struct
{
    /** Ethernet header destination address */
    uint8_t dest_addr[MAC_ADDR_LENGTH];
    /** Ethernet header source address */
    uint8_t src_addr[MAC_ADDR_LENGTH];
    /** Ethernet header length */
    uint16_t h803_len;

} MLAN_PACK_END Eth803Hdr_t;

/** Rx packet header */
typedef /*MLAN_PACK_START*/ struct
{
    /** Etherner header */
    Eth803Hdr_t eth803_hdr;

} MLAN_PACK_END RxPacketHdr_t;


#define CMD_HDR_SIZE	12
#define CMD_SDIO_HDR_SIZE	4
#define TYPE_DATA	0
#define TYPE_CMD_CMDRSP	1
#define TYPE_EVENT	3
/** HostCmd_DS_COMMAND */
typedef struct  _HostCmd_DS_COMMAND
{
    /** Command Header : pack_len */
    uint16_t pack_len;
    /** Command Header : pack_type */
    uint16_t pack_type;
    /** Command Header : Command */
    uint16_t command;
    /** Command Header : Size */
    uint16_t size;
    /** Command Header : Sequence number */
    uint8_t seq_num;
    /** Command Header : Bss */
    uint8_t bss;
    /** Command Header : Result */
    uint16_t result;
    /** Command Body */
    union
    {
        /** Hardware specifications */
        HostCmd_DS_GET_HW_SPEC hw_spec;
        /** Cfg data */
        HostCmd_DS_802_11_CFG_DATA cfg_data;
        /** MAC control */
        HostCmd_DS_MAC_CONTROL mac_ctrl;
        /** MAC address */
        HostCmd_DS_802_11_MAC_ADDRESS mac_addr;
        /** MAC muticast address */
        HostCmd_DS_MAC_MULTICAST_ADR mc_addr;
        /** Get log */
        HostCmd_DS_802_11_GET_LOG get_log;
        /** RSSI information */
        HostCmd_DS_802_11_RSSI_INFO rssi_info;
        /** RSSI information response */
        HostCmd_DS_802_11_RSSI_INFO_RSP rssi_info_rsp;
        /** SNMP MIB */
        HostCmd_DS_802_11_SNMP_MIB smib;
        /** Radio control */
        HostCmd_DS_802_11_RADIO_CONTROL radio;
        /** RF channel */
        HostCmd_DS_802_11_RF_CHANNEL rf_channel;
        /** Tx rate query */
        HostCmd_TX_RATE_QUERY tx_rate;
        /** Tx rate configuration */
        HostCmd_DS_TX_RATE_CFG tx_rate_cfg;
        /** Tx power configuration */
        HostCmd_DS_TXPWR_CFG txp_cfg;
        /** RF Tx power configuration */
        HostCmd_DS_802_11_RF_TX_POWER txp;

        /** RF antenna */
        HostCmd_DS_802_11_RF_ANTENNA antenna;
        /** Enhanced power save command */
        HostCmd_DS_802_11_PS_MODE_ENH psmode_enh;
        HostCmd_DS_802_11_HS_CFG_ENH opt_hs_cfg;
        /** Scan */
        HostCmd_DS_802_11_SCAN scan;

        /** Mgmt frame subtype mask */
        HostCmd_DS_RX_MGMT_IND rx_mgmt_ind;
        /** Scan response */
        HostCmd_DS_802_11_SCAN_RSP scan_resp;

        HostCmd_DS_802_11_BG_SCAN_CONFIG bg_scan_config;
        HostCmd_DS_802_11_BG_SCAN_QUERY bg_scan_query;
        HostCmd_DS_802_11_BG_SCAN_QUERY_RSP bg_scan_query_resp;
        HostCmd_DS_SUBSCRIBE_EVENT subscribe_event;
        HostCmd_DS_OTP_USER_DATA otp_user_data;
        /** Associate */
        HostCmd_DS_802_11_ASSOCIATE associate;

        /** Associate response */
        HostCmd_DS_802_11_ASSOCIATE_RSP associate_rsp;
        /** Deauthenticate */
        HostCmd_DS_802_11_DEAUTHENTICATE deauth;
        /** Ad-Hoc start */
        HostCmd_DS_802_11_AD_HOC_START adhoc_start;
        /** Ad-Hoc start result */
        HostCmd_DS_802_11_AD_HOC_START_RESULT adhoc_start_result;
        /** Ad-Hoc join result */
        HostCmd_DS_802_11_AD_HOC_JOIN_RESULT adhoc_join_result;
        /** Ad-Hoc join */
        HostCmd_DS_802_11_AD_HOC_JOIN adhoc_join;
        /** Domain information */
        HostCmd_DS_802_11D_DOMAIN_INFO domain_info;
        /** Domain information response */
        HostCmd_DS_802_11D_DOMAIN_INFO_RSP domain_info_resp;
        /** Add BA request */
        HostCmd_DS_11N_ADDBA_REQ add_ba_req;
        /** Add BA response */
        HostCmd_DS_11N_ADDBA_RSP add_ba_rsp;
        /** Delete BA entry */
        HostCmd_DS_11N_DELBA del_ba;
        /** Tx buffer configuration */
        HostCmd_DS_TXBUF_CFG tx_buf;
        /** AMSDU Aggr Ctrl configuration */
        HostCmd_DS_AMSDU_AGGR_CTRL amsdu_aggr_ctrl;
        /** 11n configuration */
        HostCmd_DS_11N_CFG htcfg;
        /** reject addba req conditions configuration */
        HostCmd_DS_REJECT_ADDBA_REQ rejectaddbareq;
        /** WMM status get */
        HostCmd_DS_WMM_GET_STATUS get_wmm_status;
        /** WMM ADDTS */
        HostCmd_DS_WMM_ADDTS_REQ add_ts;
        /** WMM DELTS */
        HostCmd_DS_WMM_DELTS_REQ del_ts;
        /** WMM set/get queue config */
        HostCmd_DS_WMM_QUEUE_CONFIG queue_config;
        /** WMM on/of/get queue statistics */
        HostCmd_DS_WMM_QUEUE_STATS queue_stats;
        /** WMM get traffic stream status */
        HostCmd_DS_WMM_TS_STATUS ts_status;
        /** Key material */
        HostCmd_DS_802_11_KEY_MATERIAL key_material;
        /** E-Supplicant PSK */
        HostCmd_DS_802_11_SUPPLICANT_PMK esupplicant_psk;
        /** E-Supplicant profile */
        HostCmd_DS_802_11_SUPPLICANT_PROFILE esupplicant_profile;
        /** Extended version */
        HostCmd_DS_VERSION_EXT verext;
        /** Adhoc Coalescing */
        HostCmd_DS_802_11_IBSS_STATUS ibss_coalescing;
        /** Mgmt IE list configuration */
        HostCmd_DS_MGMT_IE_LIST_CFG mgmt_ie_list;
        /** System clock configuration */
        HostCmd_DS_ECL_SYSTEM_CLOCK_CONFIG sys_clock_cfg;
        /** MAC register access */
        HostCmd_DS_MAC_REG_ACCESS mac_reg;
        /** BBP register access */
        HostCmd_DS_BBP_REG_ACCESS bbp_reg;
        /** RF register access */
        HostCmd_DS_RF_REG_ACCESS rf_reg;
        /** EEPROM register access */
        HostCmd_DS_802_11_EEPROM_ACCESS eeprom;
        /** Memory access */
        HostCmd_DS_MEM_ACCESS mem;
        /** Target device access */
        HostCmd_DS_TARGET_ACCESS target;

        /** Inactivity timeout extend */
        HostCmd_DS_INACTIVITY_TIMEOUT_EXT inactivity_to;

        HostCmd_DS_SYS_CONFIG sys_config;
        HostCmd_DS_SYS_INFO sys_info;
        HostCmd_DS_STA_DEAUTH sta_deauth;
        HostCmd_DS_STA_LIST sta_list;
        HostCmd_DS_POWER_MGMT_EXT pm_cfg;

        /** Sleep period command */
        HostCmd_DS_802_11_SLEEP_PERIOD sleep_pd;
        /** Sleep params command */
        HostCmd_DS_802_11_SLEEP_PARAMS sleep_param;

        /** SDIO GPIO interrupt config command */
        HostCmd_DS_SDIO_GPIO_INT_CONFIG sdio_gpio_int;
        HostCmd_DS_SDIO_PULL_CTRL sdio_pull_ctl;
        HostCmd_DS_SET_BSS_MODE bss_mode;
        HostCmd_DS_CMD_TX_DATA_PAUSE tx_data_pause;

        HostCmd_DS_REMAIN_ON_CHANNEL remain_on_chan;
        HostCmd_DS_WIFI_DIRECT_MODE wifi_direct_mode;
        HostCmd_DS_WIFI_DIRECT_PARAM_CONFIG p2p_params_config;

        HostCmd_DS_COALESCE_CONFIG coalesce_config;
        HostCmd_DS_HS_WAKEUP_REASON hs_wakeup_reason;
        HostCmd_CONFIG_LOW_PWR_MODE low_pwr_mode_cfg;

        HostCmd_DS_RX_PKT_COAL_CFG rx_pkt_coal_cfg;
        HostCmd_DS_EAPOL_PKT eapol_pkt;
    } params;
} MLAN_PACK_END  HostCmd_DS_COMMAND;


/** Bit mask for TxPD status field for null packet */
#define MRVDRV_TxPD_POWER_MGMT_NULL_PACKET 0x01
/** Bit mask for TxPD status field for last packet */
#define MRVDRV_TxPD_POWER_MGMT_LAST_PACKET 0x08

/** Packet type: 802.11 */
#define PKT_TYPE_802DOT11   0x05
#define PKT_TYPE_MGMT_FRAME 0xE5
/** Packet type: AMSDU */
#define PKT_TYPE_AMSDU      0xE6
/** Packet type: BAR */
#define PKT_TYPE_BAR        0xE7
/** Packet type: debugging */
#define PKT_TYPE_DEBUG      0xEF

/** TxPD descriptor */
typedef  struct _TxPD
{
    /** Command Header : pack_len */
    uint16_t pack_len;
    /** Command Header : pack_type */
    uint16_t pack_type;
    /** BSS type */
    uint8_t bss_type;
    /** BSS number */
    uint8_t bss_num;
    /** Tx packet length */
    uint16_t tx_pkt_length;
    /** Tx packet offset */
    uint16_t tx_pkt_offset;
    /** Tx packet type */
    uint16_t tx_pkt_type;
    /** Tx Control */
    uint32_t tx_control;
    /** Pkt Priority */
    uint8_t priority;
    /** Transmit Pkt Flags*/
    uint8_t flags;
    /** Amount of time the packet has been queued in the driver (units = 2ms)*/
    uint8_t pkt_delay_2ms;
    /** Reserved */
    uint8_t reserved1;
    uint8_t payload[1]; // 数据链路层上的帧
} MLAN_PACK_END TxPD, *PTxPD;

/** RxPD Descriptor */
typedef  struct _RxPD
{
    /** Command Header : pack_len */
    uint16_t pack_len;
    /** Command Header : pack_type */
    uint16_t pack_type;
    /** BSS type */
    uint8_t bss_type;
    /** BSS number */
    uint8_t bss_num;
    /** Rx Packet Length */
    uint16_t rx_pkt_length;
    /** Rx Pkt offset */
    uint16_t rx_pkt_offset;
    /** Rx packet type */
    uint16_t rx_pkt_type;
    /** Sequence number */
    uint16_t seq_num;
    /** Packet Priority */
    uint8_t priority;
    /** Rx Packet Rate */
    uint8_t rx_rate;
    /** SNR */
    int8_t snr;
    /** Noise Floor */
    int8_t nf;
    /** Ht Info [Bit 0] RxRate format: LG=0, HT=1
     * [Bit 1]  HT Bandwidth: BW20 = 0, BW40 = 1
     * [Bit 2]  HT Guard Interval: LGI = 0, SGI = 1 */
    uint8_t ht_info;
    /** Reserved */
    uint8_t reserved;
    uint8_t *payload;
} MLAN_PACK_END RxPD, *PRxPD;

/** TxPD descriptor */
typedef struct _UapTxPD
{
    /** Command Header : pack_len */
    uint16_t pack_len;
    /** Command Header : pack_type */
    uint16_t pack_type;
    /** BSS type */
    uint8_t bss_type;
    /** BSS number */
    uint8_t bss_num;
    /** Tx packet length */
    uint16_t tx_pkt_length;
    /** Tx packet offset */
    uint16_t tx_pkt_offset;
    /** Tx packet type */
    uint16_t tx_pkt_type;
    /** Tx Control */
    uint32_t tx_control;
    /** Pkt Priority */
    uint8_t priority;
    /** Transmit Pkt Flags*/
    uint8_t flags;
    /** Amount of time the packet has been queued in the driver (units = 2ms)*/
    uint8_t pkt_delay_2ms;
    /** Reserved */
    uint8_t reserved1;
    /** Reserved */
    uint32_t reserved;
} MLAN_PACK_END UapTxPD, *PUapTxPD;

/** RxPD Descriptor */
typedef struct _UapRxPD
{
    /** Command Header : pack_len */
    uint16_t pack_len;
    /** Command Header : pack_type */
    uint16_t pack_type;
    /** BSS Type */
    uint8_t bss_type;
    /** BSS number*/
    uint8_t bss_num;
    /** Rx packet length */
    uint16_t rx_pkt_length;
    /** Rx packet offset */
    uint16_t rx_pkt_offset;
    /** Rx packet type */
    uint16_t rx_pkt_type;
    /** Sequence number */
    uint16_t seq_num;
    /** Packet Priority */
    uint8_t priority;
    /** Reserved */
    uint8_t reserved;
} MLAN_PACK_END UapRxPD, *PUapRxPD;



#define TX_BUFFER_SIZE 1024
#define RX_BUFFER_SIZE (3*1024)


typedef enum
{
    CON_STA_NO_NONNECTED,
    CON_STA_CONNECTING,
    CON_STA_CONNECTED,
} connect_status_e;

typedef struct
{
    uint8_t mac_address[MAC_ADDR_LENGTH];	/* 要连接的地址 */
    uint8_t ssid[MAX_SSID_LENGTH];
    uint8_t ssid_len;
    uint8_t pwd[MAX_PHRASE_LENGTH];
    uint8_t pwd_len;
    uint8_t security;
    uint16_t cap_info;
    connect_status_e con_status;
} connect_info_t;

typedef struct _sta_mac_t
{
    uint8_t used;
    uint8_t sta_mac_address[MAC_ADDR_LENGTH];
} sta_mac_t;


typedef struct
{
	void (*wifi_init_result)(uint8_t status);
	void (*wifi_scan_result)(uint8_t *ssid,uint8_t rssi,uint8_t channel,uint8_t *encryption_mode);
	void (*wifi_connect_result)(uint8_t status);
	void (*wifi_start_ap_result)(uint8_t status);
	void (*wifi_stop_ap_result)(uint8_t status);
	void (*wifi_ap_connect_result)(uint8_t *name,uint8_t *mac,uint8_t *ip);
	void (*wifi_ap_disconnect_result)(uint8_t *mac);
}wifi_cb_t;

typedef struct
{
    uint8_t bss_type;
    uint8_t mac_address[MAC_ADDR_LENGTH];				/* 本地mac 地址 */
    uint8_t remote_mac_address[MAC_ADDR_LENGTH];	/* 如果作为STA mode下，连接的AP mode的地址 */
    sta_mac_t sta_mac[WIFI_CONF_MAX_CLIENT_NUM];
    uint32_t control_io_port;
    uint8_t *mp_regs;
    uint16_t write_bitmap;
    uint16_t read_bitmap;
    uint16_t curr_rd_port;
    uint16_t curr_wr_port;
    uint16_t mp_end_port;

    uint8_t* tx_data_ptr;

    connect_info_t con_info;
} mrvl88w8801_core_t;
typedef mrvl88w8801_core_t* pmrvl88w8801_core_t;

uint8_t mrvl88w8801_init(wifi_cb_t *cb);
uint8_t mrvl88w8801_deinit(void);
uint8_t mrvl88w8801_process_packet(void);
uint8_t mrvl88w8801_scan(uint8_t *channel,uint8_t channel_num,uint16_t max_time);
uint8_t mrvl88w8801_scan_ssid(uint8_t *ssid,uint8_t ssid_len,uint16_t max_time);
uint8_t mrvl88w8801_connect(uint8_t *ssid,uint8_t ssid_len,uint8_t *pwd,uint8_t pwd_len);
uint8_t mrvl88w8801_disconnect(void);
uint8_t mrvl88w8801_disconnect_sta(uint8_t *mac_address);
uint8_t *mrvl88w8801_get_send_data_buf(void);
uint8_t mrvl88w8801_send_date(uint8_t *data,uint16_t size);
uint8_t mrvl88w8801_cre_ap(uint8_t *ssid,uint8_t ssid_len,uint8_t *pwd,uint8_t pwd_len,uint8_t sec_type,uint8_t broadcast_ssid);
uint8_t mrvl88w8801_stop_ap(void);
uint8_t mrvl88w8801_show_sta(void);

#endif
