#include "nrf24l01.h"
#include "delay.h"
#include "stm8s.h"
#include "spi.h"

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
	// delay(100000);
        // For double device 
        
}
// ready for testing only 1 byte data waiting for rx look at DYNPD later
void nrf24l01_init(void)
{
	delay_ms(100);							// wait until it happens to power down mode 100ms
	NRF_write_reg(W_REGISTER | CONFIG , CONFIG_PWR_UP);		// only start up for make standby-1
	delay_ms(2);							// wait 1.5ms for power up
	NRF_write_reg(W_REGISTER | EN_AA , EN_AA_ENAA_P0);		// pipe0 icin auto ack set et
	NRF_write_reg(W_REGISTER | EN_RXADDR , EN_RXADDR_ERX_P0);	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0x01);			// transfer retry miktari 250us de bir "1" defa tekrar et
	NRF_write_reg(W_REGISTER | RF_SETUP , RF_SETUP_250K_BPS_18_DBM); // 250kbps , -18dbm setting
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x01);			// RX 5 byte data payload beklesin pipe 0 icin ayari
	NRF_write_reg(W_REGISTER | DYNPD , DYNPD_DPL_P0);		// must be tryed dynamic payload lengh MUST! 
	NRF_write_reg(W_REGISTER | FEATURE , FEATURE_EN_ACK_PAY);	// Enables Payload with ACK
	make_tx();							// default is tx at config register
	// make_rx();
	// delay_us(130);							// wait for convert to tx or rx from datasheet	
}
	
void make_tx(void)
{
        NRF_CE_LOW;
	NRF_write_reg(W_REGISTER | CONFIG , CONFIG_PWR_UP);
        delay_us(130);
}

void make_rx(void)
{
	NRF_write_reg(W_REGISTER | CONFIG , (CONFIG_PWR_UP | PRIM_RX) );
        delay_us(130);
        NRF_CE_HIGH;
}

void set_rx_p0_size(unsigned char size)
{
  NRF_write_reg(W_REGISTER | RX_PW_P0 , size);	// RX size kadar byte data payload beklesin pipe 0 icin ayari
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
	// rx 5 byte payload beklesin pipe 0 icin ayari (data byte count)
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
void NRF_write_buf(unsigned char * data,unsigned char size)
{
    unsigned char f;
    NRF_CSN_LOW;
    spi(W_TX_PAYLOAD);
    for (f = 0; f < size; f++)
    {
    spi(data[f]);
    }
    NRF_CSN_HIGH;
}
void NRF_read_buf(unsigned char * data,unsigned char size) {
    unsigned char f;
    NRF_CSN_LOW;
    spi(R_RX_PAYLOAD);
    for (f = 0; f < size; f++)
    {
    data[f] = spi(NOP);
    }
    NRF_CSN_HIGH;
}
/*
void NRF_write_buf(unsigned char komut,unsigned char *veri,unsigned char size) {
    unsigned char f;
    NRF_CSN_LOW;
    spi(komut);
    for (f = 0; f < size; f++)
    {
    spi(veri[f]);
    }
    NRF_CSN_HIGH;
}
void NRF_read_buf(unsigned char komut,unsigned char *veri,unsigned char size) {
    unsigned char f;
    NRF_CSN_LOW;
    spi(komut);
    for (f = 0; f < size; f++)
    {
    veri[f] = spi(NOP);
    }
    NRF_CSN_HIGH;
}
*/
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
void NRF_send(unsigned char * data , unsigned char size)
{
	unsigned char var[5] = {data,0x1,0x2,0x3,0x4};
	NRF_write_buf(W_TX_PAYLOAD, var, 5);
    NRF_CE_HIGH;
    delay(10);
    NRF_CE_LOW;
    // delay(130);
}
//	sadece ilk byt ini al
unsigned char NRF_get(void)
{
	unsigned char var[5];
	NRF_read_buf(R_RX_PAYLOAD, var, 5);
	return var[0];
}



