#ifndef _DEFINES_H
#define _DEFINES_H

#define QEA 10
#define BAUD 115200
// 내장 LED 핀 번호 (ESP32 보드에서는 대개 GPIO 2)
const int ledPin = 2;

// Task TICK Time (1msec) define
const TickType_t vPeriodicTaskPeriod = 1 / portTICK_PERIOD_MS;

#endif  //_DEFINE_H END
