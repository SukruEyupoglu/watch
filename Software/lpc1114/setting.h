/*
#define SET_LRM 201
#define SET_CLK 202
#define STP_LRM 203
#define SLP 204
#define BOO 205
#define WRT_SET 206
#define LIG_DWN 207
#define LIG_UP 208
#define TM_DWN 209
#define TM_UP 210
*/

void setting(void);
// void led_write(unsigned char watch,unsigned char minute,unsigned char ref)
void set_blink(unsigned char typ,unsigned int dim_time,unsigned int shiny_time);
void yak(unsigned char sh[12]);


