#define scream 1
#define quiet 0
// array for using settings start 0x001 not 0x000 and 0x000 is empty
#define E2PROM_NAMAZ_ALERT_SETTING_ADDR 0x001
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR 0x002
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR 0x003
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR 0x004
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR 0x005
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR 0x006
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR 0x007
/*
#define e2prom_addr 0xA2
#define eeprom_last_addr 0xFFF
// 0xFFF = 4095
// 8. byte alert before namaz time if 1 look at 9. byte for how many minute
// 9. byte minute for prepare for namaz default 0
#define before_namaz_alert_addr 0x008
#define minute_for_before_namaz_alert_addr 0x009
// A. byte exta alert number how many alert saved read from here
#define how_many_extra_alert_addr 0x00A // max 6
0x00B = dakika
0x00C = saat
0x00D = gun
0x00E = ay
if gun and ay equal to zero then daily alarm so every day of year
*/
unsigned char check_alarm(ds_t * ds3231,unsigned char * eeprom_data)
{
  if( * eeprom_data == 1)
  {
    if(check_namaz_for_alert(ds3231.minute,ds3231.hour,ds3231.day,ds3231.mount,&eeprom_data))
    {
      return scream;
    }
  }
  if(check_eeprom_alert(ds3231.minute,ds3231.hour,ds3231.day,ds3231.mount,&eeprom_data))
  {
    return scream;    
  }
  if(check_ds3231_alert(ds3231.minute,ds3231.hour,alarm1_minute,alarm1_hour__am_pm))
  {
    return scream;    
  }
  if(check_ds3231_alert(ds3231.minute,ds3231.hour,alarm2_minute,alarm2_hour__am_pm))
  {
    return scream;    
  }
  if(check_hourly_alert(ds3231.minute,ds3231.hour,&eeprom_data))
  {
    return scream;    
  }  
  return quiet;
}

unsigned char check_eeprom_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay,unsigned char * ayar)
{
  unsigned char f;
  for(f = 0 ; f < *(ayar + 0x9) ; f++)
  {
    if((*(((f * 4) + (ayar + 0x9)) + 1) == dakika) &
       (*(((f * 4) + (ayar + 0x9)) + 2) == saat) &
       ((*(((f * 4) + (ayar + 0x9)) + 3) == gun) | (*(((f * 4) + (ayar + 0x9)) + 3) == 0)) &
       ((*(((f * 4) + (ayar + 0x9)) + 4) == gun) | (*(((f * 4) + (ayar + 0x9)) + 4) == 0)))
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
