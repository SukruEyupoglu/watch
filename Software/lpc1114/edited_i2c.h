

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

unsigned char i2c(
	unsigned char addr,			        //7 bit device addr
	unsigned int reg,			          //if device data storage size maybe 16-24-32 bit
	unsigned char reg_addr_size,		//if device data storage 16 = 2 , 24 = 3 byte min = 1 per byte
	unsigned char read_or_write,		//write = 0 , read = 1
	unsigned char * data,			      //address pointer for send or receive
	unsigned int size               //size of send or receive data per byte
  );
