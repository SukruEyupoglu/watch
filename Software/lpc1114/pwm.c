#include "LPC11xx.h"
#include "e2prom.h"
#include "error.h"

void tmr16b1_pwm_init(void)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16) | (1 << 8);          // ENABLE IOCON CLK AND TMR16B1 CLK
  LPC_IOCON->PIO1_9 = 0x1;                                    // MAT0 FUNCTION SELECT
  LPC_TMR16B1->MR3 = duty;                                    // FULL DUTY CYCLE
  LPC_TMR16B1->MR0 = (duty / 100) * percent;                  // DUTY CYCLE START AT LOW AND WHEN MATCH OCCUR SET HIGH
  LPC_TMR16B1->MCR = (1 << 10);                               // RESET WHEN MR3 MATCH
  LPC_TMR16B1->PWMC = (1 << 0);                               // PWM LOW TO HIGH AT MR0 SETTING
  LPC_TMR16B1->TCR = 0x02;                                    // RESET TIMER
  LPC_TMR16B1->TCR = 0x01;                                    // ENABLE TIMER
}
void brightness_up(void)
{
  LPC_TMR16B1->TCR = 0;                                       // DISABLE TIMER  
  if(percent < 98)
  {
    percent++;
  }
  LPC_TMR16B1->MR0 = (duty / 100) * percent;                  // DUTY CYCLE START AT LOW AND WHEN MATCH OCCUR SET HIGH
  LPC_TMR16B1->TCR = 0x02;                                    // RESET TIMER
  LPC_TMR16B1->TCR = 0x01;                                    // ENABLE TIMER  
}
void brightness_down(void)
{
  LPC_TMR16B1->TCR = 0;                                       // DISABLE TIMER  
  if(percent > 2)
  {
    percent--;
  }
  LPC_TMR16B1->MR0 = (duty / 100) * percent;                  // DUTY CYCLE START AT LOW AND WHEN MATCH OCCUR SET HIGH
  LPC_TMR16B1->TCR = 0x02;                                    // RESET TIMER
  LPC_TMR16B1->TCR = 0x01;                                    // ENABLE TIMER  
}

unsigned char led_power_init(void)
{
  unsigned char data[3];
  LPC_TMR16B1->TCR = 0;                                       // DISABLE TIMER
  LPC_TMR16B1->MR3 = 0;
  if(e2prom_read(LED_LIGHT_SETTING_DUTY_LSB_ADDR,data,3) == ERR) // FIRST = LSB, SECOND = MSB, THIRD = PERCENT
  {
    return ERROR;
  }
  LPC_TMR16B1->MR3 = data[1];
  LPC_TMR16B1->MR3 <<= 8;   //  LPC_TMR16B1->MR0 = (LPC_TMR16B1->MR0 << 8);
  LPC_TMR16B1->MR3 |= data[0];
  if(data[2] > 100)
  {
    data[2] = 100;
  }
  LPC_TMR16B1->MR0 = (LPC_TMR16B1->MR3 / 100 ) * data[2]; // data[2] max value must be 100
  LPC_TMR16B1->TCR = 0x02;                                    // RESET TIMER
  LPC_TMR16B1->TCR = 0x01;                                    // ENABLE TIMER    
  return OK;
}



