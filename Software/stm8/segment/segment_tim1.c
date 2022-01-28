
unsigned char tim1_interrupt_flag = 0;

void tim1_init(unsigned short sec)
{
  // THIS TIMER MAKED FOR LONG TIMING , ONLY SECOND
  // max second = 1638sec , min second = 1sec
  // frequency = F_CLK / ( ( (TIM1_PSCRH << 8) + TIM1_PSCRL) * (1 + ( (TIM1_ARRH << 8) + TIM1_ARRL) ) )
  TIM1_CR1    = 0;            // Disable TIM1
  TIM1->PSCRH = ( ( sec * 40 ) >> 8);
  TIM1->PSCRL = ( ( sec * 40 ) & 0xFF);
  TIM1->ARRH = 0xC3;
  TIM1->ARRL = 0x50;
  
  TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  TIM1_IER      |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  TIM1->CR1 = TIM1_CR1_CEN; // Enable the counter
}

void timer_isr() __interrupt(TIM1_ISR) {
  tim1_interrupt_flag = 1;
  TIM1_SR &= ~(1 << TIM1_SR_UIF);
}



