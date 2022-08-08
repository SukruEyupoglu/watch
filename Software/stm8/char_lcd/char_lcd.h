





#define LCD_EN (1 << 4) // falling edge triggered
#define LCD_RW (1 << 5) // 0 = write , 1 = read
#define LCD_RS (1 << 6) // 0 = command , 1 = data


void lcd_init_4_bit(void);
void lcd_send_4_bit(unsigned char data);


