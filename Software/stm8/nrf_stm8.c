#include "stm8s.h"
#include "list.h"
#include "nrf24l01.h"

int main(void)
{
  unsigned char send_data[5] = {5,4,3,2,1};
  unsigned char get_data[5];
  nrf24l01_init(); // default tx
  second_nrf24l01_init(); // default rx
  
  nrf_send(send_data , 5);
  wait_for_second_nrf();
  nrf_get(get_data , 5);
  
  if(send_data[0] == get_data[0])
  {
    led_yak();
  }
  
  while(1)
  {
    
  }
}
