#include "stm8s.h"
#include "nrf8.h"


////////////////////////////////////////////////////////////////
// THIS TESTED WITH OSCILOSKOP
  // SET CLK TO FULL SPEED (16MHZ)
  //CLK_CKDIVR = 0;
void delay_us(volatile unsigned char bekle);
void delay_us(volatile unsigned char bekle)
{
	while(bekle)
	{
		bekle--;
	}
	//	delay(0)	1.63us
	//	delay(1)	2.07us
	//	delay(2)	2.51us
	//	delay(3)	2.95us
	//	delay(4)	3.39us
	//	delay(5)	3.83us
	//	delay(6)	4.27us
	//	delay(19)	9.99us
	//	delay(20)	10.43us
	//	delay(224)	100.1us	
	//	delay(255)	113.8us  //MAX
}
#define delay_10us delay(20)
///////////////////////////////////////////////////////////////////////
void delay_ms(volatile unsigned char bekle);
void delay_ms(volatile unsigned char bekle)
{
	while(bekle)
	{
		bekle--;
		delay_us(224);delay_us(224);delay_us(224);delay_us(224);delay_us(224);
		delay_us(224);delay_us(224);delay_us(224);delay_us(224);delay_us(224);
	}
}	

void nrf_gpio_init(void)
{
  	//	NRF IRQ SETTINGS
	//	MAKE DIRECTION INPUT PC4,PC3
	PC_DDR &= ~( (1 << 3) | (1 << 4) ); // 3 FOR NRF1 --- 4 FOR NRF2
	//	NRF CE SETTINGS CHIP ENABLE ACTIVES RX - TX MODE --- ACTIVE HIGH 
	//	RX MODE CE MUST BE HIGH 
	//	TX MODE CE MUST BE A PULSE MORE THAN 10us -- 4ms DEADLINE FOR CE HIGH TIME
	//	YOU CAN USE 15us FOR COMMINICATION BEWARE FOR TX MODE DEADLINE
	PA_DDR |= (1 << 3); // NRF1
	PD_DDR |= (1 << 3); // NRF2
	PA_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR &= ~(1 << 3); // OUTPUT LOW
	PD_ODR &= ~(1 << 3); // OUTPUT LOW
	//	NRF CSN SETTINGS SPI CHIP SELECT ACTIVE LOW
	PA_DDR |= (1 << 2); // NRF1
	PD_DDR |= (1 << 2); // NRF2
	PA_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR |= (1 << 3); // OUTPUT HIGH
	PD_ODR |= (1 << 3); // OUTPUT HIGH
	
 	//	100ms delay for nrf24l01 wakeup ---  FROM DATASHEET
	delay(100000);
}


void NRF_TX_INIT(void)
{
	// config registerini set et default tx modu zaten 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 3));
	delay(1500);
	// pipe0 icin auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , (1 << 0));
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps sec -18db sec
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 icin ayari
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayari
	NRF_write_reg(W_REGISTER | DYNPD , (1 << 0));
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 1) | (1 << 2));
}
void NRF_RX_INIT(void)
{
	// config registerini set et rx olarak 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 3) | (1 << 0));
	delay(1500);
	// pipe0 icin auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , (1 << 0));
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps sec -18db sec
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 icin ayari
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayari
	NRF_write_reg(W_REGISTER | DYNPD , (1 << 0));
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 1) | (1 << 2));
}

void NRF_TX_INIT_NO_ACK(void)
{
	// config registerini set et default tx modu zaten 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 4) | (1 << 6));
	delay(1500);
	// pipe0 icin auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , 0x00);
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0x00);
	// 250kbps sec -18db sec
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 icin ayari
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayari
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 0));
}
void NRF_RX_INIT_NO_ACK(void)
{
	// config registerini set et rx olarak 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 4) | (1 << 0) | (1 << 5));
	delay(1500);
	// pipe0 icin auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , 0x00);
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	//NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps sec -18db sec
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 icin ayari
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayari
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 0));
}

void NRF_write_buf(unsigned char komut,unsigned char *veri,unsigned int size) {
    unsigned int turn;
    NRF_CSN_LOW;
    spi(komut);
    for (turn = 0; turn < size; turn++) {
    spi(veri[turn]);
    }
    NRF_CSN_HIGH;
}
void NRF_read_buf(unsigned char komut,unsigned char *veri,unsigned int size) {
    unsigned int turn;
    NRF_CSN_LOW;
    spi(komut);
    for (turn = 0; turn < size; turn++) {
    veri[turn] = spi(NOP);
    }
    NRF_CSN_HIGH;
}
void NRF_write_reg(unsigned char komut,unsigned char deger) {
    NRF_CSN_LOW;
    spi(komut);
    spi(deger);
    NRF_CSN_HIGH;
}
unsigned char NRF_read_reg(unsigned char komut) {
    unsigned char sonuc;
    NRF_CSN_LOW;
    spi(komut);
    sonuc = spi(NOP);
    NRF_CSN_HIGH;
    return sonuc;
}
void NRF_flush_tx(void) {
	NRF_CSN_LOW;
    spi(FLUSH_TX);
    NRF_CSN_HIGH;
}
void NRF_flush_rx(void) {
	NRF_CSN_LOW;
    spi(FLUSH_RX);
    NRF_CSN_HIGH;
}

//	sadece ilk bytini degistir gonder toplamda 5 byte var
void NRF_send(unsigned char data)
{
	unsigned char var[5] = {data,0x1,0x2,0x3,0x4};
	NRF_write_buf(W_TX_PAYLOAD, var, 5);
    NRF_CE_HIGH;
    delay(10);
    NRF_CE_LOW;
    delay(130);
}
//	sadece ilk byt ini al
unsigned char NRF_get(void)
{
	unsigned char var[5];
	NRF_read_buf(R_RX_PAYLOAD, var, 5);
	return var[0];
}



