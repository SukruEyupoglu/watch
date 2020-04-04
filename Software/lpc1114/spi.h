void spi_init(void);
unsigned char spi(unsigned char TX_Data);


#define SSPSR_TNF (1 << 1)
#define SSPSR_BSY (1 << 4)
#define SSPSR_RNE (1 << 2)



