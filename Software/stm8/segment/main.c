
#include "stm8s.h"
#include "i2c.h"
#include "spi.h"
#include "beep.h"
#include "button.h"

void timer_isr() __interrupt(TIM1_ISR);
void tim1_init(unsigned short sec);
unsigned char time2reg(unsigned char time);
unsigned char reg2time(unsigned char reg);
void place_ds3231_cursor(unsigned char x);

#define DS3231_SECOND_ADDR 0x00
#define DS3231_MINUTE_ADDR 0x01
#define DS3231_HOUR_ADDR 0x02
#define DS3231_ALARM_MINUTE_ADDR 0x08
#define DS3231_ALARM_HOUR_ADDR 0x09

#define BOOT_BUTTON_PRESS ( !( PA_IDR & (1 << 3) ) )
#define UP_BUTTON_PRESS ( !( PC_IDR & (1 << 3) ) )
#define DOWN_BUTTON_PRESS ( !( PD_IDR & (1 << 3) ) )

#define BUTTON_PRESSED 0

// active high
#define LATCH PC_ODR |= (1 << 4);PC_ODR &= ~(1 << 4)

unsigned char tim1_interrupt_flag = 1;


int main(void)
{
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char alarm_hour;
	unsigned char alarm_minute;
	unsigned char d[0x13];
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	
	i2c_init();
	spi_init();
	
	// latch init
	PC_DDR |= (1 << 4); // direction output
	PC_CR1 |= (1 << 4); // make push-pull
	PC_ODR &= ~(1 << 4);// make low first
		
		
		
	while(1)
	{
		if(tim1_interrupt_flag == 1)
		{
			place_ds3231_cursor(0x00);
			// GET ALL DATA FROM DS3231 TO d[0x13]
			i2c_start();
			i2c_write_addr(0xD1); // read
			i2c_read_arr(d,0x13);
			i2c_stop();
			// WRITE HOUR AND MINUTE
			spi(num2dig( reg2time( d[DS3231_HOUR_ADDR]) ); //first hour
			spi(num2dig( reg2time( d[DS3231_MINUTE_ADDR]) ); //second minute
			LATCH;
			// CHECK ALERT FLAG
			check_alert( alarm _minute );
			tim1_interrupt_flag = 0;
			
			tim1_init( 240 + ( 60 - second ) );
		}
		check_boot_button();
	}
}

void timer_isr() __interrupt(TIM1_ISR) {
  tim1_interrupt_flag = 1;
  TIM1_SR &= ~(1 << TIM1_SR_UIF);
}

void tim1_init(unsigned short sec)
{
  // THIS TIMER MAKED FOR LONG TIMING , ONLY SECOND
  // max second = 1638sec , min second = 1sec
  // frequency = F_CLK / ( ( (TIM1_PSCRH << 8) + TIM1_PSCRL) * (1 + ( (TIM1_ARRH << 8) + TIM1_ARRL) ) )
  TIM1_CR1    = 0;            // Disable TIM1
  TIM1->PSCRH = ( ( sec * 40 ) >> 8);
  TIM1->PSCRL = ( ( sec * 40 ) & 0xFF);
  TIM1->ARRH = 0xC3;
  TIM1->ARRL = 0x50;
  
  TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  TIM1_IER      |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  TIM1->CR1 = TIM1_CR1_CEN; // Enable the counter
}

unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}

void write_ds3231_minute(unsigned char minute)
{
    if(minute < 60)
    {
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write_addr(DS3231_MINUTE_ADDR);
	    i2c_write(time2reg(minute) )
	    i2c_stop();
    }
}
			    
void write_ds3231_hour(unsigned char hour)
{
    if(hour < 12)
    {
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write_addr(DS3231_HOUR_ADDR);
	    i2c_write(time2reg(hour) )
	    i2c_stop();
    }
}

void place_ds3231_cursor(unsigned char x)
{
			// I2C TAKE THE CURSOR TO START
			i2c_start();
			i2c_write_addr(0xD0); // write
			i2c_write(x); // cursor setting
			i2c_stop();
}

void button_init(void)
{
  //  MAKE PA3 BOOT BUTTON INPUT
  PA_DDR &= ~(1 << 3);
  //  MAKE PC3 UP BUTTON INPUT
  PC_DDR &= ~(1 << 3);  
  //  MAKE PD3 DOWN BUTTON INPUT
  PD_DDR &= ~(1 << 3);  
}

void check_boot_button(void)
{
  if(BOOT_BUTTON_PRESS)
  {
    while(BOOT_BUTTON_PRESS);
    turn_on_minute_dot_light();
    boot_button_first_pressed_function();
  }
}

void boot_button_first_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
      turn_on_hour_dot_light();
      boot_button_second_pressed_function();
      break;
    }
    if(UP_BUTTON_PRESS)
    {
      increase_minute();
      while(UP_BUTTON_PRESS);
    }
    if(DOWN_BUTTON_PRESS)
    {
      decrease_minute();
      while(DOWN_BUTTON_PRESS);
    }
  }
}
			    
void boot_button_second_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
      boot_button_third_pressed_function();
      break;
    }
    if(UP_BUTTON_PRESS)
    {
      increase_hour();
      while(UP_BUTTON_PRESS);
    }
    if(DOWN_BUTTON_PRESS)
    {
      decrease_hour();
      while(DOWN_BUTTON_PRESS);
    }
  }
}
			    
void boot_button_third_pressed_function(void)
{
  save_changes();
}

unsigned char num2dig(unsigned char num)
{
	switch(num)
	{
		case 0:
		{		     // .GFE DCBA 7 segment display
			return 0x3F; // 0011 1111 
		}
		break;
		case 1:
		{
			return 0x06; // 0000 0110 
		}
		break;
		case 2:
		{
			return 0x5B; // 0101 1011 
		}
		break;
		case 3:
		{
			return 0x4F; // 0100 1111 
		}
		break;
		case 4:
		{
			return 0x66; // 0110 0110 
		}
		break;
		case 5:
		{
			return 0x6C; // 0110 1101 
		}
		break;
		case 6:
		{
			return 0x7C; // 0111 1101 
		}
		break;
		case 7:
		{
			return 0x07; // 0000 0111 
		}
		break;
		case 8:
		{
			return 0x7F; // 0111 1111 
		}
		break;
		case 9:
		{
			return 0x6F; // 0110 1111 
		}
		break;
		case 10:
		{
			return 0x70; // 0111 0000 
		}
		break;
		case 11:
		{
			return 0x36; // 0011 0110 
		}
		break;
		default:
		{
			return 0x0;
		}	
	}
	return 0x0;
}
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    




