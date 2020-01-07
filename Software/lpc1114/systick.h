

#define SYST_CSR (0xE000E010UL)
#define SYST_RVR (0xE000E014UL)
#define SYST_CVR (0xE000E018UL)
#define SYST_CALIB (0xE000E01CUL)

#define SYSTEM_CLOCK_FREQUENCY 12 // 12MHZ

#define SYSTICK_CLKSOURCE_BIT 2
#define SYSTICK_TICKINT_BIT 1
#define SYSTICK_ENABLE_BIT 0




void delay_sys(unsigned int u_sec);
void SysTick_Handler(void);




