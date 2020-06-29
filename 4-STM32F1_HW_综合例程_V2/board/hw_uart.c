/******************************************************************************
  * @file    hw_usart.c
  * @author  Yu-ZhongJun
  * @version V0.0.1
  * @date    2018-6-26
  * @brief   usart source file
******************************************************************************/

#include "hw_uart.h"

uint8_t uart_receive_parse(uint8_t *shell_string);

#define UART1_MAX_REV	256
uint8_t uart1_rev_buffer[UART1_MAX_REV];
uint8_t uart1_rev_len = 0;


/******************************************************************************
 * func name   : fputc
 * para        : ch(IN)  --> output char
                 fp(IN)  --> file point
 * return      : return output char
 * description : The fputc () function redirects the fputc called by printf
                 For subsequent calls to printf,
                 you can use the PC terminal output from USART1 directly
******************************************************************************/
int fputc(int ch, FILE *fp)
{
    if (fp == stdout)
    {
        /*If you want to output a line feed, you can automatically add a carriage
        return to prevent the horizontal position of some terminal terminals
        from changing after line feed.*/
        if (ch == '\n')
        {
            while ((USART1->SR & USART_SR_TXE) == 0);
            USART1->DR = '\r';
        }
        /* Output characters to USART1 */
        while ((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = ch;
    }
    return ch;
}

/******************************************************************************
 * func name   : uart1_send
 * para        : buf(IN)  --> Buffer to send
                 len(IN)  --> The buffer length to be sent
 * return      : NULL
 * description : The send function of USART1
******************************************************************************/
void uart1_send(uint8_t *buf,uint8_t len)
{
    uint8_t index;
    for(index = 0; index < len ; index++)
    {
        /* wait transport complete */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1,buf[index]);
    }
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}


/******************************************************************************
 * func name   : hw_uart_debug_init
 * para        : baud_rate(IN)  --> Baud rate of uart1
 * return      : hw_uart_debug_init result
 * description : Initialization of USART1.PA9->TX PA10->RX
******************************************************************************/
uint8_t hw_uart_debug_init(uint32_t baud_rate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable RCC clock for USART1,GPIOA,DMA1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);

    /* Initialization GPIOA9 GPIOA10 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Data format :1:8:1, no parity check, no hardware flow control */
    USART_InitStructure.USART_BaudRate = baud_rate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    /* Enable USART interrupts, mainly for idle interrupts */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=DEBUG_PREE_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = DEBUG_SUB_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Initializes USART1 to enable USART, USART idle interrupts and USART RX DMA */
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1,  USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART1, ENABLE);


    return HW_ERR_OK;

}



/******************************************************************************
 * func name   : USART1_IRQHandler
 * para        : NULL
 * return      : NULL
 * description : Interrupt handler for usart1
******************************************************************************/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
    {
    	USART_ReceiveData(USART1);
        if(uart1_rev_len != 0)
        {
            /* Call the parse function */
            uart1_rev_buffer[uart1_rev_len] = 0;
            uart_receive_parse(uart1_rev_buffer);
            uart1_rev_len = 0;
        }

        USART_ClearITPendingBit(USART1,USART_IT_IDLE);
    }

    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        uart1_rev_buffer[uart1_rev_len++] = USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}


