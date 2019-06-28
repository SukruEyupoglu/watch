void tmr16b1_pwm_init(unsigned int lowtime,unsigned int hightime)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16) | (1 << 8);          // ENABLE IOCON CLK AND TMR16B1 CLK
  LPC_IOCON->PIO1_9 = 0x1;                                    // MAT0 FUNCTION SELECT
  LPC_TMR16B1->MR3 = lowtime + hightime;                      // FULL DUTY CYCLE
  LPC_TMR16B1->MR0 = lowtime;                                 // DUTY CYCLE START AT LOW AND WHEN MATCH OCCUR SET HIGH
  LPC_TMR16B1->MCR = (1 << 10);                               // RESET WHEN MR3 MATCH
  LPC_TMR16B1->PWMC = (1 << 0);                               // PWM LOW TO HIGH AT MR0 SETTING
  LPC_TMR16B1->TCR = 0x02;                                    // RESET TIMER
  LPC_TMR16B1->TCR = 0x01;                                    // ENABLE TIMER
}
void brightness_up(void)
{
  if(hightime < 0x000FFFFF)
  {
    hightime <<= 4;
  }
}
void brightness_down(void)
{
  if(hightime > 0xFFFFF000)
  {
    hightime >>= 4;
  }
}



