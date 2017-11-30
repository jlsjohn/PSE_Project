/* Very basic example to test the pwm library
 * Hook up an LED to pin14 and you should see the intensity change
 *
 * Part of esp-open-rtos
 * Copyright (C) 2015 Javier Cardona (https://github.com/jcard0na)
 * BSD Licensed as described in the file LICENSE
 */
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stepper.h"
#include "esp8266.h"


void task1(void *pvParameters)
{
    printf("Hello from task1!\r\n");
    uint32_t const init_count = 0;
    while(1) {
        vTaskDelay(1000);
    	stepper_open();
    	stepper_close();
    }
}

void user_init(void)
{
    //uint8_t pins[1];
    uart_set_baud(0, 115200);

    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    stepper_set_speed(100);
    stepper_step(25);
    stepper_init(10, 20, 30, 40);

    stepper_set_angle(90);
    stepper_open();
    stepper_close();

    xTaskCreate(task1, "tsk1", 256, NULL, 2, NULL);
}
