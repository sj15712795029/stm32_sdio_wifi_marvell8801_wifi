/******************************************************************************
  * @file    IoT_lwos_sem.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-19
  * @brief   sem header file			
******************************************************************************/
#ifndef OS_SEM_H_H_H
#define OS_SEM_H_H_H
#include "IoT_lwos_port.h"
#include "IoT_lwos_conf.h"


typedef struct
{
	uint32_t 	sem_cnt;										/* 信号量个数 */
	uint8_t	sem_evt_group;							/* 信号量时间组 */
	uint8_t	sem_evt_table[CONF_RDY_TBL_SIZE];  	/* 信号量时间表 */
}IoT_lwos_sem_t;

typedef IoT_lwos_sem_t * pIoT_lwos_sem_t;

uint8_t  IoT_lwos_cre_sem(pIoT_lwos_sem_t psem,uint16_t cnt);
uint8_t  IoT_lwos_wait_sem(pIoT_lwos_sem_t psem,uint32_t ticks);
uint8_t  IoT_lwos_sig_sem(pIoT_lwos_sem_t psem);

#endif
