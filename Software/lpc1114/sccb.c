void sccb_init(void)
{
	select_way(SCCB_WAY);
	SCL_UP;
	SDA_UP;
}

void sccb_start(void)
{
SCL_UP;
SDA_UP;
Delay_Us;
SDA_DOWN;
Delay_Us;
SCL_DOWN;
Delay_Us;
}

void sccb_stop(void)
{
SDA_DOWN;
SCL_DOWN;
Delay_Us;
SCL_UP;
Delay_Us;
SDA_UP;
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
	SCL_DOWN;
	}
	SDA_DOWN;
	SDA_DIR_INN;
	Delay_Us;
	SCL_UP;
	Delay_Us;
	if((SDA_INN) == 0)
	{
		err = 1;
	}
	SCL_DOWN;
	Delay_Us;
	SDA_DIR_OUT;
	return err;
}
unsigned char sccb_read(void)
{
	unsigned char i,data;
	SDA_DIR_INN;
	Delay_Us;
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
		Delay_Us;
		SCL_DOWN;
		Delay_Us;
	}
	SDA_DIR_OUT;
	SDA_DOWN; //SDA_UP;
	Delay_Us;
	SCL_UP;
	Delay_Us;
	SDA_UP; //SDA_DOWN;
	return data;
}
void ov7670_write(unsigned char reg, unsigned char data)
{
	//	WRITING MUST BE 3 PHASE
	sccb_start();
	//	phase 1 : send writing command
	sccb_write(0x42);
	Delay_Us;
	//	phase 2 : send reg id for write
	sccb_write(reg);
	Delay_Us;
	//	phase 3	: send reg data
	sccb_write(data);
	//	exiting
	sccb_stop();
}

unsigned char ov7670_read(unsigned char reg)
{
	unsigned char data;
	//	READING MUST BE 2 PHASE
	sccb_start();
	//	phase 1 : send 0x42 write ov7670 command for read which reg select
	sccb_write(0x42);
	Delay_Us;
	//	phase 2 : send reg id for reading which we want to read
	sccb_write(reg);
	Delay_Us;
	//	stop and start for 2 phase reading
	sccb_stop();
	Delay_Us;
	Delay_Us;
	Delay_Us;
	Delay_Us;
	sccb_start();
	Delay_Us;
	//	phase 1 : send 0x43 reading command
	sccb_write(0x43);
	Delay_Us;
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
	ov7670_write( 0x12, 0x80);
}
