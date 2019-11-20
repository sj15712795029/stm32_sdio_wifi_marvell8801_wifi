/******************************************************************************
  * @file    IoT_lwos_time.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-10
  * @brief   IoT_lwos_time源文件
******************************************************************************/
#include "IoT_lwos_time.h"
#include "IoT_lwos_port.h"
#include "IoT_lwos_conf.h"
#include "IoT_lwos_core.h"

extern pIoT_lwos_core_t pIoT_lwos_core;

/******************************************************************************
 *	函数名:	IoT_lwos_delay
 * 参数:  		ticks(IN)	-->延时多少个ticks
 * 返回值: 	IoT_lwos_delay执行结果
 * 描述:		表示延时多少个tick
******************************************************************************/
uint8_t IoT_lwos_delay(uint32_t ticks)
{
    uint8_t y;
    if(pIoT_lwos_core->os_int_nesting > 0)
    {
        return OS_RET_DELAY_ISR;
    }

    if(ticks <= 0)
    {
        return OS_RET_DELAY_INVALID;
    }
    /* 设置tcb延时 */
    IoT_lwos_critial_enter();
    pIoT_lwos_core->os_tcb_current->tcb_delay = ticks;

    /* 把cur task从tcb ready表中移除为了下一个task调度做准备 */
    y = pIoT_lwos_core->os_tcb_current->tcb_y;
    (pIoT_lwos_core->os_ready_table)[y] &= ~(pIoT_lwos_core->os_tcb_current->tcb_bitx);
    if (pIoT_lwos_core->os_ready_table[y] == 0u)
    {
        pIoT_lwos_core->os_ready_group &= ~(pIoT_lwos_core->os_tcb_current->tcb_bity);
    }
    IoT_lwos_critial_exit();
    IoT_lwos_sched();
    return OS_RET_OK;

}

/******************************************************************************
 *	函数名:	IoT_lwos_delayHMSM
 * 参数:  		hours(IN)	-->延时多少小时
 				mins(IN)	-->延时多少分钟
 				seconds(IN)-->延时多少秒
 				ms(IN)	-->延时多少毫秒
 * 返回值: 	IoT_lwos_delayHMSM执行结果
 * 描述:		表示延时多少个小时，分钟，秒，毫秒
 				但是需要注意的是:此部分会有误差，比如1s会触发100次systick中断
 				相当于一次tick为10ms，但是如果要延时4ms，那么就无法准确做到
 				所以为了保证尽可能的准确，所以做了一个四舍五入的简单算法
 				如果是>=5ms,那么就延时1tick,如果<5ms,那么就不延时
******************************************************************************/
uint8_t IoT_lwos_delayHMSM(uint8_t hours,uint8_t mins,uint8_t seconds,uint16_t ms)
{
    uint32_t ticks;
    if(pIoT_lwos_core->os_int_nesting > 0)
    {
        return OS_RET_DELAY_ISR;
    }
    if(mins >59 || seconds >59 || ms>999)
    {
        return OS_RET_DELAY_INVALID;
    }
    /* 此部分有误差，比如一个systick是10ms，但是如果要延时4ms,那么就不能达到1个systick,为了精度更准确一点，所以做了一个四舍五入的动作 */
    ticks = (hours*3600+mins*60+seconds)*CONF_TICKS_PER_SEC + (ms+5)/(1000/CONF_TICKS_PER_SEC);

    IoT_lwos_delay(ticks);
    return OS_RET_OK;

}

/******************************************************************************
 *	函数名:	IoT_lwos_get_tick
 * 参数:  		NULL
 * 返回值: 	返回系统运行的时间(以tick为单位)
 * 描述:		获取系统运行的tick数
******************************************************************************/
uint32_t IoT_lwos_get_tick()
{
    return pIoT_lwos_core->os_time;
}

/******************************************************************************
 *	函数名:	IoT_lwos_set_tick
 * 参数:  		ticks(IN)	-->要设置的ticks数目
 * 返回值: 	NULL
 * 描述:		设置系统运行的tick数
******************************************************************************/
void IoT_lwos_set_tick(uint32_t ticks)
{
    pIoT_lwos_core->os_time = ticks;
}

/******************************************************************************
 *	函数名:	IoT_lwos_printf_runtime
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		打印系统运行时间 HOURS:MIN:SEC:MS
******************************************************************************/
void IoT_lwos_printf_runtime()
{

    uint32_t ms_total = (pIoT_lwos_core->os_time)*(1000/CONF_TICKS_PER_SEC);
    uint16_t hours,ms;
    uint8_t mins,seconds;

    hours = ms_total/3600000;
    ms_total -= hours*3600000;

    mins = ms_total/60000;
    ms_total -= mins*60000;

    seconds = ms_total/1000;
    ms_total -= seconds*1000;

    ms = ms_total;
    os_printf("IoT_lwos runing time:%d:%02d:%02d:%d\n",hours,mins,seconds,ms);

}

