/*
#define SET_LRM 201
#define SET_CLK 202
#define STP_LRM 203
#define SLP 204
#define BOO 205
#define WRT_SET 206
#define LIG_DWN 207
#define LIG_UP 208
#define TM_DWN 209
#define TM_UP 210
*/


void setting(void)
{
  unsigned int ee_reg = 1;
  unsigned char set;
  unsigned char btn;
  unsigned char cho1,cho2;
  unsigned char mux = 1;
  systick_second_sleep(255);
  if(i2c(eeprom_addr,ee_reg,2,1,&set,1) == ERR)
  {
    error();
  }
  while(1)
  {
    led_write(set,(60 - ee_reg),((60 - ee_reg) - mux));
    cho1 = 0;
    while(1)
    {
      btn = check_button();
      switch(btn)
      {
        case 201:
          {
            systick_second_sleep(255);
            cho1 = 1;
          }
          break;
        case 202:
          {
            systick_second_sleep(255);
            cho1 = 1;
          }
          break;
        case 203:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case 204:
          {
            systick_second_sleep(1);
            cho1 = 1;
            cho2 = 1;
          }
          break;
        case 205:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case 206:
          {
            systick_second_sleep(255);
            cho1 = 1;
            cho2 = 1;
            
          }
          break;
        case 207:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case 208:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case 209:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(check_registered_data(ee_reg))
            {
              if(set)
              {
                set = 0;
              }
              else
              {
                set = 1;
              }
            }
            else
            {
              if(set == 255)
              {
                set = 0;
              }
              else
              {
                set++;
              }
            }
          }
          break;
        case 210:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(check_registered_data(ee_reg))
            {
              if(set)
              {
                set = 0;
              }
              else
              {
                set = 1;
              }
            }
            else
            {
              if(set == 0)
              {
                set = 255;
              }
              else
              {
                set--;
              }
            }
          }
          break;
        default:
          {
            set_blink(0,100000,100000);
          }
          break;
      }
      if(cho1)
      {
        break;
      }
    }
    if(cho2)
    {
      break;
    }
  }
}
// void led_write(unsigned char watch,unsigned char minute,unsigned char ref)
void set_blink(unsigned char typ,unsigned int dim_time,unsigned int shiny_time)
{
  unsigned char bl[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  if(typ)
  {
    bl[11] = led[11];
    bl[10] = led[10];
    bl[9] = led[9];
    bl[8] = led[8];
  }
  else
  {
    bl[7] = led[7];
    bl[6] = led[6];
    bl[5] = led[5];
    bl[4] = led[4];
    bl[3] = led[3];
    bl[2] = led[2];
    bl[1] = led[1];
    bl[0] = led[0];
  }
  yak(bl);
  delay(dim_time);
  yak(led);
  delay(shiny_time);
}
void yak(unsigned char sh[12])
{
  unsigned char f;
  for(f = 0 ; f < 12 ; f++)
  {
    spi( sh[f] );
  }
  latch();
}




