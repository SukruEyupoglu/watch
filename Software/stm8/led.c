void led_init()
{
  PB_DDR |= (1 << 5); // DEFAULT OPEN DRAIN
  PB_ODR |= (1 << 5); // OUTPUT HIGH AND LED DIMMED
}

void led_open()
{
  PD_ODR &= ~(1 << 5); // OUTPUT LOW AND OPEN DRAIN AND LED SHINING
}

void led_close()
{
  PB_ODR |= (1 << 5); // OUTPUT HIGH AND LED DIMMED
}




