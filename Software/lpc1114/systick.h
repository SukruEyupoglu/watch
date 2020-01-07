

// interrupt ları interrupt içinde tekrar kurmak gerekir 
// yeniden interrupt a girsin diye
// fakat systick interrupt unun tekrar girmesine gerek yoktur.
// biz çağırınca girmesi gerekir.
// o yüzden interrupt un tekrar içinde aktif edilmez.

#define SYSTEM_CLOCK_FREQUENCY 12 // 12MHZ

#define SYSTICK_CLKSOURCE_BIT 2
#define SYSTICK_TICKINT_BIT 1
#define SYSTICK_ENABLE_BIT 0




void delay_sys(unsigned int u_sec);
void SysTick_Handler(void);




