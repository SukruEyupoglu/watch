#include "LPC11xx.h"
#include "systick.h"

void delay_sys(unsigned int u_sec)
{
  // systick max 24 bit === 0xFFFFFF
  if(u_sec < 0xFFFFFF)
  {
  SYST_RVR = (SYSTEM_CLOCK_FREQUENCY * u_sec) - 1; // must be tested "1" maybe too low "5" maybe
  }
  else
  {
    SYST_RVR = 0xFFFFFF;
  }
  SYST_CVR = 0;
  SYST_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
  __WFI();  // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
}
void SysTick_Handler(void)
{
  SYST_CSR &= ~( (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT) );
}




