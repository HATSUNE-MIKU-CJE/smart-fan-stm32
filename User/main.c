#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Key.h"
#include "Menu.h"

int main()
{
    uint8_t keyNum=0;
    LED_Init();
    OLED_Init();
    LightSensor_Init();
    TemperatureSensor_Init();
    Menu_Init();
    Key_Init();
    while (1)
    {
        keyNum=Key_GetNum();
        if (keyNum==1)
        {
            Menu_Down();
            Delay_ms(50);
        }
        if (keyNum==2)
        {
            Menu_Up();
            Delay_ms(50);
        }
        if (LightSensor_Get()==1)
        {
            LED_on();
        }
        else
        {
            LED_off();
        }
        if (TemperatureSensor_Get()==1)
        {
        }
        else
        {
        }
        Delay_ms(10);
    }
}
