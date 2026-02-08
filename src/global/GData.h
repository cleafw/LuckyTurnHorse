//
// Created by 99081 on 2026/2/6.
//

#ifndef WISHINGTREE_GDATA_H
#define WISHINGTREE_GDATA_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// ==================== 引脚定义 ====================
#define StripLight_PIN_0    D0      // 灯带 0 数据引脚
#define StripLight_PIN_1    D1      // 灯带 1 数据引脚
#define StripLight_PIN_2    D2      // 灯带 2 数据引脚
#define StripLight_PIN_3    D5      // 灯带 3 数据引脚
#define Relay_PIN           D9      // 继电器数字引脚
#define HallSensor_PIN      D8      // 霍尔传感器数字引脚

// ==================== 灯带配置 ====================
#define STRIP_COUNT         4       // 灯带数量
#define STRIP_NUM_LEDS      200     // 每条灯带 LED 数量
#define STRIP_BRIGHTNESS    250     // 灯带默认亮度 (0-255)
#define STRIP_COLOR_R       255      // 灯带固定颜色 R
#define STRIP_COLOR_G       255     // 灯带固定颜色 G
#define STRIP_COLOR_B       51       // 灯带固定颜色 B

// ==================== 交互模式配置 ====================
#define MAX_HALL_TRIGGERS   8       // 完全点亮所需的霍尔触发次数
#define TIMEOUT_MS          5000    // 超时时间（5秒）

// ==================== 系统状态 ====================
enum SystemState {
    STATE_NORMAL,       // 正常状态：常亮，继电器打开
    STATE_INTERACTIVE   // 交互状态：根据霍尔信号进度点亮，初始继电器关闭
};

#endif //WISHINGTREE_GDATA_H
