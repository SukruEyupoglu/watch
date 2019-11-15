#include "spi.h"
#include "motor.h"


void release_motor(void)
{
  spi(SB);
  latch();
}

unsigned char motor_next(unsigned char stat,unsigned char type)
{
  switch(type)
  {
    case FULL_STEP:
      {
        // one by one // "7" is last step total 8 step (0-7)
        if(stat >= 7)
        {
          return 0;
        }
        else
        {
          return (stat + 1);
        }
      }
      break;
    case HALF_STEP:
      {
        if(stat % 2)
        {
          // move 2 by 2 with single numbers (1,3,5,7) 4 step total
          if(stat >= 7)
          {
            return 1;
          }
          else
          {
            return (stat + 2);
          }
        }
        else
        {
          return (stat + 1);
        }
      }
      break;
    case QUARTER_STEP:
      {
        if(stat % 2)
        {
          // if sigle number and last number move to start and dual numbers
          if(stat >= 7)
          {
            return 0;
          }
          else
          {
            return (stat + 1);
          }
        }
        else
        {
          // two by two // "6" is last step total 4 step (0,2,4,6)
          if(stat >= 6)
          {
            return 0;
          }
          else
          {
            return (stat + 2);
          }
        }        
      }
      break;
    default:
      {
        
      }
      break;     
  }
}

unsigned char motor_back(unsigned char stat,unsigned char type)
{
  switch(type)
  {
    case FULL_STEP:
      {
        // one by one // "7" is last step total 8 step (0-7)
        if(stat == 0)
        {
          return 7;
        }
        else
        {
          return (stat - 1);
        }
      }
      break;
    case HALF_STEP:
      {
        if(stat == 0)
        {
          return 7;
        }
        if(stat % 2)
        {
          // move 2 by 2 with single numbers (1,3,5,7) 4 step total
          if(stat == 1)
          {
            return 7;
          }
          else
          {
            return (stat - 2);
          }
        }
        else
        {
          return (stat - 1);
        }
      }
      break;
    case QUARTER_STEP:
      {
        if(stat % 2)
        {
          // if sigle number and last number move to start and dual numbers
          if(stat == 1)
          {
            return 6;
          }
          else
          {
            return (stat - 1);
          }
        }
        else
        {
          // two by two // "6" is last step total 4 step (0,2,4,6)
          if(stat == 0)
          {
            return 6;
          }
          else
          {
            return (stat - 2);
          }
        }        
      }
      break;
    default:
      {
        
      }
      break;     
  }
}


unsigned char motor_back(unsigned char stat,unsigned char type)
{
  
}

unsigned char motor_status(void)
{
  
}

void hold_motor(unsigned char endurance_amount)
{
  
}

// step_type --> step_queue reduce double point and reduce motor torque
// 0 or 1 or 2 power of steps , not distance (weak steps = long distances)
// --> 0 = increase 1 by 1 FULL_STEP
// --> 1 = increase 2 by 2 but only one coil QUARTER_STEP
// --> 2 = increase 2 by 2 but with two coil HALF_STEP
// direction 1 = next , 0 = back
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















