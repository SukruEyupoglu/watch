
start_alarm();
stop_alarm();

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
  
  
}
