#include "nrf.h"
#include "delay.h"
#include "stm8s.h"
#include "spi.h"

void nrf_gpio_init(void)
{
	//	NRF IRQ SETTINGS
	//	MAKE DIRECTION INPUT PC4,PC3
	PC_DDR &= ~( (1 << 3) | (1 << 4) ); // 3 FOR NRF1 --- 4 FOR NRF2
	// For double device 
	PA_DDR |= (1 << 3); // NRF1 CE
	PA_DDR |= (1 << 2); // NRF2 CE
	PA_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1 CE
	PA_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2 CE
	PA_ODR &= ~(1 << 3); // OUTPUT LOW NRF1 CE
	PA_ODR &= ~(1 << 2); // OUTPUT LOW NRF2 CE
	
	//	NRF CSN SETTINGS SPI CHIP SELECT ACTIVE LOW
	PD_DDR |= (1 << 3); // NRF1 CSN
	PD_DDR |= (1 << 2); // NRF2 CSN
	PD_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1 CSN
	PD_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2 CSN
	PD_ODR |= (1 << 3); // OUTPUT HIGH NRF1 CSN
	PD_ODR |= (1 << 2); // OUTPUT HIGH NRF2 CSN
}

void wait_irq(unsigned char which_nrf)
{
	// NRF1 IRQ PIN IS PC3 ---- READ PC3 PIN UNTIL BE LOW
	if(which_nrf == 3)
	{
		while( !(PC_IDR & (1 << 3) ) );
	}
	else
	{
		while( !(PC_IDR & (1 << 4) ) );
	}
}

void nrf24l01_init(unsigned char which_nrf)
{
	delay_ms(100);							// wait until it happens to power down mode 100ms
	nrf_write_reg(W_REGISTER | CONFIG , (CONFIG_PWR_UP | CONFIG_EN_CRC),which_nrf);		// only start up for make standby-1
	delay_ms(2);							// wait 1.5ms for power up
	nrf_write_reg(W_REGISTER | EN_AA , EN_AA_ENAA_P0,which_nrf);		// FOR PIPE0 SET OUTO ACK
	nrf_write_reg(W_REGISTER | EN_RXADDR , EN_RXADDR_ERX_P0,which_nrf);	// ONLY ACTIVE PIPE0
	
	// communication addr byte size (3,4,5 byte)  RESET_VALUE = 5(GOOD NOT CHANGED) 
	// NRF_write_reg(W_REGISTER | SETUP_AW , 0x5,which_nrf);
	
	nrf_write_reg(W_REGISTER | SETUP_RETR , 0x01,which_nrf);			// TRANSFER RETRY COUNT 250us ONLY "1" 
	
	// SETS FREQUENCY CHANNEL (0 - 128) RESET_VALUE = 2(GOOD NOT CHANGED) 
	// NRF_write_reg(W_REGISTER | RF_CH , 0x2,which_nrf);
	
	nrf_write_reg(W_REGISTER | RF_SETUP , RF_SETUP_250K_BPS_18_DBM,which_nrf); // 250kbps , -18dbm setting
	
	// Number of bytes in RX payload in data pipe
	// from pipe 0 wait 1 byte data
	set_rx_pw_px(0,1,which_nrf);
	
	nrf_write_reg(W_REGISTER | DYNPD , DYNPD_DPL_P0,which_nrf);		// must be tryed dynamic payload lengh MUST! 
	// enable with ack
	// nrf_write_reg(W_REGISTER | FEATURE , FEATURE_EN_ACK_PAY,which_nrf);	// Enables Payload with ACK
	// enable without ack
	 nrf_write_reg(W_REGISTER | FEATURE , FEATURE_EN_DYN_ACK,which_nrf);	// Enables Payload without ACK
	make_tx(which_nrf);							// default is tx at config register
	// make_rx(which_nrf);
	// delay_us(130);							// wait for convert to tx or rx from datasheet
	// no need to hange comminication address for now
}
void make_tx(unsigned char which_nrf)
{
	PA_ODR &= ~(1 << which_nrf);// NRF CE LOW
	// close MAX_RT interrupt and RX_DR interrupt
	nrf_write_reg(W_REGISTER | CONFIG , (CONFIG_PWR_UP | CONFIG_EN_CRC | CONFIG_MASK_MAX_RT | CONFIG_MASK_RX_DR),which_nrf);
	// 100.1us + 9.99us + 9.99us + 9.99us
	delay_130us;
}

void make_rx(unsigned char which_nrf)
{
	// close MAX_RT interrupt and TX_DS interrupt
	nrf_write_reg(W_REGISTER | CONFIG , (CONFIG_PWR_UP | CONFIG_EN_CRC | CONFIG_PRIM_RX | CONFIG_MASK_TX_DS | CONFIG_MASK_MAX_RT),which_nrf);
	// 100.1us + 9.99us + 9.99us + 9.99us
	delay_130us;
	PA_ODR |= (1 << which_nrf);// NRF CE HIGH
}

void nrf_send(unsigned char which_nrf)
{
    PA_ODR |= (1 << which_nrf);// NRF CE HIGH
    delay_10us;
    PA_ODR &= ~(1 << which_nrf);// NRF CE LOW 
}

/*
void get_rx_addr_p_0_1(unsigned char x_0_1,unsigned char * addr,unsigned char which_nrf) // 5 byte total
{

    unsigned char f;
    PD_ODR &= ~(1 << which_nrf); // NRF CSN LOW
    spi(R_REGISTER | (RX_ADDR_PX + x_0_1));
    for (f = 0 ; f < 5 ; f++)
    {
    	* (addr + f) = spi(NOP); // LSByte is read first
    }
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}

// MSB 4 BYTE SAME AS P1 ONLY LAST BYTE WRITE THIS REG (FROM DATASHEET)
unsigned char get_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5,unsigned char which_nrf)
{
	return nrf_read_reg(R_REGISTER | (RX_ADDR_PX + x_2_3_4_5) ,which_nrf);
}

void get_tx_addr(unsigned char * addr,unsigned char which_nrf)
{

    unsigned char f;
    PD_ODR &= ~(1 << which_nrf); // NRF CSN LOW
    spi(R_REGISTER | TX_ADDR);
    for (f = 0 ; f < 5 ; f++)
    {
    	*( addr + f) = spi(NOP); // LSByte is read first
    }
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}

*/

// set nrf rx comminication addr
void set_rx_addr_p_0_1(unsigned char x_0_1,unsigned char addr[5],unsigned char which_nrf)
{

    unsigned char f;
    PD_ODR &= ~(1 << which_nrf); // NRF CSN LOW
    spi(W_REGISTER | (RX_ADDR_PX + x_0_1));
    for (f = 0 ; f < 5 ; f++)
    {
    	spi(addr[f]); // LSByte is written first
    }
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}

// MSB 4 BYTE SAME AS P1 ONLY LAST BYTE WRITE THIS REG (FROM DATASHEET)
void set_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5,unsigned char addr,unsigned char which_nrf)
{
	nrf_write_reg(W_REGISTER | (RX_ADDR_PX + x_2_3_4_5) , addr,which_nrf);
}

// set nrf tx comminication addr
void set_tx_addr(unsigned char addr[5],unsigned char which_nrf)
{

    unsigned char f;
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(W_REGISTER | TX_ADDR);
    for (f = 0 ; f < 5 ; f++)
    {
    	spi(addr[f]); // LSByte is written first
    }
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}


// pipe number and how many byte watiting at this pipe
void set_rx_pw_px(unsigned char pipe,unsigned char x_1_32,unsigned char which_nrf) // x_1_32 = Number of bytes in RX payload
{
	nrf_write_reg(W_REGISTER | (RX_PW_PX + pipe) , x_1_32,which_nrf);
}

void nrf_write_buf(unsigned char * data,unsigned char size,unsigned char which_nrf)
{
    unsigned char f;
    if(size < 32)
    {
    	PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    	spi(W_TX_PAYLOAD);
    	for (f = 0; f < size; f++)
    	{
    		spi( *(data + f) );
    	}
    	PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
    }
    else
    {
	    // return ERROR;
    }
	
}
void nrf_read_buf(unsigned char * data,unsigned char size,unsigned char which_nrf) {
    unsigned char f;
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(R_RX_PAYLOAD);
    for (f = 0; f < size; f++)
    {
    	*(data + f) = spi(NOP);
    }
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}

void clear_irq(unsigned char which_nrf)
{
	nrf_write_reg(STATUS_REG,( STATUS_RX_DR | STATUS_TX_DS | STATUS_MAX_RT ),which_nrf);
}

void nrf_write_reg(unsigned char reg,unsigned char data,unsigned char which_nrf) {
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(reg);
    spi(data);
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}
unsigned char nrf_read_reg(unsigned char reg,unsigned char which_nrf) {
    unsigned char sonuc;
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(reg);
    sonuc = spi(NOP);
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
    return sonuc;
}
void nrf_flush_tx(unsigned char which_nrf) {
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(FLUSH_TX);
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}
void nrf_flush_rx(unsigned char which_nrf) {
    PD_ODR &= ~(1 << which_nrf);// NRF CSN LOW
    spi(FLUSH_RX);
    PD_ODR |= (1 << which_nrf);//NRF CSN HIGH
}
