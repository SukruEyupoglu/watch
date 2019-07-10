unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}
unsigned char i2c(unsigned char addr,unsigned char start_reg,unsigned char * data,unsigned int size)
{
    if((addr % 10) == 0)
    {
        
    }
    else
    {
LPC_I2C->CONSET = I2CONSET_STA_BIT5; 
while(LPC_I2C->STAT != I2CSTAT_START_0x08);
LPC_I2C->DAT					=	addr; // write = 0
LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x20) | (LPC_I2C->STAT == I2CSTAT_ACK_0x18)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
	LPC_I2C->DAT				=	start_reg;
    	LPC_I2C->CONSET = I2CONSET_RSTA_BIT5; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
	}
else 
	{
	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    	return 1;
	}
while(LPC_I2C->STAT != I2CSTAT_START_0x10);
LPC_I2C->DAT					=	addr + 1; // read = 1
LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);	
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x48) | (LPC_I2C->STAT == I2CSTAT_ACK_0x40)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x40)
	{
	LPC_I2C->CONSET = I2CONSET_MULTIBYTE_AA_BIT2;
	}
else 
	{
	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    	return 1;
	}
while(size)
{
	while((LPC_I2C->STAT != I2CSTAT_ACK_0x50) | (LPC_I2C->STAT != I2CSTAT_ACK_0x58);
	if(LPC_I2C->STAT == I2CSTAT_ACK_0x50)
		{
		*data = LPC_I2C->DAT;
		LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
		}
	      else if(LPC_I2C->STAT == I2CSTAT_ACK_0x58)
	 	     {
		      LPC_I2C->CONCLR = I2CONCLR_MULTIBYTE_AAC_BIT2;
		      *data = LPC_I2C->DAT;
			LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
			LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
			return 0;        
		      }
		else 
		{
		LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
		LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    		return 1;
		}
	data++;
	size--;
} 
return 0;        
}
}
