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










