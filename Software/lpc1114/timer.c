void timer_0_16_init(void)
{
LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
LPC_TMR16B0->PR  = System_Core_Clock/1000000;
}
void systick_second_sleep(unsigned char second)
{
	// Enable SysTick counter, Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt
	//SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
	
  	tick_second = second;
	
 	// Enable SysTick counter
	SYSTICK_CSR |= (1 << SYSTICK_ENABLE_BIT); 
  
}

volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 0;

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





