#include "stm32f10x.h"
#include "Delay.h"

static uint8_t lastKey1State=1;
static uint8_t lastKey2State=1;

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    lastKey1State = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
    lastKey2State = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum=0;
    uint8_t currentKey1State,currentKey2State;

    currentKey1State=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
    currentKey2State=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);

    if (lastKey1State==1 && currentKey1State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
        {
            KeyNum=1;
        }
        
    }
    if (lastKey2State==1 && currentKey2State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0)
        {
            KeyNum=2;
        }
    }
    lastKey1State=currentKey1State;
    lastKey2State=currentKey2State;
    return KeyNum;
}
