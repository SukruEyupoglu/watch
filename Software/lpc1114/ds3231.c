unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}
void led_write(unsigned char watch,unsigned char minute)
{
    unsigned char led[12];
    unsigned char i,j;
    unsigned char x;
    unsigned char y = (minute / 8);
    unsigned char z = (minute % 8);
    for(i=0;i<y;i++)
    {
        led[i] = 0xFF;
    }
    for(j=0;j<z;j++)
    {
        x |= (x << j);
    }
    led[i] |= x;
    switch( watch )
        case 0:
        {
            
        }
        break;
         case 1:
        {
        }
        break;
        case 2:
        {
        }
        break;
         case 3:
        {
        }
        break;
        case 4:
        {
        }
        break;
         case 5:
        {
        }
        break;
        case 6:
        {
        }
        break;
         case 7:
        {
        }
        break;
        case 8:
        {
        }
        break;
         case 9:
        {
        }
        break;
        case 10:
        {
        }
        break;
         case 11:
        {
        }
        break;
        case 12:
        {
        }
        break;
         case 13:
        {
        }
        break;
        case 14:
        {
        }
        break;
         case 15:
        {
        }
        break;
        case 16:
        {
        }
        break;
         case 17:
        {
        }
        break;
        case 18:
        {
        }
        break;
         case 19:
        {
        }
        break;
        case 20:
        {
        }
        break;
         case 21:
        {
        }
        break;
        case 22:
        {
        }
        break;
         case 23:
        {
        }
        break;

}
