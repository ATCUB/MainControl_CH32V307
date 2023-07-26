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

#define KEY_NUMBER_ALL  1   //��������

#define SET_KEY_PinRead  GPIO_ReadInputDataBit(KEY_1_GPIO_Port,KEY_1_Pin) //���ð���

//�����ṹ������
typedef enum
{
    NONE_KEY    = 0x00, //�ް���
    SET_KEY     = 0x01, //���ð���
}KeyName;

typedef enum
{
    SHORT_TOUCH = 0x00, //�̰�
    LONG_TOUCH  = 0x01, //����
}KeyActionName;

typedef struct
{
    unsigned int  CntTimer[KEY_NUMBER_ALL + 1]; //��������ʱ�仺��
    unsigned char Action;                       //��������
}KeyInit;


uint8_t Touch_GetKey(void);
void TouchDriver_Loop(void const * argument);


#endif // _KEY_FUNC_H_
