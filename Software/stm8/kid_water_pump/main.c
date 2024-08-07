void timer4_init(unsigned char us)
{
  // CLK_CKDIVR = 0x1F; // minimum F_CLK = 15625
  // 4.17second = 15625 / (2 * 128 * 255) = maximum wait time
  // frequency = F_CLK / (2 * prescaler * (1 + ARR))
  //  125Hz = 16.000.000 / (2 * 128 * (1 + 249)
  //  10us = 16.000.000 / (2 * 8 * (1 + 9) (1 step per 10us)
  // TIM4_PSCR = 1, 2, 4, 8, 16, 32, 64 and 128
  // TIM4_PSCR     = 0x03; // 8
  TIM4_PSCR     = 0x07; // 128
  // TIM4_ARR      = 0x0B; // 10 us for delay
  TIM4_ARR      = 0xFF;
  TIM4_CR1      |= (1 << TIM4_CR1_OPM); // stop at max value from ARR
  TIM4_IER |= (1 << TIM4_IER_UIE); // Enable Update Interrupt
  TIM4_CR1      |= (1 << TIM4_CR1_CEN); // Enable TIM4
  
}
