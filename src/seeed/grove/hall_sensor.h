//
// Grove 霍尔传感器驱动头文件
// 型号: Grove - Hall Sensor
// 工作电压: 3.3V - 5V
// 接口: 数字输入，检测到磁场时输出低电平 (LOW)
// 检测范围: 南极磁场触发
//

#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <Arduino.h>

class HallSensor {
private:
    uint8_t hallPin;        // 数字输入引脚
    bool    lastState;      // 上一次状态（用于边沿检测）

public:
    // 构造函数
    explicit HallSensor(uint8_t pin);

    // 初始化
    void begin();

    // 读取当前磁场检测状态: true = 检测到磁场, false = 未检测到磁场
    bool isDetected();

    // 检测是否刚检测到磁场（下降沿），需要在循环中持续调用
    bool onDetected();

    // 检测是否磁场刚消失（上升沿），需要在循环中持续调用
    bool onLost();
};

#endif // HALL_SENSOR_H
