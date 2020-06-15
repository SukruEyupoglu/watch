#include "stm8s.h"
#include "timer.h"

void timer4_init(unsigned char us)
{
  // frequency = F_CLK / (2 * prescaler * (1 + ARR))
  //  125Hz = 16.000.000 / (2 * 128 * (1 + 249)
  //  10us = 16.000.000 / (2 * 8 * (1 + 9) (1 step per 10us)
  // TIM4_PSCR = 1, 2, 4, 8, 16, 32, 64 and 128
  TIM4_PSCR     = 0x03; // 8
  // TIM4_ARR      = 0x09; // 9
  TIM4_ARR      = us -1;
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
    TIM4_CR1      |= (1 << TIM4_CR1_CEN); // Enable TIM4
  }
  else
  {
    TIM4_CR1      &= ~(1 << TIM4_CR1_CEN); // Disable TIM4
  }
}
