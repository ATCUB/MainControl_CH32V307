/*_LED_DRIVE_*/
#include "leddrive.h"
#include "FreeRTOS.h"
#include "task.h"

/*************************************************************
** Function name:       Led1Run_Loop
** Descriptions:        LED1闪烁控制
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Led1Run_Loop(uint16_t *TickTime, uint16_t x1,uint16_t x2,uint16_t x3,uint16_t ALL)
{
    if(*TickTime < ALL)
    {
        *TickTime += 1;   //时基递加
        if(*TickTime < x1)      LED_1_ON;
        else if(*TickTime < x1+x2) LED_1_OFF;
        else if(*TickTime < x1+x2+x3) LED_1_ON;
        else LED_1_OFF;
    }
    else *TickTime = 0;
}
/*************************************************************
** Function name:       Led2Run_Loop
** Descriptions:        LED2闪烁控制
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Led2Run_Loop(uint16_t *TickTime, uint16_t x1,uint16_t x2,uint16_t x3,uint16_t ALL)
{
    if(*TickTime < ALL)
    {
        *TickTime += 1;   //时基递加
        if(*TickTime < x1)      LED_2_ON;
        else if(*TickTime < x1+x2) LED_2_OFF;
        else if(*TickTime < x1+x2+x3) LED_2_ON;
        else LED_2_OFF;
    }
    else *TickTime = 0;
}

/*************************************************************
** Function name:       LedDriver_Loop
** Descriptions:        LED底层刷新函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             1ms刷新
*************************************************************/
void LedDriver_Loop(void const * argument)
{
    while (1)
    {
        static uint16_t RTickTimes = 0;
        static uint16_t BTickTimes = 0;
        static uint8_t LastSysState = 0;
        uint8_t SystemState;

        SystemState = NormalRun_Action;     //获取当前系统状态
        if(SystemState != LastSysState)   //时基清零
        {
            RTickTimes = 0;
            BTickTimes = 0;
            LED_2_OFF;
            LED_1_OFF;
        }
        switch(SystemState)
        {
            case Startup_Check:
                Led1Run_Loop(&RTickTimes,60,20,60,200);
                Led2Run_Loop(&BTickTimes,80,30,30,160);
                break;
            case Debug_Action:
                Led1Run_Loop(&RTickTimes,100,50,100,400);
                Led2Run_Loop(&BTickTimes,50,20,50,1000);
                break;
            case StopRun_Action:
                Led1Run_Loop(&RTickTimes,50,20,50,1000);
                break;
            case NormalRun_Action:
                Led2Run_Loop(&BTickTimes,80,40,80,1000);
                break;
            case ErrWarning_Action:
                Led1Run_Loop(&RTickTimes,100,50,100,400);
                break;
            default:break;
        }
        LastSysState = SystemState;
        vTaskDelay(1);
    }
}


