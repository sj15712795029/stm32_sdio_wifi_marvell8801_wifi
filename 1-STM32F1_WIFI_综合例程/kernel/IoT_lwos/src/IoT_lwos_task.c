/******************************************************************************
  * @file    IoT_lwos_task.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   IoT_lwos_task源文件
******************************************************************************/
#include "IoT_lwos_task.h"
#include "IoT_lwos_conf.h"
#include "IoT_lwos_core.h"

extern pIoT_lwos_core_t pIoT_lwos_core;
extern os_stack *IoT_lwos_stack_init (task_func_t task_function,void *p_arg,os_stack *ptos);

/******************************************************************************
 *	函数名:	IoT_lwos_cre_tsk
 * 参数:  		task_function(IN)		-->task执行函数的指针
 				p_arg(IN)				-->task执行函数的入参
 				ptos(IN)				-->栈顶
 				prio(IN)				-->task优先级
 * 返回值: 	创建task的返回结果
 * 描述:		创建一个task
******************************************************************************/
uint8_t  IoT_lwos_cre_tsk(task_func_t task_function,void *p_arg,os_stack *ptos,uint8_t prio)
{
    os_stack *psp;
    uint8_t ret;

    if(prio > CONF_LOWEST_PRIO)
    {
        return OS_RET_PRIO_INVALID;
    }


    if(pIoT_lwos_core->os_int_nesting > 0)
    {
        return OS_RET_TASK_CREATE_ISR;
    }

    if((pIoT_lwos_core->os_tcb_prio_table)[prio] != (pIoT_lwos_tcb_t)0)
    {
        return OS_RET_PRIO_EXIST;
    }

    (pIoT_lwos_core->os_tcb_prio_table)[prio] = (pIoT_lwos_tcb_t)1;

    psp = (os_stack *)IoT_lwos_stack_init(task_function,p_arg,ptos);
    if(psp == NULL)
    {
        return OS_RET_TASK_PIP_INVALID;
    }
    ret = IoT_lwos_tcb_init(prio,psp);
    if(ret == OS_RET_OK)
    {
        if(pIoT_lwos_core->os_running == TRUE)
        {
            IoT_lwos_sched();
        }
    }
    else
    {
        (pIoT_lwos_core->os_tcb_prio_table)[prio] = (pIoT_lwos_tcb_t)0;
    }

    return ret;
}
