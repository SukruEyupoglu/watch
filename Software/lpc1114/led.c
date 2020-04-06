#include "spi.h"
#include "led.h"
#include "LPC11xx.h"

void led_init(void)
{
		//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 6);

  // LATCH SETTINGS FOR SHIFT REGISTERS
  LPC_IOCON->PIO2_10      = 0;
  LPC_GPIO2->DIR					|=	(1 << 10);
  // THERE IS A TRANSISTOR AT LINE ACTIVE LOW BUT BECAUSE TRANSISTOR ACTIVE HIGH
  // LOW IS INACTIVE (ACTIVE HIGH) SET LOW NOW
  LPC_GPIO2->DATA					&=	~(1 << 10);
	
	// OUTPUT ENABLE SETTING FOR MBI5026GF 
	LPC_IOCON->PIO1_9      = 0;
	LPC_GPIO1->DIR		|= (1 << 9);
	// FOR REDUCE LIGHT POWER ENABLE TIMER CT16B1_MAT0 PWM
	// FOR NOW ONLY GPIO
	// LOW ENABLE BUT THERE IS A TRANSISTOR AT LINE THUS FOR CODE HIGH ENABLE
	LPC_GPIO1->DATA		|= (1 << 9);  
}
// FOR LED DATA HOLDER ARRAY EVERY FUNCTION REACABLE OPTION
volatile unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void set_led_write_reg(unsigned char minute,unsigned char hour)
{
  // ZERO dan minuteye kadar olan ledleri yakar.
  limit_yaz(ONE,minute);
  // sol digite 10(ON) ve katları, sag digite 10(ON) a kadar olan sayılar
  led_write_digit((hour / 10),(hour % 10));
}
	
void latch(void) // duzeltildi.
{
LPC_GPIO2->DATA   	&= ~(1 << 10);
LPC_GPIO2->DATA		|= (1 << 10);
}

void led_write(void)
{
  unsigned char f;
  for(f = 0 ; f < 12 ; f++)
  {
    spi( led[(11 - f)] );
  }
  latch();
}        	
// BELIRLI BIR ALANDAKI LEDLERI YAKAN FONKSIYON
// x DEN BASLAYARAK y YE KADAR OLAN LEDLERI YAKAR
// SAAT YADA DAKIKA YAZMAK ICIN UYGUNDUR
void limit_yaz(unsigned char x,unsigned char y)
{
  unsigned char f;
  // led_zero();
  if( (x < 60) & (y < 60) )
  {
    if(y < x)
    {
      for(f = y ; f <= x ; f++)
      {
        led_yan(f);
      }
    }
    else
    {
      for(f = x ; f <= y ; f++)
      {
        led_yan(f);
      }
    }
  }
}
// BELIRLI BIR ALANDAKI LEDLERI SONDUREN FONSIYON 
// ORNEGIN x DEN BASLAYARAK y YE KADAR SIL
void limit_sil(unsigned char x,unsigned char y)
{
  unsigned char f;
  // led_one();
  if( (x < 60) & (y < 60) )
  {
    if(y < x)
    {
      for(f = y ; f <= x ; f++)
      {
        led_son(f);
      }
    }
    else
    {
      for(f = x ; f <= y ; f++)
      {
        led_son(f);
      }
    }
  }
}
// 0 - 60 between
// SADECE BIR LEDI YAKAN FONKSIYON
void led_yan(unsigned char xx)
{
  unsigned char x = xx;
  if(xx < 61)
  {
    if(x == 0)
    {
      x = 60;
    }
    led[ (x - 1) / 8] |= (1 << ( (x - 1) % 8) );
  }
  // yaz();
}
// 0 - 60 between
// SADECE BIR LEDI SONDUREN FONKSIYON
void led_son(unsigned char xx)
{
  unsigned char x = xx;
  if(x < 61)
  {
    if( x == 0)
    {
      x = 60;
    }
    led[ (x - 1) / 8] &= ~(1 << ( (x - 1) % 8) );
  }
  // yaz();
}
// BUTUN LEDLERI SONDUREN FONKSIYON
void led_zero(void)
{
  unsigned char f = 60;
  while(f)
  {
    led_son(f);
    f--;
  }
}
// BUTUN LEDLERI YAKAN FONKSIYON
void led_one(void)
{
  unsigned char f = 60;
  while(f)
  {
    led_yan(f);
    f--;
  }
}

void led_write_digit(unsigned char left,unsigned char right)
{
  switch(left)
  {
    case '.':
    {
      led[8] = 0x00;
      led[9] = 0x00;
    }
    break;
    case 0:
    {
      led[8] = 0xFF;
      led[9] = 0x0F;
    }
    break;
    case 1:
    {
      led[8] = 0x3C;
      led[9] = 0x00;
    }
    break;
    case 2:
    {
      led[8] = 0xCF;
      led[9] = 0x33;
    }
    break;
    case 3:
    {
      led[8] = 0xFF;
      led[9] = 0x30;
    }
    break;
    case 4:
    {
      led[8] = 0x3C;
      led[9] = 0x3C;
    }
    break;
    case 5:
    {
      led[8] = 0xF3;
      led[9] = 0x3C;
    }
    break;
    case 6:
    {
      led[8] = 0xF3;
      led[9] = 0x3F;
    }
    break;
    case 7:
    {
      led[8] = 0x3F;
      led[9] = 0x00;
    }
    break;
    case 8:
    {
      led[8] = 0xFF;
      led[9] = 0x3F;
    }
    break;
    case 9:
    {
      led[8] = 0xFF;
      led[9] = 0x3C;
    }
    break;      
    case 'A':
    {
      led[8] = 0x3F;
      led[9] = 0x3F;
    }
    break;
    case 'B':
    {
      led[8] = 0xDB;
      led[9] = 0x1F;
    }
    break;
    case 'C':
    {
      led[8] = 0xC3;
      led[9] = 0x0F;
    }
    break;
    case 'D':
    {
      led[8] = 0xDB;
      led[9] = 0x0F;
    }
    break;
    case 'E':
    {
      led[8] = 0xC3;
      led[9] = 0x3F;
    }
    break;
    case 'F':
    {
      led[8] = 0x03;
      led[9] = 0x3F;
    }
    break;
    case 'G':
    {
      led[8] = 0xD3;
      led[9] = 0x1F;
    }
    break;
    case 'H':
    {
      led[8] = 0x3C;
      led[9] = 0x3F;
    }
    break;
    case 'I':
    {
      led[8] = 0x00;
      led[9] = 0x0F;
    }
    break;
    case 'J':
    {
      led[8] = 0xFC;
      led[9] = 0x00;
    }
    break;
    case 'K':
    {
      led[8] = 0x24;
      led[9] = 0x3F;
    }
    break;
    case 'L':
    {
      led[8] = 0xC0;
      led[9] = 0x0F;
    }
    break;
    case 'M':
    {
      led[8] = 0x34;
      led[9] = 0x3B;
    }
    break;
    case 'N':
    {
      led[8] = 0x3B;
      led[9] = 0x07;
    }
    break;
    case 'O':
    {
      led[8] = 0xDB;
      led[9] = 0x06;
    }
    break;
    case 'P':
    {
      led[8] = 0x0F;
      led[9] = 0x3F;
    }
    break;
    case 'R':
    {
      led[8] = 0x03;
      led[9] = 0x0F;
    }
    break;
    case 'S':
    {
      led[8] = 0xD1;
      led[9] = 0x2C;
    }
    break;
     case 'T':
    {
      led[8] = 0x00;
      led[9] = 0x3F;
    }
    break;
    case 'U':
    {
      led[8] = 0xFC;
      led[9] = 0x0F;
    }
    break;
    case 'V':
    {
      led[8] = 0xD4;
      led[9] = 0x0A;
    }
    break;
    case 'Y':
    {
      led[8] = 0xFD;
      led[9] = 0x3D;
    }
    break;
    case 'Z':
    {
      led[8] = 0xD8;
      led[9] = 0x32;
    }
    break;
    default:
    {
      led[8] = 0x00;
      led[9] = 0x00;
    }
    break;    
  }
  switch(right)
  {
    case '.':
    {
      led[10] = 0x00;
      led[11] = 0x00;
    }
    break;
    case 0:
    {
      led[10] = 0xFF;
      led[11] = 0x0F;
    }
    break;
    case 1:
    {
      led[10] = 0x3C;
      led[11] = 0x00;
    }
    break;
    case 2:
    {
      led[10] = 0xCF;
      led[11] = 0x33;
    }
    break;
    case 3:
    {
      led[10] = 0xFF;
      led[11] = 0x30;
    }
    break;
    case 4:
    {
      led[10] = 0x3C;
      led[11] = 0x3C;
    }
    break;
    case 5:
    {
      led[10] = 0xF3;
      led[11] = 0x3C;
    }
    break;
    case 6:
    {
      led[10] = 0xF3;
      led[11] = 0x3F;
    }
    break;
    case 7:
    {
      led[10] = 0x3F;
      led[11] = 0x00;
    }
    break;
    case 8:
    {
      led[10] = 0xFF;
      led[11] = 0x3F;
    }
    break;
    case 9:
    {
      led[10] = 0xFF;
      led[11] = 0x3C;
    }
    break;      

    case 'A':
    {
      led[10] = 0x3F;
      led[11] = 0x3F;
    }
    break;
    case 'B':
    {
      led[10] = 0xDB;
      led[11] = 0x1F;
    }
    break;
    case 'C':
    {
      led[10] = 0xC3;
      led[11] = 0x0F;
    }
    break;
    case 'D':
    {
      led[10] = 0xDB;
      led[11] = 0x0F;
    }
    break;
    case 'E':
    {
      led[10] = 0xC3;
      led[11] = 0x3F;
    }
    break;
    case 'F':
    {
      led[10] = 0x03;
      led[11] = 0x3F;
    }
    break;
    case 'G':
    {
      led[10] = 0xD3;
      led[11] = 0x1F;
    }
    break;
    case 'H':
    {
      led[10] = 0x3C;
      led[11] = 0x3F;
    }
    break;
    case 'I':
    {
      led[10] = 0x00;
      led[11] = 0x0F;
    }
    break;
    case 'J':
    {
      led[10] = 0xFC;
      led[11] = 0x00;
    }
    break;
    case 'K':
    {
      led[10] = 0x24;
      led[11] = 0x3F;
    }
    break;
    case 'L':
    {
      led[10] = 0xC0;
      led[11] = 0x0F;
    }
    break;
    case 'M':
    {
      led[10] = 0x34;
      led[11] = 0x3B;
    }
    break;
    case 'N':
    {
      led[10] = 0x3B;
      led[11] = 0x07;
    }
    break;
    case 'O':
    {
      led[10] = 0xDB;
      led[11] = 0x06;
    }
    break;
    case 'P':
    {
      led[10] = 0x0F;
      led[11] = 0x3F;
    }
    break;
    case 'R':
    {
      led[10] = 0x03;
      led[11] = 0x0F;
    }
    break;
    case 'S':
    {
      led[10] = 0xD1;
      led[11] = 0x2C;
    }
    break;
     case 'T':
    {
      led[10] = 0x00;
      led[11] = 0x3F;
    }
    break;
    case 'U':
    {
      led[10] = 0xFC;
      led[11] = 0x0F;
    }
    break;
    case 'V':
    {
      led[10] = 0xD4;
      led[11] = 0x0A;
    }
    break;
    case 'Y':
    {
      led[10] = 0xFD;
      led[11] = 0x3D;
    }
    break;
    case 'Z':
    {
      led[10] = 0xD8;
      led[11] = 0x32;
    }
    break;
    default:
    {
      led[10] = 0x00;
      led[11] = 0x00;
    }
    break;    
  }
}
