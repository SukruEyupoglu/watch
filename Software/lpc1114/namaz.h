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


or 3 temmuz 2019

imsak 3:09
gunes 5:29
ogle 13:20
ikindi 17:20
aksam 20:48
yatsi 22:48


*/
const unsigned int namaz[12][31][2];
