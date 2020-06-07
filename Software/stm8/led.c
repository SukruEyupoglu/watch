#include "stm8s.h"
#include "led.h"

void led_init(void)
{
  PB_DDR |= (1 << 5); // DEFAULT OPEN DRAIN
  PB_ODR |= (1 << 5); // OUTPUT HIGH AND LED DIMMED
}

void led_open(void)
{
  PB_ODR &= ~(1 << 5); // OUTPUT LOW AND OPEN DRAIN AND LED SHINING
}

void led_close(void)
{
  PB_ODR |= (1 << 5); // OUTPUT HIGH AND LED DIMMED
}




