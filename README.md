# 📝 README.md 更新内容（v0.6.0版本）

```markdown
# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-Active_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.6.0-brightgreen)  
![Progress](https://img.shields.io/badge/Progress-90%25-green)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented

#### 🎮 **混合输入系统** (Hybrid Input System) - **v0.6.0 重大升级**
- **EC11旋转编码器** - 精准旋钮输入，支持顺时针/逆时针检测
  **EC11 Rotary Encoder** - Precise knob input with CW/CCW detection
- **独立按键系统** - 3按键分离设计（确认/返回/模式切换）
  **Independent Button System** - 3-button separate design (OK/Back/Mode)
- **输入状态机管理** - 完整的消抖算法和非阻塞状态机架构
  **Input State Machine Management** - Complete debouncing algorithm and non-blocking state machine architecture

#### 📊 **传感器系统** (Sensor System)
- **光照强度检测** - ADC精确读取光敏电阻值，5档位自动判断（黑夜/微光/阴天/明亮/强光）  
  **Light Intensity Detection** - ADC precision reading with 5-level auto-detection (Black/Dim/Mild/Bright/Glare)
- **温度检测系统** - 热敏电阻ADC读取，6档位判断（很冷/冷/凉/适宜/热/很热）  
  **Temperature Detection System** - Thermistor ADC reading with 6-level detection (Very Cold/Cold/Cool/Comfortable/Hot/Very Hot)
- **实时数据显示** - 光照档位、温度档位、AD值、电压值精确显示  
  **Real-time Data Display** - Light level, temperature level, AD value, voltage precision display

#### ⚡ **控制系统** (Control System)
- **PWM LED调光** - 基于TIM2_CH3实现LED亮度随光照自动变化  
  **PWM LED Dimming** - LED brightness auto-adjusts with light intensity via TIM2_CH3
- **智能风扇控制** - 完整的温度自适应控制系统  
  **Smart Fan Control** - Complete temperature-adaptive control system
  - **手动控制模式**：5档位PWM风速调节  
  **Manual Control Mode**: 5-level PWM speed adjustment
  - **自动控制模式**：基于温度传感器的6档位智能调速  
  **Auto Control Mode**: 6-level intelligent speed adjustment based on temperature sensor
- **系统滴答计时** - TIM4实现1ms中断的GetTick()函数  
  **System Tick Timer** - 1ms interrupt via TIM4 for GetTick() function

#### 🔄 **系统架构** (System Architecture)
- **模块化设计** - 驱动层与应用层分离，代码结构清晰  
  **Modular Design** - Driver layer separated from application layer, clean code structure
- **非阻塞框架** - 所有功能采用非阻塞设计，确保系统响应性  
  **Non-blocking Framework** - All functions designed non-blocking to ensure system responsiveness
- **多层状态机** - 菜单状态、输入状态、控制状态分层管理  
  **Multi-layer State Machine** - Menu states, input states, and control states managed hierarchically

## 📁 项目结构 / Project Structure

```
smart-fan-stm32/
├── User/                    # 用户应用层
│   ├── main.c              # 主程序入口
│   └── menu.c/h            # 菜单系统（非阻塞状态机）
├── Hardware/               # 硬件驱动层
│   ├── ad.c/h              # ADC驱动（已实现）
│   ├── oled.c/h            # OLED显示驱动（已优化）
│   ├── light_sensor.c/h    # 光照传感器驱动（ADC版）
│   ├── rotary.c/h          # 旋转编码器驱动（新增）
│   ├── key.c/h             # 独立按键驱动（3按键）
│   ├── led.c/h             # LED控制驱动
│   ├── motor.c/h           # 电机驱动（已实现）
│   └── temperature_sensor.c/h # 温度传感器驱动
├── Library/                # 库文件
│   └── STM32F10x_StdPeriph_Driver/  # STM32标准外设库
├── Start/                  # 启动文件
├── docs/                   # 项目文档
│   ├── learning_notes.md   # 学习笔记
│   └── changelog.md        # 更新日志
├── .gitignore              # Git忽略规则
├── README.md               # 项目说明文档
├── LICENSE                 # MIT许可证
└── Project.uvprojx         # Keil MDK工程文件
```

## 🎮 菜单系统说明 / Menu System Guide

### 主菜单结构 (Main Menu Structure)
```
1. Status          系统状态 - 显示传感器数据（旋钮选择）
2. Manual Control  手动控制 - PWM风扇5档位调节（旋钮调节）
3. Auto Mode       自动模式 - 温度自适应控制（按键开关）
4. Settings        系统设置 - 参数配置（框架）
5. About           关于信息 - 项目版本
```

### 操作方式 (Operation Method)
```
旋钮操作：
  顺时针旋转：光标下移 / 档位增加
  逆时针旋转：光标上移 / 档位减少
  
按键操作：
  Key_OK（确认键）：进入选定功能 / 确认选择
  Key_Back（返回键）：返回上级菜单 / 取消操作
  Key_Mode（模式键）：模式切换 / 特殊功能
```

## 🛠️ 硬件配置 / Hardware Configuration

### 当前硬件连接 (Current Hardware Connection)
```
STM32F103C8T6    外设模块
PB8 (SCL)  -----> OLED SCL
PB9 (SDA)  -----> OLED SDA
PA0        -----> 光敏电阻ADC输入（ADC0）
PA7        -----> 热敏电阻ADC输入（ADC7）
PA2        -----> PWM输出（TIM2_CH3，控制LED）
PA3        -----> 电机PWM控制（TIM2_CH2）
PA4        -----> 电机方向控制（AIN2）
PA5        -----> 电机方向控制（AIN1）

EC11旋转编码器：
PA11       -----> CLK（旋转检测A相）
PA12       -----> DT（旋转检测B相）

独立按键：
PA9        -----> 确认键（Key_OK）
PA15       -----> 返回键（Key_Back）
PB3        -----> 模式键（Key_Mode）

PC13       -----> LED状态指示
3.3V       -----> 各模块VCC
GND        -----> 各模块GND
```

### 电机驱动连接
```
STM32          TB6612电机驱动
PA3 (PWM)  --> PWMA
PA5        --> AIN1
PA4        --> AIN2
PB12       --> STBY (使能)
VM (12V)   --> 电机电源
VCC (5V)   --> 逻辑电源
GND        --> 共地
```

### 硬件特性 (Hardware Specifications)
- **主控芯片**：STM32F103C8T6 (72MHz Cortex-M3, 64KB Flash, 20KB RAM)
- **显示屏**：0.96寸OLED (SSD1306, I2C, 128×64分辨率)
- **输入设备**：EC11旋转编码器 + 3个独立按键
- **光照传感器**：光敏电阻 + 10K分压电阻 (ADC通道0)
- **温度传感器**：热敏电阻 + 10K分压电阻 (ADC通道7)
- **电机驱动**：TB6612FNG双路电机驱动模块
- **电机**：直流减速电机（风扇驱动）

## 📈 技术实现 / Technical Implementation

### 核心算法 (Core Algorithms)

#### 1. 旋转编码器驱动算法
```c
// 旋转编码器状态机
typedef enum {
    ROTARY_IDLE,        // 空闲状态
    ROTARY_CW_STEP1,    // 顺时针第一步
    ROTARY_CW_STEP2,    // 顺时针第二步
    ROTARY_CCW_STEP1,   // 逆时针第一步
    ROTARY_CCW_STEP2    // 逆时针第二步
} RotaryState;

// 旋转检测状态机处理
RotaryDirection Rotary_Process(void) {
    static RotaryState state = ROTARY_IDLE;
    uint8_t clk = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
    uint8_t dt = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
    
    switch(state) {
        case ROTARY_IDLE:
            if(clk == 0) state = ROTARY_CW_STEP1;
            else if(dt == 0) state = ROTARY_CCW_STEP1;
            break;
        case ROTARY_CW_STEP1:
            if(dt == 0) state = ROTARY_CW_STEP2;
            else state = ROTARY_IDLE;
            break;
        case ROTARY_CW_STEP2:
            if(clk == 1) return DIR_CW;  // 顺时针旋转
            state = ROTARY_IDLE;
            break;
        // ... 逆时针状态处理
    }
    return DIR_NONE;
}
```

#### 2. 混合输入系统架构
```c
// 输入事件分发器
void Input_Process(void) {
    // 处理旋转编码器
    RotaryDirection dir = Rotary_GetDirection();
    if(dir != DIR_NONE) {
        Menu_HandleRotary(dir);
    }
    
    // 处理独立按键
    uint8_t key_event = Key_Scan();
    if(key_event != KEY_NONE) {
        Menu_HandleKey(key_event);
    }
}
```

#### 3. 温度控制算法
```c
// 自动温度控制算法（优化版）
void Motor_AutoControl(void) {
    static uint32_t last_update = 0;
    uint32_t now = GetTick();
    
    if(now - last_update >= 200) {  // 200ms更新一次
        int8_t temp_level = TEMSensor_GetLevel();
        
        // 温度-速度映射：线性关系
        int8_t target_speed = (temp_level - 1) * (-20);
        if(target_speed < -100) target_speed = -100;
        if(target_speed > 0) target_speed = 0;
        
        // 平滑过渡（避免突变）
        static int8_t current_speed = 0;
        if(target_speed != current_speed) {
            current_speed = target_speed;
            Motor_SetSpeed(current_speed);
        }
        
        last_update = now;
    }
}
```

#### 4. 系统滴答计时
```c
// 使用TIM4实现1ms滴答
uint32_t GetTick(void) {
    return g_tick_count; // TIM4中断更新
}
```

## 📊 项目进度 / Project Progress

| 日期 | 里程碑 | 状态 | 完成度 |
|------|--------|------|--------|
| 2026.01.30 | 项目初始化与Git配置 | ✅ 完成 | 100% |
| 2026.01.30 | 基础传感器驱动开发 | ✅ 完成 | 100% |
| 2026.01.30 | OLED显示系统实现 | ✅ 完成 | 100% |
| 2026.01.31 | OLED菜单系统V0.2.0 | ✅ 完成 | 100% |
| 2026.02.01 | ADC学习与光敏传感器改造 | ✅ 完成 | 100% |
| 2026.02.01 | 菜单系统重构V0.3.0 | ✅ 完成 | 100% |
| 2026.02.02 | 非阻塞菜单重构V0.4.0 | ✅ 完成 | 100% |
| 2026.02.03 | PWM控制与电机驱动调试 | ✅ 完成 | 100% |
| 2026.02.04 | 手动/自动控制完整实现 | ✅ 完成 | 100% |
| 2026.02.05 | 旋转编码器输入系统重构 | ✅ 完成 | 100% |
| 2026.02.06 | 系统优化与功能完善 | 🔄 进行中 | 60% |

### 当前完成度：90%
- ✅ 用户交互系统：100%（旋钮+按键混合输入）
- ✅ 传感器数据采集：100%
- ✅ 执行器控制系统：100%
- 🔄 系统集成与优化：70%

## 🔄 更新日志 / Changelog

### v0.6.0 (2026-02-05) - 旋转编码器输入系统版
#### 🎯 重大架构升级
- **输入系统重构**：弃用4按键方案，采用EC11旋转编码器+3独立按键混合输入
- **状态机架构**：完整的输入状态机设计，支持旋钮旋转和按键事件分发
- **操作逻辑优化**：旋钮用于光标移动和档位调节，按键用于确认/返回/模式切换
- **模块化驱动**：独立的Rotary.c（纯旋转检测）和Key.c（独立按键）驱动模块

#### 🔧 技术改进
1. **旋转编码器驱动**：
   - 实现EC11编码器的GPIO中断检测
   - 4状态状态机算法，精准检测顺时针/逆时针旋转
   - 软件消抖处理，避免误触发

2. **独立按键系统**：
   - 3按键独立设计：确认键、返回键、模式键
   - 统一按键扫描接口，支持边沿检测
   - 非阻塞按键处理，集成到主循环

3. **输入事件分发**：
   - 统一的输入事件处理器`Input_Process()`
   - 旋钮事件和按键事件分离处理
   - 事件队列机制，避免输入丢失

4. **菜单交互优化**：
   - 旋钮控制光标移动，操作更直观
   - 确认键进入功能，返回键退出
   - 模式键快速切换手动/自动模式

#### 🐛 Bug修复与优化
1. **输入响应优化**：修复了按键响应延迟问题，实现即时响应
2. **旋钮检测精度**：优化状态机算法，提高旋转检测准确率
3. **代码结构清理**：移除旧版4按键相关代码，保持代码整洁
4. **功耗优化**：优化GPIO配置，降低系统待机功耗

#### 📁 新增文件
- `Hardware/rotary.c/h` - 旋转编码器驱动模块
- `Hardware/key.c/h` - 独立按键驱动模块（重构版）

### v0.5.0 (2026-02-04) - 完整控制系统版
#### 🎯 主要更新
- **完整手动控制**：实现5档位PWM风扇调速界面，支持实时速度显示
- **智能自动控制**：基于温度的6档位自适应调速系统，25°C阈值启动
- **温度传感器集成**：热敏电阻ADC采集，6档位温度判断算法
- **4按键系统**：新增返回键，完善页面导航逻辑
- **统一显示框架**：所有页面采用相似布局，提升用户体验

### v0.4.0 (2026-02-02) - 非阻塞菜单与PWM控制版
#### 🎯 主要更新
- **非阻塞菜单系统**：重构菜单为状态机设计，解决阻塞导致LED不更新问题
- **PWM控制实现**：基于TIM2_CH3实现LED亮度随光照自动变化
- **电机驱动框架**：新增Motor.c模块，支持风扇/小车复用设计
- **系统滴答计时**：使用TIM4实现1ms中断的GetTick()函数，解决SysTick冲突
- **状态页面优化**：实时刷新传感器数据，解决显示停滞问题

## 🧪 今日成果 / Today's Achievements (2026.02.05)

### 完成的任务
1. **输入系统重构**：成功从4按键迁移到旋转编码器+3按键混合输入
2. **旋转编码器驱动**：实现EC11的GPIO检测和状态机算法
3. **独立按键系统**：设计并实现3按键独立检测逻辑
4. **事件分发架构**：建立统一的输入事件处理框架
5. **菜单交互优化**：重新设计所有页面的交互逻辑

### 技术收获
- ✅ 掌握旋转编码器的工作原理和驱动方法
- ✅ 理解状态机在输入检测中的应用
- ✅ 实践混合输入系统的设计与实现
- ✅ 学习事件驱动架构的设计模式

### 核心代码实现
```c
// 混合输入系统主循环处理
void main(void) {
    System_Init();
    
    while(1) {
        // 非阻塞输入处理
        Input_Process();
        
        // 菜单状态机
        Menu_Process();
        
        // 自动控制处理（如果启用）
        if(g_system_mode == MODE_AUTO) {
            Motor_AutoControl();
        }
        
        // 系统后台任务
        System_BackgroundTask();
    }
}
```

### 问题解决记录
1. **问题**：旋钮旋转检测不准确，存在误触发
2. **排查**：
   - 检查EC11的CLK和DT信号波形
   - 分析状态机状态转换逻辑
   - 测试不同消抖时间参数
3. **解决**：
   - 优化状态机算法，增加中间状态
   - 调整GPIO中断触发边沿
   - 添加软件滤波，消除机械抖动

## 🚀 下一步计划 / Next Steps

### 近期功能开发（按优先级）
1. **温度精确显示**（1天）
   - 增加温度小数位显示（XX.X°C）
   - 校准热敏电阻参数，提高测量精度
   - 添加温度采样滤波算法（滑动平均滤波）

2. **定时功能实现**（1-2天）
   - 倒计时关闭功能（30分钟/1小时/2小时）
   - 定时器状态显示和设置界面
   - 定时结束后自动返回自动模式

3. **智能场景模式**（2天）
   - **睡眠模式**：夜间自动降低风速和噪音
   - **恒定模式**：维持设定温度的风速
   - **节能模式**：根据环境动态调整功耗
   - 场景快速切换（旋钮选择+确认）

4. **系统优化与完善**（2天）
   - 代码架构优化，提高可维护性
   - 添加更多的错误检测和恢复机制
   - 完善用户操作反馈（LED指示）

### 技术重点
1. **滤波算法实现**
   ```c
   // 滑动平均滤波示例
   #define FILTER_SIZE 8
   float temperature_filter[FILTER_SIZE];
   float get_filtered_temperature(void);
   ```

2. **定时器框架设计**
   - 系统时基管理
   - 软件定时器设计
   - 倒计时状态机

3. **场景模式状态机**
   - 扩展现有的状态机结构
   - 模式切换平滑过渡

### 代码质量提升
1. **模块化重构**
   - 将风扇控制逻辑独立为单独模块
   - 传感器数据管理模块
   - 显示逻辑与业务逻辑分离

2. **配置文件**
   - 温度阈值可配置
   - PWM参数可调整
   - 用户偏好保存（如有EEPROM）

## 📚 学习笔记摘要 / Learning Notes Summary

### 旋转编码器技术要点
1. **工作原理**：
   - EC11编码器输出两路相位差90°的方波信号
   - 通过检测两路信号的相位关系判断旋转方向
   - 每旋转一格产生一个完整的4状态周期

2. **状态机设计**：
   - 使用4状态状态机准确检测旋转方向
   - 状态转换基于CLK和DT信号的当前状态
   - 添加中间状态提高抗干扰能力

3. **消抖处理**：
   - 机械编码器存在接触抖动
   - 软件消抖通过状态机实现
   - 适当延迟避免误检测

### 混合输入系统设计原则
1. **职责分离**：
   - 旋钮负责连续调节（光标移动、数值调整）
   - 按键负责离散操作（确认、返回、切换）

2. **事件驱动**：
   - 输入产生事件，应用层响应事件
   - 事件队列避免输入丢失
   - 异步处理提高系统响应性

3. **用户体验**：
   - 操作逻辑一致，降低学习成本
   - 即时反馈，增强操作信心
   - 容错设计，避免误操作

## 🐱 开发者心得 / Developer Insights

> "今天完成了输入系统的重大重构！从传统的4按键方案升级到旋转编码器+独立按键的混合输入系统。最大的感受是：好的硬件设计能极大提升用户体验。旋钮的连续调节比按键的离散调节更加自然流畅，特别是在调整风速档位时，那种'拧动'的感觉真的很棒。通过这次重构，我深刻理解了'硬件定义交互，软件实现逻辑'的设计理念。状态机的应用也让代码更加清晰，输入检测的准确率大大提高。接下来要专注于功能的完善和用户体验的优化。"

## 🤝 如何贡献 / How to Contribute

欢迎任何形式的贡献！你可以通过以下方式参与：

1. **报告问题**：在GitHub Issues中提交发现的bug
2. **功能建议**：提出新的功能想法或改进建议
3. **代码贡献**：提交Pull Request改进代码
4. **文档完善**：帮助改进文档或翻译

### 贡献流程 / Contribution Process
1. Fork本仓库
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开Pull Request

## 👨‍💻 作者信息 / Author Information

**Che Jiaen** - Xidian University  

- **专业**：探测制导与控制技术  
- **年级**：大二下学期  
- **GitHub**: [@HATSUNE-MIKU-CJE](https://github.com/HATSUNE-MIKU-CJE)  
- **技能方向**: 嵌入式系统、C/C++编程、STM32开发、自动控制

### 当前学习重点
- STM32外设深入：ADC、PWM、定时器、GPIO中断
- 嵌入式系统设计：状态机、模块化、实时系统
- 人机交互设计：输入设备、用户界面、用户体验

## 📄 许可证 / License

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 致谢 / Acknowledgments

- 感谢 **江科大** 的优质STM32教学视频，为我的学习之路打下坚实基础
- 感谢 **西安电子科技大学** 提供优良的学习环境和实验条件
- 感谢 **GitHub开源社区** 提供的丰富资源和工具
- 感谢所有给予我指导和帮助的老师和同学
- 感谢 **AI编程助手** 在技术实现上的指导和建议

---

**项目开始时间**：2026年1月27  
**最后更新**：2026年2月8日  
**当前版本**：v0.6.0 (旋转编码器输入系统版)  
**项目状态**：核心交互系统升级完成，进行功能完善  
**预计完成时间**：2026年2月26日  

**Project Start Date**: January 2026  
**Last Updated**: February 5, 2026  
**Current Version**: v0.6.0 (Rotary Encoder Input System)  
**Project Status**: Core interaction system upgraded, feature refinement in progress  
**Estimated Completion**: February 8, 2026  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐
```

## 🎯 README更新亮点

### 1. **版本升级**：v0.5.0 → v0.6.0
- 体现输入系统的重大重构
- 进度从85%提升到90%

### 2. **功能重构突出**：
- 重点展示旋转编码器+独立按键的混合输入系统
- 详细描述状态机架构和操作逻辑

### 3. **技术细节完善**：
- 新增旋转编码器驱动算法说明
- 更新硬件连接图（EC11编码器）
- 展示混合输入系统的代码架构

### 4. **今日成果聚焦**：
- 重点描述输入系统重构的技术收获
- 记录问题解决经验
- 展示核心代码实现

### 5. **项目计划更新**：
- 移除中文显示相关计划
- 聚焦温度精确显示、定时功能、智能场景等实用功能
- 明确优先级和时间安排

### 6. **开发者心得更新**：
- 反映输入系统重构的成就感
- 强调硬件设计与用户体验的关系
- 分享状态机应用的体会

### 7. **学习笔记补充**：
- 新增旋转编码器技术要点
- 完善混合输入系统设计原则
- 提供实际开发经验总结