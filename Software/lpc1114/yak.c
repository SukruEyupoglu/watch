// saat seçilirse başlangıçtan saat değerine kadar olan ledler yanar
#define dakika 0
// desen seçilirse düzenli bir biçimde 
// x değeri yanacak ledleri 1 - 60
// y değeri sönecek ledleri 61 - 120
// z değeri başlangıç noktasını 121 - 180
// v değeri biyiş noktasını 181 - 240
// ifade eder
#define desen 1
#define dolgu 2
void daire_yaz(unsigned char dakika,unsigned char desen,unsigned char tip)
