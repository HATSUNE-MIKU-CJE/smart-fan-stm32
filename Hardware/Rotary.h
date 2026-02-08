#ifndef __ROTARY_H
#define __ROTARY_H

#include "stm32f10x.h"

typedef enum{
    ROTARY_EVENT_NONE=0,
    ROTARY_EVENT_UP,
    ROTARY_EVENT_DOWN,
}RotaryEvent;

void Rotary_Init(void);
void Rotary_Scan(void);
RotaryEvent Rotary_GetEvent(void);
int16_t Rotary_GetValue(void);

#endif
