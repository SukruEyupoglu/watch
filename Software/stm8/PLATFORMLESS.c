#include "PLATFORMLESS.h"

void Char_To_Bit(unsigned char bit)
{
	unsigned int turn;
	for(turn = 8;turn > 0;turn--)
	{
		if((bit & (1 << (turn - 1))) == 0)uart_send('0');
		else uart_send('1');
	}
	uart_send('\r');uart_send('\n');
}


// part0 lsb // for 32 bit mcu
void int_to_char(unsigned int data,unsigned char * part0,unsigned char * part1,unsigned char * part2,unsigned char * part3)
{
	unsigned char f;
	for(f = 0 ; f < 8 ; f++)
	{
		if(data & (1 << f) )
		{
			* part0 |= (1 << f);
		}
		else
		{
			* part0 &= ~(1 << f);
		}
		if(data & (1 << (f + 8) ) )
		{
			* part1 |= (1 << f);
		}
		else
		{
			* part1 &= ~(1 << f);
		}
		if(data & (1 << (f + 16) ) )
		{
			* part2 |= (1 << f);
		}
		else
		{
			* part2 &= ~(1 << f);
		}
		if(data & (1 << (f + 24) ) )
		{
			* part3 |= (1 << f);
		}
		else
		{
			* part3 &= ~(1 << f);
		}
	}
}
// part0 lsb  // for 32 bit mcu
void char_to_int(unsigned int * data,unsigned char part0,unsigned char part1,unsigned char part2,unsigned char part3)
{
	unsigned char f;
	for(f = 0 ; f < 8 ; f++)
	{
		if(part0 & (1 << f) )
		{
			* data |= (1 << f);
		}
		else
		{
			* data &= ~(1 << f);
		}
		if(part1 & (1 << f) )
		{
			* data |= (1 << (f + 8) );
		}
		else
		{
			* data &= ~(1 << (f + 8) );
		}
		if(part2 & (1 << f) )
		{
			* data |= (1 << (f + 16) );
		}
		else
		{
			* data &= ~(1 << (f + 16) );
		}
		if(part3 & (1 << f) )
		{
			* data |= (1 << (f + 24) );
		}
		else
		{
			* data &= ~(1 << (f + 24) );
		}
	}	
}
// part0 lsb // for 32 bit mcu
void short_to_char(unsigned short data,unsigned char * part0,unsigned char * part1)
{
	unsigned char f;
	for(f = 0 ; f < 8 ; f++)
	{
		if(data & (1 << f) )
		{
			* part0 |= (1 << f);
		}
		else
		{
			* part0 &= ~(1 << f);
		}
		if(data & (1 << (f + 8) ) )
		{
			* part1 |= (1 << f);
		}
		else
		{
			* part1 &= ~(1 << f);
		}
	}	
}
// part0 lsb  // for 32 bit mcu
void char_to_short(unsigned short * data,unsigned char part0,unsigned char part1)
{
	unsigned char f;
	for(f = 0 ; f < 8 ; f++)
	{
		if(part0 & (1 << f) )
		{
			* data |= (1 << f);
		}
		else
		{
			* data &= ~(1 << f);
		}
		if(part1 & (1 << f) )
		{
			* data |= (1 << (f + 8) );
		}
		else
		{
			* data &= ~(1 << (f + 8) );
		}
	}	
}
// part0 lsb  // for 32 bit mcu
void longlong_to_int(unsigned long long data,unsigned int * part0,unsigned int * part1)
{
	unsigned char f;
	unsigned long long one = 1;
	for(f = 0 ; f < 32 ; f++)
	{
		if(data & (one << f) )
		{
			* part0 |= (one << f);
		}
		else
		{
			* part0 &= ~(one << f);
		}
		if(data & (1 << (f + 32) ) )
		{
			* part1 |= (one << f);
		}
		else
		{
			* part1 &= ~(one << f);
		}
	}	
}
// part0 lsb // for 32 bit mcu
void int_to_longlong(unsigned long long * data,unsigned int part0,unsigned int part1)
{
	unsigned char f;
	unsigned long long one = 1;
	for(f = 0 ; f < 32 ; f++)
	{
		if(part0 & (one << f) )
		{
			* data |= (one << f);
		}
		else
		{
			* data &= ~(one << f);
		}
		if(part1 & (1 << f) )
		{
			* data |= (one << (f + 32) );
		}
		else
		{
			* data &= ~(one << (f + 32) );
		}
	}	
}



void delay(volatile unsigned int bekle)
{
	while(bekle)bekle--;
}


unsigned char check_hex_data(unsigned char data)
{
	if(
		( data == '0' ) |
		( data == '1' ) |
		( data == '2' ) |
		( data == '3' ) |
		( data == '4' ) |
		( data == '5' ) |
		( data == '6' ) |
		( data == '7' ) |
		( data == '8' ) |
		( data == '9' ) |
		( data == 'a' ) |
		( data == 'b' ) |
		( data == 'c' ) |
		( data == 'd' ) |
		( data == 'e' ) |
		( data == 'f' ) |
		( data == 'A' ) |
		( data == 'B' ) |
		( data == 'C' ) |
		( data == 'D' ) |
		( data == 'E' ) |
		( data == 'F' )
	)
	{
		return 1;
	}
	return 0;
}
unsigned char ascii_to_hex(unsigned char data)
{
	switch (data)
	{
		case '0':
		{
			return 0x00;
		}
		break;
		case '1':
		{
			return 0x01;
		}
		break;
		case '2':
		{
			return 0x02;
		}
		break;
		case '3':
		{
			return 0x03;
		}
		break;
		case '4':
		{
			return 0x04;
		}
		break;
		case '5':
		{
			return 0x05;
		}
		break;
		case '6':
		{
			return 0x06;
		}
		break;
		case '7':
		{
			return 0x07;
		}
		break;
		case '8':
		{
			return 0x08;
		}
		break;
		case '9':
		{
			return 0x09;
		}
		break;
		case 'a':
		case 'A':
		{
			return 0x0A;
		}
		break;
		case 'b':
		case 'B':
		{
			return 0x0B;
		}
		break;
		case 'c':
		case 'C':
		{
			return 0x0C;
		}
		break;
		case 'd':
		case 'D':
		{
			return 0x0D;
		}
		break;
		case 'e':
		case 'E':
		{
			return 0x0E;
		}
		break;
		case 'f':
		case 'F':
		{
			return 0x0F;
		}
		break;
		default :
		{
			return 0xFF;
		}
		break;
	}
}
unsigned char hex_to_ascii(unsigned char data)
{
	switch (data)
	{
		case 0x00:
		{
			return '0';
		}
		break;
		case 0x01:
		{
			return '1';
		}
		break;
		case 0x02:
		{
			return '2';
		}
		break;
		case 0x03:
		{
			return '3';
		}
		break;
		case 0x04:
		{
			return '4';
		}
		break;
		case 0x05:
		{
			return '5';
		}
		break;
		case 0x06:
		{
			return '6';
		}
		break;
		case 0x07:
		{
			return '7';
		}
		break;
		case 0x08:
		{
			return '8';
		}
		break;
		case 0x09:
		{
			return '9';
		}
		break;
		case 0x0A:
		{
			return 'A';
		}
		break;
		case 0x0B:
		{
			return 'B';
		}
		break;
		case 0x0C:
		{
			return 'C';
		}
		break;
		case 0x0D:
		{
			return 'D';
		}
		break;
		case 0x0E:
		{
			return 'E';
		}
		break;
		case 0x0F:
		{
			return 'F';
		}
		break;
		default :
		{
			return 'X';
		}
		break;
	}
}


