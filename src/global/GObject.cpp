//
// 全局对象管理实现
//

#include "GObject.h"

// 4条灯带实例
WS2813Ring strip0(StripLight_PIN_0, STRIP_NUM_LEDS);
WS2813Ring strip1(StripLight_PIN_1, STRIP_NUM_LEDS);
WS2813Ring* strips[STRIP_COUNT] = {&strip0, &strip1};

// 霍尔传感器
HallSensor hallSensor0(HallSensor_PIN);

// 继电器
Relay relay0(Relay_PIN);
