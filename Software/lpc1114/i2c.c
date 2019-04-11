#include "LPC11xx.h"
// TIMER COUNTER COUNT 1MHZ AT SECOND
// I2C 400KHZ AT SECOND
// 1 BYTE = 8 BIT --> WITHOUT START STOP PULSE 400000/8 = 50000 --> 1000000/50000 = 20
// 1 BYTE TRANFERED AT 20 COUT TO TIMER
// DOUBLE TIME ENOUGH FOR WAIT 20*2 = 40
#define I2C_TIMEOUT 40
unsigned int I2C_ERROR = 0 ;
void i2c_init_timer(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 16);

	//	IOCONFIG I2C SETTINGS
	LPC_IOCON->PIO0_4 			=	0x1;
	LPC_IOCON->PIO0_5 			=	0x1;
	//	I2C CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 5);
	LPC_SYSCON->PRESETCTRL			|=	0x2;
	LPC_I2C->CONSET					|=	(1 << 6);
	//	400 khz setting = 3C---100 khz setting = F0
	LPC_I2C->SCLH				=	0x3C;
	LPC_I2C->SCLL				=	0x3C;
	// I2C WITHOUT INTERRUPT
	// FOR ESCAPE INFINITE DELAY USE TIMER
	// TIMER_0_16 SETTING
	//	ENABLE TIMER_0_16 CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 7);
	// System_Core_Clock 12MHZ
	LPC_TMR16B0->PR  = ((12000000/1000000) - 1);
	// STOP ON MR0 MATCH
	LPC_TMR16B0->MCR |= (1 << 2);
	// STOP AT COUNT 1000 NO NEED TOO MUCH
	LPC_TMR16B0->MR0 = 1000;	
}
void i2c_write_timer(unsigned char addr,unsigned char reg,unsigned char data)
{
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 4) | (1 << 3)| (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if(LPC_I2C->STAT == 0x08)
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 1;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->DAT				=	addr; // for write last bit must be "0"
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18))
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 2;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28))
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 3;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}	
	LPC_I2C->DAT				=	data;
	LPC_I2C->CONCLR				=	(1 << 3);
	LPC_I2C->CONSET				|=	(1 << 4);
}
unsigned char i2c_read_timer(unsigned char write_addr,unsigned char read_addr,unsigned char reg)
{
	unsigned char data;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if(LPC_I2C->STAT == 0x08)
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 4;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->DAT				=	write_addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18))
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 5;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28))
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 6;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->CONSET				|=	(1 << 4);
	LPC_I2C->CONCLR				|=	(1 << 6);
	LPC_I2C->CONSET				|=	(1 << 6) | (1 << 5);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if(LPC_I2C->STAT == 0x08)
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 7;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->DAT				=	read_addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if((LPC_I2C->STAT == 0x40) | (LPC_I2C->STAT == 0x48))
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 8;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	LPC_TMR16B0->TCR = (1 << 1) | (1 << 0);
	LPC_TMR16B0->TCR = (1 << 0);
	while(1)
	{
		if(LPC_I2C->STAT == 0x58)
		{
		break;
		}
		if(LPC_TMR16B0->TC >= I2C_TIMEOUT)
		{
			I2C_ERROR = 9;
			LPC_TMR16B0->TCR = 0;
			return;
		}
	}	
	LPC_I2C->CONSET				=	(1 << 2);
	data = LPC_I2C->DAT;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 4);
	return data;
}
void i2c_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 16);

	//	IOCONFIG I2C SETTINGS
	LPC_IOCON->PIO0_4 				=	0x1;
	LPC_IOCON->PIO0_5 				=	0x1;
	//	I2C CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 5);
	LPC_SYSCON->PRESETCTRL			|=	0x2;
	LPC_I2C->CONSET					|=	(1 << 6);
	//	400 khz setting = 3C---100 khz setting = F0
	LPC_I2C->SCLH					=	0x3C;
	LPC_I2C->SCLL					=	0x3C;
}
void i2c_write(unsigned char addr,unsigned char reg,unsigned char data)
{
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18)));
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	while(!((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28)));
	LPC_I2C->DAT				=	data;
	LPC_I2C->CONCLR				=	(1 << 3);
	LPC_I2C->CONSET				|=	(1 << 4);
}
unsigned char i2c_read(unsigned char write_addr,unsigned char read_addr,unsigned char reg)
{
	unsigned char data;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	write_addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18)));
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	while(!((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28)));
	LPC_I2C->CONSET					|=	(1 << 4);
	LPC_I2C->CONCLR					|=	(1 << 6);
	LPC_I2C->CONSET					|=	(1 << 6) |	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	read_addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x40) | (LPC_I2C->STAT == 0x48)));
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(LPC_I2C->STAT != 0x58);
	LPC_I2C->CONSET				=	(1 << 2);
	data = LPC_I2C->DAT;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 4);
	return data;
}

