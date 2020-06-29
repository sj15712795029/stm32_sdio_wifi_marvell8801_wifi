/******************************************************************************
  * @file    IoT_lwos_sem.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-21
  * @brief   IoT_lwos_mutex源文件
******************************************************************************/
#include "IoT_lwos_mutex.h"
#include "IoT_lwos_core.h"

extern pIoT_lwos_core_t pIoT_lwos_core;
extern uint8_t  const  IoT_lwos_unmap_tbl[256];

/* 函数声明区 */
static uint8_t  IoT_lwos_mutex_evt_remove (pIoT_lwos_tcb_t   ptcb,pIoT_lwos_mutex_t pmutex);
static uint8_t IoT_lwos_mutex_resume_prio(pIoT_lwos_tcb_t   ptcb,uint8_t prio);
static uint8_t IoT_lwos_mutex_task_rdy(pIoT_lwos_mutex_t pmutex,uint8_t msk,uint8_t pend_stat);

/******************************************************************************
 *	函数名:	IoT_lwos_cre_mutex
 *	参数:		pmutex(IN)		-->mutex指针
				prio(IN)		-->要反转的优先级
 *	返回值:	创建mutex的结果
 *	描述:		创建一个互斥量
******************************************************************************/
uint8_t IoT_lwos_cre_mutex(pIoT_lwos_mutex_t pmutex,uint8_t prio)
{
    if(pmutex == NULL)
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }
    /* 判断PIP是否存在 */
    if((pIoT_lwos_core->os_tcb_prio_table)[prio] != 0)
    {
        return OS_RET_MUTEX_PIP_EXIST;
    }
    (pIoT_lwos_core->os_tcb_prio_table)[prio] = (pIoT_lwos_tcb_t)1;

    pmutex->mutex_cnt = (uint16_t)((uint16_t)prio << 8) | OS_MUTEX_AVAILABLE;
    pmutex->ptcb = (pIoT_lwos_tcb_t)0;

    return OS_RET_OK;

}

/******************************************************************************
 *	函数名:	IoT_lwos_lock_mutex
 *	参数:		pmutex(IN)		-->mutex指针
 				ticks(IN)		-->超时的时钟节拍
 *	返回值:	lock mutex的结果
 *	描述:		把互斥量加锁
******************************************************************************/
uint8_t IoT_lwos_lock_mutex(pIoT_lwos_mutex_t pmutex,uint32_t ticks)
{
    uint8_t ret;
    uint8_t      pip;
    uint8_t      mprio;
    bool    rdy;
    pIoT_lwos_tcb_t ptcb;
    uint8_t      y;
    pIoT_lwos_mutex_t pmutex2;
    if(pmutex == NULL)
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }

    if(pIoT_lwos_core->os_int_nesting > 0)
    {
        return OS_RET_MUTEX_CREATE_ISR;
    }

    /* 获取到PIP */
    pip = (uint8_t)(pmutex->mutex_cnt >> 8u);

    /* 表示mutex可用 */
    if((uint8_t)(pmutex->mutex_cnt & OS_MUTEX_KEEP_LOWER_8) == OS_MUTEX_AVAILABLE)
    {
        IoT_lwos_critial_enter();
        pmutex->mutex_cnt &= OS_MUTEX_KEEP_UPPER_8;
        pmutex->mutex_cnt |= pIoT_lwos_core->os_tcb_current->tcb_prio;
        pmutex->ptcb = pIoT_lwos_core->os_tcb_current;
        if(pIoT_lwos_core->os_tcb_current->tcb_prio <= pip)
        {
            IoT_lwos_critial_exit();
            return OS_RET_MUTEX_PIP_LOWER;
        }
        else
        {
            IoT_lwos_critial_exit();
            return OS_RET_OK;
        }
    }

    /* 表示mutex不可用 */
    IoT_lwos_critial_enter();
    mprio = (uint8_t)(pmutex->mutex_cnt & OS_MUTEX_KEEP_LOWER_8);
    ptcb = pmutex->ptcb;
    if(ptcb->tcb_prio > pip)
    {
        if(mprio > pIoT_lwos_core->os_tcb_current->tcb_prio)
        {
            y = ptcb->tcb_y;
            if(((pIoT_lwos_core->os_ready_table)[y] & ptcb->tcb_bitx) != 0)
            {
                (pIoT_lwos_core->os_ready_table)[y] &= (uint8_t)~(ptcb->tcb_bitx);
                if((pIoT_lwos_core->os_ready_table)[y]  == 0)
                {
                    pIoT_lwos_core->os_ready_group &= (uint8_t)~(ptcb->tcb_bity);
                }
                rdy = TRUE;
            }
            else
            {
                pmutex2 = ptcb->os_tcb_mutex_ptr;
                if(pmutex2 != (pIoT_lwos_mutex_t)0)
                {
                    y = ptcb->tcb_y;
                    (pmutex2->mutex_evt_table)[y] &= (uint8_t)~ptcb->tcb_bitx;
                    if((pmutex2->mutex_evt_table)[y] == 0)
                    {
                        pmutex2->mutex_evt_group &= (uint8_t)~ptcb->tcb_bity;
                    }
                }
                rdy = FALSE;
            }
            ptcb->tcb_prio = pip;
            ptcb->tcb_y    = (uint8_t)( ptcb->tcb_prio >> 3);
            ptcb->tcb_x    = (uint8_t)( ptcb->tcb_prio & 0x07);
            ptcb->tcb_bity = (uint8_t)(1 << ptcb->tcb_y);
            ptcb->tcb_bitx = (uint8_t)(1 << ptcb->tcb_x);

            if(rdy == TRUE)
            {
                pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
                (pIoT_lwos_core->os_ready_table)[ptcb->tcb_y] |= ptcb->tcb_bitx;
            }
            else
            {
                pmutex2 = ptcb->os_tcb_mutex_ptr;
                if(pmutex2 != (pIoT_lwos_mutex_t)0)
                {

                    pmutex2->mutex_evt_group |= (uint8_t)ptcb->tcb_bity;
                    (pmutex2->mutex_evt_table)[ptcb->tcb_y] |= ptcb->tcb_bitx;
                }
            }
            (pIoT_lwos_core->os_tcb_prio_table)[pip] = ptcb;
        }
    }
    pIoT_lwos_core->os_tcb_current->os_tcb_status |= TCB_STAT_MUTEX;
    pIoT_lwos_core->os_tcb_current->os_tcb_pend_status = OS_STAT_PEND_OK;
    pIoT_lwos_core->os_tcb_current->tcb_delay = ticks;
    pIoT_lwos_core->os_tcb_current->os_tcb_mutex_ptr = pmutex;


    y = pIoT_lwos_core->os_tcb_current->tcb_y;
    pmutex->mutex_evt_table[y] |= pIoT_lwos_core->os_tcb_current->tcb_bitx;
    pmutex->mutex_evt_group |= pIoT_lwos_core->os_tcb_current->tcb_bity;


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
        IoT_lwos_mutex_evt_remove(pIoT_lwos_core->os_tcb_current, pmutex);
        ret = OS_RET_MUTEX_TIEMOUT;
        break;
    }
    }

    IoT_lwos_critial_enter();
    pIoT_lwos_core->os_tcb_current->os_tcb_status = TCB_STAT_RDY;
    pIoT_lwos_core->os_tcb_current->os_tcb_pend_status = OS_STAT_PEND_OK;
    pIoT_lwos_core->os_tcb_current->os_tcb_mutex_ptr = 0;
    IoT_lwos_critial_exit();
    return ret;



}

/******************************************************************************
 *	函数名:	IoT_lwos_unlock_mutex
 *	参数:		pmutex(IN)		-->mutex指针
 *	返回值:	unlock mutex的结果
 *	描述:		互斥量解锁
******************************************************************************/
uint8_t IoT_lwos_unlock_mutex(pIoT_lwos_mutex_t pmutex)
{
    uint8_t      pip;
    uint8_t      prio;
    if(pmutex == NULL)
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }

    pip = (uint8_t)(pmutex->mutex_cnt >> 8);
    prio = (uint8_t)(pmutex->mutex_cnt & OS_MUTEX_KEEP_LOWER_8);
    if(pIoT_lwos_core->os_tcb_current != pmutex->ptcb)
    {
        return OS_RET_MUTEX_NOT_OWER;
    }

    if (pIoT_lwos_core->os_tcb_current->tcb_prio == pip)
    {
        IoT_lwos_mutex_resume_prio(pIoT_lwos_core->os_tcb_current,prio);
    }

    (pIoT_lwos_core->os_tcb_prio_table)[pip] = (pIoT_lwos_tcb_t)1;
    if(pmutex->mutex_evt_group != 0)
    {
        prio = IoT_lwos_mutex_task_rdy(pmutex,TCB_STAT_MUTEX,OS_STAT_PEND_OK);
        pmutex->mutex_cnt &= OS_MUTEX_KEEP_UPPER_8;
        pmutex->mutex_cnt |= prio;
        pmutex->ptcb = (pIoT_lwos_core->os_tcb_prio_table)[prio];

        if(prio <= pip)
        {
            IoT_lwos_sched();
            return OS_RET_MUTEX_PIP_LOWER;
        }
        else
        {
            IoT_lwos_sched();
            return OS_RET_OK;
        }
    }

    pmutex->mutex_cnt |= OS_MUTEX_AVAILABLE;
    pmutex->ptcb = (pIoT_lwos_tcb_t)0;

    return OS_RET_OK;

}

/******************************************************************************
 *	函数名:	IoT_lwos_mutex_evt_remove
 *	参数:		ptcb(IN)		-->TCB指针
 				pmutex(IN)		-->mutex指针
 *	返回值:	删除mutex的event的成员结果
 *	描述:		清空mutex的event成员
******************************************************************************/
static uint8_t  IoT_lwos_mutex_evt_remove (pIoT_lwos_tcb_t   ptcb,pIoT_lwos_mutex_t pmutex)
{
    uint8_t y;

    if(ptcb == NULL ||pmutex == NULL )
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }
    y = ptcb->tcb_y;
    pmutex->mutex_evt_table[y] &= ~ptcb->tcb_bitx;
    if(pmutex->mutex_evt_table[y] == 0)
    {
        pmutex->mutex_evt_group &= ~ptcb->tcb_bity;
    }
    return OS_RET_OK;
}


/******************************************************************************
 *	函数名:	IoT_lwos_mutex_resume_prio
 *	参数:		ptcb(IN)		-->tcb指针
 				prio(IN)		-->要恢复的任务优先级
 *	返回值:	恢复优先级的结果
 *	描述:		把一个任务的优先级从反转的优先级恢复到原本的优先级
******************************************************************************/
static uint8_t IoT_lwos_mutex_resume_prio(pIoT_lwos_tcb_t   ptcb,uint8_t prio)
{
    uint8_t y;

    if(ptcb == NULL )
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }

    IoT_lwos_critial_enter();
    y = ptcb->tcb_y;

    (pIoT_lwos_core->os_ready_table)[y] &= ~ptcb->tcb_bitx;
    if((pIoT_lwos_core->os_ready_table)[y] == 0)
    {
        pIoT_lwos_core->os_ready_group &= ~ptcb->tcb_bity;
    }
    ptcb->tcb_prio = prio;
    pIoT_lwos_core->os_prio_current = prio;

    ptcb->tcb_y = (uint8_t)((uint8_t)(prio >> 3u) & 0x07u);
    ptcb->tcb_x = (uint8_t)(prio & 0x07u);

    ptcb->tcb_bity = (1 << ptcb->tcb_y);
    ptcb->tcb_bitx = (1 << ptcb->tcb_x);

    pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
    (pIoT_lwos_core->os_ready_table)[ptcb->tcb_y] |= ptcb->tcb_bitx;
    (pIoT_lwos_core->os_tcb_prio_table)[prio] = ptcb;
    IoT_lwos_critial_exit();
    return OS_RET_OK;
}

/******************************************************************************
 *	函数名:	IoT_lwos_mutex_task_rdy
 *	参数:		pmutex(IN)		-->mutex指针
 				msk(IN)		-->任务状态
 				pend_stat(IN)	-->任务pend状态
 *	返回值:	优先级
 *	描述:		把一个任务重新设置为ready状态
******************************************************************************/
static uint8_t IoT_lwos_mutex_task_rdy(pIoT_lwos_mutex_t pmutex,uint8_t msk,uint8_t pend_stat)
{
    pIoT_lwos_tcb_t ptcb;
    uint8_t y;
    uint8_t x;
    uint8_t prio;

    if(pmutex == NULL)
    {
        return OS_RET_MUTEX_INVALID_PARA;
    }
    IoT_lwos_critial_enter();
    y    = IoT_lwos_unmap_tbl[pmutex->mutex_evt_group];
    x    = IoT_lwos_unmap_tbl[pmutex->mutex_evt_table[y]];
    prio = (uint8_t)((y << 3u) + x);
    ptcb =  pIoT_lwos_core->os_tcb_prio_table[prio];
    ptcb->tcb_delay  =  0;
    ptcb->os_tcb_status &= (uint8_t)~msk;
    ptcb->os_tcb_pend_status = pend_stat;

    /* 把当前tcb的更新到调度列表中 */
    if(ptcb->os_tcb_status == TCB_STAT_RDY)
    {
        pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
        (pIoT_lwos_core->os_ready_table)[y] |= ptcb->tcb_bitx;
    }
    IoT_lwos_critial_exit();
    IoT_lwos_mutex_evt_remove(ptcb,pmutex);

    return prio;


}

