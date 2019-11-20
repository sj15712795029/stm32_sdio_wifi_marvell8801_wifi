/******************************************************************************
  * @file    IoT_lwos_tmr.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-13
  * @brief   timer manager header file			
******************************************************************************/
#ifndef OS_TMR_H_H_H
#define OS_TMR_H_H_H
#include "IoT_lwos_port.h"

typedef void (*tmr_func)(void *);

/* timer的状态 */
#define TMR_STAT_IDLE		0
#define TMR_STAT_READY	1
#define TMR_STAT_START	2

/* timer结构体定义 */
typedef struct
{
	uint8_t	tmr_handle;	/* timer句柄 */
	uint8_t 	tmr_status;	/* timer状态 */
	uint32_t 	tmr_ticks;	/* timer的回调函数在多少个时钟节拍后触发 */
	void *		para;			/* timer回调函数的入参 */
	tmr_func	tmr_func;	/* timer的回调函数 */
}IoT_lwos_tmr_t;

#if TIMER_MANAGER >0
uint8_t IoT_lwos_tmr_add(uint8_t *tmr_handle,tmr_func tmr_func,void *para,uint32_t ticks);
uint8_t IoT_lwos_tmr_mod(uint8_t *tmr_handle,uint32_t ticks);
uint8_t IoT_lwos_tmr_start(uint8_t *tmr_handle);
uint8_t IoT_lwos_tmr_del(uint8_t *tmr_handle);
void IoT_lwos_tmr_polling(void);
#endif

#endif
