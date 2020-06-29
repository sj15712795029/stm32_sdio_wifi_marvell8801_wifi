/******************************************************************************
  * @file    IoT_lwos_tmr.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-13
  * @brief   timer manager source file
******************************************************************************/
#include "IoT_lwos_tmr.h"
#include "IoT_lwos_conf.h"
#include "IoT_lwos_core.h"

extern pIoT_lwos_core_t pIoT_lwos_core;

/* 函数声明区 */
#if TIMER_MANAGER >0
static uint8_t IoT_lwos_find_idle_tmr(uint8_t *tmr_handle);
#endif


/******************************************************************************
 *	函数名:	IoT_lwos_tmr_add
 * 参数:  		tmr_handle(OUT)		-->add timer如果成功返回的句柄
 				tmr_func(IN)			-->timer回调函数指针
 				para(IN)				-->timer回调函数参数
 				ticks(IN)				-->要准备延时的tick数
 * 返回值: 	添加timer返回结果
 * 描述:		把timer数组中添加一个timer，但是还没有启动，处于ready状态
******************************************************************************/
#if TIMER_MANAGER >0
uint8_t IoT_lwos_tmr_add(uint8_t *tmr_handle,tmr_func tmr_func,void *para,uint32_t ticks)
{
    uint8_t ret;
    uint8_t temp_handle;

    if(tmr_handle == NULL || tmr_func == NULL)
    {
        return OS_RET_TMR_INVALID_PARA;
    }
    ret = IoT_lwos_find_idle_tmr(tmr_handle);
    if(ret == OS_RET_OK)
    {
        IoT_lwos_critial_enter();
        temp_handle = *tmr_handle;
        (pIoT_lwos_core->os_timer)[temp_handle].tmr_handle = temp_handle;
        (pIoT_lwos_core->os_timer)[temp_handle].tmr_status = TMR_STAT_READY;
        (pIoT_lwos_core->os_timer)[temp_handle].tmr_ticks = ticks;
        (pIoT_lwos_core->os_timer)[temp_handle].tmr_func = tmr_func;
        (pIoT_lwos_core->os_timer)[temp_handle].para = para;
        IoT_lwos_critial_exit();
    }
    return ret;
}
#endif


/******************************************************************************
 *	函数名:	IoT_lwos_tmr_mod
 * 参数:  		tmr_handle(IN)		-->timer句柄
 				ticks(IN)				-->要修改的时钟节拍数
 * 返回值: 	修改timer返回结果
 * 描述:		修改一个timer的ticks
******************************************************************************/
#if TIMER_MANAGER >0
uint8_t IoT_lwos_tmr_mod(uint8_t *tmr_handle,uint32_t ticks)
{

    if(*tmr_handle >= CONF_MAX_TIMER )
    {
        return OS_RET_INAVLID_TMR_HDL;
    }

    if((pIoT_lwos_core->os_timer)[*tmr_handle].tmr_status == TMR_STAT_IDLE)
    {
        return OS_RET_NO_TIMER;
    }

    IoT_lwos_critial_enter();
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_ticks = ticks;
    IoT_lwos_critial_exit();

    return OS_RET_OK;
}
#endif
/******************************************************************************
 *	函数名:	IoT_lwos_tmr_start
 * 参数:  		tmr_handle(IN)		-->timer句柄
 * 返回值: 	start timer返回结果
 * 描述:		启动一个timer
******************************************************************************/
#if TIMER_MANAGER >0
uint8_t IoT_lwos_tmr_start(uint8_t *tmr_handle)
{

    if(*tmr_handle >= CONF_MAX_TIMER )
    {
        return OS_RET_INAVLID_TMR_HDL;
    }

    if((pIoT_lwos_core->os_timer)[*tmr_handle].tmr_status != TMR_STAT_READY)
    {
        return OS_RET_TIMER_NOT_RDY;
    }

    IoT_lwos_critial_enter();
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_status = TMR_STAT_START;
    IoT_lwos_critial_exit();
    return OS_RET_OK;
}
#endif
/******************************************************************************
 *	函数名:	IoT_lwos_tmr_del
 * 参数:  		tmr_handle(IN)		-->timer句柄
 * 返回值: 	del timer返回结果
 * 描述:		删除一个timer
******************************************************************************/
#if TIMER_MANAGER >0
uint8_t IoT_lwos_tmr_del(uint8_t *tmr_handle)
{
    if(*tmr_handle >= CONF_MAX_TIMER )
    {
        return OS_RET_INAVLID_TMR_HDL;
    }

    if((pIoT_lwos_core->os_timer)[*tmr_handle].tmr_status == TMR_STAT_IDLE)
    {
        return OS_RET_INAVLID_TMR_HDL;
    }

    IoT_lwos_critial_enter();
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_handle = 0;
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_status = TMR_STAT_IDLE;
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_ticks = 0;
    (pIoT_lwos_core->os_timer)[*tmr_handle].tmr_func = 0;
    (pIoT_lwos_core->os_timer)[*tmr_handle].para = 0;
    IoT_lwos_critial_exit();
    return OS_RET_OK;
}
#endif
/******************************************************************************
 *	函数名:	IoT_lwos_tmr_polling
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		timer polling，查看是否有timer超时
******************************************************************************/
#if TIMER_MANAGER >0
void IoT_lwos_tmr_polling()
{
    uint8_t index = 0;
    IoT_lwos_critial_enter();
    for(index = 0; index < CONF_MAX_TIMER; index++)
    {
        if((pIoT_lwos_core->os_timer)[index].tmr_status == TMR_STAT_START)
        {
            (pIoT_lwos_core->os_timer)[index].tmr_ticks--;
            if((pIoT_lwos_core->os_timer)[index].tmr_ticks == 0)
            {
                ((pIoT_lwos_core->os_timer)[index].tmr_func)((pIoT_lwos_core->os_timer)[index].para);
                (pIoT_lwos_core->os_timer)[index].tmr_handle = 0;
                (pIoT_lwos_core->os_timer)[index].tmr_status = TMR_STAT_IDLE;
                (pIoT_lwos_core->os_timer)[index].tmr_ticks = 0;
                (pIoT_lwos_core->os_timer)[index].tmr_func = 0;
                (pIoT_lwos_core->os_timer)[index].para = 0;
            }
        }
    }
    IoT_lwos_critial_exit();
}
#endif
/******************************************************************************
 *	函数名:	IoT_lwos_find_idle_tmr
 * 参数:  		tmr_handle(OUT)	-->如果找到timer，那么就返回timer句柄
 * 返回值: 	返回查找结果
 * 描述:		查找空闲timer,并返回句柄
******************************************************************************/
#if TIMER_MANAGER >0
static uint8_t IoT_lwos_find_idle_tmr(uint8_t *tmr_handle)
{
    uint8_t index = 0;

    if(tmr_handle == NULL)
    {
        return OS_RET_TMR_INVALID_PARA;
    }

    for(index = 0; index < CONF_MAX_TIMER; index++)
    {
        if((pIoT_lwos_core->os_timer)[index].tmr_status == TMR_STAT_IDLE)
        {
            *tmr_handle = index;
            return OS_RET_OK;
        }
    }
    return OS_RET_NO_TIMER;
}
#endif
