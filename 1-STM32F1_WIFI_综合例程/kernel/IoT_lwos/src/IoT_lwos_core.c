/******************************************************************************
  * @file    IoT_lwos_core.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   IoT_lwos_core源文件
******************************************************************************/
#include "IoT_lwos_core.h"
#include "IoT_lwos_conf.h"
#include "IoT_lwos_task.h"

/* 定义IoT_lwos_core的全局变量 */
IoT_lwos_core_t IoT_lwos_core;
pIoT_lwos_core_t pIoT_lwos_core = &IoT_lwos_core;

os_stack IoT_lwos_idle_task_stack[CONF_IDLE_TASK_STK_SIZE];


/* 函数声明 */
static void IoT_lwos_core_reset(void);
static void IoT_lwos_tcb_init_list(void);
static  void  IoT_lwos_find_high_rdy (void);
static  void  IoT_lwos_idle_task_init (void);
#if CALC_CPU_LOADING>0
static void  IoT_lwos_calc_cpu_loading_enter(void);
static void  IoT_lwos_calc_cpu_loading_exit(void);
#endif

/* IoT_lwos的最高优先级unmap表 */
uint8_t  const  IoT_lwos_unmap_tbl[256] =
{
    0u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x00 to 0x0F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x10 to 0x1F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x20 to 0x2F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x30 to 0x3F */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x40 to 0x4F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x50 to 0x5F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x60 to 0x6F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x70 to 0x7F */
    7u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x80 to 0x8F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x90 to 0x9F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xA0 to 0xAF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xB0 to 0xBF */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xC0 to 0xCF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xD0 to 0xDF */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xE0 to 0xEF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u  /* 0xF0 to 0xFF */
};


/******************************************************************************
 *	函数名:	IoT_lwos_init
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		IoT_lwos的初始化
******************************************************************************/
void IoT_lwos_init(void)
{
    /* core的初始化 */
    IoT_lwos_core_reset();
    /* 初始化tcb list */
    IoT_lwos_tcb_init_list();
    /* 初始化memory */
#if MEMORY_MGR > 0
    IoT_lwos_mem_init();
#endif
    /* 创建空闲任务task */
    IoT_lwos_idle_task_init();
}

/******************************************************************************
 *	函数名:	IoT_lwos_tcb_init
 *	参数:		prio(IN)	-->task优先级设置
 				ptos(IN)	-->task堆栈顶
 *	返回值:	task tcb init结果
 *	描述:		IoT_lwos_tcb_init的初始化
******************************************************************************/
uint8_t  IoT_lwos_tcb_init (uint8_t prio, os_stack *ptos)
{
    pIoT_lwos_tcb_t ptcb;

    if(ptos == NULL)
    {
        return OS_RET_TASK_PIP_INVALID;
    }

    if(prio > CONF_LOWEST_PRIO)
    {
        return OS_RET_PRIO_INVALID;
    }

    /* 找出第一个空闲的tcb */
    ptcb = pIoT_lwos_core->os_tcb_free_list;
    if(ptcb == (pIoT_lwos_tcb_t)0)
    {
        return OS_RET_TASK_NO_MORE_TCB;
    }

    IoT_lwos_critial_enter();
    /* 把tcb free指针指向下一个tcb块 */
    pIoT_lwos_core->os_tcb_free_list = ptcb->tcb_next;

    ptcb->tcb_stack_ptr = ptos;

    /* 把存在的tcb串成一个单向链表,pIoT_lwos_core->os_tcb_list是头指针 */
    ptcb->tcb_next = pIoT_lwos_core->os_tcb_list;
    pIoT_lwos_core->os_tcb_list = ptcb;
    ptcb->tcb_delay = 0;
    ptcb->tcb_prio = prio;
    ptcb->tcb_y = (prio >> 3) & 0xff;
    ptcb->tcb_x = prio & 0x07;
    ptcb->tcb_bity = (1 << ptcb->tcb_y) & 0xff;
    ptcb->tcb_bitx = (1 << ptcb->tcb_x) & 0xff;

    /* 配置core成员 */
    (pIoT_lwos_core->os_tcb_prio_table)[prio] = ptcb;
    pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
    pIoT_lwos_core->os_tsk_cnt += 1;
    (pIoT_lwos_core->os_ready_table)[ptcb->tcb_y] |= ptcb->tcb_bitx;

    IoT_lwos_critial_exit();
    return OS_RET_OK;
}


/******************************************************************************
 *	函数名:	IoT_lwos_sched
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		查看是否有高优先级的task继续，如果存在那么就进行task切换
******************************************************************************/
void IoT_lwos_sched(void)
{
    if(pIoT_lwos_core->os_int_nesting == 0)
    {
        IoT_lwos_find_high_rdy();
        pIoT_lwos_core->os_tcb_high_rdy = (pIoT_lwos_core->os_tcb_prio_table)[pIoT_lwos_core->os_prio_high_rdy];
        /* 有更高的task，所以需要切换堆栈 */
        if(pIoT_lwos_core->os_tcb_high_rdy != pIoT_lwos_core->os_tcb_current)
        {
            (pIoT_lwos_core->os_swcontext_cnt)++;
            IoT_lwos_task_sw();
        }
    }
}

/******************************************************************************
 *	函数名:	IoT_lwos_start
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		启动最高优先级并执行
******************************************************************************/
void IoT_lwos_start(void)
{
    if(pIoT_lwos_core->os_running == FALSE)
    {
        IoT_lwos_find_high_rdy();
        pIoT_lwos_core->os_prio_current = pIoT_lwos_core->os_prio_high_rdy;
        pIoT_lwos_core->os_tcb_high_rdy = (pIoT_lwos_core->os_tcb_prio_table)[pIoT_lwos_core->os_prio_high_rdy];
        pIoT_lwos_core->os_tcb_current = pIoT_lwos_core->os_tcb_high_rdy;
        IoT_lwos_start_high_ready();

    }
}

/******************************************************************************
 *	函数名:	IoT_lwos_setos_runing
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		把IoT_lwos的状态设置为runing
******************************************************************************/
void IoT_lwos_setos_runing(void)
{
    pIoT_lwos_core->os_running = TRUE;
}

/******************************************************************************
 *	函数名:	IoT_lwos_get_task_num
 *	参数:		NULL
 *	返回值:	返回task的数量
 *	描述:		获取存在的task的数量
******************************************************************************/
uint8_t IoT_lwos_get_task_num(void)
{
	return pIoT_lwos_core->os_tsk_cnt;
}

/******************************************************************************
 *	函数名:	IoT_lwos_getos_runing
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		获取IoT_lwos的状态
******************************************************************************/
bool IoT_lwos_getos_runing(void)
{
    return pIoT_lwos_core->os_running;
}

/******************************************************************************
 *	函数名:	IoT_lwos_update_stack
 *	参数:		stack(IN)
 *	返回值:	NULL
 *	描述:		更新当前tcb的task指针
******************************************************************************/
void IoT_lwos_update_stack(os_stack * stack)
{
    pIoT_lwos_core->os_tcb_current->tcb_stack_ptr = stack;
}

/******************************************************************************
 *	函数名:	IoT_lwos_update_prio
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		更新当前task的优先级
******************************************************************************/
void IoT_lwos_update_prio()
{
    pIoT_lwos_core->os_prio_current = pIoT_lwos_core->os_prio_high_rdy;

}

/******************************************************************************
 *	函数名:	IoT_lwos_update_tcb
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		更新当前task的tcb
******************************************************************************/
void IoT_lwos_update_tcb()
{
    pIoT_lwos_core->os_tcb_current = pIoT_lwos_core->os_tcb_high_rdy;
}

/******************************************************************************
 *	函数名:	IoT_lwos_get_stack
 *	参数:		NULL
 *	返回值:	返回当前tcb的stack指针
 *	描述:		返回当前tcb的stack指针
******************************************************************************/
os_stack *IoT_lwos_get_stack()
{
    return pIoT_lwos_core->os_tcb_current->tcb_stack_ptr;
}

/******************************************************************************
 *	函数名:	IoT_lwos_int_enter
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		如果OS运行，那么此部分会累加进入systick的中断嵌套层数
******************************************************************************/
void  IoT_lwos_int_enter (void)
{
    if (IoT_lwos_getos_runing() == TRUE)
    {
#if CALC_CPU_LOADING>0
        IoT_lwos_calc_cpu_loading_enter();
#endif
        if (pIoT_lwos_core->os_int_nesting < 255u)
        {
            pIoT_lwos_core->os_int_nesting++;
        }
    }
}

/******************************************************************************
 *	函数名:	IoT_lwos_int_exit
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		如果OS运行，那么此部分会累减进入systick的中断嵌套层数
 				并且发现是否有更高优先级在ready状态，以便执行
******************************************************************************/
void  IoT_lwos_int_exit (void)
{
    if (IoT_lwos_getos_runing() == TRUE)
    {
#if CALC_CPU_LOADING>0
        IoT_lwos_calc_cpu_loading_exit();
#endif
        if (pIoT_lwos_core->os_int_nesting > 0)
        {
            pIoT_lwos_core->os_int_nesting--;
        }

        if(pIoT_lwos_core->os_int_nesting == 0)
        {
            IoT_lwos_find_high_rdy();
            pIoT_lwos_core->os_tcb_high_rdy = (pIoT_lwos_core->os_tcb_prio_table)[pIoT_lwos_core->os_prio_high_rdy];
            /* 有更高的task，所以需要切换堆栈 */
            if(pIoT_lwos_core->os_tcb_high_rdy != pIoT_lwos_core->os_tcb_current)
            {
                (pIoT_lwos_core->os_swcontext_cnt)++;
                IoT_lwos_task_sw();
            }
        }
    }

}

/******************************************************************************
 *	函数名:	IoT_lwos_time_tick
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		polling是否有task延时timeout
******************************************************************************/
void  IoT_lwos_time_tick(void)
{
    pIoT_lwos_tcb_t ptcb;
    if (IoT_lwos_getos_runing() == TRUE)
    {
        /* 轮训查看是否有timer timeout */
#if TIMER_MANAGER >0
        IoT_lwos_tmr_polling();
#endif

        pIoT_lwos_core->os_time++;
        ptcb = pIoT_lwos_core->os_tcb_list;

        while(ptcb->tcb_prio != CONF_IDL_TASK_PRIO)
        {
            /* 处理延时问题，如果有延时，没进入一次就-1,直到为0，重新加入ready表中，等待调度*/
            if(ptcb->tcb_delay != 0)
            {
                ptcb->tcb_delay--;
                if(ptcb->tcb_delay == 0)
                {
                    if((ptcb->os_tcb_status & TCB_STAT_PEND_ANY) != TCB_STAT_RDY)
                    {
                        ptcb->os_tcb_status  &= (uint8_t)~(uint8_t)TCB_STAT_PEND_ANY;
                        ptcb->os_tcb_pend_status = OS_STAT_PEND_TO;
                    }
                    else
                    {

                        ptcb->os_tcb_pend_status = OS_STAT_PEND_OK;
                    }
                    pIoT_lwos_core->os_ready_group |= ptcb->tcb_bity;
                    (pIoT_lwos_core->os_ready_table)[ptcb->tcb_y] |= ptcb->tcb_bitx;
                }
            }

            /* 指向链表的下一个tcb */
            ptcb = ptcb->tcb_next;
        }
    }

}


/******************************************************************************
 *	函数名:	IoT_lwos_calc_cpu_loading_enter
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		计算CPU loading的入口函数
 				原理为:在每次systick中断时候累加cpu_loading_tick，
 				并且如果是idle task在执行，那么就累加cpu_idle_loading_tick
******************************************************************************/
#if CALC_CPU_LOADING>0
static void  IoT_lwos_calc_cpu_loading_enter(void)
{
    pIoT_lwos_core->cpu_loading_tick++;
    if(pIoT_lwos_core->os_tcb_current->tcb_prio == CONF_IDL_TASK_PRIO)
    {
        pIoT_lwos_core->cpu_idle_loading_tick++;
    }
}
#endif
/******************************************************************************
 *	函数名:	IoT_lwos_calc_cpu_loading_exit
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		计算CPU loading的出口函数,并且计算CPU loading
 				如果发现cpu_loading_tick达到了CONF_CALC_CPU_LOADING_TICKS次数
 				那么就会计算一个idle task执行次数所占用CONF_CALC_CPU_LOADING_TICKS
 				的百分比，但是以上为空闲的，要得到CPU loading，在1-空闲
 				另外，需要注意的是CONF_CALC_CPU_LOADING_TICKS指越大，每次获取的时间
 				会变长
******************************************************************************/
#if CALC_CPU_LOADING>0
static void  IoT_lwos_calc_cpu_loading_exit(void)
{
    if(pIoT_lwos_core->cpu_loading_tick == CONF_CALC_CPU_LOADING_TICKS)
    {
        pIoT_lwos_core->cpu_loading = 1 - ((fp32)pIoT_lwos_core->cpu_idle_loading_tick) / CONF_CALC_CPU_LOADING_TICKS;
        pIoT_lwos_core->cpu_loading_tick = 0;
        pIoT_lwos_core->cpu_idle_loading_tick = 0;
    }
}
#endif


/******************************************************************************
 *	函数名:	IoT_lwos_swtsk_hook
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		任务切换的钩子程序，如果APP需要实时显示任务切换
 				则在APP层主动实现IoT_lwos_app_swtsk_hook
 				并且把SW_TASK_HOOK的宏定义打开
******************************************************************************/
void IoT_lwos_swtsk_hook()
{
#if SW_TASK_HOOK >0
    extern void IoT_lwos_app_swtsk_hook(void);
    IoT_lwos_app_swtsk_hook();
#endif
}

/******************************************************************************
 *	函数名:	IoT_lwos_get_cpu_loading
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		获取CPU loading
******************************************************************************/
#if CALC_CPU_LOADING>0
fp32 IoT_lwos_get_cpu_loading(void)
{
    return pIoT_lwos_core->cpu_loading;
}
#endif

/******************************************************************************
 *	函数名:	IoT_core_reset
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		reset IoT_lwos_core变量
******************************************************************************/
static void IoT_lwos_core_reset(void)
{
    os_memset(&IoT_lwos_core, 0, sizeof(IoT_lwos_core_t));
}

/******************************************************************************
 *	函数名:	IoT_lwos_tcb_init_list
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		把pIoT_lwos_core中的tcb table表构建出一个链表
 				tcb[0]-->tcb[1]-->tcb[2]-->.........->tcb[CONF_MAX_TCB-1]
 				并且把pIoT_lwos_core->os_tcb_free_list指向tcb[0]
 				把已经存在tcb置空
******************************************************************************/
static void IoT_lwos_tcb_init_list(void)
{
    uint8_t index = 0;
    pIoT_lwos_tcb_t ptcb_1;
    pIoT_lwos_tcb_t ptcb_2;
    /* 把core中的tcb table组成一个链表，分别指向下一个tcb */
    for(index = 0; index < CONF_MAX_TCB - 1; index++)
    {
        ptcb_1 = &(pIoT_lwos_core->os_tcb_table)[index];
        ptcb_2 = &(pIoT_lwos_core->os_tcb_table)[index + 1];
        ptcb_1->tcb_next = ptcb_2;
    }
    ptcb_1 = &(pIoT_lwos_core->os_tcb_table)[index];
    ptcb_1->tcb_next = (pIoT_lwos_tcb_t)0;

    /* 把指向存在的tcb指针置为空，把空闲的tcb指针指向第一个tcb */
    pIoT_lwos_core->os_tcb_list = (pIoT_lwos_tcb_t)0;
    pIoT_lwos_core->os_tcb_free_list = &(pIoT_lwos_core->os_tcb_table)[0];
}

/******************************************************************************
 *	函数名:	IoT_lwos_find_high_rdy
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		找出处于ready状态task的最高优先级
******************************************************************************/
static  void  IoT_lwos_find_high_rdy (void)
{
    uint8_t y;

    y = IoT_lwos_unmap_tbl[pIoT_lwos_core->os_ready_group];
    pIoT_lwos_core->os_prio_high_rdy = (uint8_t)((y << 3u) + IoT_lwos_unmap_tbl[(pIoT_lwos_core->os_ready_table)[y]]);
}


/******************************************************************************
 *	函数名:	IoT_lwos_idle_task
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		idle task执行函数
******************************************************************************/
void  IoT_lwos_idle_task(void *p_arg)
{
    p_arg = p_arg;

    while(1)
    {
        pIoT_lwos_core->os_idle_cnt++;
    }
}

/******************************************************************************
 *	函数名:	IoT_lwos_idle_task_init
 *	参数:		NULL
 *	返回值:	NULL
 *	描述:		创建空闲任务task
******************************************************************************/
static  void  IoT_lwos_idle_task_init (void)
{
#if IoT_lwos_stack_growth == 1
    IoT_lwos_cre_tsk(IoT_lwos_idle_task,
                     (void *)0,
                     &IoT_lwos_idle_task_stack[CONF_IDLE_TASK_STK_SIZE - 1u],
                     CONF_IDL_TASK_PRIO);
#else
    IoT_lwos_cre_tsk(IoT_lwos_idle_task,
                     (void *)0,
                     &IoT_lwos_idle_task_stack[0],
                     CONF_IDL_TASK_PRIO);
#endif
}
