#ifndef EXTRAS_STEPPER_H_
#define EXTRAS_STEPPER_H_

#include <stdint.h>

#define MAX_PWM_PINS    8

#ifdef __cplusplus
extern "C" {
#endif

typedef union{
  uint8_t data[6];
  struct{
    unsigned int bitPin1 : 1;
    unsigned int bitPin2 : 1;
    unsigned int bitPin3 : 1;
    unsigned int bitPin4 : 1;
    //unsigned int bitPin5 : 1;
    unsigned int pinNumber1 : 8;
    unsigned int pinNumber2 : 8;
    unsigned int pinNumber3 : 8;
    unsigned int pinNumber4 : 8;
    //unsigned int pinNumber5 : 8;
  } field;
  uint8_t nPins;
} stepperPin;

typedef struct _stepperInfoDefinition
{
    uint8_t _state;
    uint8_t _angle;
    uint16_t _speed;

    /* private */
    uint8_t _usedPins;
    stepperPin pins[5];
} stepperInfo;


void stepper_set_speed(uint16_t speed);
void stepper_step(uint16_t numberOfSteps);
void stepper_init(uint8_t motor_pin_1, uint8_t motor_pin_2, uint8_t motor_pin_3, uint8_t motor_pin_4);

void stepper_set_angle(uint8_t angle);
void stepper_open();
void stepper_close();
  // private:
  //   void stepMotor(int this_step);

  //   int direction;            // Direction of rotation
  //   unsigned long step_delay; // delay between steps, in ms, based on speed
  //   int number_of_steps;      // total number of steps this motor can take
  //   int pin_count;            // how many pins are in use.
  //   int step_number;          // which step the motor is on


#ifdef __cplusplus
}					
#endif

#endif /*EXTRAS_STEPPER_H_*/
