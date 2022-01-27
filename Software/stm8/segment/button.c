void button_init(void)
{
  //  MAKE PA3 BOOT BUTTON INPUT
  PA_DDR &= ~(1 << 3);
  //  MAKE PC3 UP BUTTON INPUT
  PC_DDR &= ~(1 << 3);  
  //  MAKE PD3 DOWN BUTTON INPUT
  PD_DDR &= ~(1 << 3);  
}

#define BOOT_BUTTON_PRESS ( !( PA_IDR & (1 << 3) ) )
#define UP_BUTTON_PRESS ( !( PC_IDR & (1 << 3) ) )
#define DOWN_BUTTON_PRESS ( !( PD_IDR & (1 << 3) ) )

#define BUTTON_PRESSED 0

void check_boot_button(void)
{
  if(BOOT_BUTTON_PRESS)
  {
    while(BOOT_BUTTON_PRESS);
    turn_on_minute_dot_light();
    boot_button_first_pressed_function();
  }
}

void boot_button_first_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
      turn_on_hour_dot_light();
      boot_button_second_pressed_function();
      break;
    }
    if(UP_BUTTON_PRESS)
    {
      increase_minute();
      while(UP_BUTTON_PRESS);
    }
    if(DOWN_BUTTON_PRESS)
    {
      decrease_minute();
      while(DOWN_BUTTON_PRESS);
    }
  }
}
void boot_button_second_pressed_function(void)
{
  while(1)
  {
    if(BOOT_BUTTON_PRESS)
    {
      while(BOOT_BUTTON_PRESS);
      boot_button_third_pressed_function();
      break;
    }
    if(UP_BUTTON_PRESS)
    {
      increase_hour();
      while(UP_BUTTON_PRESS);
    }
    if(DOWN_BUTTON_PRESS)
    {
      decrease_hour();
      while(DOWN_BUTTON_PRESS);
    }
  }
}
void boot_button_third_pressed_function(void)
{
  save_changes();
}
