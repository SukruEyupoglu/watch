#include "spi.h"
#include "motor.h"

unsigned char motor_move(unsigned char data)
{
  
}
void find_motor_coil_point(void)
{
  // move_to_safe_head();
  while(look_at_limit_switch_errors())
  {
    move_to_find_limit_switch(); // forward or backward selectable
  }
  get_status_of_motor_register_and_reverse_is_first_step of motor();
  
}
unsigned char move_to_find_limit_switch(unsigned char next_or_back)
{
  unsigned char f;
  if(next_or_back == NEXT)
  {
    while(1)
    {
      for(f = 0 ; f < 8 ; f++)
      {
        spi(step_type[f]);
        if(look_at_limit_switch_errors())
        {
          return f;
        }
      }
    }
  }
  if(next_or_back == BACK)
  {
    while(1)
    {
      for(f = 8 ; f > 0 ; f--)
      {
        spi(step_type[f - 1]);
        if(look_at_limit_switch_errors())
        {
          return f;
        }
      }
    }
  }
  return 0;
}















