/*
circle = 60 valid bit + 4 blank bit 
digit = 14 valid + 2 empty + 14 valid + 2 empty
unsigned long long int circle , z = 1 , v = 0;
circle = (z << 0) |     (v << 57) |
         (z << 1) |     (z << 58) |
         (v << 2) |     (z << 59);  // 60,61,62,63 is not matter,unvalid.
vb..
digit same as circle but 32 bit
*/
void led_hex_write(unsigned long long int circle,unsigned int digit)
{
  unsigned char f,x;
  led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
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
void led_write(unsigned char watch,unsigned char minute,unsigned char ref)
{
    unsigned char i,j,l,f;
    unsigned char x,v;
    unsigned char y = (minute / 8);
    unsigned char z = (minute % 8);
    unsigned char p = (watch / 10);
    unsigned char q = (watch % 10);
    unsigned char m = (ref    / 8);
    unsigned char n = (ref    % 8);
    unsigned char n7[20] = {0xFF,0xF,0x3C,0x0,0xCF,0x33,0xFF,0x30,0x3C,0x3C,0xF3,0x3C,0xF3,0x3F,0x3F,0x0,0xFF,0x3F,0xFF,0x3C};
    led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    if ((minute < 60) & (ref == 0))
    {
        for(i=0;i<y;i++)
        {
            led[i] = 0xFF;
        }
        for(j=0;j<z;j++)
        {
            x |= (1 << j);
        }
        led[i] |= x;
    }
    if ((minute < 60) & (ref > 0) & (ref < 60) & (ref < minute))
    {
        for(i=0;i<y;i++)
        {
            if(i > m)
            {
            led[i] = 0xFF;
            }
        }
        for(l=0;l<n;l++)
        {
            v |= (1 << l);
        }        
        led[(m*8)] &= ~v;
        for(j=0;j<z;j++)
        {
            x |= (1 << j);
        }
        led[i] |= x;
    }
if(watch < 100)
{
    led[8] = n7[(p*2)];
    led[9] = n7[(p*2)+1];
    led[10] = n7[(q*2)];
    led[11] = n7[(q*2)+1];
}
else
{
    led[8] = 0;
    led[9] = 0;
    led[10] = 0;
    led[11] = 0;    
}
for(f=0;f<12;f++)
{
    spi(led[f]);
}
}
void blink(unsigned char blink_type,unsigned int blink_shiny_time,blink_dim_time)
{
         unsigned long long int circle = 0;
         unsigned int digit = 0;
         unsigned char f,x;
         for(f = 0 ; f < 8 ; f++)
         {
                  for(x = 0 ; x < 8 ; x++)
                  {
                           if((led[f] & (1 << x)) != 0)
                           {
                                    circle |= (1 << ((f * 8) + x));
                           }
                  }
         }
         for(f = 0 ; f < 4 ; f++)
         {
                  for(x = 0 ; x < 8 ; x++)
                  {
                           if((led[f + 8] & (1 << x)) != 0)
                           {
                                    digit |= (1 << ((f * 8) + x));
                           }
                  }
         }
         if(blink_type == 0)
         {
                  led_hex_write(0,digit);
         }
         else
         {
                  led_hex_write(circle,0);
         }
         delay(blink_dim_time);
         led_hex_write(circle,digit);
         delay(blink_shiny_time);
}
