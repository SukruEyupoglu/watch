
start_alarm();
stop_alarm();
#define scream 1
#define quiet 0
#define E2PROM_NAMAZ_ALERT_SETTING_ADDR 0x0001
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR 0x0002
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR 0x0003
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR 0x0004
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR 0x0005
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR 0x0006
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR 0x0007

unsigned char i2c_read_e2prom_1_char(unsigned char ic_addr,unsigned short read_addr,unsigned char * data)
unsigned char check_alarm(unsigned char * ds_t)
{
  
}
unsigned char check_namaz_for_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay)
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
  ikindi_saat += 12;
  aksam_saat += 12;
  yatsi_saat += 12;
  if((sabah_saat == saat) & (sabah_dakika == dakika)
     {
       return scream;
     }
  if((gunes_saat == saat) & (gunes_dakika == dakika)
     {
       return scream;
     }
  if((ogle_saat == saat) & (ogle_dakika == dakika)
     {
       return scream;
     }
  if((ikindi_saat == saat) & (ikindi_dakika == dakika)
     {
       return scream;
     }
  if((aksam_saat == saat) & (aksam_dakika == dakika)
     {
       return scream;
     }
  if((yatsi_saat == saat) & (yatsi_dakika == dakika)
     {
       return scream;
     }
   return quiet;
}
