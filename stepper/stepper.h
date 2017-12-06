#ifndef EXTRAS_STEPPER_H_
#define EXTRAS_STEPPER_H_

#include <stdint.h>

/*definindo pinos para o NODEMCU*/
#define PIN_01              16
#define PIN_02              5
#define PIN_03              2
#define PIN_04              4
#define PIN_05              0
#define PIN_06              12
#define PIN_07              14
#define PIN_08              15


/*definindo pinos para o NODEMCU*/
#define HIGH                1
#define LOW                 0

/*definino direção do giro*/
#define LEFT                0
#define RIGHT               1

#define STATE_INIT          0
#define STATE_RUNNING       1
#define STATE_OPEN          2
#define STATE_CLOSED        3
#define STATE_HALF          4

/*definindo inicializadores*/
#define ANGLE_DEFAULT       0
#define SPEED_DEFAULT       10
#define USED_PINS_DEFAULT   4

/*Habilitando debug*/
#define DEBUG               1

#define MAX_STEP_NUMBER     64
#define MAX_ANGLE           360
#define MIN_ANGLE           0

#ifdef __cplusplus
extern "C" {
#endif

typedef union{
  uint8_t data[6];
  struct{
    unsigned int bit_pin1 : 1;
    unsigned int bit_pin2 : 1;
    unsigned int bit_pin3 : 1;
    unsigned int bit_pin4 : 1;
    unsigned int pin_number1 : 8;
    unsigned int pin_number2 : 8;
    unsigned int pin_number3 : 8;
    unsigned int pin_number4 : 8;
  } field;
  uint8_t n_Pins;
} valvePin;

typedef struct _valveInfoDefinition
{
    uint8_t _state;
    uint8_t _angle;
    uint8_t _direction;
    uint8_t _step_number;
    uint8_t _number_of_steps;
    uint8_t _speed;
    uint8_t _used_pins;
    valvePin pins[5];
} valveInfo;

  void valve_init(uint8_t motor_pin_1, uint8_t motor_pin_2, uint8_t motor_pin_3, uint8_t motor_pin_4);
	void valve_set_speed(uint8_t speed);
	void valve_step(uint8_t steps_to_move, uint8_t direction);
	void valve_step_motor(uint16_t this_step);
  void valve_set_angle(uint8_t angle);
	void valve_open();
	void valve_close();

#ifdef __cplusplus
}					
#endif

#endif /*EXTRAS_STEPPER_H_*/
