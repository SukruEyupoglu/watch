// saat seçilirse başlangıçtan saat değerine kadar olan ledler yanar
#define dakika 0
// dolgu seçilirse düzenli bir biçimde 32 bit için 0 - 31
// x değeri yanacak ledleri 0 - 5
// y değeri sönecek ledleri 6 - 11
// z değeri başlangıç noktasını 12 - 17
// v değeri biyiş noktasını 18 - 23
// ifade eder
#define dolgu 2
// desen seçilirse rastgele iki adet 32 bit register bit olarak şekillendirilebilir.
#define desen 1

void daire_yaz(unsigned char dakika,unsigned int dolgu,unsigned int desen_0_31,unsigned int desen_32_59,unsigned char tip)
{
  unsigned char f,j;
  switch (tip)
  {
    case 0:
    {
      if(dakika < 60)
      {
        for(f = 0 ; f < (dakika / 8) ; f++)
        {
          led[f] = 0xFF;
        }
        if(dakika % 8)
        {
          led[dakika / 8] = (dakika % 8);
        }
      }
    }
    break;
    case 1:
    {
      for(f = 0 ; f < 4 ; f++)
      {
        for(j = 0 ; j < 8 ; j++)
        {
          if(desen_0_31 & (1 << ((f * 8) + j)))
          {
            led[f] |= (1 << j); 
          }
          if(desen_32_59 & (1 << ((f * 8) + j)))
          {
            led[f + 4] |= (1 << j); 
          }
        }
      }
    }
    break;
    case 2:
    {
      
    }
    break;
    case 3:
    {
      
    }
    break;
    default:
    {
      
    }
    break;
  }
  yaz();
}
