#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Global variables assumed to be updated elsewhere
uint8_t G_DataID = 1;
int32_t G_DataValue = 10;

// Task Handles
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

// Queue Handle
QueueHandle_t Queue1;

// Structure for queue data
typedef struct {
    uint8_t dataID;
    int32_t DataValue;
} Data_t;

// Initial priority for Task2
#define TASK2_INITIAL_PRIORITY 2

// Flag to track if priority was increased
BaseType_t priorityIncreased = pdFALSE;

void ExampleTask1(void *pV) {
    Data_t data;

    const TickType_t delayTicks = pdMS_TO_TICKS(500);

    while (1) {
        data.dataID = G_DataID;
        data.DataValue = G_DataValue;

        xQueueSend(Queue1, &data, portMAX_DELAY);

        vTaskDelayUntil((TickType_t *)pV, delayTicks);
    }
}

void ExampleTask2(void *pV) {
    Data_t receivedData;
    UBaseType_t currentPriority = TASK2_INITIAL_PRIORITY;

    while (1) {
        if (xQueueReceive(Queue1, &receivedData, portMAX_DELAY) == pdPASS) {
            printf("Received -> dataID: %d, DataValue: %ld\n", receivedData.dataID, receivedData.DataValue);

            switch (receivedData.dataID) {
                case 0:
                    vTaskDelete(NULL); // Delete itself
                    break;

                case 1:
                    switch (receivedData.DataValue) {
                        case 0:
                            if (!priorityIncreased) {
                                currentPriority += 2;
                                vTaskPrioritySet(NULL, currentPriority);
                                priorityIncreased = pdTRUE;
                            }
                            break;

                        case 1:
                            if (priorityIncreased) {
                                currentPriority -= 2;
                                vTaskPrioritySet(NULL, currentPriority);
                                priorityIncreased = pdFALSE;
                            }
                            break;

                        case 2:
                            vTaskDelete(NULL); // Delete itself
                            break;

                        default:
                            // Process normally (nothing special to do)
                            break;
                    }
                    break;

                default:
                    // Unknown dataID
                    break;
            }
        }
    }
}

int main(void) {
    // Create the Queue
    Queue1 = xQueueCreate(5, sizeof(Data_t));
    if (Queue1 == NULL) {
        printf("Queue creation failed!\n");
        while (1);
    }

    // Create Task1 with lower priority
    TickType_t lastWakeTime = xTaskGetTickCount();
    xTaskCreate(ExampleTask1, "ExampleTask1", configMINIMAL_STACK_SIZE + 100, &lastWakeTime, 1, &TaskHandle_1);

    // Create Task2 with initial priority
    xTaskCreate(ExampleTask2, "ExampleTask2", configMINIMAL_STACK_SIZE + 100, NULL, TASK2_INITIAL_PRIORITY, &TaskHandle_2);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}
