/******************************************************************************
  * @file    IoT_lwos_core.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   core header file
******************************************************************************/
#ifndef OS_CORE_H_H_H
#define OS_CORE_H_H_H

#include "IoT_lwos_conf.h"
#include "IoT_lwos_port.h"
#include "IoT_lwos_tmr.h"
#include "IoT_lwos_sem.h"
#include "IoT_lwos_mutex.h"
#include "IoT_lwos_mem.h"

#define  TCB_STAT_RDY                 0x00
#define  TCB_STAT_SEM                 0x01
#define  TCB_STAT_MUTEX		0x02

#define  TCB_STAT_PEND_ANY         (TCB_STAT_SEM | TCB_STAT_MUTEX)

#define  OS_STAT_PEND_OK                0
#define  OS_STAT_PEND_TO                1



typedef struct IoT_lwos_tcb_pre
{
    os_stack *		tcb_stack_ptr;				/* task tcb的堆栈指针 */
    struct IoT_lwos_tcb_pre * tcb_next;				/* 指向下一个tcb指针 */
    uint8_t 			os_tcb_status;				/* task 状态 */
    uint8_t			os_tcb_pend_status;		/* task pend状态 */
    pIoT_lwos_sem_t	os_tcb_sem_ptr;		/* task 指向信号量的指针 */
    pIoT_lwos_mutex_t	os_tcb_mutex_ptr; /* task 指向互斥量的指针 */
    uint32_t		tcb_delay;					/* task 延时多少个时钟 */
    uint8_t			tcb_prio;						/* task 优先级 */
    uint8_t			tcb_y;							/* 对应core os_ready_group成员的bit位置以及os_ready_table的索引 */
    uint8_t			tcb_x;							/* 对应os_ready_table[index]中bit的位置 */
    uint8_t			tcb_bity;						/* 1<<tcb_y */
    uint8_t			tcb_bitx;						/* 1<<tcb_x */
} IoT_lwos_tcb_t;
typedef IoT_lwos_tcb_t * pIoT_lwos_tcb_t;


typedef struct
{
    volatile  uint32_t 	os_time; 											/* OS运行节拍 */

    uint8_t				os_int_nesting;  								/* OS中断嵌套层数 */
    uint8_t             		os_tsk_cnt;                								/* OS task数量 */
    volatile  uint32_t  	os_idle_cnt;										/* idle task计数器 */
    bool           			os_running;                 							/* OS是否运行 */
    uint32_t            		os_swcontext_cnt; 							/* OS切换堆栈的次数 */
    uint8_t           		os_ready_group;      							/* OS就绪组 */
    uint8_t				os_ready_table[CONF_RDY_TBL_SIZE];    	/* OS就绪表 */
    uint8_t				os_prio_current;								 /* 当前运行的task的优先级 */
    uint8_t				os_prio_high_rdy;								 /* 处于ready状态的task最高优先级 */
    pIoT_lwos_tcb_t 	os_tcb_current;									/* 当前运行的task的tcb */
    pIoT_lwos_tcb_t 	os_tcb_high_rdy;								/* 处于ready状态的task最高优先级的tcb */
    pIoT_lwos_tcb_t 	os_tcb_prio_table[CONF_LOWEST_PRIO + 1]; /* os prio table，每个指向一个tcb */
    IoT_lwos_tcb_t	os_tcb_table[CONF_MAX_TCB];				/* tcb table */
    pIoT_lwos_tcb_t 	os_tcb_free_list;								/* 指向空闲tcb的指针 */
    pIoT_lwos_tcb_t 	os_tcb_list;										/* 已经存在的tcb指针 */

#if CALC_CPU_LOADING>0
    volatile  uint32_t 	cpu_loading_tick;								/* CPU运行的节拍数 */
    volatile  uint32_t 	cpu_idle_loading_tick;							/* CPU运行idle tick的次数 */
    fp32					cpu_loading;										/* CPU使用率 */
#endif

#if TIMER_MANAGER >0
    IoT_lwos_tmr_t 	os_timer[CONF_MAX_TIMER];					/* timer个数 */
#endif

#if MEMORY_MGR > 0
    uint8_t *			lwos_ram;
    pIoT_lwos_mem_t lwos_ram_end;									/* 最后一个数据块 */
    pIoT_lwos_mem_t lwos_lfree;										/* 指向第一个空闲的数据块的指针 */
#endif
} IoT_lwos_core_t;
typedef IoT_lwos_core_t * pIoT_lwos_core_t;

void IoT_lwos_init(void);
uint8_t  IoT_lwos_tcb_init (uint8_t prio, os_stack *ptos);
void IoT_lwos_sched(void);
void IoT_lwos_start(void);
void IoT_lwos_setos_runing(void);
uint8_t IoT_lwos_get_task_num(void);
#if CALC_CPU_LOADING>0
fp32 IoT_lwos_get_cpu_loading(void);
#endif

#endif
