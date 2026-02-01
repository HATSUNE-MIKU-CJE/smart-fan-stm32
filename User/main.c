#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Key.h"
#include "Menu.h"
#include "AD.h"

int main()
{
    uint8_t keyNum=0;
    LED_Init();
    OLED_Init();
    AD_Init();
    TemperatureSensor_Init();
    Menu_Init();
    Key_Init();
    while (1)
    {
        keyNum=Key_GetNum();
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
        Delay_ms(10);
    }
}
