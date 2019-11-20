#include "stm8s.h

void gpio_interrupt_init(void)
{
  PC_DDR &= ~(1 << 3);          // DIRECTION INPUT SETTING FOR PC3
  PC_CR1 |= (1 << 3);           // PULLUP PC3 (HARDWARE RELATED LOOK AT PCB)
  PC_CR2 |= (1 << 3);           // INTERRUPT ENABLE PC3
  
  // 0 AND 1 BITS FOR PA
  // 2 AND 3 BITS FOR PB
  // 4 AND 5 BITS FOR PC
  // OTHERS SAME ,SAME CR1, CR2 IS CONTINUATION TO CR1
  // 0,0 = FALLING EDGE AND LOW LEVEL INTERRUPT
  // 1,0 = FALLING EDGE ONLY INTERRUPT
  // 0,1 = RISING EDGE ONLY
  // 1,1 = FALLING EDGE AND RISING EDGE INTERRUPT
  EXTI_CR1 &= ~( (1 << 4) | (1 << 5) ); // FALLING EDGE AND LOW LEVEL INTERRUPT
}

void gpio_isr(void) __interrupt(EXTI2_ISR)
{
  PC_CR2 &= ~(1 << 3);           // INTERRUPT DISABLE PC3
  limit_interrupt = LIMIT_ERROR;
}

void PC3_interrupt_enable(void)
{
  PC_CR2 |= (1 << 3);           // INTERRUPT ENABLE PC3
}



