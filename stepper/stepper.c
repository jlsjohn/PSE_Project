#include "stepper.h"
#include <espressif/esp_common.h>
#include <espressif/sdk_private.h>
#include <FreeRTOS.h>
#include <esp8266.h>

static valveInfo this_valveInfo;
static valvePin this_valvePin;

/******************************************************************
*
*	Função que permite a anitializacio na válvula
*
*******************************************************************/
void valve_init(uint8_t motor_pin_1, uint8_t motor_pin_2, uint8_t motor_pin_3, uint8_t motor_pin_4){
	
	/* Save pins information */
	this_valvePin.field.pin_number1 = motor_pin_1;
	this_valvePin.field.pin_number2 = motor_pin_2;
	this_valvePin.field.pin_number3 = motor_pin_3;
	this_valvePin.field.pin_number4 = motor_pin_4;

	/* Initialize pins */
	gpio_enable(motor_pin_1, GPIO_OUTPUT);
	gpio_enable(motor_pin_2, GPIO_OUTPUT);
	gpio_enable(motor_pin_3, GPIO_OUTPUT);
	gpio_enable(motor_pin_4, GPIO_OUTPUT);

    /* Save pins information */
    this_valveInfo._speed = SPEED_DEFAULT;
    this_valveInfo._used_pins = USED_PINS_DEFAULT;
    this_valveInfo._state = STATE_INIT;
    this_valveInfo._angle = ANGLE_DEFAULT;
   
#ifdef DEBUG   
    printf("\nthis function is valve_init\n");
#endif
}

/******************************************************************
*
*	Função que permite a manipulação a velocidade de abertura o 
*	fechamento na válvula
*
*******************************************************************/
void valve_set_speed(uint8_t speed){
	this_valveInfo._speed = speed;
#ifdef DEBUG   
    printf("\nthis function is valve_set_speed\n");
#endif
}

/******************************************************************
*
*	Função que permite o tratameno das solicitaboes e dos dados
*
*******************************************************************/
void valve_step(uint8_t steps_to_move, uint8_t direction)
{
  	/* determine direction */
	this_valveInfo._direction = direction;
  	this_valveInfo._number_of_steps = steps_to_move;

  /* decrement the number of steps, moving one step each time:*/
  while (steps_to_move > 0)
  {

      if (this_valveInfo._direction == 1)
      {
        this_valveInfo._step_number++;
        if (this_valveInfo._step_number == this_valveInfo._number_of_steps) {
          this_valveInfo._step_number = 0;
        }
      }
      else
      {
        if (this_valveInfo._step_number == 0) {
          this_valveInfo._step_number = this_valveInfo._number_of_steps;
        }
        this_valveInfo._step_number--;
      }
      /* decrement the steps left:*/
      steps_to_move--;

#ifdef DEBUG   
      	printf("%u",this_valveInfo._step_number);	
#endif        
        vTaskDelay(this_valveInfo._speed);
        valve_step_motor(this_valveInfo._step_number % 4);
    }

#ifdef DEBUG   
    printf("\nthis function is valve_step\n");
#endif 
}

/******************************************************************
*
*	Função que permite a manipulação do motor da válvula
*
*******************************************************************/
void valve_step_motor(uint16_t this_step){
    switch (this_step) {
      case 0:  // 1010
        gpio_write(this_valvePin.field.pin_number1, HIGH);
        gpio_write(this_valvePin.field.pin_number2, LOW);
        gpio_write(this_valvePin.field.pin_number3, HIGH);
        gpio_write(this_valvePin.field.pin_number4, LOW);
      break;
      case 1:  // 0110
        gpio_write(this_valvePin.field.pin_number1, LOW);
        gpio_write(this_valvePin.field.pin_number2, HIGH);
        gpio_write(this_valvePin.field.pin_number3, HIGH);
        gpio_write(this_valvePin.field.pin_number4, LOW);
      break;
      case 2:  //0101
        gpio_write(this_valvePin.field.pin_number1, LOW);
        gpio_write(this_valvePin.field.pin_number2, HIGH);
        gpio_write(this_valvePin.field.pin_number3, LOW);
        gpio_write(this_valvePin.field.pin_number4, HIGH);
      break;
      case 3:  //1001
        gpio_write(this_valvePin.field.pin_number1, HIGH);
        gpio_write(this_valvePin.field.pin_number2, LOW);
        gpio_write(this_valvePin.field.pin_number3, LOW);
        gpio_write(this_valvePin.field.pin_number4, HIGH);
      break;
    }

#ifdef DEBUG   
    printf("\nthis function is valve_step_motor\n");
#endif 
}

/******************************************************************
*
*	Função que permite a manipulação angular na válvula
*
*******************************************************************/
void valve_set_angle(uint8_t angle){
	if(this_valveInfo._state == STATE_OPEN){
		this_valveInfo._number_of_steps = angle / 5.625;
		this_valveInfo._angle = angle;
		this_valveInfo._direction = RIGHT;
		valve_step(this_valveInfo._number_of_steps, RIGHT);
	}
	else if(this_valveInfo._state == STATE_CLOSED){
		this_valveInfo._number_of_steps = angle / 5.625;
		this_valveInfo._angle = angle;
		this_valveInfo._direction = LEFT;
		valve_step(MAX_STEP_NUMBER - this_valveInfo._number_of_steps, LEFT);
	}
	else if(this_valveInfo._state == STATE_HALF){
		this_valveInfo._number_of_steps = this_valveInfo._angle / 5.625;
		uint8_t dif_number_of_steps = this_valveInfo._number_of_steps;
		if(angle >= this_valveInfo._angle){
			this_valveInfo._number_of_steps = angle / 5.625;
			this_valveInfo._angle = angle;
			dif_number_of_steps = dif_number_of_steps - this_valveInfo._number_of_steps;
			this_valveInfo._direction = RIGHT;

		}
		else{
			this_valveInfo._number_of_steps = angle / 5.625;
			this_valveInfo._angle = angle;
			dif_number_of_steps = this_valveInfo._number_of_steps - dif_number_of_steps;
			this_valveInfo._direction = LEFT;
		}
		valve_step(dif_number_of_steps,this_valveInfo._direction);
	}

	this_valveInfo._state = STATE_HALF;

#ifdef DEBUG   
    printf("\nthis function is valve_set_angle\nAngle set is = %u.\n", this_valveInfo._angle);
#endif
}

/******************************************************************
*
*	Função que permite a abertura completa da válvula
*
*******************************************************************/
void valve_open(){
	if(this_valveInfo._state != STATE_OPEN){
    	if(this_valveInfo._state == STATE_CLOSED){
	     	printf("\nthis function is valve_open\n");
	    	this_valveInfo._number_of_steps = MAX_STEP_NUMBER;
			this_valveInfo._angle = MIN_ANGLE;
	    	this_valveInfo._direction = LEFT;
	    	valve_step(this_valveInfo._number_of_steps,this_valveInfo._direction);
    	}
    	else if(this_valveInfo._state == STATE_HALF){
			this_valveInfo._number_of_steps = this_valveInfo._angle / 5.625;
			this_valveInfo._angle = MIN_ANGLE;
			this_valveInfo._direction = LEFT;
			valve_step(this_valveInfo._number_of_steps,this_valveInfo._direction);
    	}
    	printf("\nthis function is valve_open\n");
    	this_valveInfo._state = STATE_OPEN;
	}

#ifdef DEBUG   
	else printf("\nthis valve is open\n");
#endif
}

/******************************************************************
*
*	Função que permite o fechamento completo da válvula
*
*******************************************************************/
void valve_close(){
	if(this_valveInfo._state != STATE_CLOSED){
    	if(this_valveInfo._state == STATE_OPEN){
	     	printf("\nthis function is valve_close\n");
			this_valveInfo._angle = MAX_ANGLE;
	    	this_valveInfo._direction = RIGHT;
	    	this_valveInfo._number_of_steps = MAX_STEP_NUMBER;
	    	valve_step(this_valveInfo._number_of_steps,this_valveInfo._direction);
    	}
    	else if(this_valveInfo._state == STATE_HALF){
			this_valveInfo._number_of_steps = this_valveInfo._angle / 5.625;
			uint8_t dif_number_of_steps = this_valveInfo._number_of_steps;
			this_valveInfo._angle = MAX_ANGLE;
			this_valveInfo._direction = RIGHT;
			this_valveInfo._number_of_steps = MAX_STEP_NUMBER;
			dif_number_of_steps = this_valveInfo._number_of_steps - dif_number_of_steps;
			valve_step(dif_number_of_steps,this_valveInfo._direction);
    	}

#ifdef DEBUG   
    	printf("\nthis function is valve_close\n");
#endif

    	this_valveInfo._state = STATE_CLOSED;
	}

#ifdef DEBUG   
	else printf("\nthis valve is closed\n");
#endif

}
