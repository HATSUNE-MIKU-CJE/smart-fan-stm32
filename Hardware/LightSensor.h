#ifndef __LIGHTSENSOR_H
#define __LIGHTSENSOR_H

void LightSensor_Init(void);
uint8_t LightSensor_GetLevel(void);
const char* LightSensor_GetLightDescription(void);

#endif
