#define CHECK_SI_BIT (!(LPC_I2C->CONSET & (1<<3)))
#define CLEAR_SI_BIT (LPC_I2C->CONCLR = (1 << 3))
#define CLEAR_STA_BIT (LPC_I2C->CONCLR = (1 << 5))
#define SET_STA_BIT (LPC_I2C->CONSET = (1 << 5))
#define SET_STO_BIT (LPC_I2C->CONSET = (1 << 4))
#define ERROR 1
#define OK 0

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


void i2c_init(void);

unsigned char i2c
	(
	unsigned char dev_addr,	//device addr for start comminication , last bit show which read or write. write = 0 read = 1
	unsigned int reg_addr,	//device reg addr , if device a storage device maybe 16bit or 24bit
	unsigned char byte_len,	//if device a storage device there is a byte length , how many byte used inside reg value ?
				                  // 1 byte address size = 1 , 2 byte = 2 , 3 byte = 3 max = 4 byte
	unsigned char * data,	//address pointer for send or receive
	unsigned int data_size	//size of send or receive data per byte , how many byte
	);







