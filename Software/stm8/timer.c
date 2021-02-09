#include "stm8s.h"
#include "timer.h"

void timer4_init(unsigned char us)
{
  // frequency = F_CLK / (2 * prescaler * (1 + ARR))
  //  125Hz = 16.000.000 / (2 * 128 * (1 + 249)
  //  10us = 16.000.000 / (2 * 8 * (1 + 9) (1 step per 10us)
  // TIM4_PSCR = 1, 2, 4, 8, 16, 32, 64 and 128
  TIM4_PSCR     = 0x03; // 8
  // TIM4_PSCR     = 0x07; // 128
  // TIM4_ARR      = 0x0B; // 10 us for delay
  TIM4_ARR      = us -1;
  TIM4_CR1      |= (1 << TIM4_CR1_OPM); // stop at max value from ARR
  // TIM4_IER |= (1 << TIM4_IER_UIE); // Enable Update Interrupt
  // TIM4_CR1      |= (1 << TIM4_CR1_CEN); // Enable TIM4
}

void timer_isr() __interrupt(TIM4_ISR) {
    // code here
    TIM4_SR &= ~(1 << TIM4_SR_UIF);
}

void timer4_on_off(unsigned char on_off)
{
  if(on_off == 1)
  {
    TIM4_EGR = 1; // prescaler and counter register clear command
    TIM4_CR1      |= (1 << TIM4_CR1_CEN); // Enable TIM4
  }
  else
  {
    TIM4_CR1      &= ~(1 << TIM4_CR1_CEN); // Disable TIM4
  }
}

void timer1_PWM_init(unsigned char us)
{
  // F_CLK = 16.000.000
  // frequency = F_CLK / ( ( (TIM1_PSCRH << 8) + TIM1_PSCRL) * (1 + ( (TIM1_ARRH << 8) + TIM1_ARRL) ) )
  //  4.294.836.225hz = 16.000.000 / (0xFFFF * (1 + 0xFFFE) // max value for counter frequency
  //  10us = 16.000.000 / (0x4 * 0x13) (1 step per 10us)
  //  10us === TIM1_PSCRH = 0;TIM1_PSCRL = 0x4;TIM1_ARRH = 0;TIM1_ARRL = 0x13;
  //  TIM1_PSCRL must be bigger than 2 if used
  //  TIM1_PSCRH and TIM1_ARRH must be written first than TIM1_PSCRL and TIM1_ARRL
  TIM1_PSCRH     = 0x00; // 8
  TIM1_PSCRL     = 0x04; // 8
  // TIM4_PSCR     = 0x07; // 128
  // TIM4_ARR      = 0x0B; // 10 us for delay
  TIM1_ARRH      = us -1; // wrong update this line
  TIM1_ARRL      = us -1; // wrong update this line
  TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  // TIM1_IER |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  // TIM1_CR1      |= (1 << TIM1_CR1_CEN); // Enable TIM4
  // edit this lines
  TIM1_CCR4H = 0; 
  TIM1_CCR4L = 25; // 25% duty cycle (25 / (99 + 1)) 
  TIM1_CCMR4 = 0x60; // PWM mode 1 
  TIM1_CCER4|= (1 << 0); // Enable OC1 
  
  TIM1_CR1|= (1 << 0); // Enable TIM1 
  TIM1_BKR|= (1 << 7); // ban brakes 
  /* 
  TIM1_CR1&=~BIT(0); // Close TIM1
  TIM1_PSCRH = 0; 
  TIM1_PSCRL = 0; // undivided
  TIM1_ARRH = 0; 
  TIM1_ARRL = 99; 

  TIM1_CCR1H = 0; 
  TIM1_CCR1L = 25; // 25% duty cycle (25 / (99 + 1)) 
  TIM1_CCMR1 = 0x60; // PWM mode 1 
  TIM1_CCER1|=BIT(0); // Enable OC1 
  
  TIM1_CCR3H = 0; 
  TIM1_CCR3L = 75; // duty cycle of 75% (75 / (99 + 1)) 
  TIM1_CCMR3 = 0x60; // PWM mode 1 
  TIM1_CCER2|=BIT(0); // enable OC3 
  
  TIM1_CR1|=BIT(0); // Enable TIM1 
  TIM1_BKR|=BIT(7); // ban brakes 
  */
  
  
  /* if you want to use [TIM1_CH1],[TIM1_CH2],[TIM2_CH1] or vb. on STM8S003 look this lines
  This option flags reside in flash at address 0x4803 and 0x4804 and values should be 0x01 and 0xFE (the complement). In debugger open a memory window and inspect content:

004800  00 00 FF 01 FE 00 FF 00 ........  <- should look like this

004800  00 00 FF 00 FF 00 FF 00 ........  <- this is default with AFR1 reset (SPI instead of TIMER channels)

You cannot change these at runtime (easily) but have to set the options bits correctly in the IDE.

*/
}




