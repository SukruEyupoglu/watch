#include "LPC11xx.h"
#include "systick.h"
#include "init.h"

#define WAITING_FOR_ACTION 1
#define ONLY_DELAY 2

volatile unsigned char action_status;
volatile unsigned char action_data;
volatile unsigned char max_action_data;

// FOR 1 SECOND DELAY u_sec = SYSTEM_CLOCK_FREQUENCY * 1.000.000
void delay_sys(unsigned int u_sec)
{
  // systick max 24 bit === 0xFFFFFF
  if( (SYSTEM_CLOCK_FREQUENCY * u_sec) < 0xFFFFFF)
  {
    action_status = ONLY_DELAY;
    // systick start value
    SysTick->LOAD = (SYSTEM_CLOCK_FREQUENCY * u_sec) - 5; // must be tested "1" maybe too low "5" maybe
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

void deadline_sec(unsigned char wait_for_dead)
{
  max_action_data = wait_for_dead;
  action_status = WAITING_FOR_ACTION;
  SysTick->LOAD = 12000000; // 12.000.000 MHZ = 0xB71B00 = 1 second
  // clear current value
  SysTick->VAL = 0;
  // enable and set systick timer
  SysTick->CTRL |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
}

void SysTick_Handler(void)
{
  if(action_status == WAITING_FOR_ACTION)
  {
    if(action_data < max_action_data)
    {
      action_data += 1;
      // clear current value
      SysTick->VAL = 0;
      // enable and set systick timer
      SysTick->CTRL |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
    }
    else
    {
      sleep_or_powerdown(POWER_DOWN); // EYELIDS ARE GETTING HEAVY
    }
  }
  else
  {
  // CLOSE SYSTICK
  SysTick->CTRL &= ~( (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT) );
  }
}




