
#include "stm8s.h"

#define TIM1_SR_UIF 0
#define TIM1_IER_UIE 0
#define TIM1_CR1_OPM 3
#define TIM1_CR1_CEN 0

// * #define DS3231_ALARM_TYPE_MINUTE 0x08
// * #define DS3231_ALARM_TYPE_HOUR 0x09

void tim1_init(unsigned short sec);
unsigned char time2reg(unsigned char time);
unsigned char reg2time(unsigned char reg);
void place_ds3231_cursor(unsigned char x);

void write_ds3231_minute(unsigned char min_ute);
void write_ds3231_hour(unsigned char ho_ur);
void ds3231_time_write(unsigned char data ,unsigned char addr);
// * void ds3231_alarm_write(unsigned char data ,unsigned char type);

void button_init(void);
void check_boot_button(void);
void boot_button_first_pressed_function(void);
void boot_button_second_pressed_function(void);
void boot_button_third_pressed_function(void);
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

void increase_minute(void);
void decrease_minute(void);
void increase_hour(void);
void decrease_hour(void);


// #define DS3231_SECOND_ADDR 0x00
#define DS3231_MINUTE_ADDR 0x01
#define DS3231_HOUR_ADDR 0x02


#define BOOT_BUTTON_PRESS ( !( PA_IDR & (1 << 3) ) )
#define UP_BUTTON_PRESS ( !( PC_IDR & (1 << 3) ) )
#define DOWN_BUTTON_PRESS ( !( PD_IDR & (1 << 3) ) )

#define BUTTON_PRESSED 0

// active high
#define LATCH PC_ODR |= (1 << 4);PC_ODR &= ~(1 << 4)

unsigned char tim1_interrupt_flag = 0;
unsigned char blink_flag = 0;

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

	//unsigned char second;
	//unsigned char alarm_hour;
	//unsigned char alarm_minute;
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	
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
			minute = reg2time(d[DS3231_MINUTE_ADDR]) / 5;
			// DS3231 default 24 hour
			if(hour > 11)
			{
				hour = hour - 12 ;
			}
			// WRITE HOUR AND MINUTE
			spi( num2dig(hour) ); //first hour
			spi( num2dig(minute) ); //second minute
			LATCH;
			
			enable_interrupts();
		}
		if(tim1_interrupt_flag >= 1000)
		{
			tim1_interrupt_flag = 0;
		}
		if(blink_flag <= 5)
		{
			spi( num2dig(hour) | 0x80);
			spi( num2dig(minute) );
			LATCH;
		}
		else
		{
			spi( num2dig(hour) );
			spi( num2dig(minute) );
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
  TIM1_CR1    = 0;            // Disable TIM1
  TIM1_PSCRH = ( ( sec * 2 ) >> 8);
  TIM1_PSCRL = ( ( sec * 2 ) & 0xFF);
  TIM1_ARRH = 0xC3;
  TIM1_ARRL = 0x50;
  TIM1_CNTRH = 0;	
  TIM1_CNTRL = 0; // start from zero
  
  //TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  //TIM4_EGR 	= 1;
  TIM1_IER      |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  TIM1_CR1 = TIM1_CR1_CEN; // Enable the counter
}

unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}

void write_ds3231_minute(unsigned char min_ute)
{
    if(min_ute < 60)
    {
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write(DS3231_MINUTE_ADDR);
	    i2c_write(time2reg(min_ute) );
	    i2c_stop();
	    // RESET FLAGS FOR CONTINUE
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write(0x0E);
	    i2c_write(0x00);
	    //i2c_write(0x0F);
	    i2c_write(0x00);
	    i2c_stop();
    }
}
			    
void write_ds3231_hour(unsigned char ho_ur)
{
    if(ho_ur < 24)
    {
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write(DS3231_HOUR_ADDR);
	    i2c_write( (time2reg(ho_ur) );
	    i2c_stop();
	    // RESET FLAGS FOR CONTINUE
	    i2c_start();
	    i2c_write_addr(0xD0);
	    i2c_write(0x0E);
	    i2c_write(0x00);
	    //i2c_write(0x0F);
	    i2c_write(0x00);
	    i2c_stop();
    }
}

void ds3231_alarm_write(unsigned char ho_ur ,unsigned char min_ute)
{
	unsigned char edit;
 	switch(type)
	{
		case DS3231_ALARM_MINUTE_TYPE:
			{
				if(data < 60)
				{
					edit = data;
				}
				else
				{
					return;
				}
			}
			break;
		case DS3231_ALARM_HOUR_TYPE:
			{
				if(data < 24)
				{
					edit = data;
				}
				else
				{
					return;
				}
			}
			break;
		default:
			{
				return;
			}
	}
	i2c_start();
	i2c_write_addr(0xD0);
	i2c_write(addr);
	i2c_write( (time2reg(edit) );
	i2c_stop();
	// RESET FLAGS FOR CONTINUE
	i2c_start();
	i2c_write_addr(0xD0);
	i2c_write(0x0E);
	i2c_write(0x00);
	//i2c_write(0x0F);
	i2c_write(0x00);
	i2c_stop();
}
		      
void ds3231_time_write(unsigned char data ,unsigned char addr)
{
	unsigned char edit;
 	switch(addr)
	{
		case DS3231_MINUTE_ADDR:
			{
				if(data < 60)
				{
					edit = data;
				}
				else
				{
					return;
				}
			}
			break;
		case DS3231_HOUR_ADDR:
			{
				if(data < 24)
				{
					edit = data;
				}
				else
				{
					return;
				}
			}
			break;
		default:
			{
				return;
			}
	}
	i2c_start();
	i2c_write_addr(0xD0);
	i2c_write(addr);
	i2c_write( (time2reg(edit) );
	i2c_stop();
	// RESET FLAGS FOR CONTINUE
	i2c_start();
	i2c_write_addr(0xD0);
	i2c_write(0x0E);
	i2c_write(0x00);
	//i2c_write(0x0F);
	i2c_write(0x00);
	i2c_stop();
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
    disable_interrupts();
    while(BOOT_BUTTON_PRESS);
    // alarm stop
    boot_button_first_pressed_function();
    enable_interrupts();
  }
}

void boot_button_first_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
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

void increase_minute(void)
{
	if( minunte < 12 )
	{
		minute++;
	}
	else
	{
		minute = 0;
	}
		
	// WRITE HOUR AND MINUTE
	spi(0x00); //first hour
	spi( num2dig(minute) | 0x80); //second minute
	LATCH;
}

void decrease_minute(void)
{
	if( minunte == 0 )
	{
		minute = 11;
	}
	else
	{
		minute--;
	}
		
	// WRITE HOUR AND MINUTE
	spi(0x00); //first hour
	spi( num2dig(minute) | 0x80); //second minute
	LATCH;
}

void increase_hour(void)
{
	if( hour < 12 )
	{
		hour++;
	}
	else
	{
		hour = 0;
	}
		
	// WRITE HOUR AND MINUTE
	spi( num2dig(hour) | 0x80); //first hour
	spi(0x00); //second minute
	LATCH;
}

void decrease_hour(void)
{
	if( hour == 0 )
	{
		hour = 11;
	}
	else
	{
		hour--;
	}
		
	// WRITE HOUR AND MINUTE
	spi( num2dig(hour) | 0x80); //first hour
	spi(0x00); //second minute
	LATCH;
}
			    
void save_changes(void)
{
	write_ds3231_hour(hour);
	write_ds3231_minute(minute);
}
			    















			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    
			    



