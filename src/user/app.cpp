//
// Created by 99081 on 2026/2/7.
//

#include "app.h"
#include "task/timer.h"

uint8_t test_flag = 0;
// 定时器回调
void timer_callback() {
    test_flag = 1;
}


// 运行前初始化
void app_Init() {
    timer_task_init(true,timer_callback);  // 定时器任务初始化
}


// 霍尔传感器 控制 灯带、继电器
void app_Task() {
//    printf("app_Task\n");
    if(test_flag == 1){
        printf("app_Task\n");
        test_flag = 0;
    }
}