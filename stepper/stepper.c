#include "stepper.h"

#include <espressif/esp_common.h>
#include <espressif/sdk_private.h>
#include <FreeRTOS.h>
#include <esp8266.h>

// typedef struct stepperPinDefinition
// {
//     uint8_t pin;
//     uint8_t divider;
// } stepperPin;

typedef union{
  uint8_t data[6];
  struct{
    unsigned int bitPin1 : 1;
    unsigned int bitPin2 : 1;
    unsigned int bitPin3 : 1;
    unsigned int bitPin4 : 1;
    unsigned int bitPin5 : 1;
    unsigned int pinNumber1 : 8;
    unsigned int pinNumber2 : 8;
    unsigned int pinNumber3 : 8;
    unsigned int pinNumber4 : 8;
    unsigned int pinNumber5 : 8;
  } field;
  uint8_t nPins;
} stepperPin;

// typedef enum {
//     PERIOD_ON   = 0,
//     PERIOD_OFF  = 1
// } pwm_step_t;


typedef struct _stepperInfoDefinition
{
    uint8_t _state;
	uint8_t _angle;


    uint16_t dutyCycle;

    /* private */
    uint8_t _usedPins;
    stepperPin pins[5];
} stepperInfo;

static stepperInfo _stepperInfo;

static void frc1_interrupt_handler(void)
{
    // uint8_t i = 0;
    // bool out = true;
    // uint32_t load = _stepperInfo._onLoad;


    // for (; i < _stepperInfo.usedPins; ++i)
    // {
    //     gpio_write(_stepperInfo.pins[i].pin, out);
    // }

    // timer_set_load(FRC1, load);
    // _stepperInfo._step = step;
}

void stepper_init(uint8_t nPins, const uint8_t* pins)
{
    /* Assert number of pins is correct */
	switch(nPins){
		case 2:{
	        printf("Number of stepper pins is (%d)\n", nPins);
		}
		break;

		case 4:{
	        printf("Number of stepper pins is (%d)\n", nPins);
		}
		break;

		case 5:{
	        printf("Number of stepper pins is (%d)\n", nPins);		
		}
		break;

		default:{
	        printf("Incorrect number of PWM pins (%d)\n", nPins);
	        return;
		}

	}


    // /* Initialize */
    // // _stepperInfo._maxLoad = 0;
    // _stepperInfo._onLoad = 0;
    // _stepperInfo._offLoad = 0;
    // _stepperInfo._step = PERIOD_ON;

    // /* Save pins information */
    // _stepperInfo.usedPins = npins;

    // uint8_t i = 0;
    // for (; i < nPins; ++i)
    // {
    //     _stepperInfo.pins[i].pin = pins[i];

    //     /* configure GPIOs */
    //     gpio_enable(pins[i], GPIO_OUTPUT);
    // }

    // /* Stop timers and mask interrupts */
    // pwm_stop();

    // /* set up ISRs */
    // _xt_isr_attach(INUM_TIMER_FRC1, frc1_interrupt_handler);

    // /* Flag not running */
    // _stepperInfo.running = 0;
}

void stepper_set_speed(uint16_t speed){
 
}

void stepper_step(uint16_t numberOfSteps){
 
}

///void pwm_set_duty(uint16_t duty){
    // bool output;

    // _stepperInfo.dutyCycle = duty;
    // if (duty > 0 && duty < UINT16_MAX) {
    //     pwm_restart();
    //     return;
    // }

    // // 0% and 100% duty cycle are special cases: constant output.
    // pwm_stop();
    // _stepperInfo.running = 1;
    // output = (duty == UINT16_MAX);
    // for (uint8_t i = 0; i < _stepperInfo.usedPins; ++i)
    // {
    //     gpio_write(_stepperInfo.pins[i].pin, output);
    // }
//}

void stepper_set_angle(uint8_t angle){
    // if (_stepperInfo.running)
    // {
    //     pwm_stop();
    //     pwm_start();
    // }
}

void stepper_open(){
    
    // // Trigger ON
    // uint8_t i = 0;
    // for (; i < _stepperInfo.usedPins; ++i)
    // {
    //     gpio_write(_stepperInfo.pins[i].pin, true);
    // }

    // timer_set_load(FRC1, _stepperInfo._onLoad);
    // timer_set_reload(FRC1, false);
    // timer_set_interrupts(FRC1, true);
    // timer_set_run(FRC1, true);

    // _stepperInfo.running = 1;
}

void stepper_close(){
 
}
