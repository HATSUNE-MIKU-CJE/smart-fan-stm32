# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-In_Development-orange)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented
- **温度监测与显示** - 通过DHT11传感器实时监测环境温度，并在OLED上显示  
  **Temperature Monitoring & Display** - Real-time monitoring via DHT11 sensor with OLED display
- **光照强度检测** - 通过光敏电阻检测环境光照强度，自动控制LED开关  
  **Light Intensity Detection** - Automatic LED control based on ambient light via photoresistor
- **阈值比较功能** - 实时比较温度/光照与预设阈值，通过OLED状态提示  
  **Threshold Comparison** - Real-time comparison with preset thresholds, status indicated on OLED
- **人机交互界面** - 清晰的OLED显示界面，展示实时数据和系统状态  
  **Human-Machine Interface** - Clear OLED display showing real-time data and system status

### 🔄 计划功能 / Planned Features
- PWM风扇速度控制（手动/自动模式）
- 多传感器数据融合（温湿度、光照、PM2.5）
- FreeRTOS多任务管理
- Wi-Fi远程监控与控制
- 手机APP/Web控制界面
- 数据日志存储与导出

## 📁 项目结构 / Project Structure

```
smart-fan-stm32/
├── User/                    # 用户应用代码
│   ├── main.c              # 主程序入口
│   ├── fan_control.c/h     # 风扇控制逻辑
│   └── ui_manager.c/h      # 用户界面管理
├── System/                 # 系统配置
│   ├── delay.c/h           # 延时函数
│   ├── sys.c/h             # 系统初始化
│   └── usart.c/h           # 串口通信
├── Hardware/               # 硬件驱动
│   ├── dht11.c/h           # 温湿度传感器驱动
│   ├── oled.c/h            # OLED显示驱动
│   ├── light_sensor.c/h    # 光照传感器驱动
│   └── led.c/h             # LED控制驱动
├── Library/                # 库文件
│   └── STM32F10x_StdPeriph_Driver/  # STM32标准外设库
├── Start/                  # 启动文件
├── DebugConfig/            # 调试配置
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
1. **上电启动**：系统自动初始化，OLED显示欢迎界面
2. **数据监测**：实时显示温度和光照数据
3. **阈值提示**：当前数据超过预设阈值时，OLED显示相应提示
4. **自动控制**：光照不足时自动开启LED补光

### 工作模式 / Working Modes
```
模式        描述
-------    -------------------------------------------------
监测模式    实时显示环境数据，不进行主动控制
自动模式    根据环境参数自动调节设备状态
手动模式    用户通过按键手动控制各设备
设置模式    调整系统参数和阈值设置
```

## 🔧 技术细节 / Technical Details

### 主要算法 / Main Algorithms
- **滑动平均滤波**：用于传感器数据平滑处理
- **状态机设计**：管理系统工作模式和状态转换
- **阈值判断逻辑**：多级阈值触发不同响应
- **模块化设计**：各功能模块独立，便于扩展和维护

### 关键参数 / Key Parameters
- 温度测量范围：0-50°C (±2°C精度)
- 光照检测范围：0-1024 (10位ADC)
- 温度阈值：25°C (默认)
- 光照阈值：300 (默认)
- 采样频率：2Hz (每500ms采样一次)

## 📈 项目进度 / Project Progress

| 日期 | 里程碑 | 状态 | 完成度 |
|------|--------|------|--------|
| 2026.01.30 | 项目初始化与Git配置 | ✅ 完成 | 100% |
| 2026.01.30 | 基础传感器驱动开发 | ✅ 完成 | 100% |
| 2026.01.30 | OLED显示系统实现 | ✅ 完成 | 100% |
| 2026.01.31 | PWM风扇控制集成 | 🔄 进行中 | 40% |
|2026.02.05  | 实时温度与光强检测 | ⏳ 待开始 | 0% |
| 2026.02.05 | 多模式控制系统 | ⏳ 待开始 | 0% |
| 2026.02.10 | FreeRTOS移植 | ⏳ 待开始 | 0% |
| 2026.02.15 | Wi-Fi远程控制 | ⏳ 待开始 | 0% |

## 🧪 测试与调试 / Testing & Debugging

### 单元测试 / Unit Tests
- 各传感器驱动模块独立测试
- OLED显示功能验证
- 数据采集精度校准

### 集成测试 / Integration Tests
- 多传感器协同工作测试
- 系统稳定性压力测试
- 边界条件测试（极端温度/光照）

### 调试工具 / Debugging Tools
- STM32内置SWD调试接口
- 串口调试信息输出
- 逻辑分析仪（时序分析）
- 示波器（信号质量检查）

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
- 江科大STM32教程（Bilibili系列视频）

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

## 📄 许可证 / License

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 致谢 / Acknowledgments

- 感谢 **江科大** 的优质STM32教学视频
- 感谢 **西安电子科技大学** 提供优良的学习环境
- 感谢开源社区提供的丰富资源和工具
- 感谢所有给予我指导和帮助的老师和同学

---
**项目开始时间**：2026年1月  
**最后更新**：2026年1月30日  
**项目状态**：活跃开发中  

**Project Start Date**: January 2026  
**Last Updated**: January 30, 2026  
**Project Status**: Active Development  

⭐ **如果这个项目对你有帮助，请给个Star！** ⭐  
⭐ **If you find this project helpful, please give it a Star!** ⭐
