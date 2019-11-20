#ifndef WIRELESS_RTOS_CONF_H_H_H
#define WIRELESS_RTOS_CONF_H_H_H
/* ******************************** NOTED ********************************************/
/* *IoT_lwos task优先级是数字越大，优先级越低，比如优先级1比优先级0低 ****************/
/* *UCOS II  task优先级是数字越大，优先级越低，比如优先级1比优先级0低 ****************/
/* *UCOS III task优先级是数字越大，优先级越低，比如优先级1比优先级0低 ****************/
/* *FreeRTOS task优先级是数字越大，优先级越高，比如优先级1比优先级0高 ****************/
/* *rtthreas task优先级是数字越大，优先级越低，比如优先级1比优先级0低 ****************/

/* ticks/s,此处设置为100，那么100ticks/s，一个ticks是10ms */
#define CONF_RTOS_TICKS_PER_SEC 100
/* MAX prio */
#define CONF_RTOS_MAX_PRIO	32
/* memory size */
#define CONF_RTOS_MEM_CNT_SIZE	10
#define CONF_RTOS_MEM_BLK_SIZE	512
#define CONF_RTOS_MEM_SIZE	(CONF_RTOS_MEM_CNT_SIZE*CONF_RTOS_MEM_BLK_SIZE)
/* IDLE task stack size */
#define CONF_IDLE_TASK_STACK_SIZE	128
/* ISR stack size */
#define CONF_ISR_STACK_SIZE			512

//#define IOT_LWOS_ENABLE	0
//#define USOCII_ENABLE		0
//#define USOCIII_ENABLE		0
//#define FREERTOS_ENABLE	0
//#define RTTHREAD_ENABLE	0

#endif
