#ifdef __cplusplus
extern "C" {
#endif

#define DS3231_MINUTE_ADDR 0x01
#define DS3231_HOUR_ADDR 0x02
#define DS3231_STATUS_ADDR 0x0F

#define DS3231_ALARM_MINUTE_ADDR 0x08
#define DS3231_ALARM_HOUR_ADDR 0x09

class ds3231 {
	public:
		unsigned char data[0x13];
		void read_data(void);
		void place_cursor(unsigned char x);
		void restart_counting(void);
    
	private:
  
	protected:
  
};

#ifdef __cplusplus
}
#endif
  
  
  
  
