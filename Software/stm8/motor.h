/*
spi shift register motor driver with mosfet

stepper motor has two coil and four bidirectional pin 

A1 A2   B1 B2
10 10   10 10 
10101010 = 8 bit,8 mosfet, 4 N-CHANNEL, 4 P-CHANNEL
NPNPNPNP
Transistors used driving mosfets negatives bits
normally 01010101
negative 10101010
1 channels to close P-CHANNEL mosfets
0 channels to close N-CHANNEL mosfets

0101 0101 standby
0011 0101 first step with only one coil

1010 0011 second weak full step release other coil

0011 0011 second strong half step with two coil
1010 0011 second step half to full completing strongly

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
3 = forward
C = backward

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

#define FCF       0x3A
#define SCF       0xA3
#define TCF       0x33
#define FCB       0xCA
#define SCB       0xAC
#define TCB       0xCC
#define FCFSCB    0x3C
#define SCFFCB    0x3C

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















