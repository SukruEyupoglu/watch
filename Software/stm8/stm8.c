#include "stm8s.h"
#include "motor.h"

// motor_status looking for active_motor
volatile unsigned char motor_status[4] = {SB,SB,SB,SB};
volatile unsigned char active_motor;
volatile const unsigned char step_queue[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};

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


