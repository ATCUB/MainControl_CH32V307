/*_LED_DRIVE_*/
#ifndef _LED_DRIVE_
#define _LED_DRIVE_

#include "debug.h"
#include "gpio.h"

#define LED_1_OFF  GPIO_SetBits(SYS_LED1_GPIO_Port, SYS_LED1_Pin)
#define LED_1_ON   GPIO_ResetBits(SYS_LED1_GPIO_Port, SYS_LED1_Pin)

#define LED_2_OFF  GPIO_SetBits(SYS_LED2_GPIO_Port, SYS_LED2_Pin)
#define LED_2_ON   GPIO_ResetBits(SYS_LED2_GPIO_Port, SYS_LED2_Pin)


//系统管理 结构体声明
typedef enum
{
    Startup_Check    = 0x00,      //开机自检
    Debug_Action     = 0x01,    //Debug调试
    StopRun_Action   = 0x02,    //停止运行
    NormalRun_Action = 0x03,    //正常运行
    ErrWarning_Action= 0x04,    //报错警告
}SystemAction;


void LedDriver_Loop(void const * argument);













#endif /*_LED_DRIVE_*/

