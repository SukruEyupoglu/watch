/*
#define WRITE_ENABLE_COMMAND 0x06
#define WRITE_DISABLE_COMMAND 0x04
#define CHIP_ERASE_COMMAND 0xC7
#define READ_ID_COMMAND 0x9F
#define READ_STATUS_COMMAND 0x05
#define PAGE_WRITE_COMMAND 0x02
#define READ_DATA_COMMAND 0x03
#define ERASE_4KB_SECTOR_COMMAND 0xD8
#define ERASE_64KB_SUBSECTOR_COMMAND 0x20
#define DUMMY_BYTE 0xFF
#define STATUS_BUSY          (1 << 0)
#define STATUS_WEL           (1 << 1)
#define STATUS_BP0           (1 << 2)
#define STATUS_BP1           (1 << 3)
#define STATUS_BP2           (1 << 4)
#define STATUS_TB            (1 << 5)
#define STATUS_SWDW          (1 << 7)

#define BUSY 0x2
#define OK 0x0
#define ERROR 0x1

#define SUBSECTOR_SIZE       (4*1024)
#define SECTOR_SIZE          (64*1024)
#define PAGE_PROGRAM_SIZE    256

*/

int erase_all_external_spi_flash(void);
int read_spi_flash(unsigned int address,unsigned char * buffer,unsigned int size);
int write_spi_flash(unsigned int address,unsigned char * buffer,unsigned int size);
int check_error_or_busy(void);



/*
ptr++;    // Pointer moves to the next int position (as if it was an array)
++ptr;    // Pointer moves to the next int position (as if it was an array)
++*ptr;   // The value of ptr is incremented
++(*ptr); // The value of ptr is incremented
++*(ptr); // The value of ptr is incremented
*ptr++;   // Pointer moves to the next int position (as if it was an array). But returns the old content
(*ptr)++; // The value of ptr is incremented
*(ptr)++; // Pointer moves to the next int position (as if it was an array). But returns the old content
*++ptr;   // Pointer moves to the next int position, and then get's accessed, with your code, segfault
*(++ptr); // Pointer moves to the next int position, and then get's accessed, with your code, segfault
p++;    // use it then move to next int position
++p;    // move to next int and then use it
++*p;   // increments the value by 1 then use it 
++(*p); // increments the value by 1 then use it
++*(p); // increments the value by 1 then use it
*p++;   // use the value of p then moves to next position
(*p)++; // use the value of p then increment the value
*(p)++; // use the value of p then moves to next position
*++p;   // moves to the next int location then use that value
*(++p); // moves to next location then use that value
*/



