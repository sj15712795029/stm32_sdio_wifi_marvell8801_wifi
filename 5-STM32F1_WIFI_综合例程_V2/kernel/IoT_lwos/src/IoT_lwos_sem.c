/******************************************************************************
  * @file    IoT_lwos_sem.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-19
  * @brief   IoT_lwos_sem源文件
******************************************************************************/
#include "IoT_lwos_sem.h"
#include "IoT_lwos_core.h"

extern pIoT_lwos_core_t pIoT_lwos_core;
extern uint8_t  const  IoT_lwos_unmap_tbl[256];
/* 函数声明区 */
static uint8_t  IoT_lwos_sem_evt_remove (pIoT_lwos_tcb_t   ptcb,pIoT_lwos_sem_t psem);

/******************************************************************************
 *	函数名:	IoT_lwos_cre_sem
 * 参数:  		psem(IN)		-->sem指针
 				cnt(IN)		-->sem的初始化值
 * 返回值: 	创建sem的结果
 * 描述:		创建一个信号量
******************************************************************************/
uint8_t  IoT_lwos_cre_sem(pIoT_lwos_sem_t psem,uint16_t cnt)
{
    if(psem == NULL)
    {
        return OS_RET_SEM_INVALID_PARA;
    }

    psem->sem_cnt = cnt;

    return OS_RET_OK;
}

/******************************************************************************
 *	函数名:	IoT_lwos_wait_sem
 * 参数:  		psem(IN)		-->sem指针
 				ticks(IN)		-->sem等待timeout值，如果为0,则一直等待
 * 返回值: 	返回等待信号量的结果
 * 描述:		等待一个信号量
******************************************************************************/
uint8_t  IoT_lwos_wait_sem(pIoT_lwos_sem_t psem,uint32_t ticks)
{
    uint8_t y;
    uint8_t ret;

    if(psem == NULL)
    {
        return OS_RET_SEM_INVALID_PARA;
    }

    if(pIoT_lwos_core->os_int_nesting > 0)
    {
        return OS_RET_SEM_CREATE_ISR;
    }

    /* sem可用，直接return */
    if(psem->sem_cnt > 0)
    {
        psem->sem_cnt--;
        return OS_RET_OK;
    }

    IoT_lwos_critial_enter();
    /* sem不可用，初始化tcb的部分值 */
    pIoT_lwos_core->os_tcb_current->os_tcb_status |= TCB_STAT_SEM;
    pIoT_lwos_core->os_tcb_current->os_tcb_pend_status = OS_STAT_PEND_OK;
    pIoT_lwos_core->os_tcb_current->tcb_delay = ticks;
    pIoT_lwos_core->os_tcb_current->os_tcb_sem_ptr = psem;

    y = pIoT_lwos_core->os_tcb_current->tcb_y;
    psem->sem_evt_table[y] |= pIoT_lwos_core->os_tcb_current->tcb_bitx;
    psem->sem_evt_group |= pIoT_lwos_core->os_tcb_current->tcb_bity;


    (pIoT_lwos_core->os_ready_table)[y] &= ~pIoT_lwos_core->os_tcb_current->tcb_bitx;

    if((pIoT_lwos_core->os_ready_table)[y] == 0)
    {
        pIoT_lwos_core->os_ready_group &= ~pIoT_lwos_core->os_tcb_current->tcb_bity;
    }
    IoT_lwos_critial_exit();
    IoT_lwos_sched();
    switch(pIoT_lwos_core->os_tcb_current->os_tcb_pend_status)
    {
    case OS_STAT_PEND_OK:
        ret =  OS_RET_OK;
        break;
    case OS_STAT_PEND_TO:
    default:
    {
        IoT_lwos_sem_evt_remove(pIoT_lwos_core->os_tcb_current, psem);
        ret = OS_RET_SEM_TIEMOUT;
        break;
    }
    }

    IoT_lwos_critial_enter();
    pIoT_lwos_core->os_tcb_current->os_tcb_status |= TCB_STAT_RDY;
    pIoT_lwos_core->os_tcb_current->os_tcb_pend_status = OS_STAT_PEND_OK;
    pIoT_lwos_core->os_tcb_current->os_tcb_sem_ptr = 0;
    IoT_lwos_critial_exit();
    return ret;

}

/******************************************************************************
 *	函数名:	IoT_lwos_sig_sem
 * 参数:  		psem(IN)		-->sem指针
 * 返回值: 	返回发送信号量的结果
 * 描述:		发送一个信号量
******************************************************************************/
uint8_t  IoT_lwos_sig_sem(pIoT_lwos_sem_t psem)
{
    pIoT_lwos_tcb_t   ptcb;
    uint8_t     y;
    uint8_t     x;
    uint8_t     prio;

    if(psem == NULL)
    {
        return OS_RET_SEM_INVALID_PARA;
    }
    /* 如果有task在等sem,那么直接调度 */
    if(psem->sem_evt_group != 0)
    {
        IoT_lwos_critial_enter();
        y    = IoT_lwos_unmap_tbl[psem->sem_evt_group];
        x    = IoT_lwos_unmap_tbl[psem->sem_evt_table[y]];
        prio = (uint8_t)((y << 3u) + x);
        ptcb =  pIoT_lwos_core->os_tcb_prio_table[prio];
        ptcb->tcb_delay  =  0;
        ptcb->os_tcb_status = TCB_STAT_RDY;
        ptcb->os_tcb_pend_status = OS_STAT_PEND_OK;

        /* 把当前tcb的更新到调度列表中 */
        pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
        (pIoT_lwos_core->os_ready_table)[y] |= ptcb->tcb_bitx;
        IoT_lwos_critial_exit();
        IoT_lwos_sem_evt_remove(ptcb,psem);
        IoT_lwos_sched();
        return OS_RET_OK;
    }
    /* 如果没有task在等，单纯的+1 返回 */
    psem->sem_cnt++;
    return OS_RET_OK;
}


/******************************************************************************
 *	函数名:	IoT_lwos_sem_evt_remove
 * 参数:  		ptcb(IN)		-->TCB指针
 				psem(IN)		-->sem指针
 * 返回值: 	删除sem的event的成员结果
 * 描述:		清空sem的event成员
******************************************************************************/
static uint8_t  IoT_lwos_sem_evt_remove (pIoT_lwos_tcb_t   ptcb,pIoT_lwos_sem_t psem)
{
    uint8_t y;

    if(ptcb == NULL ||psem == NULL )
    {
        return OS_RET_SEM_INVALID_PARA;
    }
    y = ptcb->tcb_y;
    psem->sem_evt_table[y] &= ~ptcb->tcb_bitx;
    if(psem->sem_evt_table[y] == 0)
    {
        psem->sem_evt_group &= ~ptcb->tcb_bity;
    }
    return OS_RET_OK;
}
