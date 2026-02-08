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
#define Relay_PIN           D9      // 继电器数字引脚
#define HallSensor_PIN      D8      // 霍尔传感器数字引脚

// ==================== 灯带配置 ====================
#define STRIP_COUNT         4       // 灯带数量
#define STRIP_NUM_LEDS      200     // 每条灯带 LED 数量
#define STRIP_BRIGHTNESS    250     // 灯带默认亮度
#define STRIP_COLOR_R       250     // 灯带固定颜色 R
#define STRIP_COLOR_G       40      // 灯带固定颜色 G
#define STRIP_COLOR_B       0       // 灯带固定颜色 B

// ==================== 定时器配置 ====================
#define TIMER_INTERVAL_MS   3000    // 变为正常模式的的定时器间隔

#endif //WISHINGTREE_GDATA_H
