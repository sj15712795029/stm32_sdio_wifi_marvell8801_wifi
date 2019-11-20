/******************************************************************************
  * @file    IoT_lwos_port_cm3.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   IoT_lwos基于cortex M3的移植
******************************************************************************/
#include "IoT_lwos_port.h"
#include "IoT_lwos_task.h"
#include "IoT_lwos_core.h"
#include "IoT_lwos_conf.h"

#define NVIC_INT_CTRL 0xE000ED04	/* 中断控制和状态寄存器 */
#define NVIC_SYSPRI14 0xE000ED22	/* PENDSV中断优先级 */
#define NVIC_PENDSV_PRI 0xFF		/* 最低优先级 */
#define NVIC_PENDSVSET 0x10000000/* 终端控制和状态寄存器的bit28 设置pendsv中断 */


/******************************************************************************
 *	函数名:	IoT_lwos_stack_init
 * 参数:  		task_function(IN)	-->task 执行函数
 				p_arg(IN)			-->task 执行函数的参数
 				ptos(IN)			-->task 执行函数的栈顶
 * 返回值: 	返回task执行函数的堆栈指针
 * 描述:		task进行堆栈指针的初始化，
 				寄存器的初始化顺序不能变更(基于cortex M3架构)
******************************************************************************/
os_stack *IoT_lwos_stack_init (task_func_t task_function,void *p_arg,os_stack *ptos)
{
    os_stack *stack = ptos;

    if(task_function == NULL || stack == NULL)
    {
    	return NULL;
    }
    /* 此部分寄存器在进入中断时按照以下写程序的顺序会自动被压入堆栈中 */
    *(stack)    = (uint32_t)0x01000000L;		/* xPSR寄存器 */
    *(--stack)  = (uint32_t)task_function;       /* Entry Point PC寄存器 */
    *(--stack)  = (uint32_t)0xFFFFFFFEL;          /* R14 (LR)寄存器 */
    *(--stack)  = (uint32_t)0x12121212L;          /* R12寄存器 */
    *(--stack)  = (uint32_t)0x03030303L;          /* R3寄存器 */
    *(--stack)  = (uint32_t)0x02020202L;          /* R2寄存器 */
    *(--stack)  = (uint32_t)0x01010101L;          /* R1寄存器 */
    *(--stack)  = (uint32_t)p_arg;                   	/* R0寄存器 : argument */

    /* 此部分的寄存器需要user在进入中断后备份，在堆栈切换时恢复到寄存器中 */
    *(--stack)  = (uint32_t)0x11111111L;		/* R11寄存器 */
    *(--stack)  = (uint32_t)0x10101010L;		/* R10寄存器 */
    *(--stack)  = (uint32_t)0x09090909L;		/* R9寄存器 */
    *(--stack)  = (uint32_t)0x08080808L;		/* R8寄存器 */
    *(--stack)  = (uint32_t)0x07070707L;		/* R7寄存器 */
    *(--stack)  = (uint32_t)0x06060606L;		/* R6寄存器 */
    *(--stack)  = (uint32_t)0x05050505L;		/* R5寄存器 */
    *(--stack)  = (uint32_t)0x04040404L;             	/* R4寄存器 */

    return (stack);
}

/******************************************************************************
 *	函数名:	IoT_lwos_task_sw
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		主要用于堆栈切换，原理是触发PENDSV的中断，
 				在PENDSV中断中进行堆栈切换
******************************************************************************/
__asm void IoT_lwos_task_sw(void)
{
    /* 堆栈8字节对齐 */
    PRESERVE8

    /* 把R4,R5压入堆栈 */
    PUSH    {R4, R5}

    /* 触发PENDSV中断 */
    LDR     R4, =NVIC_INT_CTRL
	LDR     R5, =NVIC_PENDSVSET
	STR     R5, [R4]

	/* 把R4,R5从堆栈中弹出 */
	POP     {R4, R5}

	/* 返回 */
	BX      LR
	NOP
}

/******************************************************************************
 *	函数名:	IoT_lwos_start_high_ready
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		主要用于开启第一个最高优先级的task，触发PENDSV中断
 				在PENDSV中断中进行调用第一个优先级最高的task
******************************************************************************/
__asm void IoT_lwos_start_high_ready(void)
{
	extern IoT_lwos_setos_runing
	/* 堆栈8字节对齐 */
	PRESERVE8

	/* 设置PENDSV为最低的优先级 */
	LDR     R4, =NVIC_SYSPRI14
	LDR     R5, =NVIC_PENDSV_PRI
	STR     R5, [R4]

	/* 设置PSP为0 */
	MOV     R4, #0
	MSR     PSP, R4

	/* 设置为IoT_lwos为runing状态 */
	BL IoT_lwos_setos_runing

	/* 触发PENDSV中断 */
	LDR     R4, =NVIC_INT_CTRL
	LDR     R5, =NVIC_PENDSVSET
	STR     R5, [R4]

	/* 开启中断 */
	CPSIE   I

IoT_lwos_start_loop
	B	IoT_lwos_start_loop
}


/******************************************************************************
 *	函数名:	IoT_lwos_pendSV_hdl
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		PENDSV中断处理函数，主要用于
 				1.如果PSP为0,那么就运行第一个优先级最高的TASK
 				2.如果PSP不为0，那么先保存寄存器到当前堆栈指针中
 				  然后再切换到下一个最高优先级的task，弹出堆栈指针运行
******************************************************************************/
__asm void IoT_lwos_pendSV_hdl(void)
{
    extern IoT_lwos_update_prio
    extern IoT_lwos_update_tcb
    extern IoT_lwos_get_stack
    extern IoT_lwos_update_stack
    extern IoT_lwos_swtsk_hook

    /* 堆栈8字节对齐 */
    PRESERVE8

    /* 关闭中断 */
    CPSID   I

    /* 把PSP读到R0寄存器中 */
    MRS		R0, PSP

    /* 如果R0为0,也就是PSP为0,那么我们就认为是第一次运行 */
    CBZ		R0, IoT_lwos_pendSV_nosave

    /* 如果PSP不为0,那么我们应该先把R4-R11压入当前TCB的堆栈指针中 */
    SUBS	R0, R0, #0x20
    STM		R0, {R4-R11}

    /* 把最新的PSP指针更新到OSTCBCur中 */
    BL	IoT_lwos_update_stack

IoT_lwos_pendSV_nosave

    /* 获取到最高的ready状态的task优先级，赋值给current task prio */
    BL	IoT_lwos_update_prio

	PUSH    {R14}
    LDR     R0, =IoT_lwos_swtsk_hook
    BLX     R0
    POP     {R14}
	
    /* 获取到最高的ready状态的task TCB，赋值给current task tcb */
    BL	IoT_lwos_update_tcb

    /* 获取到当前TCB的stack指针,返回值存在R0中,R0是最新的堆栈指针 */
    BL	IoT_lwos_get_stack

    /* 从堆栈指针中弹出R4~R11，并相应的回复，并且更新PSP */
    LDM     R0, {R4-R11}
    ADDS    R0, R0, #0x20
    MSR     PSP, R0

    /* 设置为PSP作为堆栈指针 */
    MOV			LR,#0xfffffffd
    CPSIE   I
    BX      LR
    NOP
}

/******************************************************************************
 *	函数名:	IoT_lwos_critial_enter
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		关闭中断并返回
******************************************************************************/
__asm void IoT_lwos_critial_enter(void)
{	
    CPSID	I
    BX LR
}

/******************************************************************************
 *	函数名:	IoT_lwos_critial_exit
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		开启中断并返回
******************************************************************************/
__asm void IoT_lwos_critial_exit(void)
{
    CPSIE	I
    BX LR
}

/******************************************************************************
 *	函数名:	IoT_lwos_SV_hdl
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		SV中断
******************************************************************************/
__asm void IoT_lwos_SV_hdl(void)
{

}


/******************************************************************************
 *	函数名:	IoT_lwos_hardfault_hdl
 * 参数:  		NULL
 * 返回值: 	NULL
 * 描述:		硬错误处理
******************************************************************************/
void IoT_lwos_hardfault_hdl(void)
{
	while(1);
}
