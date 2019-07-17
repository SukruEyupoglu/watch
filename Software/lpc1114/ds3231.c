unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}
#define I2CONSET_STA_BIT5 (1 << 5)
#define I2CONCLR_STAC_BIT5 (1 << 5)
#define I2CONCLR_SIC_BIT3 (1 << 3)
#define I2CONSET_STO_BIT4 (1 << 4)
#define I2CONSET_RSTA_BIT5 (1 << 5)
#define I2CONSET_AA_BIT2 (1 << 2)
#define I2CONCLR_MULTIBYTE_AAC_BIT2 (1 << 2)

#define I2CSTAT_START_0x08 0x08
#define I2CSTAT_NACK_0x20 0x20
#define I2CSTAT_ACK_0x18 0x18
#define I2CSTAT_NACK_0x30 0x30
#define I2CSTAT_ACK_0x28 0x28
#define I2CSTAT_START_0x10 0x10
#define I2CSTAT_NACK_0x48 0x48
#define I2CSTAT_ACK_0x40 0x40
#define I2CSTAT_ACK_0x50 0x50
#define I2CSTAT_ACK_0x58 0x58
// reg addr size is byte number sample eeprom has 16bit addr size
unsigned char i2c(unsigned char addr,unsigned int reg,unsigned char reg_addr_size,unsigned char read_or_write,unsigned char * data,unsigned int size)
{
	unsigned char var,f,k;
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
}

