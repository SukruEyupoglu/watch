
#include "uart.h"
#include "list.h"
#include "nrf24l01.h"
#include "PLATFORMLESS.h"

void list(void)
{
  const unsigned char status[15] = {'S','T','A','T','U','S',SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE};
  const unsigned char rx_addr_p0_1[15] = {'R','X','_','A','D','D','R','_','P','0','-','1',SPACE,SPACE,'='};
  const unsigned char rx_addr_p2_5[15] = {'R','X','_','A','D','D','R','_','P','2','-','5',SPACE,SPACE,'='};
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
  
  const unsigned char hex_0x[3] = {SPACE,'0','x'};
  const unsigned char space_2[2] = {SPACE,SPACE};
  
  unsigned char x;
  unsigned char f;
  unsigned char y[5];
  
    // line 1 start here
  
  uart_send_array(status, 15);
  x = nrf_read_reg(STATUS_REG);
  uart_send_array(rx_dr, 8);
  if(x & STATUS_RX_DR)
  {
    uart_send('1');
  }
  else
  {
    uart_send('0');
  }
  uart_send_array(space_2, 2);
  uart_send_array(tx_ds, 8);
  if(x & STATUS_TX_DS)
  {
    uart_send('1');
  }
  else
  {
    uart_send('0');
  }
  uart_send_array(space_2, 2);
  uart_send_array(max_rt, 8);
  if(x & STATUS_MAX_RT)
  {
    uart_send('1');
  }
  else
  {
    uart_send('0');
  }
  uart_send_array(space_2, 2);
  
  uart_send_array(rx_p_no, 8);
  uart_send(hex_to_ascii( ( 0x7 & (x >> 1) ) ) );
  
  uart_send_array(space_2, 2);
  uart_send_array(tx_full, 8);
  if(x & STATUS_TX_FULL)
  {
    uart_send('1');
  }
  else
  {
    uart_send('0');
  }
  uart_send('\r');
  uart_send('\n');
  
  // line 2 start here
  
  uart_send_array(rx_addr_p0_1, 15);
  uart_send_array(hex_0x, 3);
  
  get_rx_addr_p_0_1(PIPE_0,y);
  for(f = 0 ; f < 5 ; f++)
  {
    uart_send(hex_to_ascii( ( y[(4 - f)] >> 4) & 0xF) );
    uart_send(hex_to_ascii(y[(4 - f)] & 0xF) );
  }
  
  uart_send_array(space_2, 2);
  uart_send_array(hex_0x, 3);
  
  get_rx_addr_p_0_1(PIPE_1,y);
  for(f = 0 ; f < 5 ; f++)
  {
    uart_send(hex_to_ascii( ( y[(4 - f)] >> 4) & 0xF) );
    uart_send(hex_to_ascii(y[(4 - f)] & 0xF) );
  }
  uart_send_array(space_2, 2);
  uart_send('\r');
  uart_send('\n');
  
    // line 3 start here
  
  uart_send_array(rx_addr_p2_5, 15);
  
  uart_send_array(hex_0x, 3);
  x = get_rx_addr_p_2_3_4_5(PIPE_2);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send_array(hex_0x, 3);
  x = get_rx_addr_p_2_3_4_5(PIPE_3);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send_array(hex_0x, 3);
  x = get_rx_addr_p_2_3_4_5(PIPE_4);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send_array(hex_0x, 3);
  x = get_rx_addr_p_2_3_4_5(PIPE_5);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 4 start here
  
  uart_send_array(tx_addr, 15);
  uart_send_array(hex_0x, 3);
  
  get_tx_addr(y);
  for(f = 0 ; f < 5 ; f++)
  {
    uart_send(hex_to_ascii( ( y[(4 - f)] >> 4) & 0xF) );
    uart_send(hex_to_ascii(y[(4 - f)] & 0xF) );
  }
  
  uart_send('\r');
  uart_send('\n');
  
  // line 5 start here
  
  uart_send_array(rx_pw_p0_6, 15);
  for(f = 0 ; f < 6 ; f++)
  {
    uart_send_array(hex_0x, 3);
    x = nrf_read_reg(RX_PW_PX + f);
    uart_send(hex_to_ascii( (x >> 4) & 0xF) );
    uart_send(hex_to_ascii(x & 0xF) );
  }
  
  uart_send('\r');
  uart_send('\n');
  
  // line 6 start here
  
  uart_send_array(en_aa, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(EN_AA);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 7 start here
  
  uart_send_array(en_rxaddr, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(EN_RXADDR);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 8 start here
  
  uart_send_array(rf_ch, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(RF_CH);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 9 start here
  
  uart_send_array(rf_setup, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(RF_SETUP);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 10 start here
  
  uart_send_array(config, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(CONFIG);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  
  uart_send('\r');
  uart_send('\n');
  
  // line 11 start here
  uart_send_array(dynpd_feature, 15);
  uart_send_array(hex_0x, 3);
  x = nrf_read_reg(DYNPD);
  f = nrf_read_reg(FEATURE);
  uart_send(hex_to_ascii( (x >> 4) & 0xF) );
  uart_send(hex_to_ascii(x & 0xF) );
  uart_send_array(hex_0x, 3);
  uart_send(hex_to_ascii(f & 0x7) );
  uart_send('\r');
  uart_send('\n');
  
  // end of list
  
}
void uart_send_array(unsigned char * array , unsigned char size)
{
  unsigned char f;
  for(f = 0 ; f < size ; f++)
  {
    uart_send( *(array + f) );
  }
}





