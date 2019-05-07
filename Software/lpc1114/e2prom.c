#define e2prom_addr 0xA2
#define namaz_saat_start_addr 0x0000
#define extra_data_start_addr 0x0727
#define extra_data_last_addr 0x4095

void i2c_100khz_e2prom_init(void)
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
	LPC_I2C->SCLH					=	0xF0;
	LPC_I2C->SCLL					=	0xF0;
}

unsigned char i2c_write_e2prom_32byte_1page(unsigned char ic_addr,unsigned short write_start_addr,unsigned char data[32])
{
unsigned char i;
LPC_I2C->CONSET = I2CONSET_STA_BIT5; 
while(LPC_I2C->STAT != I2CSTAT_START_0x08);
LPC_I2C->DAT					=	ic_addr;
LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x20) | (LPC_I2C->STAT == I2CSTAT_ACK_0x18)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
	LPC_I2C->DAT				=	( write_start_addr >> 8 );
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
	LPC_I2C->DAT				=	( write_start_addr & 0xF ); 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
}
else 
{
	LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
	LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
    	return 1;
}
for(i = 0 ; i < 32 ; i++)
{	
	while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x30) | (LPC_I2C->STAT == I2CSTAT_ACK_0x28)));
	if(LPC_I2C->STAT == I2CSTAT_ACK_0x28)
		{
		LPC_I2C->DAT				=	data[i];
		LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;
	}
	else 
	{
		LPC_I2C->CONSET = I2CONSET_STO_BIT4; 
		LPC_I2C->CONCLR = I2CONCLR_SIC_BIT3;  
		return 1;
	}
	LPC_I2C->CONSET = I2CONSET_STO_BIT4;
}
return 0;
}
unsigned char i2c_write_e2prom_1_char(unsigned char ic_addr,unsigned short write_addr,unsigned char data)
{
LPC_I2C->CONSET = I2CONSET_STA_BIT5; 
while(LPC_I2C->STAT != I2CSTAT_START_0x08);
LPC_I2C->DAT					=	ic_addr;
LPC_I2C->CONCLR = (I2CONCLR_SIC_BIT3 | I2CONCLR_STAC_BIT5);
while(!((LPC_I2C->STAT == I2CSTAT_NACK_0x20) | (LPC_I2C->STAT == I2CSTAT_ACK_0x18)));
if(LPC_I2C->STAT == I2CSTAT_ACK_0x18)
	{
	LPC_I2C->DAT				=	( write_addr >> 8 );
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
	LPC_I2C->DAT				=	( write_addr & 0xF ); 
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

