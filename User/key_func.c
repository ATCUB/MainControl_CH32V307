#include "key_func.h"
#include "FreeRTOS.h"
#include "task.h"

KeyInit Key = {0};
void Key_Function(void);
/*************************************************************
** Function name:       Touch_GetKey
** Descriptions:        获取按键状态
** Input parameters:    None
** Output parameters:   None
** Returned value:      按键状态
** Remarks:             None
*************************************************************/
uint8_t Touch_GetKey(void)
{
	uint8_t touchKeyAction = NONE_KEY;
	touchKeyAction = Key.Action;
	Key.Action = NONE_KEY;
	return touchKeyAction;
}
/*************************************************************
** Function name:       TouchDriver_Loop
** Descriptions:        按键底层刷新函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void TouchDriver_Loop(void const * argument)
{
	while(1)
	{
		//设置按键
		if(SET_KEY_PinRead == 0)
		{
			if(Key.CntTimer[SET_KEY] < 300)Key.CntTimer[SET_KEY] ++;
			else if(Key.CntTimer[SET_KEY] == 300)
			{
				Key.CntTimer[SET_KEY] ++;
				Key.Action = (SET_KEY << 4) | LONG_TOUCH;
			}
		}
		else
		{
			if(Key.CntTimer[SET_KEY] > 3)Key.Action = (SET_KEY << 4) | SHORT_TOUCH;
			Key.CntTimer[SET_KEY] = 0;
		}
		Key_Function();
		vTaskDelay(5);
	}
}


/*************************************************************
** Function name:      Key_Function
** Descriptions:       按键函数
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void Key_Function(void)
{
    uint8_t KeyAction;
    KeyAction = Touch_GetKey();

    if(KeyAction == ((SET_KEY << 4) | SHORT_TOUCH))//SET_KEY
    {
        printf("SET_KEY IS PUSHED!\r\n");
    }

    else if(KeyAction == ((SET_KEY << 4) | LONG_TOUCH))//SET_KEY
    {
        printf("SET_KEY IS LONG PUSHED!\r\n");
    }
}


