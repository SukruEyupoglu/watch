void timer_1_16_pwm_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE TMR16B1 CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 8);
  	//  IOCON PIN CT16B1_MAT0 FUNCTION SELECT
 	LPC_IOCON->PIO1_9      = 0x1;
	//	PRESCALER NOT USED HERE
	LPC_TMR16B1->PR           = 0x0;
	//	SET FOR RESET ON COUNTER MATCH
	LPC_TMR16B1->MCR          = 0x10;
	
	LPC_TMR16B1->EMR          |= 0x20;
	//	SET TIMER MODE
	LPC_TMR16B1->CCR          = 0; 
	//	SET CHANNEL ZERO TO PWM MODE
	LPC_TMR16B1->PWMC         = 0x1;
	//	SET VALUE FOR PERIOD = LOW AND HIGH ALL TIMES
	//LPC_TMR16B1->MR1          = 0x32;
	//	SET VALUE FOR DUTY CYCLE = ONLY HIGH TIMES FIRST LOW LATER HIGH
	//LPC_TMR16B1->MR0          = 0xC;
	//	ENABLE AND RESET COUNTER
	//LPC_TMR16B1->TCR          |= 0x3;
	//	CLEAR RESET BIT
	//LPC_TMR16B1->TCR          &= ~(0x2);
}
void set_pwm(unsigned short pwm_period,unsigned short pwm_duty_cycle)
{
	//	SET VALUE FOR PERIOD = LOW AND HIGH ALL TIMES
	LPC_TMR16B1->MR1          = pwm_period;
	//	SET VALUE FOR DUTY CYCLE = ONLY HIGH TIMES FIRST LOW LATER HIGH
	LPC_TMR16B1->MR0          = pwm_duty_cycle;
	//	ENABLE AND RESET COUNTER
	LPC_TMR16B1->TCR          |= 0x3;
	//	CLEAR RESET BIT
	LPC_TMR16B1->TCR          &= ~(0x2);
}
void systick_second_sleep(unsigned char second)
{
	// Enable SysTick counter, Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt
	//SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
	
  	tick_second = second;
	
 	// Enable SysTick counter
	SYSTICK_CSR |= (1 << SYSTICK_ENABLE_BIT); 
  
}
//Added from main file
//volatile unsigned char tick_interrupt_count = 0;
//volatile unsigned char tick_second = 10;

void SysTick_Handler(void)
{
if(tick_interrupt_count < tick_second)
{
	tick_interrupt_count++;
	SYSTICK_CVR = 0;
 	// Enable SysTick counter
	SYSTICK_CSR |= (1 << SYSTICK_ENABLE_BIT); 
}
else
{
	// Power down mode is "0"
  	sleep_or_powerdown(0);
}
}
void systick_init(void)
{
	// SysTick Reload Value Register, 1s interval using the Internal RC @12Mhz CPU/2
	SYSTICK_RVR = 0x5B8D80;  
	
	// SysTick Reload Value Register, 10ms interval using the Internal RC @12Mhz
	//SYSTICK_RVR = 0x1D4BF;  
	
	// SysTick Reload Value Register, 1ms interval using the Internal RC @48Mhz 
	//SYSTICK_RVR = 0xBB7F; 
	
	// SysTick Reload Value Register, 250usec interval using the Internal RC @48Mhz 
	//SYSTICK_RVR = 0x2EDF;
		
	// Clear Current Value Register 
	SYSTICK_CVR = 0; 						
	
	// Enable SysTick counter, Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt
	//SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
	
	// Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt 
	SYSTICK_CSR |= (1 << SYSTICK_TICKINT_BIT);
	
}
void restart_systick(void)
{
	SYSTICK_CVR = 0;
 	// Enable SysTick counter
	SYSTICK_CSR |= (1 << SYSTICK_ENABLE_BIT); 
}





