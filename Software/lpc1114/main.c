//  BUFFER PARTS
//  0-59  == MINUTE
//  60-63 == NULL
//  64-77 == 7 SEGMENT 1
//  78-79 == NULL
//  80-93 == 7 SEGMENT 2
//  94-95 == NULL
int main(void)
{
unsigned char janjan_type;
unsigned char saat[12];
saat_simdi_ne(saat);
saati_nekadar_janjanli_yazsin(janjan_type);
saati_yaz(saat,janjan_type);

return 0;
}
void saat_simdi_ne(unsigned char dizi[12])
{
}
void saati_yaz(unsigned char dizi[12],unsigned char janjan)
{
}
void saati_nekadar_janjanli_yazsin(unsigned char janjan)
{
}
