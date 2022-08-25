

//#define LCD_EN (1 << 4) // falling edge triggered
//#define LCD_RW (1 << 5) // 0 = write , 1 = read
//#define LCD_RS (1 << 6) // 0 = command , 1 = data


void char_lcd_cmd(unsigned char cmd);
void char_lcd_data(unsigned char data);
void char_lcd_4_bit_init(void);
void char_lcd(unsigned char data[20] , unsigned char size);



