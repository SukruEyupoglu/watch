



void adc_init(void);
unsigned char adc_0_mic_read(void);
unsigned char adc_1_time_up_down_read(void);
unsigned char adc_2_light_up_down_read(void);
unsigned char adc_4_pir_read(void);

unsigned char adc_read(unsigned char adcx);

// try this for too much instruction
#define ADC(x)    (x)

#define ADC0      0
#define ADC1      1
#define ADC2      2
#define ADC3      3
#define ADC4      4
#define ADC5      5
#define ADC6      6
#define ADC7      7

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

#define AD0CR_START_CONVERSION_BIT      (1 << 24)
// if capture or match u need for start look datasheet
#define AD0CR_START_CONVERSION_WITH_CAP0_MAT0          (0x7 << 24)
#define AD0CR_START_EDGE                (1 << 27)

#define AD0GDR_V_VREF                   (0x3FF << 6)
#define AD0GDR_CHN                      (0x7 << 24)
#define AD0GDR_OVERRUN                  (1 << 30)
#define AD0GDR_DONE                     (1 << 31)

#define AD0INTEN_ADINTEN_AD0            (1 << 0)
#define AD0INTEN_ADINTEN_AD1            (1 << 1)
#define AD0INTEN_ADINTEN_AD2            (1 << 2)
#define AD0INTEN_ADINTEN_AD3            (1 << 3)
#define AD0INTEN_ADINTEN_AD4            (1 << 4)
#define AD0INTEN_ADINTEN_AD5            (1 << 5)
#define AD0INTEN_ADINTEN_AD6            (1 << 6)
#define AD0INTEN_ADINTEN_AD7            (1 << 7)

#define AD0INTEN_ADGINTEN               (1 << 8)

#define AD0DRX_V_VREF                   (0x3FF << 6)
#define AD0DR_V_VREF                    0xFFC0
#define AD0DRX_OVERRUN                  (1 << 30)
#define AD0DRX_DONE                     (1 << 31)
#define AD0DR_DONE                      0x7FFFFFFF










