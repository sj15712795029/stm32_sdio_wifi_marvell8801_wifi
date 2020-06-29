/** @file  mlanregclass.h
  *
  * @brief This files contains mlanutl regclass command handling.
  *
  * (C) Copyright 2008-2018 Marvell International Ltd. All Rights Reserved
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
/************************************************************************
Change log:
     08/11/2009: initial version
************************************************************************/

#ifndef _MLANREGCLASS_H
#define _MLANREGCLASS_H

/** Nomadic */
#define BLIMIT_NOMADIC       (1 << 0)
/** Indoor */
#define BLIMIT_INDOOR_ONLY   (1 << 1)
/** Tpc */
#define BLIMIT_TPC           (1 << 2)
/** Dfs */
#define BLIMIT_DFS           (1 << 3)
/** IBSS Prohibit */
#define BLIMIT_IBSS_PROHIBIT (1 << 4)
/** Four MS CS */
#define BLIMIT_FOUR_MS_CS    (1 << 5)
/** LIC Base STA */
#define BLIMIT_LIC_BASE_STA  (1 << 6)
/** Mobile STA */
#define BLIMIT_MOBILE_STA    (1 << 7)
/** Public Safety */
#define BLIMIT_PUBLIC_SAFETY (1 << 8)
/** ISM Bands */
#define BLIMIT_ISM_BANDS     (1 << 9)

/** Enum Definitions: reg_domain */
typedef enum {
	REGDOMAIN_NULL = 0x00,

	REGDOMAIN_FCC = 0x01,
	REGDOMAIN_ETSI = 0x02,
	REGDOMAIN_MIC = 0x03,

	REGDOMAIN_OTHER = 0xFF,

} reg_domain_e;

typedef struct {
	t_u8 reg_domain;    /**< Domain */
	t_u8 regulatory_class;
			    /**< Regulatory class */
	t_u8 chan_num;	    /**< Channel Number */
	t_u8 reserved1;	    /**< Reserved */
	t_u16 start_freq;   /**< Start frequency */
	t_u16 chan_spacing; /**< channel spacing */
	t_u8 max_tx_power;  /**< Max. tx power */
	t_u8 coverage_class;/**< Coverage class */
	t_u16 reg_limits;   /**< Limits */
} __ATTRIB_PACK__ chan_entry_t;

typedef struct {
    /** Action: GET/SET */
	t_u16 action;
    /** Reg channel table */
	t_u16 table_select;
    /** Channel number */
	t_u32 chan;
    /** Channel entry */
	chan_entry_t chan_entry[75];
} __ATTRIB_PACK__ HostCmd_DS_REGCLASS_GET_CHAN_TABLE;

typedef struct {
	t_u16 action;
		    /**< Action: GET/SET */
	t_u16 reserved;
		      /**< Reserved */
	char regulatory_str[3];/**< Regulatory String */
} __ATTRIB_PACK__ HostCmd_DS_REGCLASS_CONFIG_USER_TABLE;

typedef struct {
	t_u32 multidomain_enable;
			      /**< Multi domain enable */
} __ATTRIB_PACK__ HostCmd_DS_REGCLASS_MULTIDOMAIN_CONTROL;

#endif /* _MLANREGCLASS_H */
