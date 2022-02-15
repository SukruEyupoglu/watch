
#include "stm8s.h"

#define TIM1_SR_UIF 0
#define TIM1_IER_UIE 0
#define TIM1_CR1_OPM 3
#define TIM1_CR1_CEN 0

void tim1_init(unsigned short sec);
unsigned char time2reg(unsigned char time);
unsigned char reg2time(unsigned char reg);
void place_ds3231_cursor(unsigned char x);

void button_init(void);

void check_boot_button(void);
void setting_minute(void); // first press boot button
void setting_hour(void); // second press boot button

unsigned char num2dig(unsigned char num);
void spi_init(void);
unsigned char spi(unsigned char data);
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
void i2c_write_addr(uint8_t addr);
uint8_t i2c_read();
void i2c_read_arr(uint8_t *buf, int len);

void beep_init(unsigned char beep_freq);
void beep_deinit(void);

void increase_minute(void);
void decrease_minute(void);
void increase_hour(void);
void decrease_hour(void);

#define DS3231_MINUTE_ADDR 0x01
#define DS3231_HOUR_ADDR 0x02
#define DS3231_STATUS_ADDR 0x0F

#define DS3231_ALARM_MINUTE_ADDR 0x08
#define DS3231_ALARM_HOUR_ADDR 0x09
#define A1M4 0xC0

#define BOOT_BUTTON_PRESS ( !( PA_IDR & (1 << 3) ) )
#define UP_BUTTON_PRESS ( !( PC_IDR & (1 << 3) ) )
#define DOWN_BUTTON_PRESS ( !( PD_IDR & (1 << 3) ) )

#define BUTTON_PRESSED 0

// active high
#define LATCH PC_ODR |= (1 << 4);PC_ODR &= ~(1 << 4)

unsigned short tim1_interrupt_flag = 0;
unsigned char blink_flag = 0;
unsigned char setting_flag = 0;

unsigned char hour = 0;
unsigned char minute = 0;

unsigned char d[0x13];

void timer_isr() __interrupt(TIM1_OVF_ISR) {
  tim1_interrupt_flag++;
  blink_flag++;
  TIM1_SR1 &= ~(1 << TIM1_SR_UIF);
}



int main(void)
{
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	
	BEEP_CSR = 0; // close beep look at datasheet
	
	i2c_init();
	spi_init();
	
	button_init();
	
	// latch init
	PC_DDR |= (1 << 4); // direction output
	PC_CR1 |= (1 << 4); // make push-pull
	PC_ODR &= ~(1 << 4);// make low first
		
	tim1_init(1);	// nearly 100ms 
		
	while(1)
	{
		if(tim1_interrupt_flag <= 1)
		{
			disable_interrupts();
			place_ds3231_cursor(0x00);
			// GET ALL DATA FROM DS3231 TO d[0x13]
			i2c_start();
			i2c_write_addr(0xD1); // read
			i2c_read_arr(d,0x13); // inside i2c_stop(); there are 
			
			hour = reg2time(d[DS3231_HOUR_ADDR]);
			minute = reg2time(d[DS3231_MINUTE_ADDR]);
			// WRITE HOUR AND MINUTE
			// DS3231 default 24 hour
			if(hour > 11)
			{
				spi( num2dig(hour - 12) ); //first hour
			}
			else
			{
				spi( num2dig(hour) ); //first hour
			}
			spi( num2dig(minute / 5) ); //second minute
			LATCH;
			if( ( (minute == reg2time(d[DS3231_ALARM_MINUTE_ADDR]) ) |
				  (minute == reg2time(d[DS3231_ALARM_MINUTE_ADDR]) + 1)
				) &
				(d[DS3231_HOUR_ADDR] == d[DS3231_ALARM_HOUR_ADDR] ) )
			//if( (d[DS3231_MINUTE_ADDR] == d[DS3231_ALARM_MINUTE_ADDR] ) & (d[DS3231_HOUR_ADDR] == d[DS3231_ALARM_HOUR_ADDR] ) )
			// if( (d[DS3231_STATUS_ADDR] & (1 << 0) ) == (1 << 0) )
			{
				beep_init(0);
			}
			else
			{
				if((BEEP_CSR & (1 << 5) ) == (1 << 5) ) // close alarm if alarm warning nearly 1 minute later
				{
					beep_deinit();
				}
			}
			
			
			enable_interrupts();
		}
		if(tim1_interrupt_flag >= 1000)
		{
			tim1_interrupt_flag = 0;
		}
		if(blink_flag <= 5)
		{
			if(hour > 11)
			{
				spi( num2dig(hour - 12) | 0x80); //first hour
			}
			else
			{
				spi( num2dig(hour) | 0x80); //first hour
			}
			spi( num2dig(minute / 5) );
			LATCH;
		}
		else
		{
			if(hour > 11)
			{
				spi( num2dig(hour - 12) ); //first hour
			}
			else
			{
				spi( num2dig(hour) ); //first hour
			}
			spi( num2dig(minute / 5) );
			LATCH;
			
			if(blink_flag >= 11)
			{
				blink_flag = 0;
			}
			
		}
		
		check_boot_button();
	}
}

void tim1_init(unsigned short sec)
{
  // THIS TIMER MAKED FOR LONG TIMING , ONLY SECOND
  // frequency = F_CLK / ( ( (TIM1_PSCRH << 8) + TIM1_PSCRL) * (1 + ( (TIM1_ARRH << 8) + TIM1_ARRL) ) )
  TIM1_CR1    &= ~(1 << 0);            // Disable TIM1
  TIM1_PSCRH = ( ( sec * 2 ) >> 8);
  TIM1_PSCRL = ( ( sec * 2 ) & 0xFF);
  TIM1_ARRH = 0xC3;
  TIM1_ARRL = 0x50;
  TIM1_CNTRH = 0;	
  TIM1_CNTRL = 0; // start from zero
  
  //TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  //TIM4_EGR 	= 1;
  TIM1_IER      |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  //TIM1_CR1 |= TIM1_CR1_CEN; // Enable the counter
	TIM1_CR1 |= (1 << 0);
}

unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}

void place_ds3231_cursor(unsigned char x)
{
			// RESET FLAGS FOR CONTINUE
		i2c_start();
		i2c_write_addr(0xD0);
		i2c_write(0x0E);
		i2c_write(0x00); 
		i2c_write(0x00); //i2c_write(0x0F);
		i2c_stop();
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
  unsigned char time_or_alarm_flag = 2;
  if(BOOT_BUTTON_PRESS)
  {
    disable_interrupts();
    while(BOOT_BUTTON_PRESS)
    {
	if(UP_BUTTON_PRESS)
    	{
      		while(UP_BUTTON_PRESS);
		time_or_alarm_flag = 1;
		hour = reg2time(d[DS3231_ALARM_HOUR_ADDR]);
		minute = reg2time(d[DS3231_ALARM_MINUTE_ADDR]);
			if(hour > 11)
			{
				spi( num2dig(hour - 12) ); //first hour
			}
			else
			{
				spi( num2dig(hour) ); //first hour
			}
		spi( num2dig(minute / 5) );
		LATCH;
    	}
	if(DOWN_BUTTON_PRESS)
    	{
      		while(DOWN_BUTTON_PRESS);
		time_or_alarm_flag = 0;
		hour = reg2time(d[DS3231_HOUR_ADDR]);
		minute = reg2time(d[DS3231_MINUTE_ADDR]);
			if(hour > 11)
			{
				spi( num2dig(hour - 12) ); //first hour
			}
			else
			{
				spi( num2dig(hour) ); //first hour
			}
		spi( num2dig(minute / 5) | 0x80);
		LATCH;
    	}
			if(hour > 11)
			{
				spi( num2dig(reg2time(d[DS3231_ALARM_HOUR_ADDR]) - 12) ); //first hour
			}
			else
			{
				spi( num2dig(reg2time(d[DS3231_ALARM_HOUR_ADDR]) ) ); //first hour
			}
	spi( num2dig(reg2time(d[DS3231_ALARM_MINUTE_ADDR]) / 5) );
	LATCH;	    
    }
	if(time_or_alarm_flag == 2)
	{
		beep_deinit(); // close alarm
		enable_interrupts();
		return;
	}
	  
	setting_minute(); // set minute and hour
	if(setting_flag == 1)
	{
		i2c_start();
		i2c_write_addr(0xD0);
		if(time_or_alarm_flag == 1)
		{
			i2c_write(0x08); // ds3231 alarm minute addr
			i2c_write( (time2reg(minute) ) );
			i2c_write( (time2reg(hour) ) );
			i2c_write( A1M4 );
		}
		else
		{
			i2c_write(0x01); // ds3231 alarm minute addr
			i2c_write( (time2reg(minute) ) );
			i2c_write( (time2reg(hour) ) );
		}
		i2c_stop();
		// RESET FLAGS FOR CONTINUE
		i2c_start();
		i2c_write_addr(0xD0);
		i2c_write(0x0E);
		i2c_write(0x00); 
		i2c_write(0x00); //i2c_write(0x0F);
		i2c_stop();
	}
	beep_deinit(); // close alarm
	enable_interrupts();
	setting_flag = 0;
  }
}

void setting_minute(void) // first press boot button
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
      setting_hour();
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

void setting_hour(void) // second press boot button
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
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
			return 0x6D; // 0110 1101 
		}
		break;
		case 6:
		{
			return 0x7D; // 0111 1101 
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
		break;
	}
	//return 0x0;
}
			    
void spi_init(void)
{
  // 500KHZ spi clk
  // SPI_CR1_MSTR  = spi master bit
  // SPI_CR1_SPE = spi enable bit
  // SPI_CR1_BR = baud rate bits[3,4,5] divider 
  // SPI_CR1_BR = 000; --> FMASTER / 2 --> 16 / 2 = 8 mhz
  // SPI_CR1_BR = 100; --> FMASTER / 32 --> 16 / 32 = 500 khz
  // SPI_CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE) | (1 << SPI_CR1_BR1);
  
  // 8MHZ spi clk
  SPI_CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE);
  // NOT CHANGE THIS READ DATASHEET
  //SPI_CR2 = (1 << SPI_CR2_SSM) | (1 << SPI_CR2_SSI) | (1 << SPI_CR2_BDM) | (1 << SPI_CR2_BDOE);
}

unsigned char spi(unsigned char data)
{
  while ( (SPI_SR & (1 << SPI_SR_TXE) ) != (1 << SPI_SR_TXE) );
  SPI_DR = data;
  while ( (SPI_SR & (1 << SPI_SR_RXNE) ) != (1 << SPI_SR_RXNE) );
  return SPI_DR;
}

void i2c_init(void) {
    I2C_CR1 = 0;
    I2C_FREQR = 0x10; // 16MHZ peripheral clock (not master clock)
    I2C_CCRL = 0x1A; // 400kHz
    I2C_CCRH = ( 0x0D | (1 << 7) );
    I2C_OARH = (1 << I2C_OARH_ADDMODE); // 7-bit addressing
    I2C_CR1 = (1 << I2C_CR1_PE);
}
/*
void i2c_init() { // 100khz
    I2C_CR1 = 0;
    I2C_FREQR = 1;
    I2C_CCRL = 0x32; // 100kHz
    I2C_OARH = (1 << I2C_OARH_ADDMODE); // 7-bit addressing
    I2C_CR1 = (1 << I2C_CR1_PE);
}
*/
/*
void i2c_init() { 
    I2C_CR1 = 0;
    I2C_FREQR = (1 << I2C_FREQR_FREQ1);
    I2C_CCRL = 0x0A; // 100kHz
    I2C_OARH = (1 << I2C_OARH_ADDMODE); // 7-bit addressing
    I2C_CR1 = (1 << I2C_CR1_PE);
}
*/
void i2c_start(void) {
    I2C_CR2 |= (1 << I2C_CR2_START);
    while (!(I2C_SR1 & (1 << I2C_SR1_SB)));
}

void i2c_stop(void) {
    I2C_CR2 |= (1 << I2C_CR2_STOP);
    while (I2C_SR3 & (1 << I2C_SR3_MSL));
}

void i2c_write(uint8_t data) {
    I2C_DR = data;
    while (!(I2C_SR1 & (1 << I2C_SR1_TXE)));
}

void i2c_write_addr(uint8_t addr) {
    I2C_DR = addr;
    while (!(I2C_SR1 & (1 << I2C_SR1_ADDR)));
    (void) I2C_SR3; // check BUS_BUSY
    I2C_CR2 |= (1 << I2C_CR2_ACK);
}

uint8_t i2c_read() {
    I2C_CR2 &= ~(1 << I2C_CR2_ACK);
    i2c_stop();
    while (!(I2C_SR1 & (1 << I2C_SR1_RXNE)));
    return I2C_DR;
}

void i2c_read_arr(uint8_t *buf, int len) {
    while (len-- > 1) {
        I2C_CR2 |= (1 << I2C_CR2_ACK);
        while (!(I2C_SR1 & (1 << I2C_SR1_RXNE)));
        *(buf++) = I2C_DR;
    }
    *buf = i2c_read();
}

// beep frequency 500hz,1Khz,2Khz,4Khz
// 0 = 500hz , 1 = 1Khz , 2 = 2Khz , 4 = 4Khz
void beep_init(unsigned char beep_freq)
{
  BEEP_CSR = ( (1 << 5) | (32 / (2 * beep_freq) ) );
}

void beep_deinit(void)
{
  	BEEP_CSR = 0;
	// RESET FLAGS FOR CONTINUE
	i2c_start();
	i2c_write_addr(0xD0);
	i2c_write(0x0E);
	i2c_write(0x00); 
	i2c_write(0x00); //i2c_write(0x0F);
	i2c_stop();
}

void increase_minute(void)
{
	if( minute < 59 )
	{
		minute++;
	}
	else
	{
		minute = 0;
	}
	setting_flag = 1;
	// WRITE MINUTE TWO DIGIT
	spi( num2dig(minute / 10) ); //first write decimal second char
	spi( num2dig(minute % 10) | 0x80); //second write decimal first char
	LATCH;
}

void decrease_minute(void)
{
	if( minute == 0 )
	{
		minute = 59;
	}
	else
	{
		minute--;
	}
	setting_flag = 1;
	// WRITE MINUTE TWO DIGIT
	spi( num2dig(minute / 10) ); //first write decimal second char
	spi( num2dig(minute % 10) | 0x80); //second write decimal first char
	LATCH;
}

void increase_hour(void)
{
	if( hour < 23 )
	{
		hour++;
	}
	else
	{
		hour = 0;
	}
	setting_flag = 1;
	// WRITE HOUR TWO DIGIT
	spi( num2dig(hour / 10) ); //first write decimal second char
	spi( num2dig(hour % 10) | 0x80); //second write decimal first char
	LATCH;
}

void decrease_hour(void)
{
	if( hour == 0 )
	{
		hour = 23;
	}
	else
	{
		hour--;
	}
	setting_flag = 1;
	// WRITE HOUR TWO DIGIT
	spi( num2dig(hour / 10) ); //first write decimal second char
	spi( num2dig(hour % 10) | 0x80); //second write decimal first char
	LATCH;
}















			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    




