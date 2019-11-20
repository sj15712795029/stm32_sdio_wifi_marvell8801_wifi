/******************************************************************************
  * @file    IoT_lwos_sem.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-21
  * @brief   mutex header file			
******************************************************************************/
#ifndef OS_MUTEX_H_H_H
#define OS_MUTEX_H_H_H
#include "IoT_lwos_port.h"
#include "IoT_lwos_conf.h"


#define  OS_MUTEX_KEEP_LOWER_8   ((uint16_t)0x00FFu)
#define  OS_MUTEX_KEEP_UPPER_8   ((uint16_t)0xFF00u)

#define  OS_MUTEX_AVAILABLE      ((uint16_t)0x00FFu)

typedef struct
{
	uint16_t 	mutex_cnt;										/* 互斥量标志 */
	void *ptcb;													/* 互斥量指向的任务tcb */
	uint8_t	mutex_evt_group;								/* 互斥量事件组 */
	uint8_t	mutex_evt_table[CONF_RDY_TBL_SIZE];  	/* 互斥量事件表 */
}IoT_lwos_mutex_t;
typedef IoT_lwos_mutex_t * pIoT_lwos_mutex_t;

uint8_t IoT_lwos_cre_mutex(pIoT_lwos_mutex_t pmutex,uint8_t prio);
uint8_t IoT_lwos_lock_mutex(pIoT_lwos_mutex_t pmutex,uint32_t ticks);
uint8_t IoT_lwos_unlock_mutex(pIoT_lwos_mutex_t pmutex);

#endif
