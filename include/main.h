#ifndef _MAIN_H
#define _MAIN_H

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include "BluetoothSerial.h"
#include "defines.h"

TickType_t getTick;

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;

QueueHandle_t queue;
SemaphoreHandle_t mutex;
BluetoothSerial SerialBT;

// put setup files
void portSetup();
void uartSetup(unsigned long baud);
int bleSetup();
void taskSetup();
int queueSetup(uint8_t qEa);
int syncSetup();

// put functions of tasks here
extern void Task1Code(void *pvParameters);
extern void Task2Code(void *pvParameters);
extern void Task3Code(void *pvParameters);
extern void Task4Code(void *pvParameters);

#endif  //_MAIN_H END
