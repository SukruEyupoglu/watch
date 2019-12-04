/*
circle = 60 valid bit + 4 blank bit 
digit = 14 valid + 2 empty + 14 valid + 2 empty
unsigned long long int circle , z = 1 , v = 0;
circle = (z << 0) |     (v << 57) |
         (z << 1) |     (z << 58) |
         (v << 2) |     (z << 59);  // 60,61,62,63 is not matter,unvalid.
vb..
digit same as circle but 32 bit
*/

void latch(void);
void led_hex_write(unsigned long long int circle,unsigned int digit);
void led_write(unsigned char watch,unsigned char minute,unsigned char ref);
void blink(unsigned char blink_type,unsigned int blink_shiny_time,unsigned int blink_dim_time);
void yaz(void);




