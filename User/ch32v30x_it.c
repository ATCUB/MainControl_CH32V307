/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v30x_it.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32v30x_it.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));//定义中断，CH32V307不像stm32，直接使用即可，在CH32V307中需自己定义。

uint8_t U1_RxBuffer[64]={0};//接收缓存
uint8_t U1_RxCounter=0;//
uint8_t recv_end_flag = 0;

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void USART1_IRQHandler(void)
{
    uint8_t clear=clear;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        U1_RxBuffer[U1_RxCounter++]=USART_ReceiveData(USART1);
    }else if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)
    {
        clear=USART_ReceiveData(USART1);
//---------------------------------------------------------------------------------------------------------------------------------
//用户处理
       // printf("get data=%d:%s\r\n",U1_RxCounter,U1_RxBuffer);
        recv_end_flag = 1;
//---------------------------------------------------------------------------------------------------------------------------------
        U1_RxCounter=0;
    }
}
