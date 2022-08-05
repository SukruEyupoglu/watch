
#define LCD_EN (1 << 4)
#define LCD_RW (1 << 5)
#define LCD_RS (1 << 6)


void lcd_init_4_bit(void);
void lcd_send_4_bit(unsigned char data);


