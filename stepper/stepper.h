#ifndef EXTRAS_STEPPER_H_
#define EXTRAS_STEPPER_H_

#include <stdint.h>

#define MAX_PWM_PINS    8

#ifdef __cplusplus
extern "C" {
#endif

void stepper_init(uint8_t nPins, const uint8_t* pins);
void stepper_set_speed(uint16_t speed);
void stepper_step(uint16_t numberOfSteps);

    // Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2);
    // Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
    //                              int motor_pin_3, int motor_pin_4);
    // Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
    //                              int motor_pin_3, int motor_pin_4,
    //                              int motor_pin_5);



//uint8_t version(void);


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

  //   // motor pin numbers:
  //   int motor_pin_1;
  //   int motor_pin_2;
  //   int motor_pin_3;
  //   int motor_pin_4;
  //   int motor_pin_5;          // Only 5 phase motor

  //   unsigned long last_step_time; // time stamp in us of when the last step was taken



#ifdef __cplusplus
}					
#endif

#endif /*EXTRAS_STEPPER_H_*/