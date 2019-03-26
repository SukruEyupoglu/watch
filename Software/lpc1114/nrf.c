/*
 * nrf_init.c
 *
 *  Created on: 9 Tem 2018
 *      Author: root
 */
#include "init.h"
#include "inc/LPC11xx.h"

void nrf_gpio_init(void)
{
//	NRF RECEIVER TRANSCEIVER SETTINGS
	LPC_GPIO1->DIR					&=	~(1 << 5);
	//	NRF IRQ SETTINGS
	LPC_GPIO2->DIR					&=	~(1 << 2);
	//	NRF CE SETTINGS
	LPC_GPIO1->DIR					|=	(1 << 10);
	LPC_GPIO1->DATA					&=	~(1 << 10);
	//	NRF CSN SETTINGS
	LPC_GPIO2->DIR					|=	(1 << 11);
	LPC_GPIO2->DATA					|=	(1 << 11);


	//	100ms delay for nrf24l01 wakeup
	delay(100000);
	//	SET TX FOR NRF

	//	SET RX FOR NRF
	//	NRF_RX_INIT();
	//	MESAFE AYARI BUTONU
//	LPC_GPIO0->DIR					&=	~(1 << 1);

	/*
	//	GPIO INTEERUPT FOR MODE GPIO0_1 SAME AS ISP BUTTON
	LPC_GPIO0->DIR					&=	~(1 << 1);
	//	INTERRUPT LEVEL SENSITIVE NOT EDGE SETTING
	LPC_GPIO0->IS					|=	(1 << 1);
	//	INTERRUPT LOW SETTING
	LPC_GPIO0->IEV					&=	~(1 << 1);
	//	 INTERRUPT ENABLE ON GPIO0_1
	NVIC_EnableIRQ(EINT0_IRQn);
	LPC_GPIO0->IE					|=	(1 << 1);
	//	GPIO INTERRUPT CLEAR RECOMMENDED A DELAY FROM DATASHEET
	LPC_GPIO0->IC					|=	(1 << 1);
	delay(2);
	*/
//	LED0_OFF;
//	LED1_OFF;
//	LED2_OFF;
}

void NRF_TX_INIT(void)
{
	// config registerini set et default tx modu zaten 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 3));
	delay(1500);
	// pipe0 iÃ§in auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , (1 << 0));
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps seÃ§ -18db seÃ§
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 iÃ§in ayarÄ±
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayarÄ±
	NRF_write_reg(W_REGISTER | DYNPD , (1 << 0));
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 1) | (1 << 2));
}
void NRF_RX_INIT(void)
{
	// config registerini set et rx olarak 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 3) | (1 << 0));
	delay(1500);
	// pipe0 iÃ§in auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , (1 << 0));
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps seÃ§ -18db seÃ§
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 iÃ§in ayarÄ±
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayarÄ±
	NRF_write_reg(W_REGISTER | DYNPD , (1 << 0));
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 1) | (1 << 2));
}

void NRF_TX_INIT_NO_ACK(void)
{
	// config registerini set et default tx modu zaten 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 4) | (1 << 6));
	delay(1500);
	// pipe0 iÃ§in auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , 0x00);
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	NRF_write_reg(W_REGISTER | SETUP_RETR , 0x00);
	// 250kbps seÃ§ -18db seÃ§
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 iÃ§in ayarÄ±
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayarÄ±
	NRF_write_reg(W_REGISTER | FEATURE , (1 << 0));
}
void NRF_RX_INIT_NO_ACK(void)
{
	// config registerini set et rx olarak 1.5ms bekle
	NRF_write_reg(W_REGISTER | CONFIG , (1 << 1) | (1 << 4) | (1 << 0) | (1 << 5));
	delay(1500);
	// pipe0 iÃ§in auto ack set et
	NRF_write_reg(W_REGISTER | EN_AA , 0x00);
	// sadece pipe 0 aktif olsun
	NRF_write_reg(W_REGISTER | EN_RXADDR , (1 << 0));
	//	transfer retry miktari 4000us de bir 15 defa tekrar et
	//NRF_write_reg(W_REGISTER | SETUP_RETR , 0xFF);
	// 250kbps seÃ§ -18db seÃ§
	NRF_write_reg(W_REGISTER | RF_SETUP , (1 << 5));
	// rx 5 byte payload beklesin pipe 0 iÃ§in ayarÄ±
	NRF_write_reg(W_REGISTER | RX_PW_P0 , 0x05);
	// ack'li veri tranferi aktif etme ayarÄ±
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
