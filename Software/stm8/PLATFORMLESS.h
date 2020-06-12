
void int_to_char(unsigned int data,unsigned char * part0,unsigned char * part1,unsigned char * part2,unsigned char * part3);
void char_to_int(unsigned int * data,unsigned char part0,unsigned char part1,unsigned char part2,unsigned char part3);
void short_to_char(unsigned short data,unsigned char * part0,unsigned char * part1);
void char_to_short(unsigned short * data,unsigned char part0,unsigned char part1);
void longlong_to_int(unsigned long long data,unsigned int * part0,unsigned int * part1);
void int_to_longlong(unsigned long long * data,unsigned int part0,unsigned int part1);

void delay(volatile unsigned int bekle);

unsigned char check_hex_data(unsigned char data);

unsigned char ascii_to_hex(unsigned char data);
unsigned char hex_to_ascii(unsigned char data);
void Char_To_Bit(unsigned char bit);
