// 1 year 12 month
// 1 month max 31 day
// 1 day 5 vakit and sunrise(gundogumu)
// 1 vakit 10 bit
// first 4 bit max 15
// last 6 bit max 63
// ikindi aksam yatsi (saat + 12) no need more bit
// sabah gundogumu ogle enough for 15 saat
/*
first day of the year 1 ocak

imsak 6:33
gunes 8:22
ogle 13:19
ikindi 15:40
aksam 17:54
yatsi 19:31

first 32 bit imsak gunes ogle

0110 imsak 6
100001 imsak 33
0110100001 = 6:33 = 10 bit

1000 gunes 8
010110 gunes 22
1000010110 = 8:22 = 10 bit

1101 ogle 13
010011 ogle 19
1101010011 = 13:19 = 10 bit

merge all vakit
imsak + gunes + ogle
011010000110000101101101010011 = 30 bit 
int = 32 bit enough for 3 vakit
last 2 bit is empty

for reduce size of time to fit 4 bit area erase 12
ikindi = 15:40 --> 15 - 12 = 3 --> 3:40
aksam = 17:54 --> 17 - 12 = 5 --> 5:54
yatsı = 19:31 --> 19 - 12 = 7 --> 7:31

3+40+5+54+7+31
0011+101000+0101+110110+0111+011111
ikindi + aksam + yatsı
001110100001011101100111011111 = 30 bit
int = 32 bit enough for 3 vakit
last 2 bit is empty

or 3 temmuz 2019

imsak 3:09
gunes 5:29
ogle 13:20
ikindi 17:20
aksam 20:48
yatsi 22:48

#define hour_size 4
#define minute_size 6
unsigned int i;

i <<= hour_size;      // shift hour area for imsak hour
i = 3;                // set imsak hour

i <<= minute_size;    // shift minute area for imsak minute
i |= 9;               // set imsak dakka

i <<= hour_size       // shift hour area for gunes hour
i |= 5;               // set gunes hour

i <<= minute_size     // shift minute area for gunes minute
i |= 29;              // set gunes minute

i <<= hour_size       // shift hour area for ogle hour
i |= 13;               // set gunes hour

i <<= minute_size     // shift minute area for ogle minute
i |= 20;              // set ogle minute

memory area explanation for imsak + gunes + ogle
i --> 00 0011 001001 0101 011101 1101 010100

unsigned int j;


j <<= hour_size;      // shift hour area for ikindi hour
j = 17 - 12;                // set ikindi hour

j <<= minute_size;    // shift minute area for ikindi minute
j |= 20;               // set ikindi dakka

j <<= hour_size       // shift hour area for aksam hour
j |= 20 - 12;               // set aksam hour

j <<= minute_size     // shift minute area for aksam minute
j |= 48;              // set aksam minute

j <<= hour_size       // shift hour area for yatsi hour
j |= 22 - 12;               // set yatsi hour

j <<= minute_size     // shift minute area for yatsi minute
j |= 48;              // set yatsi minute

memory area explanation for imsak + gunes + ogle
j --> 00 0101 010100 1000 110000 1010 110000

*/
const unsigned int namaz[12][31][2];
