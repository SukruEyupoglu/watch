void adc_init(void);
unsigned char adc_0_mic_read(void);
unsigned char adc_1_time_up_down_read(void);
unsigned char adc_2_light_up_down_read(void);
unsigned char adc_4_pir_read(void);

#define AD0CR_SEL_AD0                   (1 << 0)
#define AD0CR_SEL_AD1                   (1 << 1)
#define AD0CR_SEL_AD2                   (1 << 2)
#define AD0CR_SEL_AD3                   (1 << 3)
#define AD0CR_SEL_AD4                   (1 << 4)
#define AD0CR_SEL_AD5                   (1 << 5)
#define AD0CR_SEL_AD6                   (1 << 6)
#define AD0CR_SEL_AD7                   (1 << 7)

#define AD0CR_CLKDIV                    (0x77 << 8)    // 100KHZ

#define AD0CR_BURST                     (1 << 16)
#define AD0CR_BURST_CLKS                (0x000 << 17)

#define AD0CR_START_CONVERSION          (1 << 24)
// if capture or match u need for start look datasheet
#define AD0CR_START_CONVERSION_WITH_CAP0_MAT0          (0x7 << 24)

#define AD0CR_START_EDGE                (1 << 27)
















