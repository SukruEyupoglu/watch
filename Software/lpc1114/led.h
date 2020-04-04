
void led_init(void);

void set_led_write_reg(unsigned char minute,unsigned char hour);

void led_write(void);

void limit_yaz(unsigned char x,unsigned char y);
void limit_sil(unsigned char x,unsigned char y);

void led_yan(unsigned char xx);
void led_son(unsigned char xx);

void led_zero(void);
void led_one(void);

void led_write_digit(unsigned char left,unsigned char right);

void latch(void);

#define ONE 1
#define ZERO 0




