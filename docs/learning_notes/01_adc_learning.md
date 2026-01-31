# STM32菜单系统开发笔记

## 📅 开发时间线
- **开始时间**：2026年1月31日 09:00
- **结束时间**：2026年1月31日 18:00
- **总耗时**：约8小时（含调试时间）

## 🎯 开发目标
1. 实现基于状态机的OLED菜单系统
2. 支持5个页面切换（待做）
3. 实现按键导航（上下选择）
4. 优化显示效果，支持滚动

## 🏗️ 系统架构设计

### 硬件连接
STM32引脚 外设模块 功能
PB8 (SCL) -> OLED SCL I2C时钟线
PB9 (SDA) -> OLED SDA I2C数据线
PB0 -> 按键1 向下选择
PB10 -> 按键2 向上选择
PA8 -> 光敏电阻 光照检测（待改造ADC）
PA9 -> DHT11 温湿度传感器（待改造ADC）
PA0 -> LED 状态指示

text

### 软件架构图
```mermaid
graph TD
    A[main.c] --> B[Menu模块]
    A --> C[Key模块]
    A --> D[OLED模块]
    A --> E[Sensor模块]
    
    B --> F[Menu_Init初始化]
    B --> G[Menu_Draw绘制]
    B --> H[Menu_Up/Down导航]
    
    C --> I[Key_Init]
    C --> J[Key_GetNum]
    
    D --> K[OLED_ShowString]
    D --> L[OLED_ShowChar] 


💻 核心代码实现
1. 菜单数据结构设计
c
// menu.h
typedef struct Menu {
    const char* title;      // 菜单标题
    const char** items;     // 菜单项数组
    MenuAction* actions;    // 回调函数数组
    uint8_t itemCount;      // 菜单项数量
    struct Menu* parent;    // 父菜单指针
} Menu;
2. 状态机设计原理
text
状态机流程：
空闲状态 → 检测按键 → 消抖确认 → 执行动作 → 更新显示
3. 按键消抖实现（最终方案）
c
// key.c - 非阻塞式消抖
    uint8_t Key_GetNum(void)
    {
        static uint8_t lastKey1State = 1;  // 记录上次状态
        static uint8_t lastKey2State = 1;
        uint8_t KeyNum = 0;
            
        // 读取当前状态
        uint8_t currentKey1State = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
        uint8_t currentKey2State = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
            
        // 检测下降沿（按下）
        if (lastKey1State == 1 && currentKey1State == 0) {
            Delay_ms(20);  // 消抖
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) {
                KeyNum = 1;  // 按键1按下
            }
        }
            
        // 类似处理按键2...
            
        // 更新状态
        lastKey1State = currentKey1State;
        lastKey2State = currentKey2State;
            
        return KeyNum;
    }
🎨 显示效果优化
1. 滚动算法
c    
// 滚动逻辑
    if (selectedIndex < scrollOffset) {
        scrollOffset = selectedIndex;  // 选中项在显示窗口上方
    } else if (selectedIndex >= scrollOffset + maxVisibleItems) {
        scrollOffset = selectedIndex - maxVisibleItems + 1; // 选中项在下方
    }
2. 显示布局
text
行号 | 内容
-----|-------------------
1     | 标题（居中显示）
2     | > 菜单项1
3     |   菜单项2
4     |   菜单项3  v
3. 视觉反馈
选中项用 > 标识

可滚动时显示 ^（向上）和 v（向下）箭头

清空行避免残留字符：OLED_ShowString(line, 1, " ");

🔧 调试过程与问题解决
问题1：按键响应不稳定
现象：有时按键没反应，需要按好几次
原因：原按键驱动使用while循环等待释放，阻塞主循环
解决方案：

移除阻塞的while循环

改为边沿检测（比较本次和上次状态）

添加静态变量记录上一次状态

主循环添加10ms短延时，稳定扫描频率

问题2：OLED显示残留
现象：菜单切换时，旧内容有残留
原因：未清空整行，只覆盖了部分字符
解决方案：

c
// 修改前
OLED_ShowString(displayLine, 3, menuItem);

// 修改后
OLED_ShowString(displayLine, 1, "                ");  // 先清空整行
OLED_ShowString(displayLine, 3, menuItem);            // 再显示
问题3：const char* 类型不匹配
现象：编译错误 argument of type "const char *" is incompatible
原因：OLED函数参数为char*，但菜单字符串用const char*
解决方案：
修改OLED函数声明和定义：

c
// OLED.h
void OLED_ShowString(uint8_t Line, uint8_t Column, const char *String);
📊 测试结果
功能测试表
测试项目	预期结果	实际结果	状态
上电显示	显示欢迎界面3秒后进入主菜单	✅ 通过	正常
向下导航	按键1使选中项向下移动	✅ 通过	正常
向上导航	按键2使选中项向上移动	✅ 通过	正常
滚动显示	菜单项超过3个时正确滚动	✅ 通过	正常
边界循环	到达底部后按向下回到顶部	✅ 通过	正常
响应时间	按键后100ms内响应	✅ 通过	正常
性能指标
按键响应时间：<50ms

菜单刷新时间：<20ms

内存使用：RAM约2KB，Flash约15KB

CPU占用率：约5%（主循环有10ms延时）

💡 关键收获
技术收获
状态机设计：理解了嵌入式UI的状态机实现方式

非阻塞编程：学会了避免使用while循环阻塞主程序

模块化设计：Menu、Key、OLED模块分离，高内聚低耦合

消抖算法：掌握了边沿检测消抖的原理和实现

工程收获
调试技巧：通过LED、OLED显示、串口等多种方式调试

问题定位：学会分析现象→假设原因→验证解决的方法论

代码重构：从发现问题到重构代码的完整流程

文档记录：及时记录问题和解决方案的重要性

🚀 改进空间
短期改进
添加菜单确认（Enter）和返回（Back）功能

实现子菜单页面（状态页、设置页等）

优化显示效果，添加动画过渡

长期改进
使用FreeRTOS实现多任务菜单管理

添加触摸屏支持

实现菜单配置保存到EEPROM

🔗 相关文件
代码文件
User/main.c - 主程序入口

Hardware/menu.c - 菜单系统实现

Hardware/key.c - 按键驱动

Hardware/oled.c - OLED显示驱动

配置文件
Project.uvprojx - Keil工程文件

设计文件
系统架构图

📚 参考资料
STM32F103参考手册 - GPIO和I2C章节

SSD1306 OLED数据手册 - I2C通信协议

江科大STM32教程 - 按键和显示相关章节

Markdown语法指南 - 笔记编写规范

🏷️ 标签
#STM32 #嵌入式菜单 #状态机 #OLED显示 #按键消抖

创建时间：2026年1月31日
最后更新：2026年1月31日
作者：Che Jiaen
版本：v1.0