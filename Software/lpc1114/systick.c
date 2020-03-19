#include "LPC11xx.h"
#include "systick.h"

void delay_sys(unsigned int u_sec)
{
  // systick max 24 bit === 0xFFFFFF
  if( (SYSTEM_CLOCK_FREQUENCY * u_sec) < 0xFFFFFF)
  {
    // systick start value
    SysTick->LOAD = (SYSTEM_CLOCK_FREQUENCY * u_sec) - 1; // must be tested "1" maybe too low "5" maybe
  }
  else
  {
    // systick start value
    SysTick->LOAD = 0xFFFFFF;
  }
  // clear current value
  SysTick->VAL = 0;
  // enable and set systick timer
  SysTick->CTRL |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
  __WFI();  // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
}
void SysTick_Handler(void)
{
  SysTick->CTRL &= ~( (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT) );
}




