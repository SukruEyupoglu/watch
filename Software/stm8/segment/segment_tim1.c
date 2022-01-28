void tim1_init(unsigned short sec)
{
  // THIS TIMER MAKED FOR LONG TIMING , ONLY SECOND
  // max second = 1638sec , min second = 1sec
  // frequency = F_CLK / ( ( (TIM1_PSCRH << 8) + TIM1_PSCRL) * (1 + ( (TIM1_ARRH << 8) + TIM1_ARRL) ) )
  TIM1_CR1    = 0;            // Disable TIM1
  TIM1->PSCRH = ( ( sec * 40 ) >> 8);
  TIM1->PSCRL = ( ( sec * 40 ) & 0xFF);
  TIM1->ARRH = 0xC3;
  TIM1->ARRL = 0x50;
  
  TIM1_CR1      |= (1 << TIM1_CR1_OPM); // stop at max value from ARR
  TIM1_IER      |= (1 << TIM1_IER_UIE); // Enable Update Interrupt
  TIM1->CR1 = TIM1_CR1_CEN; // Enable the counter
}

void timer_isr() __interrupt(TIM1_ISR) {
  
  
		// I2C TAKE THE CURSOR TO START
		i2c_start();
		i2c_write_addr(0xD0); // write
		i2c_write(0x0); // cursor setting
		i2c_stop();
		// GET ALL DATA FROM DS3231 TO d[0x13]
		i2c_start();
		i2c_write_addr(0xD1); // read
		i2c_read_arr(d,0x13);
		i2c_stop();
		// WRITE HOUR AND MINUTE
		spi(num_to_dig(d[hour])); //first hour
		spi(num_to_dig(d[minute])); //second minute
		// CHECK ALERT FLAG
		check_alert();
  
  
    TIM1_SR &= ~(1 << TIM1_SR_UIF);
}



  /*
  const uint16_t tim1_compare_reg1 = 4000; // 25% duty cycle
  TIM1->CCR1H = (tim1_compare_reg1 >> 8);
  TIM1->CCR1L = (tim1_compare_reg1 & 0xFF);
  */



