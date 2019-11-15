#include "spi.h"
#include "motor.h"
#include "function.h"

void change_active_motor(unsigned char motor_number)
{
  // volatile unsigned char active_motor at main file
  active_motor = motor_number;
}
// use this rescue mosfet short circuit
// use this save current consumption
// beware dont use if you not wanted losing location data
void release_motor(void)
{
  spi(SB);
  latch();
}

unsigned char motor_next(unsigned char stat)
{
  switch(step_type)
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

unsigned char motor_back(unsigned char stat)
{
  switch(step_type)
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

void change_direction(void)
{
  if(direction == 0)
  {
    direction = 1;
  }
  else
  {
    direction = 0;
  }
}

unsigned char look_at_motor_status(void)
{
  return motor_status[active_motor];
}

void write_motor_status(last_motor_status)
{
  motor_status[active_motor] = last_motor_status;
}

void hold_motor(unsigned char endurance_amount)
{
  // one gpio must start pwm 
  // gpio connected from spi shift registers
}

// step_type --> step_queue reduce double point and reduce motor torque
// 0 or 1 or 2 power of steps , not distance (weak steps = long distances)
// --> 0 = increase 1 by 1 FULL_STEP
// --> 1 = increase 2 by 2 but only one coil QUARTER_STEP
// --> 2 = increase 2 by 2 but with two coil HALF_STEP
// direction 1 = next , 0 = back
unsigned char motor_move(unsigned char step_count,unsigned char speed)
{
  unsigned char f,mot_sta;
  mot_sta = look_at_motor_status();
  // if there are starting errors call clerk
  if(look_at_limit_switch_errors())
  {
    return FATAL_ERROR; // there are unexpecting limit switch status
  }  
  for(f = 0 ; f < step_count ; f++)
  {
    if(speed)
    {
      // with hold and release
      // not consume too many current use pwm for waiting
      motor_delay(speed);
    }
    
    if(active_motor_direction)
    {
      mot_sta = motor_next(mt_sta,step_type);
    }
    else
    {
      mot_sta = motor_back(mt_sta,step_type);      
    }
    // mosfet short circuit rescue
    // release_motor(); // place STANDBY before every step if u need
    spi(step_queue[mot_sta]);
    latch();
    if(look_at_limit_switch_errors())
    {
      // rescue from error status immadietaly
      if(active_motor_direction)
      {
        // reverse one step
        mot_sta = motor_back(mt_sta,step_type); 
        // NOT LIKE THIS mot_sta = motor_next(mt_sta,step_type);
      }
      else
      {
        // reverse one step
        mot_sta = motor_next(mt_sta,step_type);
        // NOT LIKE THIS mot_sta = motor_back(mt_sta,step_type);      
      }
      spi(step_queue[mot_sta]);
      latch();
      return ACTIVE_AREA_LIMIT_ERROR;
    }      
  }
  // release_motor(); // STANDBY without current
  // hold_motor();    // HOLD current consuption
  write_motor_status(mot_sta);
  return OK;
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
          latch();
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
          latch();
          return f;
        }
      }
    }
  }
  return 0;
}















