unsigned char check_hex_data(unsigned char data)
{
  if  (
		  data == '0' |
		  data == '1' |
		  data == '2' |
		  data == '3' |
		  data == '4' |
  		data == '5' |
	  	data == '6' |
		  data == '7' |
  		data == '8' |
  		data == '9' |
  		data == 'a' |
  		data == 'b' |
  		data == 'c' |
  		data == 'd' |
  		data == 'e' |
  		data == 'f' |
	  	data == 'A' |
		  data == 'B' |
		  data == 'C' |
		  data == 'D' |
		  data == 'E' |
		  data == 'F'
      )
      {
      return 1;
      }
   return 0;
}
unsigned char ascii_to_hex(unsigned char x,unsigned char y)
{
	unsigned char data;
	switch (x)
	{
		case '0':
		{
			data	=	0x00;
		}
		break;
		case '1':
		{
			data	=	0x10;
		}
		break;
		case '2':
		{
			data	=	0x20;
		}
		break;
		case '3':
		{
			data	=	0x30;
		}
		break;
		case '4':
		{
			data	=	0x40;
		}
		break;
		case '5':
		{
			data	=	0x50;
		}
		break;
		case '6':
		{
			data	=	0x60;
		}
		break;
		case '7':
		{
			data	=	0x70;
		}
		break;
		case '8':
		{
			data	=	0x80;
		}
		break;
		case '9':
		{
			data	=	0x90;
		}
		break;
		case 'a':
		case 'A':
		{
			data	=	0xA0;
		}
		break;
		case 'b':
		case 'B':
		{
			data	=	0xB0;
		}
		break;
		case 'c':
		case 'C':
		{
			data	=	0xC0;
		}
		break;
		case 'd':
		case 'D':
		{
			data	=	0xD0;
		}
		break;
		case 'e':
		case 'E':
		{
			data	=	0xE0;
		}
		break;
		case 'f':
		case 'F':
		{
			data	=	0xF0;
		}
		break;
	}
	switch (y)
		{
			case '0':
			{
				data	|=	0x00;
			}
			break;
			case '1':
			{
				data	|=	0x01;
			}
			break;
			case '2':
			{
				data	|=	0x02;
			}
			break;
			case '3':
			{
				data	|=	0x03;
			}
			break;
			case '4':
			{
				data	|=	0x04;
			}
			break;
			case '5':
			{
				data	|=	0x05;
			}
			break;
			case '6':
			{
				data	|=	0x06;
			}
			break;
			case '7':
			{
				data	|=	0x07;
			}
			break;
			case '8':
			{
				data	|=	0x08;
			}
			break;
			case '9':
			{
				data	|=	0x09;
			}
			break;
			case 'a':
			case 'A':
			{
				data	|=	0x0A;
			}
			break;
			case 'b':
			case 'B':
			{
				data	|=	0x0B;
			}
			break;
			case 'c':
			case 'C':
			{
				data	|=	0x0C;
			}
			break;
			case 'd':
			case 'D':
			{
				data	|=	0x0D;
			}
			break;
			case 'e':
			case 'E':
			{
				data	|=	0x0E;
			}
			break;
			case 'f':
			case 'F':
			{
				data	|=	0x0F;
			}
			break;
	}
	return data;
}
unsigned short hex_to_ascii(unsigned char x)
{
	unsigned short data;
	switch (x & 0xF0)
		{
		case 0x00:
			{
				data = '0';
			}
		break;
		case 0x10:
			{
				data = '1';
			}
		break;
		case 0x20:
			{
				data = '2';
			}
		break;
		case 0x30:
			{
				data = '3';
			}
		break;
		case 0x40:
			{
				data = '4';
			}
		break;
		case 0x50:
			{
				data = '5';
			}
		break;
		case 0x60:
			{
				data = '6';
			}
		break;
		case 0x70:
			{
				data = '7';
			}
		break;
		case 0x80:
			{
				data = '8';
			}
		break;
		case 0x90:
			{
				data = '9';
			}
		break;
		case 0xA0:
			{
				data = 'A';
			}
		break;
		case 0xB0:
			{
				data = 'B';
			}
		break;
		case 0xC0:
			{
				data = 'C';
			}
		break;
		case 0xD0:
			{
				data = 'D';
			}
		break;
		case 0xE0:
			{
				data = 'E';
			}
		break;
		case 0xF0:
			{
				data = 'F';
			}
		break;
		}
	switch (x & 0x0F)
		{
		case 0x00:
			{
				data = (data << 8) | '0';
			}
		break;
		case 0x01:
			{
				data = (data << 8) | '1';
			}
		break;
		case 0x02:
			{
				data = (data << 8) | '2';
			}
		break;
		case 0x03:
			{
				data = (data << 8) | '3';
			}
		break;
		case 0x04:
			{
				data = (data << 8) | '4';
			}
		break;
		case 0x05:
			{
				data = (data << 8) | '5';
			}
		break;
		case 0x06:
			{
				data = (data << 8) | '6';
			}
		break;
		case 0x07:
			{
				data = (data << 8) | '7';
			}
		break;
		case 0x08:
			{
				data = (data << 8) | '8';
			}
		break;
		case 0x09:
			{
				data = (data << 8) | '9';
			}
		break;
		case 0x0A:
			{
				data = (data << 8) | 'A';
			}
		break;
		case 0x0B:
			{
				data = (data << 8) | 'B';
			}
		break;
		case 0x0C:
			{
				data = (data << 8) | 'C';
			}
		break;
		case 0x0D:
			{
				data = (data << 8) | 'D';
			}
		break;
		case 0x0E:
			{
				data = (data << 8) | 'E';
			}
		break;
		case 0x0F:
			{
				data = (data << 8) | 'F';
			}
		break;
		}
	return data;
}


