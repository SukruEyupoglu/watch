void timer4_init()
{
  // Frequency = F_CLK / (2 * prescaler * (1 + ARR))
  // 160Hz = 16.000.000 / (2 * 200 * (1 + 249)
  TIM4_PSCR = 200;
  TIM4_ARR = 249;
  TIM4_CR1 |= (1 << TIM4_CR1_CEN); // Enable TIM4
}
