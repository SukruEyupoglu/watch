


#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))
#define stop_alarm_button_pressed (LPC_GPIO2->DATA & (1 << 4))
#define sleep_button_pressed (LPC_GPIO2->DATA & (1 << 5))
#define boot_button_pressed (LPC_GPIO0->DATA & (1 << 1))
#define write_setting_button_pressed (LPC_GPIO3->DATA & (1 << 4))

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
#define SETTING_LRM 199
#define SETTING_CLK 198
#define SETTING_E2PROM_0xC00_0xFFF 196
#define SETTING_E2PROM_0x800_0xC00 192
#define SETTING_E2PROM_0x400_0x800 188
#define SETTING_E2PROM_0x300_0x400 184
#define SETTING_E2PROM_0x200_0x300 183
#define SETTING_E2PROM_0x100_0x200 182
#define SETTING_E2PROM_0x050_0x100 181
#define SETTING_E2PROM_0x000_0x050 180

void gpio_init(void);
unsigned char check_button(void);


