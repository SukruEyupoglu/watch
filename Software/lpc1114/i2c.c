#include "LPC11xx.h"
void i2c_init(void)
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
}
/* this must be re written
void i2c_write(unsigned char addr,unsigned char reg,unsigned char data)
{
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 4) | (1 << 3)| (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	addr; // for write last bit must be "0"
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18)));
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	while(!((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28)));
	LPC_I2C->DAT				=	data;
	delay(500);
	LPC_I2C->CONCLR				=	(1 << 3);
	delay(500);
	LPC_I2C->CONSET				|=	(1 << 4);
	delay(500);
}
unsigned char i2c_read(unsigned char addr,unsigned char reg)
{
	unsigned char data;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	addr;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x20) | (LPC_I2C->STAT == 0x18)));
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR				=	(1 << 3);
	while(!((LPC_I2C->STAT == 0x30) | (LPC_I2C->STAT == 0x28)));
	LPC_I2C->CONSET				|=	(1 << 4);
	delay(500);
	LPC_I2C->CONCLR				|=	(1 << 6);
	delay(500);
	LPC_I2C->CONSET				|=	(1 << 6) |	(1 << 5);
	while(LPC_I2C->STAT != 0x08);
	LPC_I2C->DAT				=	0x43;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(!((LPC_I2C->STAT == 0x40) | (LPC_I2C->STAT == 0x48)));
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3);
	while(LPC_I2C->STAT != 0x58);
	LPC_I2C->CONSET				=	(1 << 2);
	data = LPC_I2C->DAT;
	LPC_I2C->CONCLR				=	(1 << 5) | (1 << 3) | (1 << 2);
	LPC_I2C->CONSET				|=	(1 << 4);
	delay(500);
	return data;
}
*/
