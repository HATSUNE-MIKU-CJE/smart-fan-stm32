#include "stm32f10x.h"
#include "AD.h"

uint16_t ADValue_T;

#define TEM_LEVEL_1_MAX 1900  // 档位1的最大值
#define TEM_LEVEL_2_MAX 1700  // 档位2的最大值
#define TEM_LEVEL_3_MAX 1500  // 档位3的最大值
#define TEM_LEVEL_4_MAX 1300  // 档位4的最大值
#define TEM_LEVEL_5_MAX 1000  // 档位5的最大值

void TemperatureSensor_Init(void)
{
    AD_Init();
}

int8_t TEMSensor_GetLevel(void)
{
    ADValue_T=AD_GetValue(ADC_Channel_7);
    if (ADValue_T>=TEM_LEVEL_1_MAX) {return 1;}
    else if (ADValue_T<TEM_LEVEL_1_MAX && ADValue_T >=TEM_LEVEL_2_MAX ) 
    {return 2;}
    else if (ADValue_T<TEM_LEVEL_2_MAX && ADValue_T >=TEM_LEVEL_3_MAX )
    {return 3;}
    else if (ADValue_T<TEM_LEVEL_3_MAX && ADValue_T >=TEM_LEVEL_4_MAX )
    {return 4;}
    else if (ADValue_T<TEM_LEVEL_4_MAX && ADValue_T >=TEM_LEVEL_5_MAX )
    {return 5;}
    else {return 6;}
}

