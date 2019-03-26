//USE INTERNAL CRYSTAL TO GENERATE INTERNAL SYSTEM CLOCK
void init(void)
{
LPC_SYSCON->SYSAHBCLKDIV              = 0x1;                    //set clock divider for core to 1
LPC_SYSCON->MAINCLKSEL                &= ~(0x03);               //set main clock to IRC oscillator, 
                                                                //if not system will lock up when PLL turns off
LPC_SYSCON->MAINCLKUEN                &= ~(1);                  //write a zero to the MAINCLKUEN register,
                                                                //necessary for MAINCLKSEL to update
LPC_SYSCON->MAINCLKUEN                |= 1;                     //write a one to the MAINCLKUEN register,
                                                                //necessary for MAINCLKSEL to update
LPC_SYSCON->SYSPLLCLKSEL              = 0x0;                    //connect system oscillator to SYSTEM PLL 
LPC_SYSCON->SYSPLLCLKUEN              &= ~(1);                  //write a zero to SYSPLLUEN register,
                                                                //necessary for SYSPLLCLKSEL to update
LPC_SYSCON->SYSPLLCLKUEN              |= 1;                     //write a one to SYSPLLUEN register,
                                                                //necessary for SYSPLLCLKSEL to update
LPC_SYSCON->PDRUNCFG                  |= (1<<7);                //power down the PLL before changing divider values
LPC_SYSCON->SYSPLLCTRL                = 0x23;                   //set MSEL = 0x00011 and PSEL = 0x01 --> 48MHZ --> 0x23
                                                                //set MSEL = 0x00010 and PSEL = 0x10 --> 36MHZ --> 0x42
                                                                //set MSEL = 0x00001 and PSEL = 0x10 --> 24MHZ --> 0x41
LPC_SYSCON->PDRUNCFG                  &= ~(1<<7);               //power up PLL after divider values changed 
while((LPC_SYSCON->SYSPLLSTAT & 1) == 0);                       //wait for PLL to lock
LPC_SYSCON->MAINCLKSEL                = 0x03;                   //set system oscillator to the output of the PLL 
LPC_SYSCON->MAINCLKUEN                &= ~(1);                  //write a zero to the MAINCLKUEN register,
                                                                //necessary for MAINCLKSEL to update
LPC_SYSCON->MAINCLKUEN                |= 1;                     //write a one to the MAINCLKUEN register 
}
