#include "stm32f10x.h"
#include "Delay.h"

static uint8_t lastKey1State=1;
static uint8_t lastKey2State=1;
static uint8_t lastKey3State=1;
static uint8_t lastKey4State=1;

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    lastKey1State = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
    lastKey2State = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
    lastKey3State = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
    lastKey4State = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum=0;
    uint8_t currentKey1State,currentKey2State,currentKey3State,currentKey4State;

    currentKey1State=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
    currentKey2State=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);
    currentKey3State=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
    currentKey4State=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);

    if (lastKey1State==1 && currentKey1State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)
        {
            KeyNum=1;
        }
        
    }
    if (lastKey2State==1 && currentKey2State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0)
        {
            KeyNum=2;
        }
    }
    if (lastKey3State==1 && currentKey3State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
        {
            KeyNum=3;
        }
    }
    if (lastKey4State==1 && currentKey4State==0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
        {
            KeyNum=4;
        }
    }
    lastKey1State=currentKey1State;
    lastKey2State=currentKey2State;
    lastKey3State=currentKey3State;
    lastKey4State=currentKey4State;
    return KeyNum;
}
