#include "delay.h"


////////////////////////////////////////////////////////////////
// THIS TESTED WITH OSCILOSKOP
  // SET CLK TO FULL SPEED (16MHZ)
  //CLK_CKDIVR = 0;
void delay_us(volatile unsigned char bekle)
{
	while(bekle)
	{
		bekle--;
	}
	//	delay(0)	1.63us
	//	delay(1)	2.07us
	//	delay(2)	2.51us
	//	delay(3)	2.95us
	//	delay(4)	3.39us
	//	delay(5)	3.83us
	//	delay(6)	4.27us
	//	delay(19)	9.99us
	//	delay(20)	10.43us
	//	delay(224)	100.1us	
	//	delay(255)	113.8us  //MAX
}
///////////////////////////////////////////////////////////////////////

void delay_ms(volatile unsigned char bekle)
{
	while(bekle)
	{
		bekle--;
		delay_us(224);delay_us(224);delay_us(224);delay_us(224);delay_us(224);
		delay_us(224);delay_us(224);delay_us(224);delay_us(224);delay_us(224);
	}
}


