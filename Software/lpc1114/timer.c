void timer_0_16_init(void)
{
LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
LPC_TMR16B0->PR  = System_Core_Clock/1000000;
}
