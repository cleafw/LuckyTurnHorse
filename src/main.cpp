#include <Arduino.h>
#include "seeed/grove/ws2813_ring.h"
#include "global/GData.h"
#include "global/GObject.h"
#include "user/app.h"


void setup() {
    Serial.begin(115200);

    app_Init();    // 初始化
}

void loop() {
    app_Task();     // 业务任务
}