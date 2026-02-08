//
// 全局对象管理 - 集中管理所有外设实例
//

#ifndef WISHINGTREE_GOBJECT_H
#define WISHINGTREE_GOBJECT_H

#include "GData.h"
#include "seeed/grove/ws2813_ring.h"
#include "seeed/grove/relay.h"
#include "seeed/grove/hall_sensor.h"

// ==================== 全局对象集合 ====================
extern WS2813Ring strip0;
extern WS2813Ring strip1;
extern WS2813Ring* strips[STRIP_COUNT];

extern HallSensor hallSensor0;
extern Relay relay0;

#endif // WISHINGTREE_GOBJECT_H
