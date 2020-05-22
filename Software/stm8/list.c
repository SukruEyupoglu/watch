
#include "uart.h"
#include "list.h"
#include "nrf24l01.h"
#include "PLATFORMLESS.h"

void list(void)
{
  const unsigned char status[15] = {'S','T','A','T','U','S',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char rx_addr_p0_1[15] = {'R','X','_','A','D','D','R','_','P','0','-','1',SPACE,SPACE,'='};
  const unsigned char rx_addr[15] = {'R','X','_','A','D','D','R','_','P','2','-','5',SPACE,SPACE,'='};
  const unsigned char tx_addr[15] = {'T','X','_','A','D','D','R',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char rx_pw_p0_6[15] = {'R','X','_','P','W','_','P','0','-','6',SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char en_aa[15] = {'E','N','_','A','A',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char en_rxaddr[15] = {'E','N','_','R','X','A','D','D','R',SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char rf_ch[15] = {'R','F','_','C','H',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char rf_setup[15] = {'R','F','_','S','E','T','U','P',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char config[15] = {'C','O','N','F','I','G',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,'='};
  const unsigned char dynpd_feature[15] = {'D','Y','N','P','D','/','F','E','A','T','U','R','E',SPACE,'='};
  
  const unsigned char rx_dr[8] = {'R','X','_','D','R',SPACE,SPACE,'='};
  const unsigned char tx_ds[8] = {'T','X','_','D','S',SPACE,SPACE,'='};
  const unsigned char max_rt[8] = {'M','A','X','_','R','T',SPACE,'='};
  const unsigned char rx_p_no[8] = {'R','X','_','P','_','N','O','='};
  const unsigned char tx_full[8] = {'T','X','_','F','U','L','L','='};
  
  const unsigned char hex_0x[2] = {'0','x'};
  
  unsigned char x;
  uart_send_array(status, 15);
  x = nrf_read_reg(STATUS_REG);
  uart_send_array(rx_dr, 8);
  
  
}
void uart_send_array(unsigned char * array , unsigned char size)
{
  unsigned char f;
  for(f = 0 ; f < size ; f++)
  {
    uart_send( *(array + f) );
  }
}





