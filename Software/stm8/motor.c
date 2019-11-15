#include "spi.h"
#include "motor.h"


void release_motor(void)
{
  spi(SB);
  latch();
}

unsigned char motor_next(unsigned char stat,unsigned char double_or_single)
{
  
}

unsigned char motor_back(unsigned char stat,unsigned char double_or_single)
{
  
}

unsigned char motor_status(void)
{
  
}

void hold_motor(unsigned char endurance_amount)
{
  
}

// step_type --> step_queue reduce double point and reduce motor torque
// 0 or 1 or 2 
// --> 0 = increase 1 by 1
// --> 1 = increase 2 by 2 but only one coil
// --> 2 = increase 2 by 2 but with two coil
unsigned char motor_move(unsigned char step_count,unsigned char step_type,unsigned char speed,unsigned char direction)
{
  unsigned char f,mt_sta;
  mt_sta = motor_status();
  for(f = 0 ; f < step_count ; f++)
  {
    if(look_at_limit_switch_errors())
    {
      return ERROR;
    }
    if(speed)
    {
      // with hold and release
      // not consume too many current
      motor_delay(speed);
    }
    if(direction)
    {
      mt_sta = motor_next(mt_sta,step_type);
    }
    else
    {
      mt_sta = motor_back(mt_sta,step_type);      
    }
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















