#include "can.h"

/*********************************************************************
 * @fn      CAN_Mode_Init
 *
 * @brief   Initializes CAN communication test mode.
 *          Bps =Fpclk1/((tpb1+1+tbs2+1+1)*brp)
 *
 * @param   tsjw - CAN synchronisation jump width.
 *          tbs2 - CAN time quantum in bit segment 1.
 *          tbs1 - CAN time quantum in bit segment 2.
 *          brp - Specifies the length of a time quantum.
 *          mode - Test mode.
 *            CAN_Mode_Normal.
 *            CAN_Mode_LoopBack.
 *            CAN_Mode_Silent.
 *            CAN_Mode_Silent_LoopBack.
 *
 * @return  none
 */
void CAN_Test_Mode_Init( u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode )
{
    GPIO_InitTypeDef GPIO_InitSturcture={0};
    CAN_InitTypeDef CAN_InitSturcture={0};
    CAN_FilterInitTypeDef CAN_FilterInitSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE );

    GPIO_PinRemapConfig( GPIO_Remap1_CAN1, ENABLE);

    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitSturcture);

    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( GPIOB, &GPIO_InitSturcture);

    CAN_InitSturcture.CAN_TTCM = DISABLE;
    CAN_InitSturcture.CAN_ABOM = DISABLE;
    CAN_InitSturcture.CAN_AWUM = DISABLE;
    CAN_InitSturcture.CAN_NART = ENABLE;
    CAN_InitSturcture.CAN_RFLM = DISABLE;
    CAN_InitSturcture.CAN_TXFP = DISABLE;
    CAN_InitSturcture.CAN_Mode = mode;
    CAN_InitSturcture.CAN_SJW = tsjw;
    CAN_InitSturcture.CAN_BS1 = tbs1;
    CAN_InitSturcture.CAN_BS2 = tbs2;
    CAN_InitSturcture.CAN_Prescaler = brp;
    CAN_Init( CAN1, &CAN_InitSturcture );

    CAN_FilterInitSturcture.CAN_FilterNumber = 0;
    CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitSturcture.CAN_FilterIdHigh = 0;
    CAN_FilterInitSturcture.CAN_FilterIdLow = 0;
    CAN_FilterInitSturcture.CAN_FilterMaskIdHigh =0;
    CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x0006;
    CAN_FilterInitSturcture.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;
    CAN_FilterInitSturcture.CAN_FilterActivation = ENABLE;
    CAN_FilterInit( &CAN_FilterInitSturcture );

}

/*********************************************************************
 * @fn      CAN_Send_Msg
 *
 * @brief   CAN Transmit function.
 *
 * @param   msg - Transmit data buffer.
 *          len - Data length.
 *
 * @return  0 - Send successful.
 *          1 - Send failed.
 */
u8 CAN_Send_Msg( int32_t msg, u8 speed )
{
    u8 mbox;
    u16 i = 0;

    CanTxMsg CanTxStructure;

    CanTxStructure.StdId = 0x200;
    CanTxStructure.IDE = CAN_Id_Standard;
    CanTxStructure.RTR = CAN_RTR_Data;
    CanTxStructure.DLC = 0x08;

    CanTxStructure.Data[0] = (msg & (0xF));
    CanTxStructure.Data[1] = ((msg & (0xF0)) >> 4);
    CanTxStructure.Data[2] = ((msg & (0xF00)) >> 8);
    CanTxStructure.Data[3] = ((msg & (0xF000)) >> 12);
    CanTxStructure.Data[4] = ((msg & (0xF0000)) >> 16);
    CanTxStructure.Data[5] = ((msg & (0xF00000)) >> 20);
    CanTxStructure.Data[6] = speed;
    CanTxStructure.Data[7] = 0;

    mbox = CAN_Transmit(CAN1, &CanTxStructure);

    i = 0;

    while( ( CAN_TransmitStatus( CAN1, mbox ) != CAN_TxStatus_Ok ) && (i < 0xFFF) )
    {
        i++;
    }

    if( i == 0xFFF )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*********************************************************************
 * @fn      CAN_Receive_Msg
 *
 * @brief   CAN Receive function.
 *
 * @param   buf - Receive data buffer.
 *          len - Data length.
 *
 * @return  CanRxStructure.DLC - Receive data length.
 */
u8 CAN_Receive_Msg( u8 *buf )
{
    u8 i;

    CanRxMsg CanRxStructure;

    if( CAN_MessagePending( CAN1, CAN_FIFO1 ) == 0)
    {
        return 0;
    }

    CAN_Receive( CAN1, CAN_FIFO1, &CanRxStructure );

    for( i=0; i<8; i++ )
    {
        buf[i] = CanRxStructure.Data[i];
    }

    return CanRxStructure.DLC;
}

