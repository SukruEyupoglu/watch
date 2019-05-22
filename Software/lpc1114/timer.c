void timer_0_16_init(void)
{
LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
LPC_TMR16B0->PR  = System_Core_Clock/1000000;
}
void systick_second_sleep(unsigned char second)
{
	// Enable SysTick counter, Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt
	//SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
  
 	// Enable SysTick counter
	SYSTICK_CSR |= (1 << SYSTICK_ENABLE_BIT); 
  
}
void SysTick_Handler(void)
{

  
}
void systick_init(void)
{
	
	// SysTick Reload Value Register, 10ms interval using the Internal RC @12Mhz
	SYSTICK_RVR = 0x1D4BF;  
	
	// SysTick Reload Value Register, 1ms interval using the Internal RC @48Mhz 
	//SYSTICK_RVR = 0xBB7F; 
	
	// SysTick Reload Value Register, 250usec interval using the Internal RC @48Mhz 
	//SYSTICK_RVR = 0x2EDF;
		
	// Clear Current Value Register 
	SYSTICK_CVR = 0; 						
	
	// Enable SysTick counter, Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt
	//SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT) | (1 << SYSTICK_ENABLE_BIT);
	
	// Select clock source (1=CPU, 0=CPU/2), Enable SysTick interrupt 
	SYSTICK_CSR |= (1 << SYSTICK_CLKSOURCE_BIT) | (1 << SYSTICK_TICKINT_BIT);
	
}






