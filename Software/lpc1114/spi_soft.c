void spi_soft_send(unsigned char x);
void spi_soft_init(void);
unsigned char spi_soft_get(void);

#define CLK_HIGH LPC_GPIO1->DATA |= (1 << 2)
#define CLK_LOW LPC_GPIO1->DATA &= ~(1 << 2)
#define MOSI_HIGH LPC_GPIO1->DATA |= (1 << 0)
#define MOSI_LOW LPC_GPIO1->DATA &= ~(1 << 0)
#define MISO LPC_GPIO1->DATA & (1 << 1)

void spi_soft_init(void)
{
  //	ENABLE IOCON CLK
  LPC_SYSCON->SYSAHBCLKCTRL |=	(1 << 16);
  //	ENABLE GPIO CLK
  LPC_SYSCON->SYSAHBCLKCTRL |=	(1 << 6);
  
  // LPC_IOCON->SWDIO_PIO1_3 = 1; // cs or ss if u need
  LPC_IOCON->R_PIO1_2 = 1;
  LPC_IOCON->R_PIO1_1 = 1;
  LPC_IOCON->R_PIO1_0 = 1;
  
  LPC_GPIO1->DIR |= (1 << 0) | (1 << 2);
  LPC_GPIO1->DIR &= ~(1 << 1);
  
  LPC_GPIO1_DATA &= ~((1 << 0) | (1 << 2));
}






void spi_soft_send(unsigned char x)
{
  
}
unsigned char spi_soft_get(void)
{
  
}
