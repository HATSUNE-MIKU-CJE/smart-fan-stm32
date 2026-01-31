# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-In_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.2.0-brightgreen)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented
- **温度监测与显示** - 通过DHT11传感器实时监测环境温度，并在OLED上显示  
  **Temperature Monitoring & Display** - Real-time monitoring via DHT11 sensor with OLED display
- **光照强度检测** - 通过光敏电阻检测环境光照强度，自动控制LED开关  
  **Light Intensity Detection** - Automatic LED control based on ambient light via photoresistor
- **OLED菜单系统** - 5页面可滚动菜单系统，支持状态机设计  
  **OLED Menu System** - 5-page scrollable menu with state machine design
- **按键控制系统** - 支持上下导航、确认和返回操作  
  **Button Control System** - Support for up/down navigation, confirm and back operations
- **模块化架构** - 代码分层清晰，Menu、OLED、Key模块独立  
  **Modular Architecture** - Clear code layering with independent Menu, OLED, and Key modules

### 🔄 近期计划 / Short-term Plan
- **数据精度提升** - ADC读取光照强度，DHT11精确温湿度读取
- **状态页面实现** - 实时显示传感器精确数值
- **风扇PWM控制** - 多档位风速调节
- **系统优化** - 低功耗模式、看门狗保护

### 🎯 长期计划 / Long-term Plan
- FreeRTOS多任务管理
- Wi-Fi远程监控与控制
- 手机APP/Web控制界面
- 数据日志存储与导出

## 📁 项目结构 / Project Structure

```
smart-fan-stm32/
├── User/                    # 用户应用层
│   ├── main.c              # 主程序入口
│   └── menu_pages.c/h      # 菜单页面定义（新增）
├── System/                 # 系统配置层
│   ├── delay.c/h           # 延时函数
│   ├── sys.c/h             # 系统初始化
│   └── usart.c/h           # 串口通信（预留）
├── Hardware/               # 硬件驱动层
│   ├── dht11.c/h           # 温湿度传感器驱动
│   ├── oled.c/h            # OLED显示驱动
│   ├── light_sensor.c/h    # 光照传感器驱动
│   ├── key.c/h             # 按键驱动（新增）
│   ├── menu.c/h            # 菜单系统模块（新增）
│   └── led.c/h             # LED控制驱动
├── Library/                # 库文件
│   └── STM32F10x_StdPeriph_Driver/  # STM32标准外设库
├── Start/                  # 启动文件
├── DebugConfig/            # 调试配置
├── docs/                   # 项目文档（新增）
│   └── learning_notes.md   # 学习笔记
├── .gitignore              # Git忽略规则
├── README.md               # 项目说明文档
├── LICENSE                 # MIT许可证
└── Project.uvprojx         # Keil MDK工程文件
```

## 🛠️ 硬件需求 / Hardware Requirements

### 必需元件 / Required Components
- **主控芯片**：STM32F103C8T6 (ARM Cortex-M3)
- **显示屏**：0.96寸OLED (SSD1306, I2C接口)
- **温度传感器**：DHT11温湿度模块
- **光照传感器**：光敏电阻模块
- **按键**：2个轻触开关（用于菜单导航）
- **指示器**：LED灯 (用于状态指示)
- **电源**：USB 5V供电或3.7V锂电池

### 可选扩展 / Optional Extensions
- 直流风扇 + L298N电机驱动模块 (用于风扇控制)
- ESP8266 Wi-Fi模块 (用于物联网连接)
- SD卡模块 (用于数据存储)
- 蜂鸣器 (用于声音提示)

## 💻 开发环境 / Development Environment

- **IDE**：Keil MDK-ARM v5
- **编译器**：ARMCC v5
- **调试器**：ST-Link V2
- **固件库**：STM32F10x标准外设库
- **版本控制**：Git + GitHub
- **文档工具**：Markdown + Draw.io (系统框图)

## 🚀 快速开始 / Quick Start

### 1. 克隆项目 / Clone Project
```bash
git clone https://github.com/HATSUNE-MIKU-CJE/smart-fan-stm32.git
cd smart-fan-stm32
```

### 2. 打开工程 / Open Project
- 使用Keil MDK打开 `Project.uvprojx`
- 确认器件选择为 `STM32F103C8`
- 配置正确的编译路径和头文件包含

### 3. 硬件连接 / Hardware Connection
```
STM32F103C8T6    外设模块
PB6 (SCL)  -----> OLED SCL
PB7 (SDA)  -----> OLED SDA
PA0        -----> 光敏电阻模拟输入
PA1        -----> DHT11数据线
PB0        -----> 按键1（向下导航）
PB10       -----> 按键2（向上导航）
PC13       -----> LED控制
3.3V       -----> 各模块VCC
GND        -----> 各模块GND
```

### 4. 编译与下载 / Build & Download
- 点击 `Build` 按钮编译项目
- 使用ST-Link连接开发板
- 点击 `Download` 下载程序到STM32
- 复位开发板查看运行效果

## 📊 使用说明 / Usage Instructions

### 基本操作 / Basic Operations
1. **上电启动**：系统显示欢迎界面3秒后进入主菜单
2. **菜单导航**：
   - 按键1：向下选择菜单项
   - 按键2：向上选择菜单项
3. **菜单页面**：
   - 主菜单：系统功能入口
   - 状态页面：显示传感器数据（开发中）
   - 风速设置：调节风扇速度（开发中）
   - 亮度调节：控制LED亮度（开发中）
   - 系统设置：系统参数配置（开发中）
   - 关于页面：项目信息展示

### 工作模式 / Working Modes
```
模式        描述
-------    -------------------------------------------------
监测模式    实时显示环境数据，不进行主动控制
自动模式    根据环境参数自动调节设备状态（开发中）
手动模式    用户通过按键手动控制各设备（开发中）
设置模式    调整系统参数和阈值设置（开发中）
```

## 🔧 技术细节 / Technical Details

### 核心模块 / Core Modules
- **菜单系统**：基于状态机的5页面菜单，支持滚动显示
- **按键驱动**：非阻塞式消抖，边沿检测算法
- **显示驱动**：OLED字符和字符串显示，支持居中算法
- **传感器驱动**：DHT11温湿度传感器、光敏电阻

### 设计模式 / Design Patterns
- **模块化设计**：各功能模块独立，高内聚低耦合
- **状态机设计**：菜单状态转换清晰，逻辑严谨
- **回调函数机制**：菜单项与功能实现解耦
- **分层架构**：硬件驱动→功能模块→应用层

### 关键参数 / Key Parameters
- 温度测量范围：0-50°C (±2°C精度)
- 光照检测范围：0-1024 (10位ADC，待实现)
- 按键消抖时间：20ms
- 菜单刷新频率：按需刷新，非定时刷新
- OLED分辨率：128×64

## 📈 项目进度 / Project Progress

| 日期 | 里程碑 | 状态 | 完成度 |
|------|--------|------|--------|
| 2026.01.30 | 项目初始化与Git配置 | ✅ 完成 | 100% |
| 2026.01.30 | 基础传感器驱动开发 | ✅ 完成 | 100% |
| 2026.01.30 | OLED显示系统实现 | ✅ 完成 | 100% |
| 2026.01.31 | OLED菜单系统开发 | ✅ 完成 | 100% |
| 2026.01.31 | 按键控制系统实现 | ✅ 完成 | 100% |
| 2026.02.01 | ADC学习与光敏传感器改造 | 🔄 进行中 | 20% |
| 2026.02.02 | 数据精度提升（精确数值显示） | ⏳ 待开始 | 0% |
| 2026.02.03 | PWM风扇控制集成 | ⏳ 待开始 | 0% |
| 2026.02.04 | 低功耗设计与系统优化 | ⏳ 待开始 | 0% |

### 当前重点 / Current Focus
- **学习ADC原理与应用**：系统掌握STM32 ADC模块
- **数据精度提升**：从定性显示升级到定量显示
- **代码优化**：提高系统稳定性和响应速度

## 🧪 测试与调试 / Testing & Debugging

### 已完成测试 / Completed Tests
- ✅ 各传感器驱动模块独立测试
- ✅ OLED显示功能验证
- ✅ 菜单系统基本功能测试
- ✅ 按键响应与消抖测试

### 待测试项目 / Pending Tests
- 🔄 数据采集精度校准
- 🔄 多传感器协同工作测试
- 🔄 系统稳定性压力测试
- 🔄 边界条件测试（极端温度/光照）

### 调试工具 / Debugging Tools
- STM32内置SWD调试接口
- 串口调试信息输出（预留接口）
- 逻辑分析仪（时序分析）
- 示波器（信号质量检查）

## 🎓 学习笔记 / Learning Notes

本项目开发过程中记录了详细的学习笔记，包含：

### 已记录内容
1. **项目规划与架构设计** - 如何设计嵌入式系统架构
2. **Git与版本控制实践** - 团队协作与代码管理
3. **模块化编程思想** - 高内聚低耦合的实现
4. **状态机设计模式** - 菜单系统的核心思想
5. **按键消抖算法** - 软件消抖与边沿检测

### 计划记录内容
1. **STM32 ADC原理与应用** - 模拟信号数字化
2. **传感器滤波算法** - 提高数据稳定性
3. **PWM控制原理** - 精确控制风扇转速
4. **低功耗设计** - 延长电池续航

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

## 📚 学习资源 / Learning Resources

### 官方文档 / Official Documentation
- [STM32F103参考手册](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [STM32标准外设库用户手册](https://www.st.com/resource/en/user_manual/cd00246267-stm32f10xxx-standard-peripheral-libraries-um1581-stmicroelectronics.pdf)
- [Keil MDK用户指南](http://www.keil.com/support/man/docs/uv4/uv4_cm_arm.htm)

### 教程资源 / Tutorial Resources
- 江科大STM32教程（Bilibili系列视频）- 强烈推荐
- STM32CubeMX官方教程
- ARM Cortex-M系列处理器权威指南

### 推荐书籍 / Recommended Books
- 《STM32库开发实战指南》
- 《ARM Cortex-M3与Cortex-M4权威指南》
- 《嵌入式C语言自我修养》

## 👨‍💻 作者信息 / Author Information
 
**Che Jiaen** - Xidian University  

- **专业**：探测制导与控制技术  
- **年级**：大二下学期  
- **GitHub**: [@HATSUNE-MIKU-CJE](https://github.com/HATSUNE-MIKU-CJE)  
- **邮箱**: 136163328@qq.com  
- **技能方向**: 嵌入式系统、C/C++编程、STM32开发、自动控制

### 学习目标 / Learning Goals
- 掌握嵌入式系统开发全流程
- 深入理解ARM Cortex-M架构
- 培养项目管理和团队协作能力
- 为全国大学生电子设计竞赛做准备

### 项目心得 / Project Insights
> "通过这个项目，我深刻理解了理论到实践的转化过程。从最初的点亮LED，到现在的完整菜单系统，每一步都充满挑战和收获。嵌入式开发不仅是写代码，更是对硬件、软件、算法和系统思维的综合考验。"

## 📄 许可证 / License

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 致谢 / Acknowledgments

- 感谢 **江科大** 的优质STM32教学视频，为我的学习之路打下坚实基础
- 感谢 **西安电子科技大学** 提供优良的学习环境和实验条件
- 感谢 **GitHub开源社区** 提供的丰富资源和工具
- 感谢所有给予我指导和帮助的老师和同学
- 特别感谢我的 **AI编程助手** 在技术实现上的耐心指导

---
**项目开始时间**：2026年1月  
**最后更新**：2026年1月31日  
**当前版本**：v0.2.0 (菜单系统版)  
**项目状态**：活跃开发中  

**Project Start Date**: January 2026  
**Last Updated**: January 31, 2026  
**Current Version**: v0.2.0 (Menu System Edition)  
**Project Status**: Active Development  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐

## 🔄 更新日志 / Changelog

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
```

## 🎯 **更新亮点**

1. **版本号管理**：添加了v0.2.0版本标识，方便跟踪进度
2. **进度透明**：明确展示了每个阶段的状态和完成度
3. **学习导向**：强调了"学习笔记"部分，体现学习过程
4. **技术深度**：增加了设计模式和架构说明
5. **用户体验**：详细说明了菜单操作方法
6. **未来规划**：区分短期和长期计划，更清晰
