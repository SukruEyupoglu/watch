#include "LPC11xx.h"
#include "lpc1114_i2c.h"
#include "lpc1114_delay.h"

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
	//	400 khz setting = 3C      <--->      100 khz setting = F0
	LPC_I2C->SCLH					=	0x3C;
	LPC_I2C->SCLL					=	0x3C;
}

// while ile bekledikten sonra SIC(status interrupt clear) yapılmalı 
// kod pek düzgün degil ama calısır belki bastan yazmak lazim
// en asagıda dogru mantık var.
// reg addr size is byte number sample eeprom has 16bit addr size
unsigned char i2c
	(
	unsigned char dev_addr,	//device addr for start comminication , last bit show which read or write. write = 0 read = 1
	unsigned int reg_addr,	//device reg addr , if device a storage device maybe 16bit or 24bit
	unsigned char byte_len,	//if device a storage device there is a byte length , how many byte used inside reg value ?
				// 1 byte address size = 1 , 2 byte = 2 , 3 byte = 3 max = 4 byte
	unsigned char * data,	//address pointer for send or receive
	unsigned int data_size	//size of send or receive data per byte , how many byte
	)
{
	unsigned char reg_addr_part = 0,f,k;
	unsigned int size = data_size;
	if( (byte_len < 1) | (byte_len > 4) | (data_size == 0) )
	{
		return ERROR;
	}
	CLEAR_SI_BIT;
	SET_STA_BIT; 
	while(CHECK_SI_BIT);
	if(LPC_I2C->STAT == I2CSTAT_START_0x08)
	{
		LPC_I2C->DAT		=	dev_addr & 0xFE; // FIRST BYTE MUSTBE WRITE
		CLEAR_SI_BIT;
		CLEAR_STA_BIT;
	}
	else
	{
		SET_STO_BIT;
		CLEAR_SI_BIT;
		return ERROR_0x08;
	}
	while(CHECK_SI_BIT);
	if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
		for(f = 0 ; f < byte_len ; f++)
		{
			for(k = 0 ; k < 8 ; k++)
			{
				if(reg_addr & (1 << (k + (((byte_len - 1) - f) * 8))))
				{
					reg_addr_part |= (1 << k);
				}
			}
			LPC_I2C->DAT	=	reg_addr_part;
			CLEAR_SI_BIT;
			while(CHECK_SI_BIT);
			if(LPC_I2C->STAT != I2CSTAT_ACK_0x28)
			{
					SET_STO_BIT; 
					CLEAR_SI_BIT;  
    					return ERROR_0x28;
			}
		}
	}
	else 
	{
		SET_STO_BIT; 
		CLEAR_SI_BIT;  
    		return ERROR_0x18;
	}
	
	// write = 0 read = 1
	if(dev_addr & 0x01)
	{
	// READ SELECTING
		CLEAR_SI_BIT;
		SET_STA_BIT;
		while(CHECK_SI_BIT);
		if(LPC_I2C->STAT == I2CSTAT_START_0x10)
		{
			LPC_I2C->DAT	=	dev_addr;
			CLEAR_SI_BIT;
			CLEAR_STA_BIT;
		}
		else
		{
			SET_STO_BIT;
			CLEAR_SI_BIT;
			return ERROR_0x10;
		}
		while(CHECK_SI_BIT);
		if(LPC_I2C->STAT == I2CSTAT_ACK_0x40)
		{
			LPC_I2C->CONSET = I2CONSET_AA_BIT2;
			CLEAR_SI_BIT;
		}
		else 
		{
			SET_STO_BIT; 
			CLEAR_SI_BIT;  
    			return ERROR_0x40;
		}
		while(size)
		{
			while(CHECK_SI_BIT);
			if(LPC_I2C->STAT == I2CSTAT_ACK_0x50)
			{
				*data = LPC_I2C->DAT;
				CLEAR_SI_BIT;
			}
			else 
			{
				SET_STO_BIT; 
				CLEAR_SI_BIT;  
    				return ERROR_0x50;
			}
			if(size > 1)
			{
				data++;
			}
			size--;
		}
		SET_STO_BIT;
		CLEAR_SI_BIT;
		return OK;
	}
	else
	{
	// WRITE SELECTING
		while(size)
		{
			if(LPC_I2C->STAT == I2CSTAT_ACK_0x28)
			{
				LPC_I2C->DAT	=	* data; 
				CLEAR_SI_BIT;
			}
			else 
			{
				SET_STO_BIT; 
				CLEAR_SI_BIT;  
    				return ERROR_0x28;
			}
			while(CHECK_SI_BIT);
			if(size > 1)
			{
				data++;
			}
			size--;
		}
		if(LPC_I2C->STAT == I2CSTAT_ACK_0x28)
		{
			SET_STO_BIT;
			CLEAR_SI_BIT;
			delay(1000); // in succession this line must be 
			return OK;
		}
		else
		{
			SET_STO_BIT;
			CLEAR_SI_BIT;
			return ERROR_0x28;
		}
	}
	return OK;
}

/*
            LPC_I2C->CONSET       = (1<<5);
            while(!(LPC_I2C->CONSET & (1<<3)));   //Wait for interupt to be set
            LPC_I2C->DAT               = 0x38;             //Device adress + W
             LPC_I2C->CONCLR     = (1<<5); // Reset STA
             LPC_I2C->CONCLR     = (1<<3); //Reset interupt
 
             //Transmit 1:st registry adress to start read from
             //while(LPC_I2C->STAT != 0x18);
             while(!(LPC_I2C->CONSET & (1<<3)));
             LPC_I2C->DAT              = 0x01;
             LPC_I2C->CONCLR     = (1<<3);
 
             //start bit + accelerometer adress + readbit
             while(!(LPC_I2C->CONSET & (1<<3)));
             LPC_I2C->CONCLR     = (1<<3);
             LPC_I2C->CONSET     = (1<<5);               //Set Startbit
 
             //Adress + readbit with repeated start
             while(!(LPC_I2C->CONSET & (1<<3)));
             LPC_I2C->CONCLR     = (1<<3);
             LPC_I2C->DAT              = 0x39;           //Device adress + R
 
             //wait for last i2c operation to execute
             //while(!(LPC_I2C->CONSET & (1<<3)));
             LPC_I2C->CONCLR     = (1<<5);          //Clear Startbit
             LPC_I2C->CONCLR     = (1<<3);
 
             // Read X MSB
             while(!(LPC_I2C->CONSET & (1<<3)));
             Rbuf[0] = LPC_I2C->DAT;           
             LPC_I2C->CONSET = (1<<2);          // ACK first byte
             LPC_I2C->CONCLR     = (1<<3);
 
             // Read X LSB
             while(!(LPC_I2C->CONSET & (1<<3)));
             Rbuf[1] = LPC_I2C->DAT;
             LPC_I2C->CONCLR = (1<<2);          //NACK Second byte
             LPC_I2C->CONCLR     = (1<<3);
 
             while(!(LPC_I2C->CONSET & (1<<3)));
               LPC_I2C->CONCLR     = (1<<5);   //cleat STA
               LPC_I2C->CONSET     = (1<<4);   
               LPC_I2C->CONCLR     = (1<<3);
	       
	       
	       */
