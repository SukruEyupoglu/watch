/*
//#include "LPC11xx.h"
// TIMER COUNTER COUNT 1MHZ AT SECOND
// I2C 400KHZ AT SECOND
// 1 BYTE = 8 BIT --> WITHOUT START STOP PULSE 400000/8 = 50000 --> 1000000/50000 = 20
// 1 BYTE TRANFERED AT 20 COUT TO TIMER
// DOUBLE TIME ENOUGH FOR WAIT 20*2 = 40
#define I2C_TIMEOUT 40
unsigned int I2C_ERROR = 0 ;
*/

void i2c_init_timer(void);
void i2c_write_timer(unsigned char addr,unsigned char reg,unsigned char data);
unsigned char i2c_read_timer(unsigned char write_addr,unsigned char read_addr,unsigned char reg);
void i2c_init(void);
void i2c_write(unsigned char addr,unsigned char reg,unsigned char data);
unsigned char i2c_read(unsigned char write_addr,unsigned char read_addr,unsigned char reg);





