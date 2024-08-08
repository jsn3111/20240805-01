/*
4개의 타스크 함수들 정의
1.Task1Code : 블루투스로부터 수신/파싱
2.Task2Code : 블루투스로 송신
3.Task3Code : 큐 문자열 메세지 송신
4.Task4Code : 큐 문자열 메세지 수신
*/
#include "task.h"

void Task1Code(void *pvParameters) {
    uint32_t ledDly = 0;
    uint32_t task1Dly = 0;

    for(;;) {
        vTaskDelay(1 / portTICK_PERIOD_MS);
        // xTaskDelayUntil(&getTick, vPeriodicTaskPeriod);

        ledDly++;
        if(ledDly == 500) {
            digitalWrite(ledPin, HIGH);
        }
        else if(ledDly >= 1000) {
            digitalWrite(ledPin, LOW);
            ledDly = 0;
        }

        //smartphone message will be received by pc
        if (SerialBT.available() > 0) {
            String data = SerialBT.readStringUntil('\n');
            Serial.print("Received from Bluetooth: ");
            Serial.println(data);
        }
    }
}

void Task2Code(void *pvParameters) {
    uint32_t task2Dly = 0;

    for(;;) {
        vTaskDelay(1 / portTICK_PERIOD_MS);
        // xTaskDelayUntil(&getTick, vPeriodicTaskPeriod);

        task2Dly++;
        // PC로부터 ESP32가 수신한 문자열을 블루투스 통신으로 전송하겠다.
        if (Serial.available() > 0) {
            String data = Serial.readStringUntil('\n');
            SerialBT.print(data + "\n");
        }
    }
}

void Task3Code(void *pvParameters) {
    uint32_t task3Dly = 0;
    int index = 0;

    for(;;) {
        vTaskDelay(1 / portTICK_PERIOD_MS);
        // xTaskDelayUntil(&getTick, vPeriodicTaskPeriod);

        task3Dly++;
        if(task3Dly >= 1000) {
            task3Dly = 0;
            esp_task_wdt_init(30, false);   //30초 워치독 리셋
            if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
                xSemaphoreGive(mutex);
                if(xQueueSend(queue, &messages[index], portMAX_DELAY) != pdPASS) {
                    Serial.println("Failed to send to queue!!!");
                }
                else {
                    // SerialBT.print(messages[index]);
                    Serial.print("Send to queue :     ");
                    Serial.println(messages[index]);
                }
                index = (index + 1) % 10;   //다음 메시지로 이동
            }
        }
    }
}

void Task4Code(void * pvParameters) {
    uint32_t task4Dly = 0;
    const char *rcvmsg;

    for(;;) {
        vTaskDelay(1 / portTICK_PERIOD_MS);
        // xTaskDelayUntil(&getTick, vPeriodicTaskPeriod);

        if(xQueueReceive(queue, &rcvmsg, portMAX_DELAY) == pdPASS) {
            if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
                Serial.print("Received QueueMsg : ");
                Serial.println(rcvmsg);
                xSemaphoreGive(mutex);
            }
        }
    }
}
