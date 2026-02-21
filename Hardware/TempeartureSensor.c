#include "stm32f10x.h"
#include "Delay.h"


#define DHT22_GPIO_PORT GPIOA
#define DHT22_GPIO_PIN  GPIO_Pin_7
#define DHT22_RCC       RCC_APB2Periph_GPIOA

static float last_temperature = 25.0f;   // 默认温度
static float last_humidity    = 50.0f;   // 默认湿度（暂未使用）
static uint32_t last_read_time = 0;      // 上次成功读取的时间戳


void DHT22_SetOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Pin=DHT22_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(DHT22_GPIO_PORT,&GPIO_InitStructure);
    GPIO_SetBits(DHT22_GPIO_PORT,DHT22_GPIO_PIN);
}

void DHT22_SetInput(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=DHT22_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(DHT22_GPIO_PORT,&GPIO_InitStructure);
    GPIO_SetBits(DHT22_GPIO_PORT,DHT22_GPIO_PIN);
}

uint8_t DHT22_ReadBit(void)
{
    uint32_t timeout=0;
    while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT,DHT22_GPIO_PIN)==Bit_RESET)
    {
        if (++timeout>6000) return 0;
    }
    Delay_us(40);
    if (GPIO_ReadInputDataBit(DHT22_GPIO_PORT,DHT22_GPIO_PIN)==Bit_SET)
    {
        while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT,DHT22_GPIO_PIN)==Bit_SET);
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t DHT22_ReadByte(void)
{
    uint8_t data=0;
    for (uint8_t i=0;i<8;i++)
    {
        data<<=1;
        if (DHT22_ReadBit())
        {
            data |=1; //如果读到1，那么将最低位变为1
        }
    }
    return data;
}

uint8_t DHT22_Read(float *temperatrue,float *humidity)
{
    uint8_t buffer[5]={0};

    //主机发起复位信号
    DHT22_SetOutput();
    GPIO_ResetBits(DHT22_GPIO_PORT,DHT22_GPIO_PIN);
    Delay_us(20000);
    GPIO_SetBits(DHT22_GPIO_PORT,DHT22_GPIO_PIN);
    Delay_us(30);
    DHT22_SetInput();

    //等待DHT22响应
    //等待数据线变低（DHT22拉低响应）
    uint32_t timeout = 0;
    while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_SET) {
        if (++timeout > 60000) return 0;
    }
    // 响应低电平持续 80μs，等待它结束
    timeout = 0;
    while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_RESET) {
        if (++timeout > 60000) return 0;
    }
    // 响应高电平持续 80μs，等待它结束（之后数据开始）
    timeout = 0;
    while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_SET) {
        if (++timeout > 60000) return 0;
    }

    //读取40位数据
    for (uint8_t i=0;i<5;i++)
    {
        buffer[i]=DHT22_ReadByte();
    }

    //校验和
    uint8_t checksum=buffer[0]+buffer[1]+buffer[2]+buffer[3];
    if (checksum != buffer[4]) return 0;

    //解析温度湿度
    int16_t temp_raw=(int16_t)( (buffer[2]<<8) | buffer[3] );
    *temperatrue=temp_raw / 10.0f;
    *humidity = ( (buffer[0]<<8) | buffer[1] ) / 10.0f;

    return 1;
}

void UpdateSensorData(void)
{
    uint32_t now = GetTick();
    if (now - last_read_time >= 1000)    // 达到1秒间隔
    {
        float temp, humi;
        if (DHT22_Read(&temp, &humi))   // 读取成功才更新
        {
            last_temperature = temp;
            last_humidity    = humi;
            last_read_time   = now;
        }
        // 读取失败则保持旧缓存，不更新时间戳，下次循环会再次尝试
    }
}

void TemperatureSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(DHT22_RCC,ENABLE);
    DHT22_SetOutput();
    UpdateSensorData();
}

int8_t TEMSensor_GetLevel(void)
{
    UpdateSensorData();

    float temp = last_temperature;
    // 根据温度映射档位（可自定义阈值）
    if (temp < 25.0f)          return  1;
    else if (temp < 28.0f)     return  2;
    else if (temp < 31.0f)     return  3;
    else if (temp < 34.0f)     return  4;
    else if (temp < 37.0f)     return  5;
    else                       return  6; 

}

float TEMSensor_GetTemperature(void)
{
    UpdateSensorData();
    return last_temperature;
}

