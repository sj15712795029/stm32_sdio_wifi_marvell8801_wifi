/******************************************************************************
  * @file    IoT_lwos_task.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   task header file			
******************************************************************************/
#ifndef OS_TASK_H_H_H
#define OS_TASK_H_H_H
#include "IoT_lwos_port.h"

typedef void (*task_func_t)( void * );
uint8_t  IoT_lwos_cre_tsk(task_func_t task_function,void *p_arg,os_stack *ptos,uint8_t prio);

#endif
