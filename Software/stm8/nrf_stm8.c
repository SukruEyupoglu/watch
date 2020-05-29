#include "stm8s.h"
#include "list.h"
#include "nrf24l01.h"

int main(void)
{
  nrf24l01_init(); // default tx
  second_nrf24l01_init(); // default tx
  while(1)
  {
    
  }
}
