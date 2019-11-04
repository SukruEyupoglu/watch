void get_ds3231_data(void);
unsigned char time2reg(unsigned char time);
unsigned char reg2time(unsigned char reg);
void raw_to_ds_t(ds_t * ds,unsigned char array[19]);
