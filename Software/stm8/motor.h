/*
spi shift register motor driver with mosfet

stepper motor has two coil and four bidirectional pin 

A1 A2   B1 B2
10 10   10 10 
01010101 = 8 bit,8 mosfet, 4 N-CHANNEL, 4 P-CHANNEL
PNPNPNPN
Transistors used driving mosfets negatives bits
normally 10101010
negative 01010101
0 channels to close P-CHANNEL mosfets
1 channels to close N-CHANNEL mosfets

0101 0101 standby
0011 0101 first step with only one coil

1010 0011 second weak full step release other coil

0011 0011 second strong half step with two coil
0101 0011 second step half to full completing strongly

if you want to hold strongly step motor use timer and pwm
and refresh same coil pulse with close and open if motor is
heating reduce pwm pulse high time but reducing this will weak
hold torque

start_timer for hold motor without heating
if start moving stop timer
if stop moving start timer for hold motor without heating

#define standby 0101_0101                                           0x55  SB
#define first_coil_forward_on                       0101_1100       0x5C  FCF
#define second_coil_forward_on                      1100_0101       0xC5  SCF
#define two_coil_forward_on                         1100_1100       0xCC  TCF
#define first_coil_backward_on                      0101_0011       0x53  FCB
#define second_coil_backward_on                     0011_0101       0x35  SCB
#define two_coil_backward_on                        0011_0011       0x33  TCB
#define first_coil_forward_second_coil_backward     0011_1100       0x3C  FCFSCB
#define second_coil_forward_first_coil_backward     1100_0011       0xC3  SCFFCB

5 = idle
C = forward
3 = backward

use standby to protecting mosfet short circuit

strong move motors toward
SB // OUT FUNCTION PROTECT

FCF
TCF
SCF
SCFFCB
FCB
TCB
SCB
FCFSCB

sequentally motor movement array
unsigned char motor[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};


*/

#define SB        0x55 // edited at 2021

#define FCF       0x5C
#define SCF       0xC5
#define TCF       0xCC
#define FCB       0x53
#define SCB       0x35
#define TCB       0x33
#define FCFSCB    0x3C
#define SCFFCB	  0xC3


#define WAIT_FOR_INTERRUPT 100

#define NEXT 1
#define BACK 0

unsigned char rescue_from_limit_switch_errors_instant(void);
unsigned char look_at_limit_switch_errors(void);
void change_active_motor(unsigned char motor_number);
void release_motor(void);
unsigned char motor_next(unsigned char stat);
unsigned char motor_back(unsigned char stat);
void change_direction(void);
unsigned char look_at_motor_status(void);
void write_motor_status(last_motor_status);
void hold_motor(unsigned char endurance_amount);
unsigned char motor_move(unsigned char step_count,unsigned char speed);
unsigned char move_to_find_limit_switch(unsigned char next_or_back);


/* example of motor movement

#include "stm8s.h"
#include "uart.h"
#include "delay.h"
#include "spi.h"
#include "led.h"
#include "timer.h"
#include "board_init.h"
#include "adc.h"


#define SB        0x55

#define FCF       0x5C
#define SCF       0xC5
#define TCF       0xCC
#define FCB       0x53
#define SCB       0x35
#define TCB       0x33
#define FCFSCB    0x3C
#define SCFFCB	  0xC3

#define latch PB_ODR |= (1 << 5);PB_ODR &= ~(1 << 5) // latch assert(LOW) // latch deassert(HIGH)

int main(void)
{
	unsigned char motor[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};
	unsigned char f = 0;
	// SET CLK TO FULL SPEED (16MHZ)
	// CLK_CKDIVR = 0;
	board_init();

	spi_init();
	ACTIVE_MOTOR_4_CLK;
	spi(SB);	// standby
	latch;
	delay_ms(1);

	// STANDBY SECURE MODE (this must be later from spi(SB);
	{
	// PUSH PULL MODE
	 PC_CR1 |= (1 << 4);
	// FAST MODE ENABLE
	 PC_CR2 |= (1 << 4);
	// CLOCK OUTPUT ON PC4
	// (0xC << 1) = Fmaster
	 CLK_CCOR |= ( (1 << 0) | (0xC << 1) );
	}

	// DIRECT CONNECT CLOSE STANDBY
	 //PC_CR1 |= (1 << 4);
	 //PC_ODR |= (1 << 4);
	 //PC_ODR &= ~(1 << 4); // close all motors

	while(1)
	{

		spi(motor[f]);
		latch;
		delay_ms(1);

		f = f + 2;
		if(f == 8)
		{
			f = 0;
		}

	}
}

*/















