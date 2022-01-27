


#define BOOT_BUTTON_PRESS ( !( PA_IDR & (1 << 3) ) )
#define UP_BUTTON_PRESS ( !( PC_IDR & (1 << 3) ) )
#define DOWN_BUTTON_PRESS ( !( PD_IDR & (1 << 3) ) )

#define BUTTON_PRESSED 0

void button_init(void);
void check_boot_button(void);
void boot_button_first_pressed_function(void);
void boot_button_second_pressed_function(void);
void boot_button_third_pressed_function(void);





