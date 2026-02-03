#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor_SetSpeed(int8_t Speed);
void Motor_SpeedUp(int8_t *Speed);
void Motor_SpeedDown(int8_t *Speed);
void Motor_Auto(int8_t *Speed);
int8_t Motor_GetSpeed(void);

#endif
