#include "Arduino.h"
#include "input-config/input-config.h"
#include "output-config/output-config.h"

TaskHandle_t logicTaskHandle = NULL;
TaskHandle_t relayTaskHandle = NULL;

typedef struct
{
    uint8_t relayIndex;
    bool turnOn;
} RelayCommand;

void InputTask(void *pvParameters)
{
    while (true)
    {
        for (int i = 0; i < MAX_INPUT; i++)
        {
            IN_Pin[i].Poll();

            if (IN_Pin[i].change)
            {
                IN_Pin[i].change = 0;

                Serial.print(IN_Pin[i].inname);
                Serial.print(" changed: ");
                Serial.println(IN_Pin[i].current);

             
                xTaskNotify(logicTaskHandle, i, eSetValueWithOverwrite);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


void LogicTask(void *pvParameters)
{
    uint32_t inputIndex;
    RelayCommand cmd;

    while (true)
    {
        xTaskNotifyWait(0, 0, &inputIndex, portMAX_DELAY);

       
        cmd.relayIndex = inputIndex;

     
        cmd.turnOn = IN_Pin[inputIndex].current;

       
        xTaskNotify(relayTaskHandle, *(uint32_t *)&cmd, eSetValueWithOverwrite);
    }
}

void RelayTask(void *pvParameters)
{
    RelayCommand cmd;

    while (true)
    {
        xTaskNotifyWait(0, 0, (uint32_t *)&cmd, portMAX_DELAY);

        if (cmd.relayIndex < MAX_OUTPUT)
        {
            if (cmd.turnOn)
            {
                OutRelay[cmd.relayIndex].on();
                Serial.printf("Relay %d ON\n", cmd.relayIndex);
            }
            else
            {
                OutRelay[cmd.relayIndex].off();
                Serial.printf("Relay %d OFF\n", cmd.relayIndex);
            }
        }
    }
}

extern "C" void app_main(void)
{
    initArduino();
    Serial.begin(115200);

    xTaskCreate(RelayTask, "RelayTask", 4096, NULL, 3, &relayTaskHandle);
    xTaskCreate(LogicTask, "LogicTask", 4096, NULL, 2, &logicTaskHandle);
    xTaskCreate(InputTask, "InputTask", 4096, NULL, 1, NULL);
}
