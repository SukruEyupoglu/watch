#include "LPC11xx.h"
//USE INTERNAL CRYSTAL TO GENERATE INTERNAL SYSTEM CLOCK
void init(void)
{
#ifdef USE_48MHZ
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
#else
LPC_SYSCON->MAINCLKSEL                = 0x00;                   //set system oscillator to 12MHZ IRC oscillator
LPC_SYSCON->MAINCLKUEN                &= ~(1);                  //write a zero to the MAINCLKUEN register,
                                                                //necessary for MAINCLKSEL to update
LPC_SYSCON->MAINCLKUEN                |= 1;                     //write a one to the MAINCLKUEN register 
#endif
}
void sleep_or_powerdown(unsigned char sleep_type)
{
switch(sleep_type)
{
  case :0 //deep power down mode enable
  {                                 // ONLY WAKEUP PIN USED FOR AWAKENING FROM DEEP POWER DOWN
                                    // RESET NOT WORKING AT THIS STATUS WAKEUP PIN BEHAVES LIKE RESET OR START
  LPC_PMU->PCON |= (1 << 11);       // CLEAR DEEP POWER DOWN FLAG 
                                    // ALSO IF YOU NEED BEFORE ENTERED DEEP POWER DOWN MODE CHECK THIS REGISTER
  LPC_PMU->GPREG0 = 0x12345678;     // GENERAL PURPOSE REGISTERS 
                                    // FOR RETAINED DATA LATER FROM DEEP POWER DOWN MODE
  LPC_PMU->PCON |= (1 << 1);        // SELECT POWER DOWN MODE
                                    // &= ~(1 << 1) FOR SLEEP OR DEEP SLEEP MODE
  LPC_SYSCON->PDSLEEPCFG = 0x18FF;  // DISABLE WDT AND BOD AT DEEPSLEEP
                                    // NO NEED POWER DOWN MODE
  LPC_SYSCON->SCR |= (1 << 2);      // DEEP SLEEP SELECTING AND SLEEP MODE DESELECTING
                                    // NO NEED POWER DOWN MODE
  LPC_SYSCON->PDRUNCFG &= ~((1 << 0) | (1 << 1)); // NEED FOR DEEP POWER DOWN MODE
                                    // BEFORE SLEEP,DEEP SLEEP AND POWER DOWN MODES SET IRC TO MAIN OSC
                                    // WAKEUP PIN MUST BE PULLED HIGH DURING POWER DOWN MODE
   __WFI();                         // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
  }
  case :1 //deep sleep mode enable
  {                                 //The processor state and registers, peripheral registers,
                                    // and internal SRAM values are maintained, and the logic levels of the pins remain static.
  LPC_PMU->PCON |= (1 << 8);        // CLEAR DEEP SLEEP FLAG 
                                    // ALSO IF YOU NEED BEFORE ENTERED DEEP SLEEP MODE CHECK THIS REGISTER
  LPC_PMU->PCON &= ~(1 << 1);       // SELECT DEEP SLEEP MODE
                                    // &= ~(1 << 1) FOR SLEEP OR DEEP SLEEP MODE
  LPC_SYSCON->PDSLEEPCFG = 0x18FF;  // DISABLE WDT AND BOD AT DEEPSLEEP
  LPC_SYSCON->MAINCLKSEL = 0;       // SET IRC TO MAIN CLK,IF NEED TIMER WAKEUP WDT MUST BE MAINCLKSEL
  LPC_SYSCON->SCR |= (1 << 2);      // DEEP SLEEP SELECTING
  LPC_SYSCON->PDRUNCFG &= ~((1 << 0) | (1 << 1)); // NEED FOR DEEP SLEEP MODE
                                    // BEFORE SLEEP,DEEP SLEEP AND POWER DOWN MODES SET IRC TO MAIN OSC
   __WFI();                         // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
  }
  case :2 //sleep mode enable
  {
  LPC_PMU->PCON |= (1 << 8);       // CLEAR SLEEP FLAG 
                                    // ALSO IF YOU NEED BEFORE ENTERED SLEEP MODE CHECK THIS REGISTER
  LPC_PMU->PCON &= ~(1 << 1);       // SELECT SLEEP MODE
                                    // &= ~(1 << 1) FOR SLEEP OR DEEP SLEEP MODE
  LPC_SYSCON->SCR &= ~(1 << 2);     // SLEEP MODE SELECTING
  LPC_SYSCON->PDRUNCFG &= ~((1 << 0) | (1 << 1)); // NEED FOR SLEEP MODE
                                    // BEFORE SLEEP,DEEP SLEEP AND POWER DOWN MODES SET IRC TO MAIN OSC
   __WFI();                         // WAIT FOR INTERRUPT INSTRUCTION (CMSIS)
  }

}

}
