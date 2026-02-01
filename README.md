## 📝 README.md 更新内容

```markdown
# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-Active_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.3.0-brightgreen)  
![Progress](https://img.shields.io/badge/Progress-55%25-green)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented

#### 🎮 **交互系统** (Interaction System)
- **OLED菜单系统** - 5页面可滚动菜单，基于状态机设计，支持居中标题和滚动提示  
  **OLED Menu System** - 5-page scrollable menu with state machine design, centered titles and scroll indicators
- **按键控制系统** - 3按键非阻塞式消抖（上/下/选择），边沿检测算法  
  **Button Control System** - 3-key non-blocking debouncing (up/down/select) with edge detection

#### 📊 **传感器系统** (Sensor System)
- **光照强度检测** - ADC精确读取光敏电阻值，5档位自动判断（黑夜/微光/阴天/明亮/强光）  
  **Light Intensity Detection** - ADC precision reading with 5-level auto-detection (Black/Dim/Mild/Bright/Glare)
- **温度湿度监测** - DHT11传感器数据读取（基础功能，待精度提升）  
  **Temperature & Humidity** - DHT11 sensor reading (basic function, precision to be improved)

#### 🖥️ **显示系统** (Display System)
- **系统状态页面** - 实时显示光照档位、AD值、电压值、温湿度占位符  
  **System Status Page** - Real-time display of light level, AD value, voltage, temperature & humidity
- **模块化显示驱动** - 支持字符、字符串、数字、16进制、二进制显示  
  **Modular Display Driver** - Support for char, string, number, hex, and binary display

### 🔄 开发中功能 / In Development
- **手动风扇控制** - PWM风速调节界面（框架已搭建）
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
│   └── menu.c/h            # 菜单系统（重构完成）
├── Hardware/               # 硬件驱动层
│   ├── ad.c/h              # ADC驱动（已实现）
│   ├── dht11.c/h           # 温湿度传感器驱动
│   ├── oled.c/h            # OLED显示驱动（已优化）
│   ├── light_sensor.c/h    # 光照传感器驱动（ADC版）
│   ├── key.c/h             # 按键驱动（3按键支持）
│   └── led.c/h             # LED控制驱动
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
PA9        -----> 按键1（Key1 - 向上）
PA11       -----> 按键2（Key2 - 向下）
PA15       -----> 按键3（Key3 - 选择/确认）
PC13       -----> LED状态指示
3.3V       -----> 各模块VCC
GND        -----> 各模块GND
```

### 硬件特性 (Hardware Specifications)
- **主控芯片**：STM32F103C8T6 (72MHz Cortex-M3, 64KB Flash, 20KB RAM)
- **显示屏**：0.96寸OLED (SSD1306, I2C, 128×64分辨率)
- **光照传感器**：光敏电阻 + 10K分压电阻 (ADC通道0)
- **温湿度传感器**：DHT11 (单总线协议)
- **按键**：3个轻触开关 (上/下/选择)

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

#### 2. 菜单状态机设计
- 状态：主菜单 → 子页面 → 返回主菜单
- 导航：上/下键滚动，选择键进入，选择键返回
- 显示：动态滚动，选中指示器(>)，滚动提示(^v)

#### 3. 按键消抖算法
- 边沿检测：检测下降沿触发
- 软件消抖：20ms延时确认
- 非阻塞设计：不影响主循环运行

### 关键参数 (Key Parameters)
- **ADC分辨率**：12位 (0-4095)
- **参考电压**：3.3V
- **光照档位**：5档 (基于实测阈值划分)
- **电压精度**：0.01V (两位小数显示)
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
| 2026.02.02 | PWM风扇控制学习 | 🔄 进行中 | 30% |
| 2026.02.03 | 风扇硬件电路设计与购买 | ⏳ 待开始 | 0% |
| 2026.02.04 | 系统整合与调试 | ⏳ 待开始 | 0% |

### 当前完成度：55%
- ✅ 用户交互系统：100%
- ✅ 传感器数据采集：80%
- 🔄 执行器控制系统：30%
- ⏳ 系统集成调试：0%

## 🔄 更新日志 / Changelog

### v0.3.0 (2026-02-01) - 菜单重构与ADC集成版
#### 🎯 主要更新
- **菜单系统重构**：重新设计5页面菜单结构（Status, Manual Control, Auto Mode, Settings, About）
- **ADC集成完成**：光照传感器从GPIO改为ADC读取，实现5档位自动判断
- **状态页面优化**：实时显示光照档位、AD值、电压值
- **按键系统修复**：修复选择键不工作的问题，优化按键检测逻辑
- **类型错误修复**：修复uint8_t接收ADC值导致的显示错误

#### 🐛 Bug修复
1. **按键初始化错误**：Key.c中lastKey3State赋值错误
2. **菜单选择逻辑**：Menu_Select函数缺少break语句
3. **数据类型错误**：ADC值用uint8_t接收导致截断
4. **显示返回问题**：子页面缺少Menu_Draw()调用

#### 📁 代码优化
- 移除冗余的Brightness页面，功能整合到Status
- 优化显示布局，提高信息密度
- 添加电压值精确显示（两位小数）
- 改进代码注释和结构

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

## 🧪 今日成果 / Today's Achievements

### 完成的任务
1. **ADC理论学习与实践**：掌握STM32 ADC配置，完成光敏电阻ADC读取
2. **光照档位设计**：实现5档位光照强度判断（漆黑/微光/柔和/明亮/强光）
3. **菜单系统重构**：优化菜单结构，移除冗余页面
4. **状态页面实现**：集成光照信息显示，支持实时更新
5. **Bug修复**：解决按键不工作和AD值显示异常问题

### 技术收获
- ✅ 掌握STM32 ADC配置流程
- ✅ 理解模拟信号到数字信号的转换原理
- ✅ 实践数据滤波和阈值判断算法
- ✅ 优化状态机设计，提高系统稳定性

## 🚀 下一步计划 / Next Steps

### 短期目标 (2月2-3日)
1. **PWM学习**：掌握STM32定时器PWM模式
2. **LED呼吸灯实验**：验证PWM控制功能
3. **风扇硬件准备**：确定元件规格并下单购买

### 中期目标 (2月4-5日)
1. **风扇驱动电路**：学习MOS管驱动原理
2. **手动控制实现**：PWM风扇多档位调节
3. **系统整合测试**：软硬件联调

### 长期目标
1. **自动控制模式**：温度-风速映射算法
2. **FreeRTOS集成**：多任务管理系统
3. **物联网扩展**：远程监控与控制

## 📚 学习笔记摘要 / Learning Notes Summary

### 今日学习要点
1. **ADC配置关键步骤**：
   - 时钟使能（ADC1、GPIOA、ADC时钟分频）
   - GPIO模式配置（模拟输入AIN）
   - 通道和采样时间设置
   - 校准流程（复位校准→开始校准）

2. **数据精度处理**：
   - 电压计算：`电压 = AD值 / 4095 * 3.3`
   - 类型选择：ADC值必须用uint16_t存储
   - 显示优化：浮点数转换为整数显示

3. **菜单设计原则**：
   - 功能分类清晰：监测、控制、设置、信息
   - 用户体验优先：减少按键次数，明确操作反馈
   - 扩展性考虑：为未来功能预留接口

## 🐱 开发者心得 / Developer Insights

> "今天解决了困扰已久的按键问题，发现很多时候bug就藏在细节里——一个变量的类型错误，一个忘记的break语句。嵌入式开发教会我：耐心调试，系统思考。从ADC理论到实际应用，从定性判断到定量显示，每一步都是进步。期待明天让风扇转起来！"

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
- STM32外设深入：ADC、PWM、定时器
- 嵌入式系统设计：模块化、状态机、实时系统
- 硬件电路设计：传感器接口、功率驱动

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
**最后更新**：2026年2月1日  
**当前版本**：v0.3.0 (菜单重构与ADC集成版)  
**项目状态**：活跃开发中  
**预计完成时间**：2026年2月10日  

**Project Start Date**: January 2026  
**Last Updated**: February 1, 2026  
**Current Version**: v0.3.0 (Menu Reconstruction & ADC Integration)  
**Project Status**: Active Development  
**Estimated Completion**: February 10, 2026  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐
```

## 🎯 README更新亮点

### 1. **版本升级**：v0.2.0 → v0.3.0
- 体现重要的功能重构和Bug修复

### 2. **进度可视化**：
- 添加进度条：55%完成
- 更新进度表格，标记今日成果

### 3. **技术细节丰富**：
- 详细描述ADC配置和光照档位算法
- 展示硬件连接图和参数

### 4. **今日成果突出**：
- 单独列出今日完成的任务和技术收获
- 包含开发者心得，体现学习过程

### 5. **下一步计划明确**：
- 分短期/中期/长期目标
- 与你的学习计划对齐

### 6. **学习笔记集成**：
- 总结今日学习要点
- 为其他学习者提供参考