void timer4_init()
{
  // Frequency = F_CLK / (2 * prescaler * (1 + ARR))
  //  125Hz = 16.000.000 / (2 * 128 * (1 + 249)
  //  31250Hz = 16.000.000 / (2 * 128 * (1 + 1)
  TIM4_PSCR     = 0x07; // 128
  TIM4_ARR      = 0xF9; // 249
  TIM4_CR1      |= (1 << TIM4_CR1_CEN); // Enable TIM4
}
