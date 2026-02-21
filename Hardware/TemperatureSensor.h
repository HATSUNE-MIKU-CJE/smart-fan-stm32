#ifndef __TEMPERATURESENSOR_H
#define __TEMPERATURESENSOR_H

void DHT22_SetOutput(void);
void DHT22_SetInput(void);
uint8_t DHT22_ReadBit(void);
uint8_t DHT22_ReadByte(void);
uint8_t DHT22_Read(float *temperatrue,float *humidity);
void TemperatureSensor_Init(void);
int8_t TEMSensor_GetLevel(void);
float TEMSensor_GetTemperature(void);
void UpdateSensorData(void);

#endif
