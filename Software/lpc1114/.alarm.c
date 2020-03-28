#define scream 1
#define quiet 0
// array for using settings start 0x001 not 0x000 and 0x000 is empty
// all address stored  +1 to arrays
#define E2PROM_NAMAZ_ALERT_SETTING_ADDR 0x001             // 1 or 0
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR 0x002      // 1 or 0
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR 0x003      // 1 or 0
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR 0x004       // 1 or 0
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR 0x005     // 1 or 0
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR 0x006      // 1 or 0
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR 0x007      // 1 or 0
#define BEFORE_NAMAZ_SETTING_ADDR 0x008                   // 1 or 0
#define MINUTE_FOR_BEFORE_NAMAZ_SETTING_ADDR 0x009        // max 60 minute
#define EXTRA_ALRT_NUMBER_SETTING_ADDR 0x00A              // max 10 alert
#define HOURLY_ALERT_SETTING_ADDR 0x00B                   // 1 or 0
#define NUMBER_HOURLY_ALERT_SETTING_ADDR 0x00C            // 1 or 2 or 3 or 4 or 6 or 12 or 24
#define EXTRA_ALARM_START_ADDR 0x03D // 61                // 
#define EXTRA_ALARM_LAST_ADDR 0x064 // 100                // 
/*
#define e2prom_addr 0xA2
#define eeprom_last_addr 0xFFF
// 0xFFF = 4095
// 8. byte alert before namaz time if 1 look at 9. byte for how many minute
// 9. byte minute for prepare for namaz default 0
#define before_namaz_alert_addr 0x008
#define minute_for_before_namaz_alert_addr 0x009
// A. byte exta alert number how many alert saved read from here
#define how_many_extra_alert_addr 0x00A
// extra alarm start addr 0x03D == 61
// max extra alarm = 10
0x03D = dakika
0x03E = saat
0x03F = gun
0x040 = ay
if gun and ay equal to zero then daily alarm so every day of year
*/

unsigned char check_alarm(ds_t * ds3231,unsigned char * eeprom_data)
{
// namaz const related alert check
  if( * eeprom_data == 1)
  {
    if((* (ayar + 0x007) == 1) & (* (ayar + 0x008) < 61))
    {
         if((* (ayar + 0x008) + ds3231.minute) < 60)
         {
           if(check_namaz_for_alert((ds3231.minute + (* (ayar + 0x007))),ds3231.hour,ds3231.day,ds3231.mount,&eeprom_data))
            {
              return scream;
            }                       
         }
         else
         {
           if(check_namaz_for_alert((ds3231.minute + (* (ayar + 0x007))) - 60,ds3231.hour + 1,ds3231.day,ds3231.mount,&eeprom_data))
            {
              return scream;
            }                                  
         }
    }
    else
    {
      if(check_namaz_for_alert(ds3231.minute,ds3231.hour,ds3231.day,ds3231.mount,&eeprom_data))
      {
        return scream;
      }
    }
  }
// eeprom saved alert check  
  if (  * (eeprom_data + 0x009) != 0)
  {
    if(check_eeprom_alert(ds3231.minute,ds3231.hour,ds3231.day,ds3231.mount,&eeprom_data))
    {
      return scream;    
    }
  }
// ds3231 related alarm check
  if(check_ds3231_alert(ds3231.minute,ds3231.hour,alarm1_minute,alarm1_hour__am_pm))
  {
    return scream;    
  }
  return quiet;
}
unsigned char check_ds3231_alert(unsigned char dakika,unsigned char saat,unsigned char alarm_dakika,unsigned char alarm_saat)
{
  if((dakika == alarm_dakika) & (saat == alarm_saat))
  {
    return scream;
  }
}
  
unsigned char check_eeprom_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay,unsigned char * number)
{
  unsigned char f;
  unsigned char ayar[40];
  if(i2c(eeprom_addr,0x03D,2,1,ayar,40) == ERR)
  {
    error();
  }
  for(f = 0 ; f < * (number + 0x009); f++)
  {
    if((ayar[f * 4] == dakika) &
       (ayar[(f * 4) + 1] == saat) &
       (ayar[(f * 4) + 2] == gun) | (ayar[(f * 4) + 2] == 0)) &
       (ayar[(f * 4) + 3] == gun) | (ayar[(f * 4) + 3] == 0)))
    {
      return scream;
    }
  }
  if( * (number + 0x00A) == 1)
  {
    if((dakika == 0) & ((saat == 0) | ((saat % (* (number + 0x00B))) == 0))
    {
      return scream;
    }
  }
  return quiet;
}

unsigned char check_namaz_for_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay,unsigned char * ayar)
{
  unsigned char f;
  unsigned char sabah_saat,gunes_saat,ogle_saat,ikindi_saat,aksam_saat,yatsi_saat;
  unsigned char sabah_dakika,gunes_dakika,ogle_dakika,ikindi_dakika,aksam_dakika,yatsi_dakika;
  unsigned int sgo = namaz[ay][gun][1];
  unsigned int iay = namaz[ay][gun][2];
  for(f = 26 ; f < 30 ; f++)
  {
    if(sgo & (1 << f))
    {
      sabah_saat |= (1 << (f - 26));
    }
  }
  for(f = 20 ; f < 26 ; f++)
  {
    if(sgo & (1 << f))
    {
      sabah_dakika |= (1 << (f - 20));
    }
  }
    for(f = 16 ; f < 20 ; f++)
  {
    if(sgo & (1 << f))
    {
      gunes_saat |= (1 << (f - 16));
    }
  }
    for(f = 10 ; f < 16 ; f++)
  {
    if(sgo & (1 << f))
    {
      gunes_dakika |= (1 << (f - 10));
    }
  }
    for(f = 6 ; f < 10 ; f++)
  {
    if(sgo & (1 << f))
    {
      ogle_saat |= (1 << (f - 6));
    }
  }
    for(f = 0 ; f < 6 ; f++)
  {
    if(sgo & (1 << f))
    {
      ogle_dakika |= (1 << (f - 0));
    }
  }
  
  for(f = 26 ; f < 30 ; f++)
  {
    if(iay & (1 << f))
    {
      ikindi_saat |= (1 << (f - 26));
    }
  }
  for(f = 20 ; f < 26 ; f++)
  {
    if(iay & (1 << f))
    {
      ikindi_dakika |= (1 << (f - 20));
    }
  }
    for(f = 16 ; f < 20 ; f++)
  {
    if(iay & (1 << f))
    {
      aksam_saat |= (1 << (f - 16));
    }
  }
    for(f = 10 ; f < 16 ; f++)
  {
    if(iay & (1 << f))
    {
      aksam_dakika |= (1 << (f - 10));
    }
  }
    for(f = 6 ; f < 10 ; f++)
  {
    if(iay & (1 << f))
    {
      yatsi_saat |= (1 << (f - 6));
    }
  }
    for(f = 0 ; f < 6 ; f++)
  {
    if(iay & (1 << f))
    {
      yatsi_dakika |= (1 << (f - 0));
    }
  }

  // look at namaz.h for this information
  ikindi_saat += 12;
  aksam_saat += 12;
  yatsi_saat += 12;
  
  if((sabah_saat == saat) & (sabah_dakika == dakika) & (*(ayar + 1) == 1))
     {
       return scream;
     }
  if((gunes_saat == saat) & (gunes_dakika == dakika) & (*(ayar + 2) == 1))
     {
       return scream;
     }
  if((ogle_saat == saat) & (ogle_dakika == dakika) & (*(ayar + 3) == 1))
     {
       return scream;
     }
  if((ikindi_saat == saat) & (ikindi_dakika == dakika) & (*(ayar + 4) == 1))
     {
       return scream;
     }
  if((aksam_saat == saat) & (aksam_dakika == dakika) & (*(ayar + 5) == 1))
     {
       return scream;
     }
  if((yatsi_saat == saat) & (yatsi_dakika == dakika) & (*(ayar + 6) == 1))
     {
       return scream;
     }
   return quiet;
}
