void delay(volatile unsigned int bekle)
{
	while(bekle)bekle--;
}
