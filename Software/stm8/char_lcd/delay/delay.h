

#define delay_10us delay_us(20)
// 100.1us + 9.99us + 9.99us + 9.99us
#define delay_130us delay_us(224);delay_us(19);delay_us(19);delay_us(19)

void delay_us(volatile unsigned char bekle);
void delay_ms(volatile unsigned char bekle);
void delay_s(volatile unsigned char bekle);

////////////////////////////////////////////////////////////////
// THIS TESTED WITH OSCILOSKOP
  // SET CLK TO FULL SPEED (16MHZ)
//CLK_CKDIVR = 0;




