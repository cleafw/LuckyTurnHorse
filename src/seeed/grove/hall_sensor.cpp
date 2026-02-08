//
// Grove 霍尔传感器驱动实现
//

#include "hall_sensor.h"

HallSensor::HallSensor(uint8_t pin)
        : hallPin(pin), lastState(false) {
    begin();
}

void HallSensor::begin() {
    // ✅ 使用 INPUT_PULLUP 模式，防止引脚悬空
    pinMode(hallPin, INPUT_PULLUP);
    lastState = isDetected();
}

bool HallSensor::isDetected() {
    // 霍尔传感器检测到磁场时输出 LOW，因此需要反转逻辑
    return digitalRead(hallPin) == LOW;
}

bool HallSensor::onDetected() {
    bool current = isDetected();
    bool detected = (current && !lastState);
    lastState = current;
    return detected;
}

bool HallSensor::onLost() {
    bool current = isDetected();
    bool lost = (!current && lastState);
    lastState = current;
    return lost;
}