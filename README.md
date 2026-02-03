# 📝 README.md 更新内容（v0.5.0版本）

```markdown
# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-Active_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.5.0-brightgreen)  
![Progress](https://img.shields.io/badge/Progress-85%25-green)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented

#### 🎮 **交互系统** (Interaction System)
- **OLED菜单系统** - 5页面非阻塞状态机菜单，支持居中标题和滚动提示  
  **OLED Menu System** - 5-page non-blocking state machine menu with centered titles and scroll indicators
- **按键控制系统** - 4按键边沿检测+软件消抖，非阻塞设计  
  **Button Control System** - 4-key edge detection + software debouncing, non-blocking design

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
- **状态机管理** - 菜单状态与系统模式分离管理  
  **State Machine Management** - Menu states and system modes managed separately

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
│   ├── key.c/h             # 按键驱动（4按键支持）
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
1. Status          系统状态 - 显示传感器数据
2. Manual Control  手动控制 - PWM风扇5档位调节（已实现）
3. Auto Mode       自动模式 - 温度自适应控制（已实现）
4. Settings        系统设置 - 参数配置（框架）
5. About           关于信息 - 项目版本
```

### 状态页面显示内容 (Status Page Display)
```
第1行： System Status
第2行： Light: [1-5]/5 [描述]
第3行： AD:[0-4095] V:[0.00-3.30]
第4行： ADT:[0-4095] (温度ADC值)
```

### 手动控制页面 (Manual Control Page)
```
第1行： Manual Control
第2行： 空行
第3行： Wind Speed: [0-5]/5
第4行： 按键提示：上/下调速，OK停止，BACK返回
```

### 自动模式页面 (Auto Mode Page)
```
第1行： Auto Mode
第2行： Tem:[1-6]/6 Wind:[0-5]/5
第3行： AD:[0-4095] V:[0.00-3.30]
第4行： Status: ON/OFF
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
PA9        -----> 按键1（Key1 - 向上/自动模式开关）
PA11       -----> 按键2（Key2 - 向下）
PA15       -----> 按键3（Key3 - 选择/确认/停止）
PB3        -----> 按键4（Key4 - 返回/退出）
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
- **光照传感器**：光敏电阻 + 10K分压电阻 (ADC通道0)
- **温度传感器**：热敏电阻 + 10K分压电阻 (ADC通道7)
- **按键**：4个轻触开关 (上/下/选择/返回)
- **电机驱动**：TB6612FNG双路电机驱动模块
- **电机**：直流减速电机（风扇驱动）

## 📈 技术实现 / Technical Implementation

### 核心算法 (Core Algorithms)

#### 1. ADC数据采集与处理
```c
// 5档位光照判断算法
uint8_t LightSensor_GetLevel(void) {
    uint16_t adValue = AD_GetValue(ADC_Channel_0);  // 0-4095
    if (adValue <= 824) return 1;      // 漆黑
    else if (adValue <= 1633) return 2;// 微光
    else if (adValue <= 2441) return 3;// 柔和
    else if (adValue <= 3250) return 4;// 明亮
    else return 5;                     // 强光
}

// 6档位温度判断算法
uint8_t TEMSensor_GetLevel(void) {
    uint16_t adValue = AD_GetValue(ADC_Channel_7);  // 0-4095
    if (adValue >= 3500) return 1;      // 很冷
    else if (adValue >= 3000) return 2; // 冷
    else if (adValue >= 2500) return 3; // 凉
    else if (adValue >= 2000) return 4; // 适宜
    else if (adValue >= 1500) return 5; // 热
    else return 6;                      // 很热
}
```

#### 2. 非阻塞菜单状态机
- **状态管理**：`g_menu_state`全局变量跟踪当前页面
- **周期处理**：`Menu_Process()`在main循环中调用，更新显示
- **按键分发**：不同页面响应不同按键逻辑
- **页面管理**：统一的重绘标志管理，提高显示效率

#### 3. PWM电机控制
```c
// 电机速度控制（-100到0，0为停止，-100为最大）
void Motor_SetSpeed(int8_t Speed) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_4); // AIN2=0
    GPIO_SetBits(GPIOA, GPIO_Pin_5);   // AIN1=1（正转）
    PWM_SetCompare1(-Speed);           // 设置PWM占空比
}

// 自动温度控制算法
void Motor_Auto(int8_t *Speed) {
    int8_t temp_level = TEMSensor_GetLevel();  
    int8_t target_speed = (temp_level - 1) * (-20); // 1档=0, 6档=-100
    if (target_speed < -100) target_speed = -100;
    if (target_speed > 0) target_speed = 0;
    
    *Speed = target_speed;
    Motor_SetSpeed(*Speed);
}
```

#### 4. 系统滴答计时
```c
// 使用TIM4实现1ms滴答
uint32_t GetTick(void) {
    return g_tick_count; // TIM4中断更新
}
```

### 关键参数 (Key Parameters)
- **ADC分辨率**：12位 (0-4095)
- **参考电压**：3.3V
- **PWM频率**：1kHz (72MHz/72/1000)
- **PWM分辨率**：0.1% (0-1000)
- **系统滴答**：1ms精度
- **温度档位**：6档（很冷/冷/凉/适宜/热/很热）
- **风扇档位**：6档（停止 + 5个速度档）
- **更新频率**：手动模式500ms，自动模式200ms
- **温度阈值**：25°C（ADC值约2000）开始转动

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
| 2026.02.05 | 系统集成与优化调试 | 🔄 进行中 | 60% |
| 2026.02.06 | 性能测试与文档完善 | ⏳ 待开始 | 0% |

### 当前完成度：85%
- ✅ 用户交互系统：100%
- ✅ 传感器数据采集：100%
- ✅ 执行器控制系统：100%
- 🔄 系统集成调试：60%

## 🔄 更新日志 / Changelog

### v0.5.0 (2026-02-04) - 完整控制系统版
#### 🎯 主要更新
- **完整手动控制**：实现5档位PWM风扇调速界面，支持实时速度显示
- **智能自动控制**：基于温度的6档位自适应调速系统，25°C阈值启动
- **温度传感器集成**：热敏电阻ADC采集，6档位温度判断算法
- **4按键系统**：新增返回键，完善页面导航逻辑
- **统一显示框架**：所有页面采用相似布局，提升用户体验

#### 🔧 技术改进
1. **电机控制算法**：
   - 手动控制：5档位调速（0-100% PWM）
   - 自动控制：温度-速度映射算法（1档对应0%，6档对应100%）
   - 非阻塞定时：手动模式500ms更新，自动模式200ms更新

2. **温度检测系统**：
   - 热敏电阻分压电路设计
   - 6档位温度分级（很冷/冷/凉/适宜/热/很热）
   - ADC通道7配置与校准

3. **状态机优化**：
   - 页面重绘标志管理（status_need_redraw等）
   - 首次进入立即更新机制
   - 统一的页面退出处理

4. **按键逻辑完善**：
   - 手动模式：Key1加速，Key2减速，Key3停止，Key4返回
   - 自动模式：Key1开关，Key3启动，Key4返回
   - 其他页面：Key4统一返回主菜单

#### 🐛 Bug修复
1. **速度显示同步**：修复手动模式下速度显示不同步问题
2. **自动模式初始化**：修复首次进入自动模式不更新问题
3. **PWM方向控制**：修正电机转动方向逻辑
4. **显示刷新优化**：减少不必要的OLED清屏操作

### v0.4.0 (2026-02-02) - 非阻塞菜单与PWM控制版
#### 🎯 主要更新
- **非阻塞菜单系统**：重构菜单为状态机设计，解决阻塞导致LED不更新问题
- **PWM控制实现**：基于TIM2_CH3实现LED亮度随光照自动变化
- **电机驱动框架**：新增Motor.c模块，支持风扇/小车复用设计
- **系统滴答计时**：使用TIM4实现1ms中断的GetTick()函数，解决SysTick冲突
- **状态页面优化**：实时刷新传感器数据，解决显示停滞问题

### v0.3.0 (2026-02-01) - 菜单重构与ADC集成版
#### 🎯 主要更新
- **菜单系统重构**：重新设计5页面菜单结构
- **ADC集成完成**：光照传感器从GPIO改为ADC读取，实现5档位自动判断
- **状态页面优化**：实时显示光照档位、AD值、电压值
- **按键系统修复**：修复选择键不工作的问题
- **类型错误修复**：修复uint8_t接收ADC值导致的显示错误

### v0.2.0 (2026-01-31) - 菜单系统版
- ✅ 实现5页面OLED菜单系统
- ✅ 添加按键控制系统（上下导航）
- ✅ 优化项目结构，增加Menu模块
- ✅ 完善项目文档和README

### v0.1.0 (2026-01-30) - 基础功能版
- ✅ 项目初始化和Git配置
- ✅ 基础传感器驱动开发
- ✅ OLED显示系统实现
- ✅ 基本阈值比较功能

## 🧪 今日成果 / Today's Achievements (2026.02.04)

### 完成的任务
1. **完整手动控制实现**：5档位PWM风扇调速，实时速度显示
2. **智能自动控制系统**：温度自适应6档位调速算法
3. **温度传感器集成**：热敏电阻ADC采集与6档位判断
4. **4按键导航系统**：完善所有页面的按键逻辑
5. **统一显示框架**：优化页面布局和刷新机制

### 技术收获
- ✅ 掌握PWM精细控制技术，实现多档位调速
- ✅ 理解传感器数据到控制输出的完整映射流程
- ✅ 实践非阻塞状态机在复杂系统中的应用
- ✅ 学习热敏电阻特性曲线与温度判断算法

### 核心算法实现
```c
// 温度到速度的映射算法
int8_t target_speed = (temp_level - 1) * (-20);
// 温度档位: 1(很冷) → 速度: 0% (停止)
// 温度档位: 4(适宜) → 速度: 60% (-60)
// 温度档位: 6(很热) → 速度: 100% (-100)
```

### 问题解决记录
1. **问题**：自动模式首次进入不更新
2. **排查**：
   - 检查`first_auto_run`标志位逻辑
   - 验证`GetTick()`时间管理
   - 调试温度传感器数据读取
3. **解决**：
   - 添加首次进入立即更新机制
   - 修正时间戳初始化逻辑
   - 优化温度档位判断阈值

## 🚀 下一步计划 / Next Steps

### 短期目标 (2月5日)
1. **系统集成测试**：全面测试手动/自动模式切换稳定性
2. **性能优化**：优化PWM控制精度和响应速度
3. **边界条件处理**：完善异常情况处理逻辑

### 中期目标 (2月6日)
1. **设置页面开发**：添加温度校准、风速调节参数
2. **数据记录功能**：记录运行数据并显示统计信息
3. **功耗优化**：优化系统功耗，延长电池使用时间

### 优化方向
1. **算法优化**：更平滑的温度-速度曲线
2. **用户体验**：添加声音反馈、动画效果
3. **扩展功能**：定时开关、模式记忆等

## 📚 学习笔记摘要 / Learning Notes Summary

### 温度控制算法设计要点
1. **阈值选择**：
   - 启动阈值：25°C（ADC值约2000）
   - 档位划分：6档均匀分布，覆盖常见室温范围
   - 迟滞处理：避免档位频繁切换

2. **PWM控制要点**：
   - 频率选择：1kHz兼顾效率和控制精度
   - 分辨率：1000级提供细腻控制
   - 方向控制：AIN1/AIN2逻辑组合

3. **非阻塞设计原则**：
   - 时间片管理：不同任务分配不同时间片
   - 状态标志：使用标志位避免阻塞等待
   - 资源复用：最大化硬件资源利用率

### 硬件调试经验
1. **温度传感器校准**：
   - 室温下测量ADC基准值
   - 热水/冰水测试边界值
   - 软件线性插值提高精度

2. **电机控制调试**：
   - 先验证PWM信号再连接电机
   - 分步测试方向控制和速度控制
   - 电流监测防止过载

## 🐱 开发者心得 / Developer Insights

> "今天完成了智能风扇的核心控制功能！从传感器数据采集到PWM输出控制的完整链路终于打通了。最大的成就感在于：温度变化能实时反映在风扇转速上，形成了一个真正的闭环控制系统。通过这个项目，我深刻理解了嵌入式系统的'感知-决策-执行'三大核心环节。手动和自动模式的切换也让我思考了不同控制策略的适用场景。接下来的重点是系统优化和稳定性提升。"

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
- STM32外设深入：ADC、PWM、定时器、通信接口
- 嵌入式系统设计：状态机、模块化、实时系统
- 控制算法基础：PID控制、传感器融合

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

**项目开始时间**：2026年1月  
**最后更新**：2026年2月4日  
**当前版本**：v0.5.0 (完整控制系统版)  
**项目状态**：核心功能已完成，进行优化调试  
**预计完成时间**：2026年2月6日  

**Project Start Date**: January 2026  
**Last Updated**: February 4, 2026  
**Current Version**: v0.5.0 (Complete Control System)  
**Project Status**: Core functions completed, optimization in progress  
**Estimated Completion**: February 6, 2026  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐
```

## 🎯 README更新亮点

### 1. **版本升级**：v0.4.0 → v0.5.0
- 体现手动控制和自动控制的完整实现
- 进度从65%提升到85%

### 2. **功能完整性**：
- 明确标注手动控制和自动控制为已实现状态
- 详细描述温度传感器集成和算法实现

### 3. **技术细节完善**：
- 新增温度控制算法说明
- 完善硬件连接图（新增温度传感器）
- 更新关键参数表

### 4. **今日成果突出**：
- 重点展示完整控制系统的实现
- 记录温度-速度映射算法细节
- 总结问题解决经验

### 5. **项目状态更新**：
- 核心功能已完成，进入优化阶段
- 调整下一步计划，侧重系统优化

### 6. **开发者心得更新**：
- 反映完成核心功能的成就感
- 强调"感知-决策-执行"闭环理解

### 7. **学习笔记补充**：
- 新增温度控制算法设计要点
- 完善硬件调试经验总结