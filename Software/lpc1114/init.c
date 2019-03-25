//USE INTERNAL CRYSTAL TO GENERATE INTERNAL SYSTEM CLOCK
void init(void)
{
LPC_SYSCON->SYSAHBCLKDIV              = 0x1;                    //set clock divider for core to 1
LPC_SYSCON->MAINCLKSEL                &= ~(0x03);               //set main clock to IRC oscillator, 
                                                                //if not system will lock up when PLL turns off
LPC_SYSCON->MAINCLKUEN                &= ~(1);










}
