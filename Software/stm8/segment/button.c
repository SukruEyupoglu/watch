void button_init(void)
{
  //  MAKE PA3 BOOT BUTTON INPUT
  PA_DDR &= ~(1 << 3);
  //  MAKE PC3 UP BUTTON INPUT
  PC_DDR &= ~(1 << 3);  
  //  MAKE PD3 DOWN BUTTON INPUT
  PD_DDR &= ~(1 << 3);  
}



void check_boot_button(void)
{
  if(BOOT_BUTTON_PRESS == TRUE)
  {
    while(BOOT_BUTTON_PRESS == FALSE);
    
  }
  
  
  
}
