#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Key.h"
#include "Menu.h"
#include "AD.h"
#include "Motor.h"

extern MenuState_t g_menu_state;

int main()
{
    uint8_t keyNum=0;
    uint8_t Motor_Auto_On=0;
    int8_t speed=0;

    Systick_Init();
    LED_PWM_Init();
    OLED_Init();
    AD_Init();
    TemperatureSensor_Init();
    Menu_Init();
    Key_Init();
    Motor_Init();
    Motor_SetSpeed(speed);

    while (1)
    {
        LED_Auto();
        Menu_Process();
        keyNum=Key_GetNum();

        if (Motor_Auto_On==1)
        {
            if (g_menu_state==MENU_STATE_AUTO)
            {
                OLED_ShowString(4,9,"ON ");
            }
            static uint32_t last_auto_call=0;
            if (GetTick()-last_auto_call>=200)
            {
                Motor_Auto(&speed);
                last_auto_call=GetTick();
            }
            
        }
        if (keyNum!=0)
        {
            if (g_menu_state==MENU_STATE_MAIN)
            {
                if (keyNum==2)
                {
                    Menu_Down();
                    Delay_ms(50);
                }
                if (keyNum==1)
                {
                    Menu_Up();
                    Delay_ms(50);
                }
                if (keyNum==3)
                {
                    Menu_Select();
                    Delay_ms(50);
                }
            }
            else if (g_menu_state==MENU_STATE_MANUAL)
            {
                if (keyNum==1)
                {
                    Motor_SpeedUp(&speed);
                    OLED_ShowNum(3,12,(-speed)/20,1);
                    Delay_ms(50);
                }
                if (keyNum==2)
                {
                    Motor_SpeedDown(&speed);
                    OLED_ShowNum(3,12,(-speed)/20,1);
                    Delay_ms(50);
                }
                if (keyNum==3)
                {
                    speed=0;
                    Motor_SetSpeed(speed);
                    Delay_ms(50);
                }
                if (keyNum==4)
                {
                    Menu_ExitCurrent();
                    Delay_ms(50);
                }
            }
            else if (g_menu_state==MENU_STATE_AUTO)
            {
                if (keyNum==3)
                {
                    Motor_Auto_On=1;
                    OLED_ShowString(4,9,"ON ");
                    Delay_ms(50);
                }
                if (keyNum==4)
                {
                    Menu_ExitCurrent();
                    Delay_ms(50);
                }
                if (keyNum==1)
                {
                    OLED_ShowString(4,9,"OFF");
                    Motor_Auto_On=0;
                    speed=0;
                    Motor_SetSpeed(speed);
                    Delay_ms(50);
                }
            }
            else
            {
                if (keyNum==4)
                {
                    Menu_ExitCurrent();
                    Delay_ms(50);
                }
            }
        }
        Delay_ms(10);
    }
}
