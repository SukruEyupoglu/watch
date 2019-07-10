void error(void)
{
  write_digit('E','R');
  delay(blink_delay);
  write_digit(NONE,NONE);
  delay(blink_delay);  
}
void write_digit(unsigned char left,unsigned char right)
{
  unsigned char f;
  switch(left)
  {
    case 'A':
    {
      led[8] = 0x3F;
      led[9] = 0x3F;
    }
    break;
    case 'B':
    {
      led[8] = 0xDB;
      led[9] = 0x1F;
    }
    break;
    case 'C':
    {
      led[8] = 0xC3;
      led[9] = 0x0F;
    }
    break;
    case 'D':
    {
      led[8] = 0xDB;
      led[9] = 0x0F;
    }
    break;
    case 'E':
    {
      led[8] = 0xC3;
      led[9] = 0x3F;
    }
    break;
    case 'F':
    {
      led[8] = 0x03;
      led[9] = 0x3F;
    }
    break;
    case 'G':
    {
      led[8] = 0xD3;
      led[9] = 0x1F;
    }
    break;
    case 'H':
    {
      led[8] = 0x3C;
      led[9] = 0x3F;
    }
    break;
    case 'I':
    {
      led[8] = 0x00;
      led[9] = 0x0F;
    }
    break;
    case 'J':
    {
      led[8] = 0xFC;
      led[9] = 0x00;
    }
    break;
    case 'K':
    {
      led[8] = 0x24;
      led[9] = 0x3F;
    }
    break;
    case 'L':
    {
      led[8] = 0xC0;
      led[9] = 0x0F;
    }
    break;
    case 'M':
    {
      led[8] = 0x34;
      led[9] = 0x3B;
    }
    break;
    case 'N':
    {
      led[8] = 0x3B;
      led[9] = 0x07;
    }
    break;
    case 'O':
    {
      led[8] = 0xDB;
      led[9] = 0x06;
    }
    break;
    case 'P':
    {
      led[8] = 0x0F;
      led[9] = 0x3F;
    }
    break;
    case 'R':
    {
      led[8] = 0x03;
      led[9] = 0x0F;
    }
    break;
    case 'S':
    {
      led[8] = 0xD1;
      led[9] = 0x2C;
    }
    break;
     case 'T':
    {
      led[8] = 0x00;
      led[9] = 0x3F;
    }
    break;
    case 'U':
    {
      led[8] = 0xFC;
      led[9] = 0x0F;
    }
    break;
    case 'V':
    {
      led[8] = 0xD4;
      led[9] = 0x0A;
    }
    break;
    case 'Y':
    {
      led[8] = 0xFD;
      led[9] = 0x3D;
    }
    break;
    case 'Z':
    {
      led[8] = 0xD8;
      led[9] = 0x32;
    }
    break;    
  }
  switch(right)
  {
    case 'A':
    {
      led[10] = 0x3F;
      led[11] = 0x3F;
    }
    break;
    case 'B':
    {
      led[10] = 0xDB;
      led[11] = 0x1F;
    }
    break;
    case 'C':
    {
      led[10] = 0xC3;
      led[11] = 0x0F;
    }
    break;
    case 'D':
    {
      led[10] = 0xDB;
      led[11] = 0x0F;
    }
    break;
    case 'E':
    {
      led[10] = 0xC3;
      led[11] = 0x3F;
    }
    break;
    case 'F':
    {
      led[10] = 0x03;
      led[11] = 0x3F;
    }
    break;
    case 'G':
    {
      led[10] = 0xD3;
      led[11] = 0x1F;
    }
    break;
    case 'H':
    {
      led[10] = 0x3C;
      led[11] = 0x3F;
    }
    break;
    case 'I':
    {
      led[10] = 0x00;
      led[11] = 0x0F;
    }
    break;
    case 'J':
    {
      led[10] = 0xFC;
      led[11] = 0x00;
    }
    break;
    case 'K':
    {
      led[10] = 0x24;
      led[11] = 0x3F;
    }
    break;
    case 'L':
    {
      led[10] = 0xC0;
      led[11] = 0x0F;
    }
    break;
    case 'M':
    {
      led[10] = 0x34;
      led[11] = 0x3B;
    }
    break;
    case 'N':
    {
      led[10] = 0x3B;
      led[11] = 0x07;
    }
    break;
    case 'O':
    {
      led[10] = 0xDB;
      led[11] = 0x06;
    }
    break;
    case 'P':
    {
      led[10] = 0x0F;
      led[11] = 0x3F;
    }
    break;
    case 'R':
    {
      led[10] = 0x03;
      led[11] = 0x0F;
    }
    break;
    case 'S':
    {
      led[10] = 0xD1;
      led[11] = 0x2C;
    }
    break;
     case 'T':
    {
      led[10] = 0x00;
      led[11] = 0x3F;
    }
    break;
    case 'U':
    {
      led[10] = 0xFC;
      led[11] = 0x0F;
    }
    break;
    case 'V':
    {
      led[10] = 0xD4;
      led[11] = 0x0A;
    }
    break;
    case 'Y':
    {
      led[10] = 0xFD;
      led[11] = 0x3D;
    }
    break;
    case 'Z':
    {
      led[10] = 0xD8;
      led[11] = 0x32;
    }
    break;    
  }
  for(f = 0 ; f < 12 ; f++)
  {
    spi( led[f] );
  }
}
