void sccb_init(void)
{
SCL_UP;
SDA_UP;
}

void sccb_start(void)
{
SDA_DOWN;
Delay_Us;
SCL_DOWN;
Delay_Us;
}

void sccb_stop(void)
{
SDA_DOWN;
SCL_UP;
Delay_Us;
SDA_UP;
}
void sccb_repeated_start(void)
{
SDA_UP;
SCL_UP;
Delay_Us;
SDA_DOWN;	
SCL_DOWN;
Delay_Us;
}
unsigned char sccb_write( unsigned char data)
{
	unsigned char i, err = 0;
	for(i = 0 ; i < 8 ; i++)
	{
		if((data << i) & 0x80)
		{
			SDA_UP;
		}
		else
		{
			SDA_DOWN;
		}
		Delay_Us;
		SCL_UP;
		Delay_Us;
	}
	SCL_DOWN;
	SDA_DOWN;
	SDA_DIR_INN;
	Delay_Us;
	SCL_UP;
	if((SDA_INN) == 0)
	{
		err = 1;
	}
	Delay_Us;
	SCL_DOWN;
	Delay_Us;
	SDA_DIR_OUT;
	return err;
}
unsigned char sccb_read(void)
{
	unsigned char i,data;
	SDA_DOWN; // FOR REFUSE
	SDA_DIR_INN;
	for(i = 0 ; i < 8 ; i++)
	{
		SCL_UP;
		if(SDA_INN != 0)
			{
			data = 0x01 | (data << 1);
			}
		else
			{
			data = 0xFE & (data << 1) ;
			}
		Delay_Us; // SCL HIGH TIME
		SCL_DOWN;
		Delay_Us; // SCL LOW TIME
	}
	SDA_DIR_OUT;
	SDA_DOWN; // ACK_LOW = TRANFER OK
	SCL_UP;	
	Delay_Us; // SCL HIGH TIME
	SCL_DOWN; // SCL DOWN
	Delay_Us; // SCL LOW TIME
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
