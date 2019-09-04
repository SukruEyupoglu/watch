/*
    
#define e2prom_addr 0xA2
#define eeprom_last_addr 0xFFF
// 0xFFF = 4095
// 8. byte alert before namaz time if 1 look at 9. byte for how many minute
// 9. byte minute for prepare for namaz default 0
#define before_namaz_alert_addr 0x008
#define minute_for_before_namaz_alert_addr 0x009
// A. byte exta alert number how many alert saved read from here
#define how_many_extra_alert_addr 0x00A
*/

void i2c_100khz_e2prom_init(void);
unsigned char i2c_write_e2prom_32byte_1page(unsigned char ic_addr,unsigned short write_start_addr,unsigned char data[32]);
unsigned char i2c_write_e2prom_1_char(unsigned char ic_addr,unsigned short write_addr,unsigned char data);
unsigned char i2c_read_e2prom_1_char(unsigned char ic_addr,unsigned short read_addr,unsigned char * data);
unsigned char i2c_read_e2prom_multi_char(unsigned char ic_addr,unsigned short read_addr,unsigned char * data,unsigned short size);





