#include "stm8s.h"
#include "spi.h"


void change_spi_clk_channel(unsigned char channel)
{
  PA_ODR = channel;
}












