#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))
#define stop_alarm_button_pressed (LPC_GPIO2->DATA & (1 << 4))
#define sleep_button_pressed (LPC_GPIO2->DATA & (1 << 5))
#define boot_button_pressed (LPC_GPIO0->DATA & (1 << 1))
#define write_setting_button_pressed (LPC_GPIO3->DATA & (1 << 4))

unsigned char check_button(void)
{
  if(setting_alarm_button_pressed != 0)
  {
    return 201;
  }
  if(setting_clk_button_pressed != 0)
  {
    return 202;
  }
  if(stop_alarm_button_pressed != 0)
  {
    return 203;
  }
  if(sleep_button_pressed != 0)
  {
    return 204;
  }
  if(boot_button_pressed != 0)
  {
    return 205;
  }
  if(write_setting_button_pressed != 0)
  {
    return 206;
  }
  switch (adc_2_light_up_down_read())
  {
    case 5:
    {
      return 207;
    }
    case 20:
    {
      return 208;
    }
  switch (adc_1_time_up_down_read())
  {
    case 5:
    {
      return 209;
    }
    case 20:
    {
      return 210;
    }
}
