#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Key.h"

int main()
{
    LED_Init();
    OLED_Init();
    LightSensor_Init();
    TemperatureSensor_Init();
    OLED_ShowString(1,1,"Welcome to");
    OLED_ShowString(2,1,"smart-fan-stm32!");
    Delay_s(5);
    OLED_Clear();
    OLED_ShowString(1,1,"time:");
    OLED_ShowString(2,1,"temperature:");
    OLED_ShowString(3,1,"brightness:");
    while (1)
    {
        if (LightSensor_Get()==1)
        {
            OLED_ShowString(3,12,"dark ");
            LED_on();
        }
        else
        {
            OLED_ShowString(3,12,"light");
            LED_off();
        }
        if (TemperatureSensor_Get()==1)
        {
            OLED_ShowString(2,13,"cold");
        }
        else
        {
            OLED_ShowString(2,13,"hot ");
        }
    }
}
