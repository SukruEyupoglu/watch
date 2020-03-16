
#include "error.h"
#include "led.h"

#define ERR 1
#define ERROR 1
#define OK 0

void error(void)
{
  led_write_digit('E','R');
  led_write();
}

