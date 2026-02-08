#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"

#define CONFIRM_KEY_PIN GPIO_Pin_8
#define BACK_KEY_PIN GPIO_Pin_10
#define CONFIRM_KEY_PORT GPIOA
#define BACK_KEY_PORT GPIOA

#define KEY_DEBOUNCE_TIME 20

typedef enum{
    KEY_IDLE,
    KEY_PRESS_DEBOUNCE,
    KEY_PRESSED,
    KEY_RELEASE_DEBOUNCE
}KeyState;

static KeyState confirm_state=KEY_IDLE;
static uint8_t last_confirm_state=1;
static uint32_t confirm_debounce_time=0;


static KeyState back_state=KEY_IDLE;
static uint8_t last_back_state=1;
static uint32_t back_debounce_time=0;


static KeyEvent pending_event=KEY_EVENT_NONE;

void Key_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = CONFIRM_KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CONFIRM_KEY_PORT, &GPIO_InitStructure);
    
    // 配置返回键为上拉输入
    GPIO_InitStructure.GPIO_Pin = BACK_KEY_PIN;
    GPIO_Init(BACK_KEY_PORT, &GPIO_InitStructure);
    
    // 读取初始状态
    last_confirm_state = GPIO_ReadInputDataBit(CONFIRM_KEY_PORT, CONFIRM_KEY_PIN);
    last_back_state = GPIO_ReadInputDataBit(BACK_KEY_PORT, BACK_KEY_PIN);
}

static uint8_t DetectSingleKEY(GPIO_TypeDef* port, uint16_t pin, 
                                   uint8_t* last_state, KeyState* state, 
                                   uint32_t* debounce_time) {
    uint8_t current_state = GPIO_ReadInputDataBit(port, pin);
    uint32_t current_time = GetTick();
    
    switch (*state) {
        case KEY_IDLE:
            // 检测按下（下降沿）
            if (current_state == 0 && *last_state == 1) {
                *state = KEY_PRESS_DEBOUNCE;
                *debounce_time = current_time;
            }
            break;
            
        case KEY_PRESS_DEBOUNCE:
            // 消抖等待
            if (current_time - *debounce_time >= KEY_DEBOUNCE_TIME) {
                current_state = GPIO_ReadInputDataBit(port, pin);
                if (current_state == 0) {
                    // 确认按下
                    *state = KEY_PRESSED;
                    return 1; // 按键按下
                } else {
                    // 是抖动
                    *state = KEY_IDLE;
                }
            }
            break;
            
        case KEY_PRESSED:
            // 检测释放（上升沿）
            if (current_state == 1 && *last_state == 0) {
                *state = KEY_RELEASE_DEBOUNCE;
                *debounce_time = current_time;
            }
            break;
            
        case KEY_RELEASE_DEBOUNCE:
            // 释放消抖
            if (current_time - *debounce_time >= KEY_DEBOUNCE_TIME) {
                *state = KEY_IDLE;
            }
            break;
    }
    
    *last_state = current_state;
    return 0;
}

// 扫描所有按键
void Key_Scan(void) {
    uint32_t current_time = GetTick();
    
    // 检测确认键
    if (DetectSingleKEY(CONFIRM_KEY_PORT, CONFIRM_KEY_PIN, 
                          &last_confirm_state, &confirm_state, 
                          &confirm_debounce_time)) {
        pending_event = KEY_EVENT_CONFIRM;
    }
    
    // 检测返回键
    if (DetectSingleKEY(BACK_KEY_PORT, BACK_KEY_PIN, 
                          &last_back_state, &back_state, 
                          &back_debounce_time)) {
        pending_event = KEY_EVENT_BACK;
    }
    
    // 如果两个键同时按下，可以定义特殊功能（可选）
    if (confirm_state == KEY_PRESSED && back_state == KEY_PRESSED) {
        static uint32_t both_press_time = 0;
        if (both_press_time == 0) {
            both_press_time = current_time;
        } else if (current_time - both_press_time > 2000) {
            // 双键长按2秒，可以定义特殊功能（如恢复出厂设置）
            pending_event = KEY_EVENT_RESET;
            both_press_time = 0;
        }
    } else {
        // 重置双键计时
        // 可以在static变量定义时初始化为0
    }
}

// 获取按键事件
KeyEvent Key_GetEvent(void) {
    KeyEvent event = pending_event;
    pending_event = KEY_EVENT_NONE;
    return event;
}
