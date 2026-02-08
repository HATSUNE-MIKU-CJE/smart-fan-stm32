#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Menu.h"
#include "AD.h"
#include "Motor.h"
#include "Rotary.h"
#include "Key.h"

extern MenuState_t g_menu_state;

int main()
{
    uint8_t auto_mode=0;
    int8_t speed=0;
    RotaryEvent rotary_event;
    KeyEvent key_event;

    Systick_Init();
    LED_PWM_Init();
    OLED_Init();
    AD_Init();
    TemperatureSensor_Init();
    Menu_Init();
    Key_Init();
    Rotary_Init();
    Motor_Init();

    Motor_SetSpeed(speed);

    while (1)
    {
        LED_Auto();
        Menu_Process();
        
        Rotary_Scan();
        Key_Scan();

        rotary_event=Rotary_GetEvent();
        key_event=Key_GetEvent();

        if (key_event != KEY_EVENT_NONE) {
            switch (g_menu_state) {
                case MENU_STATE_MAIN:
                    if (key_event == KEY_EVENT_CONFIRM) {
                        Menu_Select();  // 确认键：进入选中的菜单项
                        Delay_ms(50);
                    } else if (key_event == KEY_EVENT_BACK) {
                        // 返回键在主菜单无操作，或可定义特殊功能
                        // 如长按返回键关机等
                    }
                    break;
                    
                case MENU_STATE_MANUAL:
                    if (key_event == KEY_EVENT_CONFIRM) {
                        // 确认键：切换启停状态
                        if (speed == 0) {
                            speed = -20;  // 启动到1档
                        } else {
                            speed = 0;    // 停止
                        }
                        Motor_SetSpeed(speed);
                        Delay_ms(50);
                    } else if (key_event == KEY_EVENT_BACK) {
                        // 返回键：返回主菜单
                        Menu_ExitCurrent();
                        Delay_ms(50);
                    }
                    break;
                    
                case MENU_STATE_AUTO:
                    if (key_event == KEY_EVENT_CONFIRM) {
                        // 确认键：切换自动模式开关
                        auto_mode = !auto_mode;
                        OLED_ShowString(4, 9, auto_mode ? "ON " : "OFF");
                        if (!auto_mode) {
                            speed = 0;
                            Motor_SetSpeed(speed);
                        }
                        Delay_ms(50);
                    } else if (key_event == KEY_EVENT_BACK) {
                        // 返回键：返回主菜单
                        Menu_ExitCurrent();
                        auto_mode = 0;
                        speed = 0;
                        Motor_SetSpeed(speed);
                        Delay_ms(50);
                    }
                    break;
                    
                default:  // 其他页面（Settings, About）
                    if (key_event == KEY_EVENT_BACK) {
                        // 返回键：返回主菜单
                        Menu_ExitCurrent();
                        Delay_ms(50);
                    }
                    break;
            }
        }
        
        /* ========== 处理旋钮事件 ========== */
        if (rotary_event != ROTARY_EVENT_NONE) {
            switch (g_menu_state) { 
                case MENU_STATE_MAIN:
                    // 主菜单：旋转选择菜单项
                    if (rotary_event == ROTARY_EVENT_DOWN) {
                        Menu_Up();
                    } else if (rotary_event == ROTARY_EVENT_UP) {
                        Menu_Down();
                    }
                    break;
                    
                case MENU_STATE_MANUAL:
                    // 手动模式：旋转调整风速
                    if (rotary_event == ROTARY_EVENT_UP) {
                        speed = (speed > -100) ? speed - 20 : -100;
                        Motor_SetSpeed(speed);
                    } else if (rotary_event == ROTARY_EVENT_DOWN) {
                        speed = (speed < 0) ? speed + 20 : 0;
                        Motor_SetSpeed(speed);
                    }
                    break;
                    
                case MENU_STATE_AUTO:
                    // 自动模式：旋转可以调整温度阈值（如果实现）
                    // 暂时不处理旋转，或可以预留功能
                    break;
                    
                default:
                    // 其他页面不处理旋转
                    break;
            }
        }
        
        // 自动模式处理
        if (auto_mode && g_menu_state == MENU_STATE_AUTO) {
            static uint32_t last_auto_call = 0;
            if (GetTick() - last_auto_call >= 200) {
                Motor_Auto(&speed);
                last_auto_call = GetTick();
            }
        }
        
        Delay_ms(5);  // 主循环延时
    }
}
