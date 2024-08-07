#include <Arduino.h>
#include "main.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {

  esp_task_wdt_init(30, false);   //30초 워치독 리셋
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // 낮은 전원 검출 비활성화(재리셋 부팅 방지)
  getTick = xTaskGetTickCount();

  portSetup();
  uartSetup(BAUD);
  bleSetup();
  taskSetup();
  syncSetup();
  queueSetup(QEA);

  return x + y;
}

// put setup files
void portSetup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void uartSetup(unsigned long baud) {
  Serial.begin(baud);
}

int bleSetup() {
  if(!SerialBT.begin("DroneBTSeason4")) {
    Serial.println("Failed Bluetooth Initializing!!!");
    return -1;
  }
  else {
    Serial.println("Success Bluetooth Initializing!");
    return 0;
  }
}

void taskSetup() {
  xTaskCreatePinnedToCore(Task1Code, "Task1", 2048, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(Task2Code, "Task2", 2048, NULL, 1, &Task2, 0);
  xTaskCreatePinnedToCore(Task3Code, "Task3", 2048, NULL, 1, &Task3, 1);
  xTaskCreatePinnedToCore(Task4Code, "Task4", 2048, NULL, 1, &Task4, 1);
}

int queueSetup(uint8_t qEa) {
  queue = xQueueCreate(qEa, sizeof(int));
  if(queue == NULL) {
    Serial.println("Failed to create queue!!!");
    return -1;
  }
  else {
    Serial.println("queue created successfully!");
    return 0;
  }
}

int syncSetup() {
  mutex = xSemaphoreCreateMutex();
  if(mutex == NULL) {
    Serial.println("Failed to create mutex!!!");
    return -1;
  }
  else {
    Serial.println("Success to create mutex!");
    return 0;
  }
}
