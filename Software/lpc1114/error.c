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
      led[9] = 0x
    }
    break;
    case 'H':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'I':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'J':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'K':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'L':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'M':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'N':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'O':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'P':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'R':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'S':
    {
      led[8] = 
      led[9] = 
    }
    break;
     case 'T':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'U':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'V':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'Y':
    {
      led[8] = 
      led[9] = 
    }
    break;
    case 'Z':
    {
      led[8] = 
      led[9] = 
    }
    break;    
    
     
     
     
     
     
  }
  for(f = 0 ; f < 12 ; f++)
  {
    spi( led[f] );
  }
}
