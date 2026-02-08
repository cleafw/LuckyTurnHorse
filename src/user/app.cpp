//
// Created by 99081 on 2026/2/7.
//

#include "app.h"
#include "task/timer.h"

// ==================== 全局状态变量 ====================
SystemState currentState = STATE_NORMAL;    // 当前系统状态
volatile bool timeoutFlag = false;          // 定时器超时标志
uint8_t hallTriggerCount = 0;               // 霍尔触发计数（1-8）

// 内部函数（可选声明）
void handleHallTrigger();
void enterInteractiveState();
void enterNormalState();
void updateProgress();
void handleTimeout();

// ==================== 定时器回调 ====================
void timer_callback() {
    timeoutFlag = true;  // 仅设置标志位，不做其他操作
}
//灯带测试
void strips_Test() {
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->setBrightness(STRIP_BRIGHTNESS);
        strips[i]->fillColor(STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        strips[i]->show();

        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(255, 0, 0);
            strips[i]->show();
        }
        delay(1000);

        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(0, 255, 0);
            strips[i]->show();
        }
        delay(1000);
        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(0, 0, 255);
            strips[i]->show();
        }
        delay(1000);

        for(int n = 0; n < STRIP_NUM_LEDS; n ++){
            for(int i = 0; i < STRIP_COUNT; i ++){
                strips[i]->setPixelColor(n, 255, 255, 255);
                strips[i]->show();
            }
            delay(50);
        }
        delay(1000);
    }
}

//霍尔传感器测试
void hall_Sensor_Test() {
    while (1) {
        if (hallSensor.isDetected()) {
            Serial.println("Hall Sensor Detected");
        }
        delay(100);
    }
}

//继电器测试
void relay_Test() {
    while (1) {
        relay.on();
        delay(1000);
        relay.off();
        delay(1000);
    }
}

// ==================== 处理霍尔触发 ====================
void handleHallTrigger() {
    Serial.println("\n>>> 检测到霍尔信号");

    // 情况1: 当前在正常状态 → 进入交互状态
    if (currentState == STATE_NORMAL) {
        enterInteractiveState();
        return;
    }

    // 情况2: 当前在交互状态 → 增加计数
    if (currentState == STATE_INTERACTIVE) {
        if (hallTriggerCount < MAX_HALL_TRIGGERS) {
            hallTriggerCount++;
            updateProgress();

            // 重启定时器（重新计时）
            timer_restart();
            timeoutFlag = false;

            Serial.printf("定时器已重启，重新计时 %d 秒\n", TIMEOUT_MS / 1000);
        } else {
            Serial.println("已达到最大次数(8/8)，忽略此信号");
        }
    }
}

// ==================== 进入交互状态 ====================
void enterInteractiveState() {
    Serial.println("\n========== 进入交互状态 ==========");

    currentState = STATE_INTERACTIVE;
    hallTriggerCount = 0;
    timeoutFlag = false;

    // 关闭继电器
    relay.off();
    Serial.println("继电器: 关闭");

    // 清空灯带
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->clear();
        strips[i]->show();
    }
    Serial.println("灯带: 清空");

    // 启动定时器
    timer_restart();
    Serial.printf("定时器: 已启动 (%d 秒倒计时)\n", TIMEOUT_MS / 1000);

    Serial.println("等待霍尔信号...");
    Serial.println("=====================================\n");
}

// ==================== 更新进度 ====================
void updateProgress() {
    // 计算应该点亮的LED数量
    uint16_t ledsToLight = (STRIP_NUM_LEDS * hallTriggerCount) / MAX_HALL_TRIGGERS;

    Serial.printf("进度: %d/%d (点亮 %d/%d 个LED)\n",
                  hallTriggerCount, MAX_HALL_TRIGGERS,
                  ledsToLight, STRIP_NUM_LEDS);

    // 更新所有灯带
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->clear();
        for (uint16_t j = 0; j < ledsToLight; j++) {
            strips[i]->setPixelColor(j, STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        }
        strips[i]->show();
    }

    // 检查是否完成（8/8）
    if (hallTriggerCount >= MAX_HALL_TRIGGERS) {
        Serial.println("\n!!! 进度完成 8/8 !!!");
        Serial.println("继电器: 打开");
        relay.on();
        Serial.println();
    }
}

// ==================== 处理超时 ====================
void handleTimeout() {
    timeoutFlag = false;

    Serial.println("\n========== 超时 ==========");
    Serial.printf("%d秒内无霍尔信号 (当前进度: %d/%d)\n",
                  TIMEOUT_MS / 1000,
                  hallTriggerCount, MAX_HALL_TRIGGERS);
    Serial.println("返回正常状态...");
    Serial.println("===========================\n");

    enterNormalState();
}

// ==================== 进入正常状态 ====================
void enterNormalState() {
    Serial.println("\n--- 进入正常状态 ---");

    currentState = STATE_NORMAL;
    hallTriggerCount = 0;
    timeoutFlag = false;

    // 停止定时器
    timer_stop();
    Serial.println("定时器: 已停止");

    // 打开继电器
    relay.on();
    Serial.println("继电器: 打开");

    // 灯带全亮
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->fillColor(STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        strips[i]->show();
    }
    Serial.println("灯带: 全亮\n");
}

/// ==================== 初始化 ====================
void app_Init() {
    Serial.begin(115200);
    delay(100);

    Serial.println("\n=== 系统初始化 ===");

//     1. 初始化灯带
    Serial.println("[1/4] 初始化灯带...");
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->begin();
        strips[i]->setBrightness(STRIP_BRIGHTNESS);
        Serial.printf("  灯带 %d 初始化完成\n", i);
    }

    // 2. 初始化霍尔传感器
    Serial.println("[2/4] 霍尔传感器已就绪");

    // 3. 初始化继电器
    Serial.println("[3/4] 继电器已就绪");

    // 4. 初始化定时器（5秒超时）
    timer_task_init(TIMEOUT_MS, timer_callback);
    Serial.printf("[4/4] 定时器已初始化 (超时: %d ms)\n", TIMEOUT_MS);

    // 5. 进入正常状态
    Serial.println("\n--- 进入正常状态 ---");
    currentState = STATE_NORMAL;
    hallTriggerCount = 0;
    timeoutFlag = false;

    relay.on();
    Serial.println("继电器: 打开");

    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->fillColor(STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        strips[i]->show();
    }
    Serial.println("灯带: 全亮");

    Serial.println("\n=== 初始化完成 ===\n");
}

/// ==================== 主任务循环 ====================
void app_Task() {
    app_Init();
    for(;;){
        static bool lastHallState = false;

        // 1. 检测霍尔传感器（边沿检测）
        bool currentHallState = hallSensor.isDetected();

        if (currentHallState && !lastHallState) {
            // 检测到霍尔信号（下降沿）
            handleHallTrigger();
        }

        lastHallState = currentHallState;

        // 2. 在交互状态下检查超时
        if (currentState == STATE_INTERACTIVE && timeoutFlag) {
            handleTimeout();
        }

        delay(10);
    }

}

// 业务任务
//void app_Task() {
//    strips_Test();  // 灯带测试
//    hall_Sensor_Test();  // 霍尔传感器测试
//    relay_Test();   // 继电器测试
//    delay(1000); // 延时1秒
//}