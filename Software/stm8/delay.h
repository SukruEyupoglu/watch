

#define delay_10us delay_us(20)

void delay_us(volatile unsigned char bekle);
void delay_ms(volatile unsigned char bekle);
void delay_s(volatile unsigned char bekle);

////////////////////////////////////////////////////////////////
// THIS TESTED WITH OSCILOSKOP
  // SET CLK TO FULL SPEED (16MHZ)
//CLK_CKDIVR = 0;
