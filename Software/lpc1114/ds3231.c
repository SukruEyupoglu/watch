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
    unsigned char n7[20] = {0xFF,0xF,0x3C,0x0,0xCF,0x33,0xFF,0x30,0x3C,0x3C,0xF3,0x3C,0xF3,0x3F,0x3F,0x0,0xFF,0x3F,0xFF,0x3C};
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
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 1:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0x3C;
            led[11] = 0x0;
        }
        break;
        case 2:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 3:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
        case 4:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 5:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
        case 6:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 7:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
        case 8:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 9:
        {
            led[8]  = 0xFF;
            led[9]  = 0xF;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
        case 10:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 11:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
        case 12:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;
        }
        break;
         case 13:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
        case 14:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
         case 15:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
        case 16:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
         case 17:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
        case 18:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
         case 19:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
        case 20:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
         case 21:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
        case 22:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;
         case 23:
        {
            led[8]  = 0x3C;
            led[9]  = 0x0;
            led[10] = 0xFF;
            led[11] = 0xF;            
        }
        break;

}
