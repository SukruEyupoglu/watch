#define e2prom_addr 0xA2
#define namaz_saat_start_addr 0x0000
#define extra_data_start_addr 0x0727
#define extra_data_last_addr 0x4095

void i2c_100khz_init(void)
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



