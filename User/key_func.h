/***********************************************************************
 * @file key_func.h
 * Description:
 *
 **********************************************************************/
#ifndef _KEY_FUNC_H_
#define _KEY_FUNC_H_

#include "stdint.h"
#include "debug.h"
#include "gpio.h"

#define KEY_NUMBER_ALL  1   //按键数量

#define SET_KEY_PinRead  GPIO_ReadInputDataBit(KEY_1_GPIO_Port,KEY_1_Pin) //设置按键

//按键结构体声明
typedef enum
{
    NONE_KEY    = 0x00, //无按键
    SET_KEY     = 0x01, //设置按键
}KeyName;

typedef enum
{
    SHORT_TOUCH = 0x00, //短按
    LONG_TOUCH  = 0x01, //长按
}KeyActionName;

typedef struct
{
    unsigned int  CntTimer[KEY_NUMBER_ALL + 1]; //按键触发时间缓存
    unsigned char Action;                       //按键动作
}KeyInit;


uint8_t Touch_GetKey(void);
void TouchDriver_Loop(void const * argument);


#endif // _KEY_FUNC_H_
