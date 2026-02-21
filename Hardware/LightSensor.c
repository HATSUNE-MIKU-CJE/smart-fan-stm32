#include "stm32f10x.h"
#include "AD.h"

#define LIGHT_LEVEL_1_MAX 824   // 档位1的最大值
#define LIGHT_LEVEL_2_MAX 1633  // 档位2的最大值
#define LIGHT_LEVEL_3_MAX 2441  // 档位3的最大值
#define LIGHT_LEVEL_4_MAX 3250  // 档位4的最大值


uint16_t ADValue;

void LightSensor_Init(void)
{
    AD_Init();
}

uint8_t LightSensor_GetLevel(void)
{
    ADValue=AD_GetValue(ADC_Channel_0);
    if (ADValue<=LIGHT_LEVEL_1_MAX) {return 1;}
    else if (ADValue>LIGHT_LEVEL_1_MAX && ADValue <=LIGHT_LEVEL_2_MAX ) 
    {return 2;}
    else if (ADValue>LIGHT_LEVEL_2_MAX && ADValue <=LIGHT_LEVEL_3_MAX )
    {return 3;}
    else if (ADValue>LIGHT_LEVEL_3_MAX && ADValue <=LIGHT_LEVEL_4_MAX )
    {return 4;}
    else {return 5;}
}

const char* LightSensor_GetLightDescription(void)
{
    uint8_t level=LightSensor_GetLevel();
    switch (level)
    {
        case 1: return "强光";
        case 2: return "明亮";
        case 3: return "柔和";
        case 4: return "微光";
        case 5: return "昏暗";
        default: return "未知";
    }
}

