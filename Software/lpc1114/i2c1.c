unsigned char i2c_write_1_char(unsigned char addr,unsigned char reg,unsigned char data)
{
LPC_I2C->CONSET = I2CONSET_STA_BIT5; 
while(LPC_I2C->STAT != I2CSTAT_START_0x08);
LPC_I2C->DAT					=	addr;
LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x20) | (LPC_I2C->STAT == I2CSTAT_ACK_0x18)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
	LPC_I2C->DAT				=	reg;
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
	}
else 
	{
	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    	return 1;
	}
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x30) | (LPC_I2C->STAT == I2CSTAT_ACK_0x28)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x28)
	{
	LPC_I2C->DAT				=	data;
    	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
}
else 
{
	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    	return 1;
}
return 0;
}
unsigned char i2c_read_1_char(unsigned char addr,unsigned char reg,unsigned char data)
{
	
	
	
}



