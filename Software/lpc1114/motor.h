/*
spi shift register motor driver with mosfet

stepper motor has two coil and four bidirectional pin 

A1 A2   B1 B2
10 10   10 10 
10101010 = 8 bit,8 mosfet, 4 N-CHANNEL, 4 P-CHANNEL

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




*/
