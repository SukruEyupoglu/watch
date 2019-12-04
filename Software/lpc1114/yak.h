/*
// saat seçilirse başlangıçtan saat değerine kadar olan ledler yanar
#define dakika 0
// dolgu seçilirse düzenli bir biçimde 32 bit için 0 - 31
// x değeri yanacak ledleri 0 - 5
// y değeri sönecek ledleri 6 - 11
// z değeri başlangıç noktasını 12 - 17
// v değeri bitiş noktasını 18 - 23
// ifade eder
#define dolgu 2
// desen seçilirse rastgele iki adet 32 bit register bit olarak şekillendirilebilir.
#define desen 1

*/

void daire_yaz(unsigned char dakika,unsigned int dolgu,unsigned int desen_0_31,unsigned int desen_32_59,unsigned char tip);
void desen_yaz(unsigned char x,unsigned char y);
void limit_yaz(unsigned char x,unsigned char y);
void limit_sil(unsigned char x,unsigned char y);
void led_yan(unsigned char xx);
void led_son(unsigned char xx);
void led_zero(void);
void led_one(void);









