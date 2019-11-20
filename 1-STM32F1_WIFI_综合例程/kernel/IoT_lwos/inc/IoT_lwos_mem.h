/******************************************************************************
  * @file    IoT_lwos_mem.h
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-7-1
  * @brief   IoT_lwos_mem头文件
******************************************************************************/
#ifndef OS_MEM_H_H_H
#define OS_MEM_H_H_H
#include "IoT_lwos_port.h"
#include "IoT_lwos_conf.h"

#if MEMORY_MGR > 0
typedef struct
{
	mem_size_t next;	/* 下一块结构体在memory中的偏移 */
	mem_size_t prev;	/* 前一块结构体在memory中的偏移 */
	uint8_t used;			/* 是否被用到，1用到，0没用 */
}IoT_lwos_mem_t;
typedef IoT_lwos_mem_t* pIoT_lwos_mem_t;


#define LWOS_MEM_ALIGN(addr) ((void *)(((uint32_t)(addr) + CONF_MEM_ALIGNMENT - 1) & ~(uint32_t)(CONF_MEM_ALIGNMENT-1)))
#define LWOS_MEM_ALIGN_SIZE(size) (((size) + CONF_MEM_ALIGNMENT - 1U) & ~(CONF_MEM_ALIGNMENT-1U))
#define MIN_SIZE_ALIGNED     LWOS_MEM_ALIGN_SIZE(CONF_MIN_SIZE)
#define SIZEOF_STRUCT_MEM    LWOS_MEM_ALIGN_SIZE(sizeof(IoT_lwos_mem_t))
#define MEM_SIZE_ALIGNED     LWOS_MEM_ALIGN_SIZE(CONF_MEM_SIZE)

void IoT_lwos_mem_init(void);
void *IoT_lwos_mem_malloc(mem_size_t size);
void *IoT_lwos_mem_calloc(mem_size_t count, mem_size_t size);
void IoT_lwos_mem_free(void *rmem);
#endif

#endif
