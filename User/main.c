/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 task1 and task2 alternate printing
*/

#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "gpio.h"
#include "can.h"
#include "leddrive.h"
#include "key_func.h"
/* Global define */
#define TASK1_TASK_PRIO     5
#define TASK1_STK_SIZE      256
#define TASK2_TASK_PRIO     5
#define TASK2_STK_SIZE      256

/* Global Variable */
TaskHandle_t Task1Task_Handler;
TaskHandle_t Task2Task_Handler;
TaskHandle_t LedTask_Handler;
TaskHandle_t KeyTask_Handler;
TaskHandle_t OrderTask_Handler;
TaskHandle_t RxTask_Handler;

extern uint8_t recv_end_flag;
extern uint8_t U1_RxBuffer[];
uint32_t commond_buffer[24] = {0x000004, 0x000005, 0x000006, 0x000007, 0x000040, 0x000050, 0x000060, 0x000070, 0x000400, 0x000500, 0x000600, 0x000700,
                                                         0x004000, 0x005000, 0x006000, 0x007000, 0x040000, 0x050000, 0x060000, 0x070000, 0x400000, 0x500000, 0x600000, 0x700000};
uint8_t order_buffer[100] = {0};
uint8_t finish_flag = 0;
uint8_t error_flag = 0;

void Order_dect(void const * argument);
void DMA_RX(void const * argument);

/*********************************************************************
 * @fn      task1_task
 *
 * @brief   task1 program.
 *
 * @param  *pvParameters - Parameters point of task1
 *
 * @return  none
 */
void task1_task(void *pvParameters)
{
    while(1)
    {
        printf("task1 entry\r\n");
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        vTaskDelay(250);
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        vTaskDelay(250);
    }
}

/*********************************************************************
 * @fn      task2_task
 *
 * @brief   task2 program.
 *
 * @param  *pvParameters - Parameters point of task2
 *
 * @return  none
 */
void task2_task(void *pvParameters)
{
    while(1)
    {
        printf("task2 entry\r\n");
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        vTaskDelay(500);
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
        vTaskDelay(500);
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	GPIO_Toggle_INIT();
	MY_USART_Init(115200);
	DMA_INIT();
	CAN_Test_Mode_Init( CAN_SJW_1tq, CAN_BS2_3tq, CAN_BS1_2tq, 6, CAN_Mode_Normal );
		
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
	printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);


	/* create two task */
//    xTaskCreate((TaskFunction_t )task2_task,
//                        (const char*    )"task2",
//                        (uint16_t       )TASK2_STK_SIZE,
//                        (void*          )NULL,
//                        (UBaseType_t    )TASK2_TASK_PRIO,
//                        (TaskHandle_t*  )&Task2Task_Handler);

    xTaskCreate((TaskFunction_t )LedDriver_Loop,
                    (const char*    )"led_task",
                    (uint16_t       )64,
                    (void*          )NULL,
                    (UBaseType_t    )5,
                    (TaskHandle_t*  )&LedTask_Handler);

    xTaskCreate((TaskFunction_t )TouchDriver_Loop,
                    (const char*    )"key_task",
                    (uint16_t       )64,
                    (void*          )NULL,
                    (UBaseType_t    )5,
                    (TaskHandle_t*  )&KeyTask_Handler);

    xTaskCreate((TaskFunction_t )Order_dect,
                    (const char*    )"order_task",
                    (uint16_t       )128,
                    (void*          )NULL,
                    (UBaseType_t    )5,
                    (TaskHandle_t*  )&OrderTask_Handler);

    xTaskCreate((TaskFunction_t )DMA_RX,
                    (const char*    )"Receive_task",
                    (uint16_t       )128,
                    (void*          )NULL,
                    (UBaseType_t    )5,
                    (TaskHandle_t*  )&RxTask_Handler);

    vTaskStartScheduler();


	while(1)
	{
	    printf("shouldn't run at here!!\n");
	}
}

void DMA_RX(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Receive loop */
    for(;;)
    {
        if(recv_end_flag ==1)
        {
            recv_end_flag=0;
            if(U1_RxBuffer[0] == 0x40)
            {
                for(uint8_t i=0; U1_RxBuffer[i] != 0x5A; i++)
                {
                    order_buffer[i] = U1_RxBuffer[i];
                }
                finish_flag = 0;
            }
        }
        vTaskDelay(500);
    }
  /* USER CODE END StartDefaultTask */
}

void Order_dect(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
    static uint32_t Motor_move = 0;
    static uint16_t order_index = 0;
  /* Toggle loop */
    for(;;)
    {
        if(order_buffer[0] == 0x40 && finish_flag == READY_RESTORE)                         //当指令集的起始位等于@，且完成标志符为0，进入还原进程
        {
            //初始化CAN数据包
            Motor_move = 0;
//            printf("receive restore order:'%s'\r\n", order_buffer);
            //运行中
            finish_flag = 2;
            //计算指令对于的索引index
            for(uint8_t i=1; order_buffer[i] != 0; i++)
            {
                //计算公式如'A'对应（0x41 - 0x41 = 0） ，依此类推，总共24个指令索引
                order_index = order_buffer[i]-0x41;
                //如果超出索引指令集最大值23，则进入error状态
                if( order_index > 23 ){
                    printf("order error\r\n");
                    error_flag = 1;
                    for(uint8_t a=0; a < 50; a++)
                    {
                        order_buffer[a] = 0;
                    }
                    break;
                 }
                //复位错误位
                error_flag = 0;
                //计算指令对于的CAN数据包
                Motor_move = commond_buffer[order_index];
                //发送CAN数据包
                CAN_Send_Msg(Motor_move, 10);
                //延时，等待电机完成旋转
                vTaskDelay(300);
            }
            //完成标志位
            finish_flag = 1;
            //清空指令数组
            for(uint8_t a=0; a < 50; a++)
            {
                order_buffer[a] = 0;
            }
        }

        else if(order_buffer[0] == 0x3F && finish_flag == READY_RESTORE)            //当指令集的起始位等于？，且完成标志符为0，进入随机打乱进程
        {
            //初始化CAN数据包
            Motor_move = 0;
            printf("receive random order:'%s'\r\n", order_buffer);
            //运行中
            finish_flag = 2;
            //计算指令对于的索引index
            for(uint8_t i=1; order_buffer[i] != '0'; i++)
            {
                //计算公式如'A'对应（0x41 - 0x41 = 0） ，依此类推，总共24个指令索引
                order_index = order_buffer[i]-0x41;
                //计算指令对于的CAN数据包
                Motor_move = commond_buffer[order_index];
                //发送CAN数据包
                CAN_Send_Msg(Motor_move, 5);
                vTaskDelay(600);
            }
            //完成标志位
            finish_flag = 1;
            //清空指令数组，以便下一次正常运行
            for(uint8_t a=0; a < 50; a++)
                order_buffer[a] = 0;
        }
        vTaskDelay(300);
    }
  /* USER CODE END StartDefaultTask */
}

