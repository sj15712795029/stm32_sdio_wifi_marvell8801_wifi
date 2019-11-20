#include "wireless_rtos_wrapper.h"
#include <stdlib.h>

uint32_t rtos_ticks = 0;;
void SysTick_Handler(void)
{
	rtos_ticks++;
#if IOT_LWOS_ENABLE > 0
    extern bool IoT_lwos_getos_runing(void);
    extern void  IoT_lwos_int_enter (void);
    extern void  IoT_lwos_time_tick(void);
    extern void  IoT_lwos_int_exit (void);

    if(IoT_lwos_getos_runing() == TRUE)
    {
        IoT_lwos_int_enter();
        IoT_lwos_time_tick();
        IoT_lwos_int_exit();
    }
#elif USOCII_ENABLE > 0
    OSIntEnter();
    OSTimeTick();
    OSIntExit();
#elif USOCIII_ENABLE > 0
    OSIntEnter();
    OSTimeTick();
    OSIntExit();
#elif FREERTOS_ENABLE > 0
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
    {
        extern void xPortSysTickHandler( void );
        xPortSysTickHandler();
    }
#elif RTTHREAD_ENABLE >0
    /* enter interrupt */
    rt_interrupt_enter();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
}

uint8_t rtos_init()
{
    uint8_t rtos_ret = RTOS_ERR_OK;
#if IOT_LWOS_ENABLE > 0
    IoT_lwos_init();
#elif USOCII_ENABLE > 0
    OSInit();
#elif USOCIII_ENABLE > 0
    OS_ERR err;
    OSInit(&err);
    if(err != OS_ERR_NONE)
        rtos_ret = RTOS_ERR_INIT_FAIL;
#elif FREERTOS_ENABLE > 0

#elif RTTHREAD_ENABLE >0

#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif

    return rtos_ret;
}


uint8_t rtos_start()
{
    uint8_t rtos_ret = RTOS_ERR_OK;
#if IOT_LWOS_ENABLE > 0
    IoT_lwos_start();
#elif USOCII_ENABLE > 0
    OSStart();
#elif USOCIII_ENABLE > 0
    OS_ERR err;
    OSStart(&err);
#elif FREERTOS_ENABLE > 0
    vTaskStartScheduler();
#elif RTTHREAD_ENABLE >0
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif

    return rtos_ret;
}

uint8_t rtos_cre_task(rtos_task_func_t task,
                      void *p_arg,
                      rtos_tcb *tcb,
                      const uint8_t *name,
                      rtos_stack *ptos,
                      rtos_stack *pbos,
                      rtos_stack stack_size,
                      uint8_t prio,
                      uint32_t tick)
{

    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_cre_tsk(task,p_arg,ptos,prio);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TASK;

#elif USOCII_ENABLE > 0
    rtos_ret = OSTaskCreate(task,p_arg,ptos,prio);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TASK;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSTaskCreate(tcb,(CPU_CHAR *)name,task,p_arg,prio,pbos,0,stack_size,0,tick,0,0,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TASK;
#elif FREERTOS_ENABLE > 0
    BaseType_t freeRTOS_err;
    freeRTOS_err = xTaskCreate(task,(const char *)name,stack_size,p_arg,prio,tcb);
    if(freeRTOS_err == pdPASS)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TASK;

#elif RTTHREAD_ENABLE >0
    *tcb = rt_thread_create((const char *)name,task,p_arg,stack_size,prio,tick);
    if (*tcb != RT_NULL)
        rt_thread_startup(*tcb);
    else
        rtos_ret = RTOS_ERR_CRE_TASK;

#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_delay_ticks(uint32_t ticks)
{
    uint8_t rtos_ret = RTOS_ERR_OK;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_delay(ticks);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DLY_TICK;
#elif USOCII_ENABLE > 0
    OSTimeDly(ticks);
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSTimeDly(ticks,OS_OPT_TIME_DLY,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DLY_TICK;
#elif FREERTOS_ENABLE > 0
    vTaskDelay(ticks);
#elif RTTHREAD_ENABLE >0
    rt_err_t rthread_err;
    rthread_err = rt_thread_delay(ticks);
    if(rthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DLY_TICK;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_cre_sem(rtos_sem *sem,uint16_t count,uint16_t max_count)
{
    uint8_t rtos_ret = RTOS_ERR_OK;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_cre_sem(sem,count);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_SEM;

#elif USOCII_ENABLE > 0
    *sem = OSSemCreate(count);
    if(*sem == (void *)0)
        rtos_ret = RTOS_ERR_CRE_SEM;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSSemCreate(sem,"ucosiii sem",count,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_SEM;
#elif FREERTOS_ENABLE > 0
    *sem=xSemaphoreCreateCounting(max_count,count);
    if(*sem != (void *)0)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_SEM;

#elif RTTHREAD_ENABLE >0
    *sem = rt_sem_create("rtthread sem", count, RT_IPC_FLAG_FIFO);
    if(*sem == RT_NULL)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_SEM;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_wait_sem(rtos_sem *sem,uint32_t ticks)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_wait_sem(sem,ticks);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else if(rtos_ret == OS_RET_SEM_TIEMOUT)
        rtos_ret = RTOS_ERR_SEM_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_WAT_SEM;

#elif USOCII_ENABLE > 0
    OSSemPend(*sem,ticks,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else if(rtos_ret == OS_ERR_TIMEOUT)
        rtos_ret = RTOS_ERR_SEM_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_WAT_SEM;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSSemPend(sem,ticks,OS_OPT_PEND_BLOCKING,(CPU_TS*)0,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else if(ucosiii_err == OS_ERR_TIMEOUT)
        rtos_ret = RTOS_ERR_SEM_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_WAT_SEM;
#elif FREERTOS_ENABLE > 0
    if(ticks == 0)
        rtos_ret = xSemaphoreTake(*sem,portMAX_DELAY);
    else
        rtos_ret = xSemaphoreTake(*sem,ticks);

    if(rtos_ret == pdTRUE )
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SEM_TIMEOUT;

#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    if(ticks == 0)
        rtthread_err = rt_sem_take(*sem, RT_WAITING_FOREVER);
    else
        rtthread_err = rt_sem_take(*sem, ticks);
    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else if(rtthread_err == -RT_ETIMEOUT)
        rtos_ret = RTOS_ERR_SEM_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_WAT_SEM;

#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_sig_sem(rtos_sem *sem)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_sig_sem(sem);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SIG_SEM;
#elif USOCII_ENABLE > 0
    rtos_ret = OSSemPost(*sem);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SIG_SEM;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSSemPost(sem,OS_OPT_POST_FIFO,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SIG_SEM;
#elif FREERTOS_ENABLE > 0
    rtos_ret=xSemaphoreGive(*sem);
    if(rtos_ret == pdTRUE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SIG_SEM;
#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    rtthread_err = rt_sem_release(*sem);
    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_SIG_SEM;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_init_tmr(rtos_timer *timer,const uint8_t *name,rtos_tmr_func timer_cb,void *p_arg,uint32_t ticks)
{
    uint8_t rtos_ret = RTOS_ERR_OK;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_tmr_add(timer,timer_cb,p_arg,ticks);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TMR;
#elif USOCII_ENABLE > 0
    *timer = OSTmrCreate(ticks,0,OS_TMR_OPT_ONE_SHOT,timer_cb,p_arg,(uint8_t *)name,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TMR;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSTmrCreate(timer,(CPU_CHAR *)name,ticks,0,OS_OPT_TMR_ONE_SHOT,timer_cb,p_arg,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TMR;
#elif FREERTOS_ENABLE > 0
    static uint8_t timer_id = 0;
    timer_id++;
    *timer = xTimerCreate((const char*)name,ticks,(UBaseType_t	)pdFALSE,&timer_id,timer_cb);
    if(*timer != (void *)0)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_TMR;
#elif RTTHREAD_ENABLE >0
    rt_timer_init(timer,(const char *)name,timer_cb,p_arg,ticks,RT_TIMER_FLAG_ONE_SHOT);
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}
uint8_t rtos_start_tmr(rtos_timer *timer)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_tmr_start(timer);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_STR_TMR;
#elif USOCII_ENABLE > 0
    OSTmrStart(*timer,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_STR_TMR;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSTmrStart(timer,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_STR_TMR;
#elif FREERTOS_ENABLE > 0
    BaseType_t freeRTOS_err;
    freeRTOS_err = xTimerStart(*timer,0);
    if(freeRTOS_err == pdPASS)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_STR_TMR;
#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    rtthread_err = rt_timer_start(timer);
    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_STR_TMR;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}
uint8_t rtos_del_tmr(rtos_timer *timer)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_tmr_del(timer);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DEL_TMR;
#elif USOCII_ENABLE > 0
    OSTmrDel(*timer,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DEL_TMR;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSTmrDel(timer,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DEL_TMR;
#elif FREERTOS_ENABLE > 0
    BaseType_t freeRTOS_err;
    freeRTOS_err = xTimerDelete(*timer,0);
    if(freeRTOS_err == pdPASS)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DEL_TMR;
#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    rt_timer_delete(timer);

    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_DEL_TMR;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

uint8_t rtos_cre_mutex(rtos_mutex *mutex,uint8_t prio)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_cre_mutex(mutex,prio);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_MUX;
#elif USOCII_ENABLE > 0
    *mutex = OSMutexCreate(prio,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_MUX;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSMutexCreate(mutex,"ucosiii mutex",&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_MUX;
#elif FREERTOS_ENABLE > 0
    *mutex=xSemaphoreCreateMutex();
    if(*mutex != (void *)0)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_MUX;
#elif RTTHREAD_ENABLE >0
    *mutex = rt_mutex_create("rtthread mutex", RT_IPC_FLAG_FIFO);
    if(*mutex != RT_NULL)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_CRE_MUX;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}
uint8_t rtos_lock_mutex(rtos_mutex *mutex,uint32_t ticks)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_lock_mutex(mutex,ticks);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else if(rtos_ret == OS_RET_MUTEX_TIEMOUT)
        rtos_ret = RTOS_ERR_MUX_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_LOCK_MUX;
#elif USOCII_ENABLE > 0
    OSMutexPend(*mutex,ticks,&rtos_ret);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else if(rtos_ret == OS_ERR_TIMEOUT)
        rtos_ret = RTOS_ERR_MUX_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_LOCK_MUX;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSMutexPend(mutex,ticks,OS_OPT_PEND_BLOCKING,(CPU_TS*)0,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else if(ucosiii_err == OS_ERR_TIMEOUT)
        rtos_ret = RTOS_ERR_MUX_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_LOCK_MUX;
#elif FREERTOS_ENABLE > 0
    if(ticks == 0)
        rtos_ret = xSemaphoreTake(*mutex,portMAX_DELAY);
    else
        rtos_ret = xSemaphoreTake(*mutex,ticks);

    if(rtos_ret == pdTRUE )
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_MUX_TIMEOUT;
#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    if(ticks == 0)
        rtthread_err = rt_mutex_take(*mutex, RT_WAITING_FOREVER);
    else
        rtthread_err = rt_mutex_take(*mutex, ticks);
    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else if(rtthread_err == RT_ETIMEOUT)
        rtos_ret = RTOS_ERR_MUX_TIMEOUT;
    else
        rtos_ret = RTOS_ERR_LOCK_MUX;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}
uint8_t rtos_unlock_mutex(rtos_mutex *mutex)
{
    uint8_t rtos_ret;
#if IOT_LWOS_ENABLE > 0
    rtos_ret = IoT_lwos_unlock_mutex(mutex);
    if(rtos_ret == OS_RET_OK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_UNLOCK_MUX;
#elif USOCII_ENABLE > 0
    rtos_ret = OSMutexPost(*mutex);
    if(rtos_ret == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_UNLOCK_MUX;
#elif USOCIII_ENABLE > 0
    OS_ERR ucosiii_err;
    OSMutexPost(mutex,OS_OPT_POST_NONE,&ucosiii_err);
    if(ucosiii_err == OS_ERR_NONE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_UNLOCK_MUX;
#elif FREERTOS_ENABLE > 0
    rtos_ret = xSemaphoreGive(*mutex);
    if(rtos_ret == pdTRUE)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_UNLOCK_MUX;
#elif RTTHREAD_ENABLE >0
    rt_err_t rtthread_err;
    rtthread_err = rt_mutex_release(*mutex);
    if(rtthread_err == RT_EOK)
        rtos_ret = RTOS_ERR_OK;
    else
        rtos_ret = RTOS_ERR_UNLOCK_MUX;
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return rtos_ret;
}

void *rtos_malloc_mem(rtos_mem_size size)
{
    void *mem_ptr;
#if IOT_LWOS_ENABLE > 0
#if MEMORY_MGR > 0
    mem_ptr = IoT_lwos_mem_malloc(size);
#else
    mem_ptr = malloc(size);
#endif
#elif USOCII_ENABLE > 0
    mem_ptr = malloc(size);
#elif USOCIII_ENABLE > 0
    mem_ptr = malloc(size);
#elif FREERTOS_ENABLE > 0
    mem_ptr = pvPortMalloc(size);
#elif RTTHREAD_ENABLE >0
    mem_ptr = rt_malloc(size);
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return mem_ptr;
}

void *rtos_calloc_mem(rtos_mem_size count,rtos_mem_size size)
{
    void *mem_ptr;
#if IOT_LWOS_ENABLE > 0
#if MEMORY_MGR > 0
    mem_ptr = IoT_lwos_mem_calloc(count,size);
#else
    mem_ptr = calloc(count,size);
#endif
#elif USOCII_ENABLE > 0
    mem_ptr = calloc(count,size);
#elif USOCIII_ENABLE > 0
    mem_ptr = calloc(count,size);
#elif FREERTOS_ENABLE > 0
    mem_ptr = calloc(count,size);
#elif RTTHREAD_ENABLE >0
    mem_ptr = rt_calloc(count,size);
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
    return mem_ptr;
}
void rtos_free_mem(void *mem_ptr)
{
#if IOT_LWOS_ENABLE > 0
#if MEMORY_MGR > 0
    IoT_lwos_mem_free(mem_ptr);
#else
    free(mem_ptr);
#endif
#elif USOCII_ENABLE > 0
    free(mem_ptr);
#elif USOCIII_ENABLE > 0
    free(mem_ptr);
#elif FREERTOS_ENABLE > 0
    vPortFree(mem_ptr);
#elif RTTHREAD_ENABLE >0
    rt_free(mem_ptr);
#else
#error "###### Please select one(must) RTOS enable marco in wireless_rtos_conf.h #######"
#endif
}
