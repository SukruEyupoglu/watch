#include "stm8s.h"
#include "motor.h"
#include "spi.h"
#include "function.h"
#include "error.h"
#include "gpio.h"


// motor_status looking for active_motor
volatile unsigned char motor_status[4] = {SB,SB,SB,SB};
volatile unsigned char active_motor; // selected active motor

// motor shift register related data
volatile unsigned char step_queue[8] = {FCF,TCF,SCF,SCFFCB,FCB,TCB,SCB,FCFSCB};

// if there is a limit error look at direction for rescue motor from error
// immadiately motor must step far away from error
volatile unsigned char active_motor_direction; // direction 0 is back 1 is next

// there are 3 type step FULL_STEP,HALF_STEP,QUARTER_STEP
// FULL_STEP = most slow but most strongly                              8 step full circle
// HALF_STEP = faster then FULL_STEP more strongly then QUARTER_STEP    4 step full circle
// QUARTER_STEP = most speed and most weak steps                        4 step full circle
volatile unsigned char step_type;

// serial or parallel shift register status 
volatile unsigned char serial_to_parallel[2];       // 2 PCS 74595
volatile unsigned char parallel_to_serial[3];       // 3 PCS 74165

// limit switch errors must be checked before every step
// only interrupt can make "1" this register
volatile unsigned char limit_interrupt;

int main(void)
{
  // SET CLK TO FULL SPEED (16MHZ)
  CLK_CKDIVR = 0;
  
  spi_init();
  uart_init();
  gpio_init();
  buzzer_init();
  adc_init();
  i2c_init();
  timer_init();
  clk_out_init();
  
PC3_interrupt_enable();
gpio_interrupt_init();
rescue_from_limit_switch_errors_instant();
look_at_limit_switch_errors();
change_active_motor(0x1);
release_motor();
motor_next(FCF);
motor_back(FCF);
change_direction();
look_at_motor_status();
write_motor_status(FCF);
//hold_motor(100);
motor_move(100,0);
move_to_find_limit_switch(BACK);


  while(1)
  {
    
  }

  return 0;
}


