#include "spi.h"
#include "motor.h"


void release_motor(void)
{
  spi(SB);
  latch();
}

void hold_motor(unsigned char endurance_amount)
{
  
}

// step_type --> step_queue reduce double point and reduce motor torque
// 1 or 0
unsigned char motor_move(unsigned char step_count,unsigned char step_type)
{
  if(look_at_limit_switch_errors())
  {
    return ERROR;
  }
  
}

// RETURN VALUE IS MOTOR COIL STATUS AT STARTUP OR FINISH AND MOVE TO STARTUP OR FINISH
unsigned char move_to_find_limit_switch(unsigned char next_or_back)
{
  unsigned char f;
  if(next_or_back == NEXT)
  {
    while(1)
    {
      for(f = 0 ; f < 8 ; f++)
      {
        spi(step_queue[f]);
        latch();
        if(look_at_limit_switch_errors())
        {
          release_motor();
          spi(step_queue[f - 1]);
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
        spi(step_queue[f - 1]);
        latch();
        if(look_at_limit_switch_errors())
        {
          release_motor();
          spi(step_queue[f]);
          return f;
        }
      }
    }
  }
  return 0;
}















