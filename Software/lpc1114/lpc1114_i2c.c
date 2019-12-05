#include "LPC11xx.h"
#include "lpc1114_i2c.h"

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

// reg addr size is byte number sample eeprom has 16bit addr size
unsigned char i2c(
	unsigned char addr,			//device addr char size
	unsigned int reg,			//if device data storage size maybe 16-24-32 bit
	unsigned char reg_addr_size,		//if device data storage 16 = 2 , 24 = 3 byte min = 1 per byte
	unsigned char read_or_write,		//write = 0 , read = 1
	unsigned char * data,			//address pointer for send or receive
	unsigned int size)			//size of send or receive data per byte
{
	unsigned char var = 0,f,k;
	LPC_I2C->CONSET = I2CONSET_STA_BIT5; 
	while(LPC_I2C->STAT != I2CSTAT_START_0x08);
	LPC_I2C->DAT					=	addr;
	LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);
	while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x20) | (LPC_I2C->STAT == I2CSTAT_ACK_0x18)));
	if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
		for(f = 0 ; f < reg_addr_size ; f++)
		{
			for(k = 0 ; k < 8 ; k++)
			{
				if(reg & (1 << (k + (((reg_addr_size - 1) - f) * 8))))
				{
					var |= (1 << k);
				}
			}
			LPC_I2C->DAT				=	var;
			LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
			while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x30) | (LPC_I2C->STAT == I2CSTAT_ACK_0x28)));
		}

	}
	else 
	{
		LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
		LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    		return 1;
	}
	
	// write = 0 read = 1
	if(read_or_write == 0)
	{
		while(size)
		{
			if(LPC_I2C->STAT == I2CSTAT_ACK_0x28)
			{
				LPC_I2C->DAT				=	* data; 
				LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
			}
			else 
			{
				LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
				LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    				return 1;
			}
			while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x30) | (LPC_I2C->STAT == I2CSTAT_ACK_0x28)));
			data++;
			size--;
		}
		LPC_I2C->CONSET = I2CONSET_STO_BIT4;
		return 0;
	}
	else
	{
		LPC_I2C->CONSET = I2CONSET_RSTA_BIT5;
		while(LPC_I2C->STAT != I2CSTAT_START_0x10);
		LPC_I2C->DAT					=	addr + 1;
		LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);	
		while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x48) | (LPC_I2C->STAT == I2CSTAT_ACK_0x40)));
		if(LPC_I2C->STAT == I2CSTAT_ACK_0x40)
		{
			LPC_I2C->CONSET = I2CONSET_AA_BIT2; // IF MULTIBYTE READ USE THIS
		}
		else 
		{
			LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
			LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    			return 1;
		}
		while(size)
		{
			while(LPC_I2C->STAT != I2CSTAT_ACK_0x50);
			if(LPC_I2C->STAT == I2CSTAT_ACK_0x50)
			{
				*data = LPC_I2C->DAT;
				LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
			}
			else 
			{
				LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
				LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    				return 1;
			}
			data++;
			size--;
			if(size == 1)
			{
				LPC_I2C->CONCLR = I2CONCLR_MULTIBYTE_AAC_BIT2;
				while(LPC_I2C->STAT != I2CSTAT_ACK_0x58);
				*data = LPC_I2C->DAT;
				LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
				LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
				return 0;				
			}
		}	
	}
	return 0;
}
