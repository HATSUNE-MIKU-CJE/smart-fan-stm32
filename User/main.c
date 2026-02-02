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
    Systick_Init();
    LED_PWM_Init();
    OLED_Init();
    AD_Init();
    TemperatureSensor_Init();
    Menu_Init();
    Key_Init();
    Motor_Init();
    Motor_SetSpeed(20);
    while (1)
    {
        LED_Auto();
        Menu_Process();
        keyNum=Key_GetNum();
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
            else
            {
                if (keyNum==3)
                {
                    Menu_ExitCurrent();
                    Delay_ms(50);
                }
            }
        }
        Delay_ms(10);
    }
}
