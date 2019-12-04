#include "stm8s.h"
#include "beep.h"

// beep frequency 500hz,1Khz,2Khz,4Khz
// 0 = 500hz , 1 = 1Khz , 2 = 2Khz , 4 = 4Khz
void beep_init(unsigned char beep_freq)
{
  BEEP_CSR = ( (1 << 5) | (32 / (2 * beep_freq) ) );
}



