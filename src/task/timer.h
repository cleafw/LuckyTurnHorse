//
// 定时器模块头文件
//

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// 定时器间隔（毫秒）
#define TIMER_INTERVAL_MS 1000

// 定义回调函数类型
typedef void (*TimerCallback)(void);

// 定时器初始化函数
// 参数: callback - 定时器触发时的回调函数（可选）
void timer_task_init(bool start = false, TimerCallback callback = NULL);

// 停止定时器
void timer_stop();

// 启动定时器
void timer_start();

// 设置定时器周期（微秒）
void timer_set_period(uint32_t microseconds);

#endif // TIMER_H