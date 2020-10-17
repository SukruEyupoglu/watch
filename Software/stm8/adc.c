#include "stm8s.h"
#include "adc.h"


//  default align left and only MSB return
//  channel 3 or 4
//  clk_div 2 or 4 or 8 or 12 Fmaster/clk_div
//  for div = 2 : clk_div = 0
unsigned char adc_read(unsigned char channel,unsigned char clk_div)
{
	//  CLEAR EOC FLAG
	ADC1_CSR &= ~(1 << ADC1_CSR_EOC);
	// write channel
	ADC1_CSR |= channel;
	// set frequency and start conversion
	ADC1_CR1 |= ( (1 << ADC1_CR1_ADON) | (clk_div << 5) );
	// wait end of conversion
	while (!(ADC1_CSR & (1 << ADC1_CSR_EOC)));
	// return only MSB
	return ADC1_DRH;;
}
