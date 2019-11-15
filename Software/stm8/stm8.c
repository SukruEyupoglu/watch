#include "stm8s.h"
#include "motor.h"

// motor_status looking for active_motor
volatile unsigned char motor_status[4] = {SB,SB,SB,SB};
volatile unsigned char active_motor; // selected active motor

// motor shift register related data
volatile const unsigned char step_queue[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};

// if there is a limit error look at direction for rescue motor from error
// immadiately motor must step far away from error
volatile unsigned char active_motor_direction; // direction 0 is back 1 is next

// there are 3 type step FULL_STEP,HALF_STEP,QUARTER_STEP
// FULL_STEP = most slow but most strongly                              8 step full circle
// HALF_STEP = faster then FULL_STEP more strongly then QUARTER_STEP    4 step full circle
// QUARTER_STEP = most speed and most weak steps                        4 step full circle
volatile unsigned char step_type;

// gpio output status 
volatile unsigned char gpio_0_to_7;
volatile unsigned char gpio_8_to_15;
volatile unsigned char gpio_16_to_23;

// limit switch errors must be checked before every step
// only interrupt can make "1" this register
volatile unsigned char limit_interrupt;

int main(void)
{



  while(1)
  {
    
  }

  return 0;
}


