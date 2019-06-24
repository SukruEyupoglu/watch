unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}
/*
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
*/
