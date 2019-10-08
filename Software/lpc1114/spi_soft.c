void spi_soft_send(unsigned char x);
#define CLK_HIGH LPC_GPIO1->DATA |= (1 << 2)
#define CLK_LOW LPC_GPIO1->DATA &= ~(1 << 2)
#define MOSI_HIGH LPC_GPIO1->DATA |= (1 << 2)
#define MOSI_LOW LPC_GPIO1->DATA &= ~(1 << 2)
#define MISO LPC_GPIO1->DATA & (1 << 1)







void spi_soft_send(unsigned char x)
{
  
}
