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

1010 1010 standby
0011 1010 first step with only one coil

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

#define standby 1010_1010                                           0xAA  SB
#define first_coil_forward_on                       0011_1010       0x3A  FCF
#define second_coil_forward_on                      1010_0011       0xA3  SCF
#define two_coil_forward_on                         0011_0011       0x33  TCF
#define first_coil_backward_on                      1100_1010       0xCA  FCB
#define second_coil_backward_on                     1010_1100       0xAC  SCB
#define two_coil_backward_on                        1100_1100       0xCC  TCB
#define first_coil_forward_second_coil_backward     0011_1100       0x3C  FCFSCB
#define second_coil_forward_first_coil_backward     1100_0011       0x3C  SCFFCB

A = idle
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

#define SB        0xAA

#define FCF       0x3A
#define SCF       0xA3
#define TCF       0x33
#define FCB       0xCA
#define SCB       0xAC
#define TCB       0xCC
#define FCFSCB    0x3C
#define SCFFCB    0x3C


