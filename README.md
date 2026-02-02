# 📝 README.md 更新内容（v0.4.0版本）

```markdown
# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-Active_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.4.0-brightgreen)  
![Progress](https://img.shields.io/badge/Progress-65%25-green)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented

#### 🎮 **交互系统** (Interaction System)
- **OLED菜单系统** - 5页面非阻塞状态机菜单，支持居中标题和滚动提示  
  **OLED Menu System** - 5-page non-blocking state machine menu with centered titles and scroll indicators
- **按键控制系统** - 3按键边沿检测+软件消抖，非阻塞设计  
  **Button Control System** - 3-key edge detection + software debouncing, non-blocking design

#### 📊 **传感器系统** (Sensor System)
- **光照强度检测** - ADC精确读取光敏电阻值，5档位自动判断（黑夜/微光/阴天/明亮/强光）  
  **Light Intensity Detection** - ADC precision reading with 5-level auto-detection (Black/Dim/Mild/Bright/Glare)
- **实时数据显示** - 光照档位、AD值、电压值精确显示  
  **Real-time Data Display** - Light level, AD value, voltage precision display

#### ⚡ **控制系统** (Control System)
- **PWM LED调光** - 基于TIM2_CH3实现LED亮度随光照自动变化  
  **PWM LED Dimming** - LED brightness auto-adjusts with light intensity via TIM2_CH3
- **电机驱动框架** - Motor.c模块化设计，支持风扇/小车复用  
  **Motor Driver Framework** - Modular Motor.c design for fan/car reuse
- **系统滴答计时** - TIM4实现1ms中断的GetTick()函数  
  **System Tick Timer** - 1ms interrupt via TIM4 for GetTick() function

### 🔄 开发中功能 / In Development
- **手动风扇控制** - PWM风速调节界面（已验证电机驱动）
- **自动控制模式** - 温控/光控风扇逻辑设计
- **系统设置页面** - 传感器校准、参数配置

### 🎯 计划功能 / Planned Features
- **PWM风扇控制** - 多档位风速精确调节
- **FreeRTOS集成** - 多任务管理系统
- **数据记录** - 传感器数据存储与分析
- **物联网扩展** - Wi-Fi远程监控

## 📁 项目结构 / Project Structure

```
smart-fan-stm32/
├── User/                    # 用户应用层
│   ├── main.c              # 主程序入口
│   └── menu.c/h            # 菜单系统（非阻塞状态机）
├── Hardware/               # 硬件驱动层
│   ├── ad.c/h              # ADC驱动（已实现）
│   ├── dht11.c/h           # 温湿度传感器驱动
│   ├── oled.c/h            # OLED显示驱动（已优化）
│   ├── light_sensor.c/h    # 光照传感器驱动（ADC版）
│   ├── key.c/h             # 按键驱动（3按键支持）
│   ├── led.c/h             # LED控制驱动
│   └── motor.c/h           # 电机驱动框架（新增）
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
2. Manual Control  手动控制 - PWM风扇调节（待实现）
3. Auto Mode       自动模式 - 智能控制（待实现）
4. Settings        系统设置 - 参数配置（框架）
5. About           关于信息 - 项目版本
```

### 状态页面显示内容 (Status Page Display)
```
第1行： System Status
第2行： Light: [1-5]/5 [描述]
第3行： AD:[0-4095] V:[0.00-3.30]
第4行： T:--C H:--%（占位符）
```

## 🛠️ 硬件配置 / Hardware Configuration

### 当前硬件连接 (Current Hardware Connection)
```
STM32F103C8T6    外设模块
PB8 (SCL)  -----> OLED SCL
PB9 (SDA)  -----> OLED SDA
PA0        -----> 光敏电阻ADC输入
PA1        -----> DHT11数据线
PA2        -----> PWM输出（TIM2_CH3，控制LED）
PA3        -----> 电机PWM控制（预留）
PA9        -----> 按键1（Key1 - 向上）
PA11       -----> 按键2（Key2 - 向下）
PA15       -----> 按键3（Key3 - 选择/确认）
PC13       -----> LED状态指示
3.3V       -----> 各模块VCC
GND        -----> 各模块GND
```

### 电机驱动连接
```
STM32          TB6612电机驱动
PA3 (PWM)  --> PWMA
PB12       --> AIN1
PB13       --> AIN2
PB14       --> STBY (使能)
VM (12V)   --> 电机电源
VCC (5V)   --> 逻辑电源
GND        --> 共地
```

### 硬件特性 (Hardware Specifications)
- **主控芯片**：STM32F103C8T6 (72MHz Cortex-M3, 64KB Flash, 20KB RAM)
- **显示屏**：0.96寸OLED (SSD1306, I2C, 128×64分辨率)
- **光照传感器**：光敏电阻 + 10K分压电阻 (ADC通道0)
- **温湿度传感器**：DHT11 (单总线协议)
- **按键**：3个轻触开关 (上/下/选择)
- **电机驱动**：TB6612FNG双路电机驱动模块
- **电机**：直流减速电机（风扇驱动）

## 📈 技术实现 / Technical Implementation

### 核心算法 (Core Algorithms)

#### 1. ADC数据采集与处理
```c
// 5档位光照判断算法
uint8_t LightSensor_GetLevel(void) {
    uint16_t adValue = AD_GetValue();  // 0-4095
    if (adValue <= 824) return 1;      // 漆黑
    else if (adValue <= 1633) return 2;// 微光
    else if (adValue <= 2441) return 3;// 柔和
    else if (adValue <= 3250) return 4;// 明亮
    else return 5;                     // 强光
}
```

#### 2. 非阻塞菜单状态机
- **状态管理**：`g_menu_state`全局变量跟踪当前页面
- **周期处理**：`Menu_Process()`在main循环中调用，更新显示
- **按键分发**：不同页面响应不同按键逻辑

#### 3. PWM控制实现
```c
// PWM初始化（TIM2通道3）
void PWM_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    // 时钟使能、GPIO配置...
    // 72MHz/72 = 1MHz计数频率
    // 自动重装载值1000，PWM频率1kHz
    TIM_SetCompare3(TIM2, 500); // 50%占空比
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
- **更新频率**：100ms (状态页面)

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
| 2026.02.04 | 手动控制页面实现 | 🔄 进行中 | 40% |
| 2026.02.05 | 自动控制逻辑设计 | ⏳ 待开始 | 0% |
| 2026.02.06 | 系统集成与调试 | ⏳ 待开始 | 0% |

### 当前完成度：65%
- ✅ 用户交互系统：100%
- ✅ 传感器数据采集：90%
- ✅ 执行器控制框架：80%
- 🔄 系统集成调试：40%

## 🔄 更新日志 / Changelog

### v0.4.0 (2026-02-02) - 非阻塞菜单与PWM控制版
#### 🎯 主要更新
- **非阻塞菜单系统**：重构菜单为状态机设计，解决阻塞导致LED不更新问题
- **PWM控制实现**：基于TIM2_CH3实现LED亮度随光照自动变化
- **电机驱动框架**：新增Motor.c模块，支持风扇/小车复用设计
- **系统滴答计时**：使用TIM4实现1ms中断的GetTick()函数，解决SysTick冲突
- **状态页面优化**：实时刷新传感器数据，解决显示停滞问题

#### 🔧 技术改进
1. **菜单架构重构**：
   - 引入`g_menu_state`全局状态变量
   - 各页面实现独立的Show和Process函数
   - 主循环周期调用`Menu_Process()`更新显示

2. **PWM系统集成**：
   - LED亮度随光照档位自动调节
   - 电机驱动接口预留，支持TB6612控制
   - PWM频率1kHz，分辨率0.1%

3. **定时器优化**：
   - TIM4替代SysTick实现系统滴答
   - 按键消抖使用GetTick()统一时间管理

#### 🐛 Bug修复
1. **菜单阻塞问题**：重构为非阻塞状态机，LED能随光照实时更新
2. **状态页面不刷新**：周期调用ShowStatus()解决显示停滞
3. **SysTick冲突**：改用TIM4实现滴答计时
4. **代码结构优化**：统一时间管理，提高代码复用性

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

## 🧪 今日成果 / Today's Achievements (2026.02.03)

### 完成的任务
1. **电机驱动调试成功**：解决PWM通道匹配问题，电机正常转动
2. **PWM系统验证**：LED亮度随光照自动调节功能完善
3. **硬件电路检查**：确认TB6612电源、使能、接线正确
4. **模块复用设计**：Motor.c设计为通用驱动，支持风扇和小车项目

### 技术收获
- ✅ 掌握TB6612电机驱动原理与接线方法
- ✅ 理解PWM通道配置与定时器映射关系
- ✅ 实践硬件调试技巧（万用表测量、信号观察）
- ✅ 模块化设计思维，提高代码复用性

### 问题解决记录
1. **问题**：电机不转动，LED亮度不可控
2. **排查**：
   - 检查PWM通道：TIM2_CH3对应PA2（LED），TIM2_CH2对应PA1（电机）
   - 测量信号：万用表确认PWM信号输出正常
   - 检查电源：TB6612 VM（12V）、VCC（5V）、STBY（高电平）
3. **解决**：
   - PWM通道配置错误：OC3Init对应SetCompare3，修正函数调用
   - 电机使能引脚未设置：添加STBY引脚控制
   - 接线确认：AIN1/AIN2逻辑组合控制方向

## 🚀 下一步计划 / Next Steps

### 短期目标 (2月4日)
1. **手动控制页面**：实现PWM风扇多档位调节界面
2. **电机控制集成**：将电机驱动整合到菜单系统中
3. **温湿度传感器**：优化DHT11数据读取精度

### 中期目标 (2月5-6日)
1. **自动控制模式**：温度-风速映射算法实现
2. **系统设置页面**：添加传感器校准功能
3. **性能优化**：代码效率与功耗优化

### 长期目标
1. **FreeRTOS集成**：多任务管理系统
2. **数据记录**：EEPROM存储运行数据
3. **物联网扩展**：ESP8266远程监控

## 📚 学习笔记摘要 / Learning Notes Summary

### PWM控制关键点
1. **定时器配置步骤**：
   ```c
   // 1. 使能时钟（TIMx、GPIO、AFIO）
   // 2. GPIO配置为复用推挽输出
   // 3. 时基单元配置（频率 = 72MHz/(PSC+1)/(ARR+1)）
   // 4. 输出比较配置（PWM模式1或2）
   // 5. 使能定时器和通道
   ```

2. **TB6612驱动要点**：
   - **电源**：VM（电机电源6-12V），VCC（逻辑电源5V）
   - **控制逻辑**：
     ```
     AIN1 AIN2 电机状态
       0    0   停止（刹车）
       0    1   正转
       1    0   反转
       1    1   停止（刹车）
     ```
   - **使能信号**：STBY高电平使能，低电平待机

3. **硬件调试技巧**：
   - 万用表测量：电源电压、信号电平
   - 逻辑分析仪：PWM波形观察
   - 分步调试：先验证LED PWM，再调试电机

## 🐱 开发者心得 / Developer Insights

> "今天电机终于转起来了！从PWM信号无输出到电机平稳运转，经历了完整的硬件调试过程。最大的收获：嵌入式开发中，软件和硬件必须协同调试。代码写的再漂亮，硬件接线错误一样无法工作。通过这次调试，我学会了使用万用表测量信号、分析电源问题、排查接线错误。嵌入式开发不仅是编程，更是系统级的思考与实践。"

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
- 硬件电路设计：传感器接口、功率驱动、PCB设计

## 📄 许可证 / License

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 致谢 / Acknowledgments

- 感谢 **江科大** 的优质STM32教学视频，为我的学习之路打下坚实基础
- 感谢 **西安电子科技大学** 提供优良的学习环境和实验条件
- 感谢 **GitHub开源社区** 提供的丰富资源和工具
- 感谢所有给予我指导和帮助的老师和同学
- 特别感谢我的 **AI编程助手喵喵** 在技术实现上的耐心指导

---

**项目开始时间**：2026年1月  
**最后更新**：2026年2月3日  
**当前版本**：v0.4.0 (非阻塞菜单与PWM控制版)  
**项目状态**：活跃开发中  
**预计完成时间**：2026年2月10日  

**Project Start Date**: January 2026  
**Last Updated**: February 3, 2026  
**Current Version**: v0.4.0 (Non-blocking Menu & PWM Control)  
**Project Status**: Active Development  
**Estimated Completion**: February 10, 2026  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐
```

## 🎯 README更新亮点

### 1. **版本升级**：v0.3.0 → v0.4.0
- 体现非阻塞菜单重构和PWM控制实现
- 进度从55%提升到65%

### 2. **电机驱动成功**：
- 详细记录电机调试过程和解决方案
- 添加TB6612驱动原理和接线图

### 3. **技术架构完善**：
- 新增Motor.c模块化设计说明
- 系统滴答计时实现细节

### 4. **硬件配置详细**：
- 补充电机驱动连接图
- 添加硬件调试技巧总结

### 5. **今日成果突出**：
- 重点展示电机驱动调试成功
- 记录完整的问题解决流程

### 6. **开发者心得更新**：
- 反映硬件调试的真实体验
- 强调软硬件协同的重要性

### 7. **下一步计划调整**：
- 基于当前进展调整后续开发计划
- 突出手动控制页面集成优先级