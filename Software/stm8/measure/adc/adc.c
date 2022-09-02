#include "../stm8s.h"
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
	ADC1_CR1 |= (1 << ADC1_CR1_ADON);
	// wait end of conversion
	while (!(ADC1_CSR & (1 << ADC1_CSR_EOC)));
	// return only MSB
	return ADC1_DRH;;
}
// int is 8 bit for stm8
// ADC1 MAX CONVERSION SPEED , ONLY 3,4,5,6 CHANNEL FOR STM8S003C8T6
// void adc(4 , 10 , &val);
void adc(unsigned char channel , unsigned char count , int *data_h)
{
	unsigned char f;
	// close ADC
	ADC1_CR1 &= ~(1 << ADC1_CR1_ADON);
	// clear EOC flag
	ADC1_CSR &= ~(1 << ADC1_CSR_EOC);
	// write channel
	ADC1_CSR |= channel;
	// set CONT bit for continuous conversion
	ADC1_CR1 |= (1 << ADC1_CR1_CONT);
	
	// power up ADC
	ADC1_CR1 |= (1 << ADC1_CR1_ADON);
	// start conversion
	ADC1_CR1 |= (1 << ADC1_CR1_ADON);
	
	for(f = 0 ; f < count ; f++)
	{
		// wait end of conversion
		while (!(ADC1_CSR & (1 << ADC1_CSR_EOC)));
		// add sum of conversion
		*data_h += (ADC1_DRH / count);
		// if last turn close ADC
		if(f = (count - 1) ) ADC1_CR1 &= ~(1 << ADC1_CR1_ADON);
		// clear EOC flag for start new converion if ADC working
		ADC1_CSR &= ~(1 << ADC1_CSR_EOC);
	}
	// close ADC
	// ADC1_CR1 &= ~(1 << ADC1_CR1_ADON);
}






