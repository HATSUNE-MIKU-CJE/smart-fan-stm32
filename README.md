恭喜你成功完成 DHT22 温度检测升级！现在你的智能风扇不仅能显示全中文菜单，还能精确到小数点后一位的温度值。下面是为你更新后的 `README.md`，版本号提升至 **v0.8.0**，完整记录这两项重要里程碑。

---

```markdown
# STM32智能风扇控制系统  
# STM32 Smart Fan Control System  

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue)  
![Keil MDK](https://img.shields.io/badge/IDE-Keil_MDK-green)  
![C语言](https://img.shields.io/badge/Language-C-blue)  
![License](https://img.shields.io/badge/License-MIT-yellow)  
![Status](https://img.shields.io/badge/Status-Active_Development-orange)  
![Version](https://img.shields.io/badge/Version-v0.8.0-brightgreen)  
![Progress](https://img.shields.io/badge/Progress-95%25-green)

## 📖 项目简介 / Project Introduction

这是一个基于STM32的智能风扇控制系统，具备环境感知、智能调控和人机交互功能。这是我（西安电子科技大学大二学生）的第一个完整嵌入式项目，旨在通过实践掌握STM32开发全流程。

This is an intelligent fan control system based on STM32, featuring environmental sensing, intelligent regulation, and human-computer interaction. As a sophomore at Xidian University, this is my first complete embedded project, aiming to master the full development process of STM32 through practice.

## ✨ 当前功能 / Current Features

### ✅ 已实现功能 / Implemented

#### 🎮 **混合输入系统** (Hybrid Input System) - **v0.6.0**
- **EC11旋转编码器** - 精准旋钮输入，支持顺时针/逆时针检测  
  **EC11 Rotary Encoder** - Precise knob input with CW/CCW detection  
- **独立按键系统** - 3按键分离设计（确认/返回/模式切换）  
  **Independent Button System** - 3-button separate design (OK/Back/Mode)  
- **输入状态机管理** - 完整的消抖算法和非阻塞状态机架构  
  **Input State Machine Management** - Complete debouncing algorithm and non-blocking state machine architecture  

#### 📊 **传感器系统** (Sensor System)
- **光照强度检测** - ADC精确读取光敏电阻值，5档位自动判断（黑夜/微光/阴天/明亮/强光）  
  **Light Intensity Detection** - ADC precision reading with 5-level auto-detection (Black/Dim/Mild/Bright/Glare)  
- **🌡️ 高精度数字温度检测** - **v0.8.0 重大升级**：采用 DHT22 数字温湿度传感器，替代原热敏电阻，实现精确到 0.1℃ 的温度测量，湿度检测（预留）  
  **High-precision Digital Temperature Detection** - **v0.8.0 Major Upgrade**: Replaced thermistor with DHT22 digital sensor, achieving 0.1℃ precision temperature measurement, humidity detection (reserved)  
- **实时数据显示** - 光照档位、温度档位、**精确温度值（含小数点）**、AD值、电压值精准显示  
  **Real-time Data Display** - Light level, temperature level, **precise temperature with decimal**, AD value, voltage precision display  

#### 🈶 **全中文显示系统** - **v0.7.0 标志性功能**  
- **自研16×16点阵字库** - 包含30+常用汉字，实现全界面中文显示（主菜单、状态页、控制页等）  
  **Self-developed 16×16 Dot-matrix Font Library** - Over 30 common Chinese characters, enabling full Chinese UI (main menu, status page, control page, etc.)  
- **OLED驱动扩展** - 完美兼容I2C OLED，支持汉字与ASCII字符混合显示  
  **OLED Driver Extension** - Fully compatible with I2C OLED, supporting mixed display of Chinese and ASCII characters  

#### ⚡ **控制系统** (Control System)
- **PWM LED调光** - 基于TIM2_CH3实现LED亮度随光照自动变化  
  **PWM LED Dimming** - LED brightness auto-adjusts with light intensity via TIM2_CH3  
- **智能风扇控制** - 完整的温度自适应控制系统  
  **Smart Fan Control** - Complete temperature-adaptive control system  
  - **手动控制模式**：5档位PWM风速调节  
  **Manual Control Mode**: 5-level PWM speed adjustment  
  - **自动控制模式**：基于 DHT22 温度的6档位智能调速，温度响应更平滑  
  **Auto Control Mode**: 6-level intelligent speed adjustment based on DHT22 temperature, smoother response  
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
│   └── menu.c/h            # 菜单系统（非阻塞状态机，全中文显示）
├── Hardware/               # 硬件驱动层
│   ├── ad.c/h              # ADC驱动（光敏电阻）
│   ├── oled.c/h            # OLED显示驱动（支持中文点阵）
│   ├── light_sensor.c/h    # 光照传感器驱动（ADC版）
│   ├── rotary.c/h          # 旋转编码器驱动
│   ├── key.c/h             # 独立按键驱动（3按键）
│   ├── led.c/h             # LED控制驱动
│   ├── motor.c/h           # 电机驱动（PWM调速）
│   └── temperature_sensor.c/h # **DHT22数字温湿度传感器驱动（新增）**
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
1. Status          系统状态 - 显示传感器数据（光照、温度精确值）
2. Manual Control  手动控制 - PWM风扇5档位调节
3. Auto Mode       自动模式 - DHT22温度自适应控制
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
```c
STM32F103C8T6    外设模块
PB8 (SCL)  -----> OLED SCL
PB9 (SDA)  -----> OLED SDA
PA0        -----> 光敏电阻ADC输入（ADC0）
PA7        -----> **DHT22 数据线**（原热敏电阻已更换）
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
3.3V       -----> 各模块VCC（DHT22需上拉电阻4.7kΩ）
GND        -----> 各模块GND
```

### 电机驱动连接
```c
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
- **显示屏**：0.96寸OLED (SSD1306, I2C, 128×64分辨率，支持中文显示)
- **输入设备**：EC11旋转编码器 + 3个独立按键
- **光照传感器**：光敏电阻 + 10K分压电阻 (ADC通道0)
- **温度传感器**：**DHT22数字温湿度传感器**（单总线，精度±0.5℃，湿度可选）
- **电机驱动**：TB6612FNG双路电机驱动模块
- **电机**：直流减速电机（风扇驱动）

## 📈 技术实现 / Technical Implementation

### 核心算法 (Core Algorithms)

#### 1. 旋转编码器驱动算法（同 v0.6.0）

#### 2. DHT22 单总线驱动（新增）
```c
// DHT22 读取一位（基于状态机）
static uint8_t DHT22_ReadBit(void) {
    uint32_t timeout = 0;
    while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_RESET) {
        if (++timeout > 6000) return 0;  // 超时
    }
    Delay_us(40);  // 延时40μs判断位值
    if (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_SET) {
        while (GPIO_ReadInputDataBit(DHT22_GPIO_PORT, DHT22_GPIO_PIN) == Bit_SET);
        return 1;
    } else {
        return 0;
    }
}

// 读取温度湿度
uint8_t DHT22_Read(float *temperature, float *humidity) {
    // 主机复位、响应、读取40位、校验和解析
    // 返回1成功，0失败
}
```

#### 3. 温度控制算法（优化版）
```c
// 自动温度控制（基于DHT22精确温度）
void Motor_AutoControl(void) {
    static uint32_t last_update = 0;
    uint32_t now = GetTick();
    
    if(now - last_update >= 200) {  // 200ms更新一次
        float temp = TEMSensor_GetTemperature();  // 返回float精确值
        int8_t target_speed;
        
        // 温度-速度映射：线性关系（示例阈值）
        if (temp < 25.0f) target_speed = 0;
        else if (temp < 28.0f) target_speed = -20;
        else if (temp < 31.0f) target_speed = -40;
        else if (temp < 34.0f) target_speed = -60;
        else if (temp < 37.0f) target_speed = -80;
        else target_speed = -100;
        
        Motor_SetSpeed(target_speed);
        last_update = now;
    }
}
```

#### 4. 全中文显示（自研点阵字库）
```c
// OLED显示汉字（16x16点阵）
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t index) {
    // 从字库数组 Chinese_Font[][32] 中提取点阵数据
    // 发送到OLED GDDRAM
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
| 2026.02.05 | 旋转编码器输入系统重构（v0.6.0） | ✅ 完成 | 100% |
| 2026.02.11 | **全中文显示系统（v0.7.0）** | ✅ 完成 | 100% |
| 2026.02.21 | **DHT22数字温度检测升级（v0.8.0）** | ✅ 完成 | 100% |
| 2026.02.21 | 系统集成与优化 | 🔄 进行中 | 80% |

### 当前完成度：95%
- ✅ 用户交互系统：100%（旋钮+按键混合输入）
- ✅ 传感器数据采集：100%（光照 + DHT22温湿度）
- ✅ 全中文显示系统：100%（30+汉字，全界面覆盖）
- ✅ 执行器控制系统：100%
- 🔄 系统集成与优化：80%

## 🔄 更新日志 / Changelog

### v0.8.0 (2026-02-21) - DHT22精确温度升级版
#### 🎯 重大功能升级
- **温度传感器换代**：将热敏电阻（ADC）更换为 **DHT22数字温湿度传感器**，实现±0.5℃精度、0.1℃分辨率的温度测量
- **精确温度显示**：所有温度显示页面（系统状态、自动模式）均支持小数点后一位，如 `25.6℃`
- **温湿度解析**：完整实现DHT22单总线驱动，包含复位、响应、40位数据读取及校验和验证
- **共享缓存机制**：优化温度读取频率，确保1秒间隔限制，所有页面共享同一份缓存数据，避免反复读取

#### 🔧 技术改进
1. **驱动层重构**：`TemperatureSensor.c` 完全重写，基于GPIO模拟单总线时序，不再依赖ADC
2. **防抖与容错**：增加超时保护和读取失败保留上次有效值的机制，提升系统稳定性
3. **显示模块适配**：修改`Menu.c`中温度显示代码，支持浮点数转字符串显示
4. **代码注释完善**：为DHT22驱动添加详细中文注释，便于后续维护

#### 🐛 Bug修复
- 修复了温度小数位始终为0的问题（原因为整型接收浮点值）
- 解决了温度显示与档位对应温度不一致的问题（统一使用缓存）

### v0.7.0 (2026-02-11) - 全中文显示完整版
#### 🎯 标志性功能
- **全界面中文显示**：主菜单、状态页、控制页等所有文本均显示中文
- **自研16×16点阵字库**：手动构建30+常用汉字字模，集成到OLED驱动中
- **混合显示支持**：汉字与ASCII字符（数字、字母、符号）同屏显示
- **字库结构优化**：字模数据存储在Flash，节省RAM空间

### v0.6.0 (2026-02-05) - 旋转编码器输入系统版
（内容同前，略）

## 🧪 今日成果 / Today's Achievements (2026.02.21)

### 完成的任务
1. **DHT22驱动编写与调试**：成功实现单总线时序，稳定读取温度和湿度
2. **温度显示精确化**：修改菜单显示代码，温度值显示到小数点后一位（如 25.6℃）
3. **缓存机制设计**：为温度传感器添加全局缓存，所有页面共享同一份最新数据，避免频繁读取
4. **系统集成测试**：验证手动/自动模式下温度响应，确保风扇根据精确温度平滑调速

### 技术收获
- ✅ 深入理解单总线协议（One-Wire）的时序要求和编程技巧
- ✅ 掌握数字传感器驱动开发流程（复位、响应、数据读取、校验）
- ✅ 实践浮点数在嵌入式系统中的显示处理（整数和小数分离）
- ✅ 学会设计数据缓存和读取频率限制，提高系统健壮性

### 核心代码实现（片段）
```c
// 温度传感器统一缓存更新
static void UpdateSensorData(void) {
    uint32_t now = GetTick();
    if (now - last_read_time >= 1000) {
        float temp, humi;
        if (DHT22_Read(&temp, &humi)) {
            last_temperature = temp;
            last_humidity = humi;
            last_read_time = now;
        }
    }
}

// 对外接口：获取精确温度
float TEMSensor_GetTemperature(void) {
    UpdateSensorData();
    return last_temperature;
}
```


## 🚀 下一步计划 / Next Steps

### 近期功能开发（按优先级）
1. **湿度显示与利用**（1天）
   - 在状态页面增加湿度显示（如 `湿度: 56.2%`）
   - 可考虑湿度参与自动控制（例如舒适度调节）

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

## 📚 学习笔记摘要 / Learning Notes Summary

### DHT22 数字传感器要点
1. **单总线协议**：只有一根数据线，需严格遵循时序（复位、响应、数据0/1）
2. **上拉电阻必要**：DHT22 开漏输出，必须外接4.7kΩ上拉，否则通信失败（没有上拉电阻，只能暂时采用上拉输出）
3. **数据格式**：40位 = 16bit湿度 + 16bit温度 + 8bit校验和，温度最高位为符号位
4. **读取间隔**：至少1秒，否则传感器不响应或数据错误

### 中文显示实现技巧
1. **字模提取**：使用PCtoLCD2002软件生成16×16点阵数据
2. **存储优化**：字模数组存储在Flash，通过索引快速访问
3. **显示函数**：按字节将点阵数据发送到OLED，实现汉字显示

## 🐱 开发者心得 / Developer Insights

> "今天把温度传感器从热敏电阻升级到 DHT22，终于能看到精确到小数点后的温度值了！之前用 ADC 只能得到模糊的档位，现在不仅温度显示更专业，而且为后续湿度控制和智能场景打下了基础。通过这次升级，我对数字传感器的通信协议理解更深了，也学会了如何设计数据缓存来避免频繁读取。风扇项目越来越完善，离'产品级'又近了一步！下一步准备把湿度也用起来，让风扇更智能。" 

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
- STM32外设深入：ADC、PWM、定时器、GPIO中断、单总线协议
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

**项目开始时间**：2026年1月27日  
**最后更新**：2026年2月21日  
**当前版本**：v0.8.0 (DHT22精确温度升级版)  
**项目状态**：核心功能全部实现，进入系统优化阶段  
**预计完成时间**：2026年3月初  

**Project Start Date**: January 27, 2026  
**Last Updated**: February 21, 2026  
**Current Version**: v0.8.0 (DHT22 Precision Temperature Upgrade)  
**Project Status**: Core features fully implemented, entering system optimization phase  
**Estimated Completion**: Early March 2026  

⭐ **如果这个项目对你有帮助，请给个Star！你的支持是我前进的最大动力！** ⭐  
⭐ **If you find this project helpful, please give it a Star! Your support is my greatest motivation!** ⭐
```

---

**主要更新点说明：**
1. **版本升级**：从 v0.6.0 → v0.8.0（v0.7.0 中文显示 + v0.8.0 DHT22 升级）
2. **新增 DHT22 功能描述**：在传感器系统、控制系统、硬件连接中体现
3. **全中文显示**：作为 v0.7.0 的独立特性加入
4. **更新日志**：新增 v0.7.0 和 v0.8.0 详细记录
5. **项目进度**：更新里程碑，完成度提升至 95%
6. **今日成果**：体现 2026-02-21 的 DHT22 升级工作
7. **硬件连接**：PA7 用途改为 DHT22 数据线，并注明上拉电阻要求
8. **开发者心得**：反映今天调试的感受
9. **技术实现**：添加 DHT22 驱动代码片段和温度控制算法示例

现在你可以直接将这份内容覆盖你的 `README.md`，并提交到 GitHub 仓库。如果有任何需要调整的地方，随时告诉我！🎉🐱