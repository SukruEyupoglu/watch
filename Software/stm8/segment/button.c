void button_init(void)
{
  //  MAKE PA3 BOOT BUTTON INPUT
  PA_DDR &= ~(1 << 3);
  //  MAKE PC3 UP BUTTON INPUT
  PC_DDR &= ~(1 << 3);  
  //  MAKE PD3 DOWN BUTTON INPUT
  PD_DDR &= ~(1 << 3);  
}

#define BOOT_BUTTON_PRESS ( PA_IDR & (1 << 3) )
#define UP_BUTTON_PRESS ( PC_IDR & (1 << 3) )
#define DOWN_BUTTON_PRESS ( PD_IDR & (1 << 3) )

#define BUTTON_PRESSED 0

void check_boot_button(void)
{
  if(BOOT_BUTTON_PRESS == BUTTON_PRESSED)
  {
    while( !(BOOT_BUTTON_PRESS == BUTTON_PRESSED) );
    turn_on_minute_dot_light();
    boot_button_first_pressed_function();
  }
}

void boot_button_first_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS == BUTTON_PRESSED)
    {
      turn_on_hour_dot_light();
      boot_button_second_pressed_function();
    }
    if(UP_BUTTON_PRESS == BUTTON_PRESSED)
    {
      increase_minute();
    }
    if(DOWN_BUTTON_PRESS == BUTTON_PRESSED)
    {
      decrease_minute();
    }
  }
}
void boot_button_second_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS == BUTTON_PRESSED)
    {
      boot_button_third_pressed_function();
    }
    if(UP_BUTTON_PRESS == BUTTON_PRESSED)
    {
      increase_hour();
    }
    if(DOWN_BUTTON_PRESS == BUTTON_PRESSED)
    {
      decrease_hour();
    }
  }
}
void boot_button_third_pressed_function(void)
{
  save_changes();
}
