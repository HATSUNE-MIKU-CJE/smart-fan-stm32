#include "stm32f10x.h"
#include "Delay.h"
#include "Rotary.h"

#define ROTARY_CLK_PIN GPIO_Pin_3 //A
#define ROTARY_CLK_PORT GPIOA
#define ROTARY_DT_PIN GPIO_Pin_1 //B
#define ROTARY_DT_PORT GPIOA

#define DEBOUNCE_TIME 10

static uint8_t last_clk_state=1;
static RotaryEvent pending_event=ROTARY_EVENT_NONE;
static int16_t rotary_counter=0;

void  Rotary_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin=ROTARY_CLK_PIN|ROTARY_DT_PIN;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(ROTARY_CLK_PORT,&GPIO_InitStructure);

    last_clk_state=GPIO_ReadInputDataBit(ROTARY_CLK_PORT,ROTARY_CLK_PIN);

}

static void DetectRotation(void) {
    uint8_t clk_state = GPIO_ReadInputDataBit(ROTARY_CLK_PORT, ROTARY_CLK_PIN);
    uint8_t dt_state = GPIO_ReadInputDataBit(ROTARY_DT_PORT, ROTARY_DT_PIN);
    uint32_t current_time = GetTick();
    static uint32_t last_rotation_time=0; 

    if (current_time-last_rotation_time<DEBOUNCE_TIME){
        last_clk_state=clk_state;
        return;
    }

    // 检测CLK下降沿（从1变0）
    if (clk_state == 0 && last_clk_state == 1) {
        // 根据DT状态判断方向
        last_rotation_time=current_time;
        if (dt_state == 1) {
            // 顺时针旋转
            rotary_counter++;
            pending_event = ROTARY_EVENT_UP;
        } else {
            // 逆时针旋转
            rotary_counter--;
            pending_event = ROTARY_EVENT_DOWN;
        }
        last_rotation_time=current_time;
    }
    
    last_clk_state = clk_state;
}

void Rotary_Scan(void) {
    // 分别检测旋转和按键
    DetectRotation();  // 旋转检测（你原来的逻辑）
}

//获取旋钮事件函数，返回待处理事件，并清空事件队列
RotaryEvent Rotary_GetEvent(void)
{
    RotaryEvent event=pending_event;
    pending_event=ROTARY_EVENT_NONE;
    return event;
}

//获取旋钮计数值函数，返回旋钮计数器值，并且可以重置
int16_t Rotary_GetValue(void)
{
    if (rotary_counter<-100) rotary_counter=-100;
    if (rotary_counter>100) rotary_counter=100;

    int16_t value=rotary_counter;
    rotary_counter=0;
    return value;
}
