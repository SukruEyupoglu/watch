// this code wrong 
// because not high low
// input or low
// when input,pullup resistor makes high this line
// when low ,gpio output low used to low
// only for SDA no need for SCL BUT PULL UP RESISTORS
// BECAUSE EACH CHANNEL(SCL,SDA) HAS PULL UP RESISTORS

void sccb_init(void)
{
SCL_IN;
SDA_IN;
}

void sccb_start(void)
{
SDA_OUT;
SCL_IN_DELAY_2;
SCL_OUT;
SCL_OUT_DELAY;
}

void sccb_stop(void)
{
SDA_OUT;
SCL_IN;
SCL_IN_DELAY;
SDA_IN;
}
void sccb_repeated_start(void)
{
SCL_IN;
SCL_IN_DELAY_2;
sccb_start();

}
unsigned char sccb_write( unsigned char data)
{
	unsigned char i, err = 0;
	for(i = 0 ; i < 8 ; i++)
	{
		if((data << i) & 0x80)
		{
			SDA_IN;
		}
		else
		{
			SDA_OUT;
		}
		SCL_IN;
		SCL_IN_DELAY;
		SCL_OUT;
		SCL_OUT_DELAY;
	}
	SDA_IN;
	SCL_IN;
	if(SDA_IN_DATA == 0)
	{
		err = 1;
	}
	SCL_IN_DELAY;
	SCL_OUT;
	SCL_OUT_DELAY;
	return err;
}
unsigned char sccb_read(void)
{
	unsigned char data = 0;
	for(i = 0 ; i < 8 ; i++)
	{
		SCL_IN;
		if(SDA_IN_DATA != 0)
			{
			data = 0x01 | (data << 1);
			}
		else
			{
			data = 0xFE & (data << 1) ;
			}
		SCL_IN_DELAY;
		SCL_OUT;
		SCL_OUT_DELAY;
	}
	SDA_OUT; // ACK_LOW = TRANFER OK
	SCL_IN;	
	SCL_IN_DELAY; // SCL HIGH TIME
	SCL_OUT; // SCL DOWN
	SCL_OUT_DELAY; // SCL LOW TIME
	return data;
}
void ov7670_write(unsigned char write_addr, unsigned char reg, unsigned char data)
{
	//	3 PHASE WRITING
	sccb_start();
	//	phase 1 : send writing command
	sccb_write(write_addr);
	//	phase 2 : send reg id for write
	sccb_write(reg);
	//	phase 3	: send reg data
	sccb_write(data);
	//	exiting
	sccb_stop();
}

unsigned char ov7670_read(unsigned char write_addr, unsigned char read_addr, unsigned char reg)
{
	unsigned char data;
	//	READING ONLY ONE BYTE
	sccb_start();
	//	phase 1 : send 0x42 write ov7670 command for read which reg select
	sccb_write(write_addr);
	//	phase 2 : send reg id for reading which we want to read
	sccb_write(reg);
	//	repeated start for reading
	sccb_repeated_start();
	//	phase 1 : send 0x43 reading command
	sccb_write(read_addr);
	//	phase 2 : get the data from ov7670
	data = sccb_read();
	//	exiting
	sccb_stop();
	//uart_send(reg_data[0]);
	return data;
}
void ov7670_init(void)
{
	sccb_init();
	//	soft reset for ov7670
	ov7670_write( 0x42,0x12,0x80);
}
