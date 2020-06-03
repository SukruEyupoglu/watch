#include "nrf24l01.h"
#include "delay.h"
#include "stm8s.h"
#include "spi.h"
#include "eeprom.h"

volatile unsigned char multi_nrf_select = 1;

void nrf_csn_low(void)
{
	if(multi_nrf_select == 1)
	{
		PA_ODR &= ~(1 << 2); // MAKE A2 LOW
	}
	else
	{
		PD_ODR &= ~(1 << 2); // MAKE D2 LOW
	}
}

void nrf_csn_high(void)
{
	if(multi_nrf_select == 1)
	{
		PA_ODR |= (1 << 2); // MAKE A2 HIGH
	}
	else
	{
		PD_ODR |= (1 << 2); // MAKE D2 HIGH
	}
}

void nrf_send(unsigned char * data , unsigned char size)
{
    nrf_write_buf(data , size);
    NRF_CE_HIGH;
    delay_10us;
    NRF_CE_LOW;
}

unsigned char check_irq_status(void)
{
  switch(nrf_read_reg(STATUS_REG) & 
    (
      STATUS_RX_DR |
      STATUS_TX_DS |
      STATUS_MAX_RT
    ) )
  {
    case STATUS_RX_DR :
    {
      return RX_DR_INT;
    }
    case STATUS_TX_DS :
    {
      return TX_DS_INT;
    }
    case STATUS_MAX_RT :
    {
      return MAX_RT_INT;
    }
  }
  return VOID_INT;
}

// ready for testing only 1 byte data waiting for rx look at DYNPD later
void nrf24l01_init(void)
{
	delay_ms(100);							// wait until it happens to power down mode 100ms
	nrf_write_reg(W_REGISTER | CONFIG , CONFIG_PWR_UP);		// only start up for make standby-1
	delay_ms(2);							// wait 1.5ms for power up
	nrf_write_reg(W_REGISTER | EN_AA , EN_AA_ENAA_P0);		// FOR PIPE0 SET OUTO ACK
	nrf_write_reg(W_REGISTER | EN_RXADDR , EN_RXADDR_ERX_P0);	// ONLY ACTIVE PIPE0
	
	// communication addr byte size (3,4,5 byte)  RESET_VALUE = 5(GOOD NOT CHANGED) 
	// NRF_write_reg(W_REGISTER | SETUP_AW , 0x3);
	
	nrf_write_reg(W_REGISTER | SETUP_RETR , 0x01);			// TRANSFER RETRY COUNT 250us ONLY "1" 
	
	// SETS FREQUENCY CHANNEL (0 - 128) RESET_VALUE = 2(GOOD NOT CHANGED) 
	// NRF_write_reg(W_REGISTER | RF_CH , 0x2);
	
	nrf_write_reg(W_REGISTER | RF_SETUP , RF_SETUP_250K_BPS_18_DBM); // 250kbps , -18dbm setting
	
	// Number of bytes in RX payload in data pipe
	set_rx_pw_px(0,5);
	
	nrf_write_reg(W_REGISTER | DYNPD , DYNPD_DPL_P0);		// must be tryed dynamic payload lengh MUST! 
	nrf_write_reg(W_REGISTER | FEATURE , FEATURE_EN_ACK_PAY);	// Enables Payload with ACK
	make_tx();							// default is tx at config register
	// make_rx();
	// delay_us(130);							// wait for convert to tx or rx from datasheet	
}

void nrf24l01_init_from_eeprom(void)
{
	unsigned char data;
	unsigned char data_array[5];
	delay_ms(100);							// wait until it happens to power down mode 100ms
	
	// Configuration Register
	eeprom_read(CONFIG_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | CONFIG , data);			// only start up for make standby-1
	
	delay_ms(2);							// wait 1.5ms for power up
	
	// Enable ‘Auto Acknowledgment’ Function Disable this functionality to be compatible with nRF2401
	eeprom_read(EN_AA_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | EN_AA , data);
	
	// Enabled RX Addresses
	eeprom_read(EN_RXADDR_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | EN_RXADDR , data);
	
	// Setup of Address Widths (common for all data pipes)
	eeprom_read(SETUP_AW_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | SETUP_AW , data);
	
	// Setup of Automatic Retransmission
	eeprom_read(SETUP_RETR_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | SETUP_RETR , data);
	
	// RF Channel 0 - 127
	eeprom_read(RF_CH_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RF_CH , data);
	
	// RF Setup Register
	eeprom_read(RF_SETUP_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RF_SETUP , data);
	
	// Receive address data pipe (LSByte is written first)
	eeprom_read(RX_ADDR_P0_EE_ADDR, data_array, MAX_ADDR_SIZE);
	set_rx_addr_p_0_1(P0,data_array);
	eeprom_read(RX_ADDR_P1_EE_ADDR, data_array, MAX_ADDR_SIZE);
	set_rx_addr_p_0_1(P1,data_array);
	eeprom_read(RX_ADDR_P2_EE_ADDR, &data, 1);
	set_rx_addr_p_2_3_4_5(P2,data);
	eeprom_read(RX_ADDR_P3_EE_ADDR, &data, 1);
	set_rx_addr_p_2_3_4_5(P3,data);	
	eeprom_read(RX_ADDR_P4_EE_ADDR, &data, 1);
	set_rx_addr_p_2_3_4_5(P4,data);
	eeprom_read(RX_ADDR_P5_EE_ADDR, &data, 1);
	set_rx_addr_p_2_3_4_5(P5,data);
	
	// Transmit address. Used for a PTX device only. (LSByte is written first)
	eeprom_read(TX_ADDR_EE_ADDR, data_array, MAX_ADDR_SIZE);
	set_tx_addr(data_array);
	
	// Number of waiting bytes in RX payload without DYNPD in data pipe ( 1 to 32 bytes )
	eeprom_read(RX_PW_P0_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P0 , data);
	eeprom_read(RX_PW_P1_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P1 , data);
	eeprom_read(RX_PW_P2_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P2 , data);
	eeprom_read(RX_PW_P3_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P3 , data);
	eeprom_read(RX_PW_P4_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P4 , data);
	eeprom_read(RX_PW_P5_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | RX_PW_P5 , data);

	// Enable dynamic payload length
	eeprom_read(DYNPD_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | DYNPD , data);
	
	// Enable dynamic payload length
	eeprom_read(FEATURE_EE_ADDR, &data, 1);
	nrf_write_reg(W_REGISTER | FEATURE , data);
	
	// default is tx at config register
	make_tx();
	// make_rx();
	// wait for convert to tx or rx from datasheet
	// delay_us(130);
}

void make_tx(void)
{
        NRF_CE_LOW;
	nrf_write_reg(W_REGISTER | CONFIG , CONFIG_PWR_UP);
        delay_us(130);
}

void make_rx(void)
{
	nrf_write_reg(W_REGISTER | CONFIG , (CONFIG_PWR_UP | PRIM_RX) );
        delay_us(130);
        NRF_CE_HIGH;
}

void get_rx_addr_p_0_1(unsigned char x_0_1,unsigned char * addr) // 5 byte total
{

    unsigned char f;
    NRF_CSN_LOW;
    spi(R_REGISTER | (RX_ADDR_PX + x_0_1));
    for (f = 0 ; f < 5 ; f++)
    {
    	* (addr + f) = spi(NOP); // LSByte is read first
    }
    NRF_CSN_HIGH;
}

// MSB 4 BYTE SAME AS P1 ONLY LAST BYTE WRITE THIS REG (FROM DATASHEET)
unsigned char get_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5)
{
	return nrf_read_reg(R_REGISTER | (RX_ADDR_PX + x_2_3_4_5) );
}

void get_tx_addr(unsigned char * addr)
{

    unsigned char f;
    NRF_CSN_LOW;
    spi(R_REGISTER | TX_ADDR);
    for (f = 0 ; f < 5 ; f++)
    {
    	*( addr + f) = spi(NOP); // LSByte is read first
    }
    NRF_CSN_HIGH;
}


void set_rx_addr_p_0_1(unsigned char x_0_1,unsigned char addr[5])
{

    unsigned char f;
    NRF_CSN_LOW;
    spi(W_REGISTER | (RX_ADDR_PX + x_0_1));
    for (f = 0 ; f < 5 ; f++)
    {
    	spi(addr[f]); // LSByte is written first
    }
    NRF_CSN_HIGH;
}

// MSB 4 BYTE SAME AS P1 ONLY LAST BYTE WRITE THIS REG (FROM DATASHEET)
void set_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5,unsigned char addr)
{
	nrf_write_reg(W_REGISTER | (RX_ADDR_PX + x_2_3_4_5) , addr);
}

void set_tx_addr(unsigned char addr[5])
{

    unsigned char f;
    NRF_CSN_LOW;
    spi(W_REGISTER | TX_ADDR);
    for (f = 0 ; f < 5 ; f++)
    {
    	spi(addr[f]); // LSByte is written first
    }
    NRF_CSN_HIGH;
}

void set_rx_pw_px(unsigned char pipe,unsigned char x_1_32) // x_1_32 = Number of bytes in RX payload in data pipe
{
	nrf_write_reg(W_REGISTER | (RX_PW_PX + pipe) , x_1_32);
}

void nrf_write_buf(unsigned char * data,unsigned char size)
{
    unsigned char f;
    if(size < 32)
    {
    	NRF_CSN_LOW;
    	spi(W_TX_PAYLOAD);
    	for (f = 0; f < size; f++)
    	{
    		spi( *(data + f) );
    	}
    	NRF_CSN_HIGH;
    }
    else
    {
	    // return ERROR;
    }
	
}
void nrf_read_buf(unsigned char * data,unsigned char size) {
    unsigned char f;
    NRF_CSN_LOW;
    spi(R_RX_PAYLOAD);
    for (f = 0; f < size; f++)
    {
    	*(data + f) = spi(NOP);
    }
    NRF_CSN_HIGH;
}

void nrf_write_reg(unsigned char reg,unsigned char data) {
    NRF_CSN_LOW;
    spi(reg);
    spi(data);
    NRF_CSN_HIGH;
}
unsigned char nrf_read_reg(unsigned char reg) {
    unsigned char sonuc;
    NRF_CSN_LOW;
    spi(reg);
    sonuc = spi(NOP);
    NRF_CSN_HIGH;
    return sonuc;
}
void nrf_flush_tx(void) {
    NRF_CSN_LOW;
    spi(FLUSH_TX);
    NRF_CSN_HIGH;
}
void nrf_flush_rx(void) {
    NRF_CSN_LOW;
    spi(FLUSH_RX);
    NRF_CSN_HIGH;
}
/*
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
*/
/*
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
*/
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
