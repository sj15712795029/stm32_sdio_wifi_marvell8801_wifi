/******************************************************************************
  * @file    IoT_lwos_port_cm3.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   IoT_lwos移植文件作用是:
  				1.数据类型	
******************************************************************************/
#ifndef OS_PORT_H_H_H
#define OS_PORT_H_H_H

#define IoT_lwos_stack_growth 1

typedef unsigned char 	uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int 	uint32_t;
typedef unsigned long long uint64_t;
typedef float 			fp32;
typedef signed char 	int8_t;
typedef signed short 	int16_t;
typedef signed int		int32_t;
typedef signed char		err_t;
typedef unsigned int   	os_stack;
typedef unsigned int	os_cpu_sr;	
typedef uint32_t mem_size_t;


void IoT_lwos_task_sw(void);
void IoT_lwos_start_high_ready(void); 
void IoT_lwos_critial_enter(void);
void IoT_lwos_critial_exit(void);

/* 中断处理函数 */
#define IoT_lwos_pendSV_hdl 	PendSV_Handler
#define IoT_lwos_SV_hdl 	SVC_Handler
#define IoT_lwos_systick_hdl 	SysTick_Handler
#define IoT_lwos_hardfault_hdl HardFault_Handler

#endif
