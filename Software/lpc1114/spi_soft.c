unsigned char spi_soft(unsigned char x);
void spi_soft_init(void);

#define CLK_HIGH LPC_GPIO1->DATA |= (1 << 2)
#define CLK_LOW LPC_GPIO1->DATA &= ~(1 << 2)
#define MOSI_HIGH LPC_GPIO1->DATA |= (1 << 0)
#define MOSI_LOW LPC_GPIO1->DATA &= ~(1 << 0)
#define MISO LPC_GPIO1->DATA & (1 << 1)
#define spi_delay delay(1000)  // half pulse delay time

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


unsigned char spi_soft(unsigned char x)
{
  unsigned char y = 0,f;
  for(f = 0 ; f < 8 ; f++)
  {
    // LSB FIRST
    if( (x & (1 << f) ) != 0)
    {
      MOSI_HIGH;
    }
    else
    {
      MOSI_LOW;
    }
    spi_delay;
    CLK_HIGH;
    // LSB FIRST
    if( (MISO & (1 << f) ) != 0)
    {
      y |= (1 << f);
    }
    else
    {
      y &= ~(1 << f);
    }
    spi_delay;
    CLK_LOW;    
  }
}



