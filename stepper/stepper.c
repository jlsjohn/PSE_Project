#include "stepper.h"

#include <espressif/esp_common.h>
#include <espressif/sdk_private.h>
#include <FreeRTOS.h>
#include <esp8266.h>

static stepperInfo _stepperInfo;
static stepperPin _stepperPin;

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

void stepper_init(uint8_t motor_pin_1, uint8_t motor_pin_2, uint8_t motor_pin_3, uint8_t motor_pin_4){
    printf("this function is stepper_init");


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
    printf("this function is stepper_set_speed");
}

void stepper_step(int stepsToMove)
{
  /*int steps_left = abs(stepsToMove);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (stepsToMove > 0) { this->direction = 1; }
  if (stepsToMove < 0) { this->direction = 0; }*/


  // decrement the number of steps, moving one step each time:
/*
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay)
    {
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
        stepMotor(this->step_number % 4);
    }
  }*/
    printf("this function is stepper_step");
}
void stepper_step_motor(uint16_t thisStep){
 /*   switch (thisStep) {
      case 0:  // 1010
        gpio_write(motor_pin_1, HIGH);
        gpio_write(motor_pin_2, LOW);
        gpio_write(motor_pin_3, HIGH);
        gpio_write(motor_pin_4, LOW);
      break;
      case 1:  // 0110
        gpio_write(motor_pin_1, LOW);
        gpio_write(motor_pin_2, HIGH);
        gpio_write(motor_pin_3, HIGH);
        gpio_write(motor_pin_4, LOW);
      break;
      case 2:  //0101
        gpio_write(motor_pin_1, LOW);
        gpio_write(motor_pin_2, HIGH);
        gpio_write(motor_pin_3, LOW);
        gpio_write(motor_pin_4, HIGH);
      break;
      case 3:  //1001
        gpio_write(motor_pin_1, HIGH);
        gpio_write(motor_pin_2, LOW);
        gpio_write(motor_pin_3, LOW);
        gpio_write(motor_pin_4, HIGH);
      break;
    }
  }*/
    printf("this function is stepper_step_motor");
 
}

void stepper_set_angle(uint8_t angle){
    //stepper_step(int stepsToMove)
    printf("this function is stepper_set_angle");
}

void stepper_open(){
    printf("this function is stepper_open");
    //stepper_step(100);

    // _stepperInfo.running = 1;
}

void stepper_close(){
    printf("this function is stepper_close");
}
