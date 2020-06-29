/******************************************************************************
  * @file    IoT_lwos_time.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-9
  * @brief   time header file			
******************************************************************************/
#ifndef OS_TIME_H_H_H
#define OS_TIME_H_H_H
#include "IoT_lwos_port.h"

uint8_t IoT_lwos_delay(uint32_t ticks);
uint8_t IoT_lwos_delayHMSM(uint8_t hours,uint8_t mins,uint8_t seconds,uint16_t ms);
uint32_t IoT_lwos_get_tick(void);
void IoT_lwos_set_tick(uint32_t ticks);
void IoT_lwos_printf_runtime(void);

#endif
