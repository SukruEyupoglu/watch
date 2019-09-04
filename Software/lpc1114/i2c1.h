unsigned char i2c_write_1_char(unsigned char w_addr,unsigned char reg,unsigned char data);
unsigned char i2c_read_1_char(unsigned char w_addr,unsigned char r_addr,unsigned char reg,unsigned char *data);
unsigned char i2c_read_multi_char(unsigned char w_addr,unsigned char r_addr,unsigned char start_reg,unsigned char data[19]);
void i2c1_init(void);


