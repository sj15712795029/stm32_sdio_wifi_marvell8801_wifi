#ifndef WIRELESS_RTOS_WRAPPER_H_H_H
#define WIRELESS_RTOS_WRAPPER_H_H_H
#include <stdint.h>
#include "wireless_rtos_conf.h"

#if IOT_LWOS_ENABLE > 0
#include "IoT_lwos_port.h"
#include "IoT_lwos_core.h"
#include "IoT_lwos_task.h"
#include "IoT_lwos_time.h"
#include "IoT_lwos_sem.h"
#include "IoT_lwos_mutex.h"
#include "IoT_lwos_mem.h"  
#elif USOCII_ENABLE > 0
#include "ucos_ii.h"
#elif USOCIII_ENABLE > 0
#include "os.h"
#elif FREERTOS_ENABLE > 0
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#elif RTTHREAD_ENABLE >0
#include "rtthread.h"
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif

/* TASK TCB */
#if IOT_LWOS_ENABLE > 0
#define rtos_tcb uint8_t
#elif USOCII_ENABLE > 0
#define rtos_tcb uint8_t
#elif USOCIII_ENABLE > 0
#define rtos_tcb OS_TCB
#elif FREERTOS_ENABLE > 0
#define rtos_tcb TaskHandle_t 
#elif RTTHREAD_ENABLE >0
#define rtos_tcb rt_thread_t
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif

/* 信号量定义 */
#if IOT_LWOS_ENABLE > 0
#define rtos_sem IoT_lwos_sem_t
#elif USOCII_ENABLE > 0
#define rtos_sem OS_EVENT *
#elif USOCIII_ENABLE > 0
#define rtos_sem OS_SEM
#elif FREERTOS_ENABLE > 0
#define rtos_sem SemaphoreHandle_t
#elif RTTHREAD_ENABLE >0
#define rtos_sem rt_sem_t
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif


/* TIMER定义 */
#if IOT_LWOS_ENABLE > 0
#define rtos_timer uint8_t
typedef void (*rtos_tmr_func)(void *);
#elif USOCII_ENABLE > 0
#define rtos_timer OS_TMR  *
typedef void (*rtos_tmr_func)(void *,void*);
#elif USOCIII_ENABLE > 0
#define rtos_timer OS_TMR
typedef void (*rtos_tmr_func)(void*,void *);
#elif FREERTOS_ENABLE > 0
#define rtos_timer TimerHandle_t
typedef void (*rtos_tmr_func)(void *);
#elif RTTHREAD_ENABLE >0
#define rtos_timer struct rt_timer
typedef void (*rtos_tmr_func)(void *);
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif


/* MUTEX定义 */
#if IOT_LWOS_ENABLE > 0
#define rtos_mutex IoT_lwos_mutex_t
#elif USOCII_ENABLE > 0
#define rtos_mutex OS_EVENT *
#elif USOCIII_ENABLE > 0
#define rtos_mutex OS_MUTEX
#elif FREERTOS_ENABLE > 0
#define rtos_mutex SemaphoreHandle_t
#elif RTTHREAD_ENABLE >0
#define rtos_mutex rt_mutex_t
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif

/* MEM SIZE定义 */
#if IOT_LWOS_ENABLE > 0
#define rtos_mem_size mem_size_t
#elif USOCII_ENABLE > 0
#define rtos_mem_size uint32_t
#elif USOCIII_ENABLE > 0
#define rtos_mem_size uint32_t
#elif FREERTOS_ENABLE > 0
#define rtos_mem_size size_t
#elif RTTHREAD_ENABLE >0
#define rtos_mem_size rt_size_t
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif


typedef void (*rtos_task_func_t)( void * );
typedef unsigned int rtos_stack;

typedef enum
{
	RTOS_ERR_OK,
	RTOS_ERR_INIT_FAIL,
	RTOS_ERR_CRE_TASK,
	RTOS_ERR_DLY_TICK,
	RTOS_ERR_CRE_SEM,
	RTOS_ERR_SEM_TIMEOUT,
	RTOS_ERR_WAT_SEM,
	RTOS_ERR_SIG_SEM,
	RTOS_ERR_CRE_TMR,
	RTOS_ERR_STR_TMR,
	RTOS_ERR_DEL_TMR,
	RTOS_ERR_CRE_MUX,
	RTOS_ERR_MUX_TIMEOUT,
	RTOS_ERR_LOCK_MUX,
	RTOS_ERR_UNLOCK_MUX,
}wireless_rtos_err_e;

uint8_t rtos_init(void);
uint8_t rtos_start(void);
uint8_t rtos_cre_task(rtos_task_func_t task,void *p_arg,rtos_tcb *tcb,const uint8_t *name,rtos_stack *ptos,rtos_stack *pbos,rtos_stack stack_size,uint8_t prio,uint32_t tick);
uint8_t rtos_delay_ticks(uint32_t ticks);
uint8_t rtos_cre_sem(rtos_sem *sem,uint16_t count,uint16_t max_count);
uint8_t rtos_wait_sem(rtos_sem *sem,uint32_t ticks);
uint8_t rtos_sig_sem(rtos_sem *sem);
uint8_t rtos_init_tmr(rtos_timer *timer,const uint8_t *name,rtos_tmr_func timer_cb,void *p_arg,uint32_t ticks);
uint8_t rtos_start_tmr(rtos_timer *timer);
uint8_t rtos_del_tmr(rtos_timer *timer);
uint8_t rtos_cre_mutex(rtos_mutex *mutex,uint8_t prio);
uint8_t rtos_lock_mutex(rtos_mutex *mutex,uint32_t ticks);
uint8_t rtos_unlock_mutex(rtos_mutex *mutex);
void *rtos_malloc_mem(rtos_mem_size size);
void *rtos_calloc_mem(rtos_mem_size count,rtos_mem_size size);
void rtos_free_mem(void *mem_ptr);
#endif

