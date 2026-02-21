#include "stm32f10x.h"
#include "PWM.h"
#include "LightSensor.h"
#include "Delay.h"

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED_on(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED_off(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED_turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    }
}

void LED_PWM_Init(void)
{
    PWM_Init();    
}

void LED_Auto(void)
{
    static uint32_t last_update = 0;
    if (GetTick()-last_update<200)
    {return;}
    uint8_t Mode=LightSensor_GetLevel();
    switch (Mode)
    {
    case 1:
        PWM_SetCompare3((uint16_t)100);
        Delay_ms(20);
        break;
    case 2:
        PWM_SetCompare3((uint16_t)75);
        Delay_ms(50);
        break;
    case 3:
        PWM_SetCompare3((uint16_t)50);
        Delay_ms(20);
        break;
    case 4:
        PWM_SetCompare3((uint16_t)25);
        Delay_ms(20);
        break;
    case 5:
        PWM_SetCompare3((uint16_t)0);
        Delay_ms(20);
        break;
    default:
        break;
    }
    last_update=GetTick();
}
