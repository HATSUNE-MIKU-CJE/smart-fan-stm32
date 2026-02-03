#include "stm32f10x.h"
#include "PWM.h"
#include "TemperatureSensor.h"
#include "OLED.h"
#include "Delay.h"

static uint8_t first_auto_run=1;
void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    PWM_Init_Motor();
    first_auto_run=1;

}

void Motor_SetSpeed(int8_t Speed)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
    GPIO_SetBits(GPIOA,GPIO_Pin_5);
    PWM_SetCompare1(-Speed);

}

void Motor_SpeedUp(int8_t *Speed)
{
    if (*Speed==-100)
    {
        *Speed=0;
    }
    else
    {
        *Speed-=20;
    }
    Motor_SetSpeed(*Speed);
}

void Motor_SpeedDown(int8_t *Speed)
{
    if (*Speed==0)
    {
        *Speed=0;
    }
    else
    {
        *Speed+=20;
    }
    Motor_SetSpeed(*Speed);
}

void Motor_Auto(int8_t *Speed)
{
    static uint32_t last_update = 0;
    uint32_t current_tick=GetTick();
    if (first_auto_run)
    {
        first_auto_run=0;
        last_update=current_tick-200;
    }
    if (current_tick-last_update<200)
    {return;}
    int8_t temp_level=TEMSensor_GetLevel();  
    int8_t target_speed=(temp_level-1)*(-20);
    if (target_speed<-100) {target_speed=-100;}
    if (target_speed>0) {target_speed=0;}

    *Speed=target_speed;
    Motor_SetSpeed(*Speed);

    last_update=GetTick();
}

uint16_t Motor_GetSpeed()
{
    return TIM_GetCapture1(TIM3);
}

