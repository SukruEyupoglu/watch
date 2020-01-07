#include "LPC11xx.h"

#define SYSTEM_CLOCK_FREQUENCY 12 // 12MHZ

void delay_sys(unsigned int u_sec)
{
  if(u_sec < 0xFFFFFF)
  {
  SYSTICK_RVR = (SYSTEM_CLOCK_FREQUENCY * u_sec) - 1; // must be tested "1" maybe too low "5" maybe
  }
  else
  {
    SYSTICK_RVR = 0xFFFFFF;
  }
  SYSTICK_CVR = 0;
  SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
  __WFI();  // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
}
void SysTick_Handler(void)
{
  SYSTICK_CSR &= ~( (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT) );
}




