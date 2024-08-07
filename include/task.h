#ifndef _TASK_H
#define _TASK_H

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "BluetoothSerial.h"
#include "defines.h"

extern TickType_t getTick;
extern BluetoothSerial SerialBT;
extern QueueHandle_t queue;
extern SemaphoreHandle_t mutex;

int qCnt = 0;

const char *messages[10] = {
    "Message 1", "Message 2", "Message 3", "Message 4", "Message 5",
    "Message 6", "Message 7", "Message 8", "Message 9", "Message 10"
};

// put functions of tasks here
void Task1Code(void *pvParameters);
void Task2Code(void *pvParameters);
void Task3Code(void *pvParameters);
void Task4Code(void *pvParameters);

#endif  //_TASK_H END