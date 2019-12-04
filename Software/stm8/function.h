#ifndef FUNCTION_H
#define FUNCTION_H

// spi clock channel select
// stm8s has A1,A2,A3 pins not A0 pin
// directly write to PA DATA register this calculated values
#define CLK_CH_M0        0x0
#define CLK_CH_M1        0x2
#define CLK_CH_M2        0x4
#define CLK_CH_M3        0x6
#define CLK_CH_GPIO_OUT  0x8
#define CLK_CH_GPIO_IN   0xC
#define CLK_CH_FLASH     0xA
#define CLK_CH_SRAM      0xE


void change_spi_clk_channel(unsigned char channel);






#endif /* FUNCTION_H */



