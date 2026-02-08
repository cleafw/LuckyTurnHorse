//
// 定时器模块实现
//

#include "timer.h"

// 定时器句柄
hw_timer_t *timer = NULL;

// 回调函数指针（使用正确的类型）
static TimerCallback timerCallback = NULL;

// 定时器中断服务函数
void IRAM_ATTR onTimer() {
    // 如果注册了回调函数，则调用
    if (timerCallback != NULL) {
        timerCallback();
    }
}

// 定时器任务初始化
void timer_task_init(bool start, TimerCallback callback) {
    // 保存回调函数
    if (callback != NULL) {
        timerCallback = callback;
        Serial.println("已注册定时器回调函数");
    }

    // 初始化定时器
    // 参数: 定时器编号(0-1), 分频器, 计数方向(true=向上计数)
    timer = timerBegin(0, 80, true);

    // 绑定中断函数
    // 参数: 定时器句柄, 中断函数, 边沿触发(true)
    timerAttachInterrupt(timer, &onTimer, true);

    // 设置定时器周期
    // 参数: 定时器句柄, 计数值, 自动重载(true)
    // 计数值 = 1000*TIMER_INTERVAL_MS 微秒
    timerAlarmWrite(timer, 1000 * TIMER_INTERVAL_MS, true);

    // 启动定时器
    if (start) {
        timer_start();
    }
}

// 停止定时器
void timer_stop() {
    if (timer != NULL) {
        timerAlarmDisable(timer);
        Serial.println("定时器已停止");
    }
}

// 启动定时器
void timer_start() {
    if (timer != NULL) {
        timerAlarmEnable(timer);
        Serial.println("定时器已启动");
    }
}

// 设置定时器周期（微秒）
void timer_set_period(uint32_t microseconds) {
    if (timer != NULL) {
        timerAlarmWrite(timer, microseconds, true);
        Serial.printf("定时器周期已设置为: %d us\n", microseconds);
    }
}