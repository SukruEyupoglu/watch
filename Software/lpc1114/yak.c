void pre_setting(void)
{
  
}
void setting(unsigned char set_number)
{
  unsigned char counter = 0;
  while(1)
  {
    button_repress_delay(); // maybe inside check_button ?
    switch(check_button())
    {
      case setting_select_button_up:
        {
          
        }
        break;
      case setting_select_button_down:
        {
          
        }
        break;
    }
  }
}
