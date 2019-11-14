#include "stm8s.h"

volatile unsigned char motor_1;
volatile unsigned char motor_2;
volatile unsigned char motor_3;
volatile unsigned char motor_4;
volatile unsigned char gpio_0_to_7;

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


