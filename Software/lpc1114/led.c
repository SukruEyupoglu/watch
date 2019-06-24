void led_hex_write(unsigned long long int circle,unsigned int digit)
{
  unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned char f,x;
  for(f = 0 ; f < 8 ; f++)
  {
    circle >>= (f * 8);
    for(x = 0 ; x < 8 ; x++)
    {
      if((circle & (1 << x)) != 0)
      {
        led[f] |= 1;
      }
    }    
  }
  for(f = 0 ; f < 4 ; f++)
  {
    digit >>= (f * 8);
    for(x = 0 ; x < 8 ; x++)
    {
      if((digit & (1 << x)) != 0)
      {
        led[f + 8] |= 1;
      }
    }    
  }  
  for(f = 0 ; f < 12 ; f++)
  {
    spi( led[f] );
  }
}
