/******************************************************************************
  * @file    IoT_lwos_conf.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   IoT_lwos配置文件作用是:
  				1.决定每个功能是否开启
  				2.各个功能的配置信息
  				3.RET返回值
  				4.通用数据类型			
******************************************************************************/

#ifndef OS_CONFIG_H_H_H
#define OS_CONFIG_H_H_H
#include <string.h>
#include <stdio.h>
#include "wireless_rtos_conf.h"
/* 1:功能开关 */
#define CALC_CPU_LOADING	1/* 开启CPU loading功能 */
#define TIMER_MANAGER	1
#define SW_TASK_HOOK		0
#define MEMORY_MGR		1

/* 2.各个功能的配置信息 */
#define CONF_LOWEST_PRIO CONF_RTOS_MAX_PRIO		/* 最低优先级 */
#define CONF_IDL_TASK_PRIO CONF_LOWEST_PRIO		/* 空闲任务的优先级 */
#define CONF_RDY_TBL_SIZE   ((CONF_LOWEST_PRIO) / 8 + 1) /* 就绪数组size定义 */
#define CONF_IDLE_TASK_STK_SIZE   CONF_IDLE_TASK_STACK_SIZE
#define CONF_MAX_TCB	20				/* TCB的数量 */
#define CONF_MAX_TIMER 32			/* timer最大个数 */
#define CONF_TICKS_PER_SEC CONF_RTOS_TICKS_PER_SEC	/* 每秒运行的tick(10ms运行systick中断一次) */
#define CONF_CALC_CPU_LOADING_TICKS	100	/* 多少个tick更新一次CPU loading */
#define CONF_MEM_ALIGNMENT 4 		/* 4字节对齐 */
#define CONF_MIN_SIZE             12		/* 申请最小为12字节，防止严重碎片化 */
#define CONF_MEM_SIZE CONF_RTOS_MEM_SIZE	/* 申请的字节数 */


/* 3.ERR返回值 */
#define OS_RET_OK	0

/* task 相关的error */
#define OS_RET_PRIO_INVALID	1
#define OS_RET_TASK_CREATE_ISR	2
#define OS_RET_PRIO_EXIST			3
#define OS_RET_TASK_NO_MORE_TCB	4
#define OS_RET_TASK_PIP_INVALID	5

/* time相关的error */
#define OS_RET_DELAY_ISR	11
#define OS_RET_DELAY_INVALID	12

/* timer相关的error */
#define OS_RET_NO_TIMER			21
#define OS_RET_TIMER_NOT_RDY	22
#define OS_RET_INAVLID_TMR_HDL	23
#define OS_RET_TMR_INVALID_PARA 24

/* sem相关的error */
#define OS_RET_SEM_INVALID_PARA		31
#define OS_RET_SEM_CREATE_ISR	32
#define OS_RET_SEM_TIEMOUT	33

/* mutex相关的error */
#define OS_RET_MUTEX_INVALID_PARA		41
#define OS_RET_MUTEX_CREATE_ISR	42
#define OS_RET_MUTEX_TIEMOUT	43
#define OS_RET_MUTEX_PIP_EXIST	44
#define OS_RET_MUTEX_PIP_LOWER	45
#define OS_RET_MUTEX_NOT_OWER 46

/* 4.通用数据类型	 */
typedef unsigned char 	bool;
#define  FALSE                       0u
#define  TRUE                        1u

#define os_memset	memset
#define os_memcpy	memcpy
#define os_memcmp	memcmp
#define os_printf		printf
#endif

