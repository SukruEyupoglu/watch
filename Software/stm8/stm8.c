#include "stm8s.h"
#include "nrf24l01.h"
#include "uart.h"

int main(void)
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
	// from pipe 0 wait 5 byte data
	set_rx_pw_px(0,5);
	
	nrf_write_reg(W_REGISTER | DYNPD , DYNPD_DPL_P0);		// must be tryed dynamic payload lengh MUST! 
	nrf_write_reg(W_REGISTER | FEATURE , FEATURE_EN_ACK_PAY);	// Enables Payload with ACK
	make_tx();							// default is tx at config register
	// make_rx();
	// delay_us(130);							// wait for convert to tx or rx from datasheet
// no need to hange comminication address for now
}
