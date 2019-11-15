#include "stm8s.h"
#include "motor.h"
volatile unsigned char motor_1;
volatile unsigned char motor_2;
volatile unsigned char motor_3;
volatile unsigned char motor_4;
volatile unsigned char gpio_0_to_7;
volatile unsigned char gpio_8_to_15;
volatile unsigned char gpio_16_to_23;

// limit switch errors must be checked before every step
// only interrupt can make "1" this register
volatile unsigned char limit_interrupt;

volatile const unsigned char step_queue[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};

int main(void)
{



  while(1)
  {
    
  }

  return 0;
}


