/* Very basic example to test the pwm library
 * Hook up an LED to pin14 and you should see the intensity change
 *
 * Part of esp-open-rtos
 * Copyright (C) 2015 Javier Cardona (https://github.com/jcard0na)
 * BSD Licensed as described in the file LICENSE
 */
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "espressif/esp_wifi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stepper.h"
#include "esp8266.h"


void task1(void *pvParameters)
{
    while(1) {
        vTaskDelay(1000);
    	valve_open();
    	valve_close();
    }
}

void user_init(void)
{
    //Desabilitando wifi
    sdk_wifi_set_opmode(NULL_MODE);
    uart_set_baud(0, 115200);

    //Inicializando a pinaem da válvula
    valve_init(PIN_01, PIN_02, PIN_03, PIN_04);

    //Seta velocidade de abertura da válvula
    valve_set_speed(30);

    //private function test
    valve_step(25,RIGHT);
    valve_step(25,LEFT);
    //private function test

    //Abre a válvula
    valve_open();

    //Posiciona a válvula no anulo escolhido
    valve_set_angle(90);

    //Fecha a válvula
    valve_close();

    xTaskCreate(task1, "tsk1", 256, NULL, 2, NULL);
}
