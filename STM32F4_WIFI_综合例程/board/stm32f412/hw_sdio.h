/******************************************************************************
  * @file    hw_sdio.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-7-31
  * @brief   sdio��ͷ�ļ�
******************************************************************************/

#ifndef HW_SDIO_H_H_H
#define HW_SDIO_H_H_H

#include "hw_misc.h"

/************************** ���� ****************************
		Card Common Control Registers (CCCR)
		Relative Card Address(RCA)
		Card Information Structure (CIS)
************************************************************/

/************************** ����<-->��Ӧ *******************
		CMD5 <--> R4
		CMD3 <--> R6
		CMD7 <--> R1b
		CMD52<--> R5
************************************************************/

/* WIFIģ���RESET���ţ��˴��õ�PDN */
#define CHIP_RESET_HIGH	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)
#define CHIP_RESET_LOW	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)

/* SDIO FUNC��� */
#define SDIO_FUNC_0		0
#define SDIO_FUNC_1		1
#define SDIO_FUNC_2		2
#define SDIO_FUNC_3		3
#define SDIO_FUNC_4		4
#define SDIO_FUNC_5		5
#define SDIO_FUNC_6		6
#define SDIO_FUNC_7		7
#define SDIO_FUNC_MAX		7

/* Ĭ�ϵ�SDIO��block size */
#define SDIO_DEFAULT_BLK_SIZE	256
/* SDIO���Դ��� */
#define SDIO_RETRY_MAX	100
/* Ĭ�ϵ�SDIO��ʱ */
#define SDIO_24M_DATATIMEOUT                  ((uint32_t)2400000)
#define SDIO_1M_DATATIMEOUT                  ((uint32_t)100000)
#define SDIO_FLAG_ALL            			((uint32_t)0x00FFFFFF)

/* SDIO�Ĳ��� */
#define SDIO_EXCU_READ	0
#define SDIO_EXCU_WRITE	1


/* SDIO CLK��Ƶ */
#define SDIO_CLK_400KHZ	0x76
#define SDIO_CLK_1MHZ		0x2E
#define SDIO_CLK_24MHZ	0x00

/* R4��response */
#define OCR_IN_R4(x)	(x&0x00ffffff)
#define S18A_IN_R4(x) ((x>>24) & 0x1)
#define MEM_IN_R4(x) ((x>>27)&0x1)
#define FUNC_NUM_IN_R4(x) ((x>>28)&0x7)
#define C_IN_R4(x) ((x>>31)&0x1)

/* R6��response */
#define CS_IN_R6(x) (x & 0xffff)
#define RCA_IN_R6(x) ((x>>16)&0xffff)

#define SDIO_FBR_BASE(x)	((x) * 0x100)

/* CMD index */
#define SDIO_CMD3          	3
#define SDIO_CMD5          	5
#define SDIO_CMD7          	7
#define SDIO_CMD8           	8
#define SDIO_CMD52		52
#define SDIO_CMD53		53

/* CCCR�Ĵ����ĵ�ַ */
#define SDIO_CCCR_SDIO_VERSION	0x0
#define SDIO_CCCR_SD_VERSION		0x1
#define SDIO_CCCR_IO_ENABLE		0x2
#define SDIO_CCCR_IO_READY			0x3
#define SDIO_CCCR_INT_ENABLE		0x4
#define SDIO_CCCR_INT_PENDING	0x5
#define SDIO_CCCR_IO_ABORT		0x6
#define SDIO_CCCR_BUS_CONTROL	0x7
#define SDIO_CCCR_CARD_CAP		0x8
#define SDIO_CCCR_CIS_PTR			0x9
#define SDIO_CCCR_BUS_SUSPEND	0xc
#define SDIO_CCCR_FUNC_SEL			0xd
#define SDIO_CCCR_EXEC_FLAG		0xe
#define SDIO_CCCR_READY_FLG		0xf
#define SDIO_CCCR_BLK_SIZE			0x10
#define SDIO_CCCR_PWR_CONTROL	0x12
#define SDIO_CCCR_BUS_SPEED_SEL	0x13
#define SDIO_CCCR_UHSI_SUPPORT	0x14
#define SDIO_CCCR_DRV_STRENGTH	0x15
#define SDIO_CCCR_INT_EXTERN		0x16

/* CIS��tuple code */
typedef enum
{
    CISTPL_NULL 		= 0x00, 	/* Null tuple */
    CISTPL_VERS_1 	= 0x15, 	/* Level 1 version/product-information */
    CISTPL_MANFID 	= 0x20,	/* Manufacturer Identification String Tuple */
    CISTPL_FUNCID 	= 0x21,	/* Function Identification Tuple */
    CISTPL_FUNCE 	= 0x22,	/* Function Extensions */
    CISTPL_END 		= 0xff,	/* The End-of-chain Tuple */
} cis_tuple_code_e;

/* func status */
typedef enum
{
    FUNC_DISABLE	= 0,
    FUNC_ENABLE	= 1,
} func_status_e;

/* func�ж��Ƿ��� */
typedef enum
{
    FUNC_INT_DISABLE	= 0,
    FUNC_INT_ENABLE	= 1,
} func_int_status_e;

/* ���ݿ�� */
typedef enum
{
    SDIO_BUS_WIDTH_1 = 0x0,
    SDIO_BUS_WIDTH_4 = 0x2,
    SDIO_BUS_WIDTH_8 = 0x3,
} bus_width_e;

/* func�Ľṹ�嶨�� */
typedef struct
{
    uint8_t func_num;		/* func��� */
    uint8_t func_status;	/* func enable״̬��0:disable 1:enable  */
    uint8_t func_int_status;/* func�ж�״̬,0:disable 1:enable */
    uint16_t cur_blk_size;	/* func��block size */
    uint16_t max_blk_size;/* func��max block size */
} sdio_func_t;
typedef sdio_func_t * psdio_func_t;

typedef struct
{
    uint8_t func_total_num;	/* �ж��ٸ�func */
    uint8_t cccr_version;		/* CCCR�İ汾 */
    uint8_t sdio_version;		/* SDIO�İ汾 */
    uint8_t sdio_int_mgr;		/* �жϹ���SDIO���жϿ��� */
    uint16_t manf_code;		/* ��������Ϣ */
    uint16_t manf_info;			/* �豸��Ϣ */
    uint8_t int_occur;
    psdio_func_t func[SDIO_FUNC_MAX];		/* funcָ�� */
} sdio_core_t;
typedef sdio_core_t*psdio_core_t;
#define SDIO_EXCU_WRITE	1


#define DMA_FLAG_TCIF3                    ((uint32_t)0x08000000)
#define DMA_FLAG_TEIF3                    ((uint32_t)0x02000000)	
#define DMA_FLAG_HTIF3                    ((uint32_t)0x04000000)
#define DMA_FLAG_DMEIF3                   ((uint32_t)0x01000000)
#define DMA_FLAG_FEIF3                    ((uint32_t)0x00400000)

/* Masks Definition */
#define TRANSFER_IT_ENABLE_MASK (uint32_t)(DMA_SxCR_TCIE | DMA_SxCR_HTIE | \
                                           DMA_SxCR_TEIE | DMA_SxCR_DMEIE)

#define DMA_Stream0_IT_MASK     (uint32_t)(DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 | \
                                           DMA_LISR_TEIF0 | DMA_LISR_HTIF0 | \
                                           DMA_LISR_TCIF0)

#define DMA_Stream1_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 6)
#define DMA_Stream2_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 16)
#define DMA_Stream3_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 22)
#define DMA_Stream4_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream5_IT_MASK     (uint32_t)(DMA_Stream1_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream6_IT_MASK     (uint32_t)(DMA_Stream2_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream7_IT_MASK     (uint32_t)(DMA_Stream3_IT_MASK | (uint32_t)0x20000000)
#define TRANSFER_IT_MASK        (uint32_t)0x0F3C0F3C

#define HIGH_ISR_MASK           (uint32_t)0x20000000
#define RESERVED_MASK           (uint32_t)0x0F7D0F7D  

/** @defgroup DMA_fifo_direct_mode 
  * @{
  */ 
#define DMA_FIFOMode_Disable              ((uint32_t)0x00000000) 
#define DMA_FIFOMode_Enable               ((uint32_t)0x00000004)


/** @defgroup DMA_fifo_threshold_level 
  * @{
  */ 
#define DMA_FIFOThreshold_1QuarterFull    ((uint32_t)0x00000000)
#define DMA_FIFOThreshold_HalfFull        ((uint32_t)0x00000001) 
#define DMA_FIFOThreshold_3QuartersFull   ((uint32_t)0x00000002)
#define DMA_FIFOThreshold_Full            ((uint32_t)0x00000003)

/** @defgroup DMA_flow_controller_definitions 
  * @{
  */ 
#define DMA_FlowCtrl_Memory               ((uint32_t)0x00000000)
#define DMA_FlowCtrl_Peripheral           ((uint32_t)0x00000020)


uint8_t hw_sdio_init(void);
uint8_t hw_chip_reset(void);
uint8_t hw_sdio_get_cccr_version(uint8_t *cccr_version);
uint8_t hw_sdio_get_sdio_version(uint8_t *sdio_version);
uint8_t hw_sdio_enable_func(uint8_t func_num);
uint8_t hw_sdio_disable_func(uint8_t func_num);
uint8_t hw_sdio_enable_mgr_int(void);
uint8_t hw_sdio_disable_mgr_int(void);
uint8_t hw_sdio_enable_func_int(uint8_t func_num);
uint8_t hw_sdio_disable_func_int(uint8_t func_num);
uint8_t hw_sdio_get_int_pending(uint8_t *int_pending);
uint8_t hw_sdio_set_func_abort(uint8_t func_num);
uint8_t hw_sdio_reset(void);
uint8_t hw_sdio_set_bus_width(uint8_t bus_width);
uint8_t hw_sdio_get_bus_width(uint8_t *bus_width);
uint8_t hw_sdio_get_cis_ptr(uint8_t func_num,uint32_t *ptr_address);
uint8_t hw_sdio_set_blk_size(uint8_t func_num,uint16_t blk_size);
uint8_t hw_sdio_get_blk_size(uint8_t func_num,uint16_t *blk_size);
uint8_t hw_sdio_cmd52(uint8_t write,uint8_t func_num,uint32_t address,uint8_t para,uint8_t *resp);
uint8_t hw_sdio_cmd53(uint8_t write, uint8_t func_num,uint32_t address, uint8_t incr_addr, uint8_t *buf,uint32_t size);

#endif




