

#define NRF_CSN_LOW nrf_csn_low()
#define NRF_CSN_HIGH nrf_csn_high()

#define NRF_CE_LOW nrf_ce_low()
#define NRF_CE_HIGH nrf_ce_high()

// commands
#define R_REGISTER                  0x00 // 000A AAAA ---> AAAAA = 5 bit Register Map Address
#define W_REGISTER                  0x20 // 001A AAAA ---> AAAAA = 5 bit Register Map Address
#define R_RX_PAYLOAD                0x61
#define W_TX_PAYLOAD                0xA0
#define FLUSH_TX                    0xE1
#define FLUSH_RX                    0xE2
#define REUSE_TX_PL                 0xE3
#define R_RX_PL_WID                 0x60
#define W_ACK_PAYLOAD               0xA8 // 1010 1PPP ----> use "OR" for appropriate PPP(PIPE) 000 to 101
#define W_TX_PAYLOAD_NO_ACK         0xB0
#define NOP                         0xFF

// registers
#define CONFIG 0x00
#define CONFIG_MASK_RX_DR           (1 << 6)
#define CONFIG_MASK_TX_DS           (1 << 5)
#define CONFIG_MASK_MAX_RT          (1 << 4)
#define CONFIG_EN_CRC               (1 << 3)
#define CONFIG_CRCO                 (1 << 2)
#define CONFIG_PWR_UP               (1 << 1)
#define CONFIG_PRIM_RX              (1 << 0)

#define EN_AA 0x01
#define EN_AA_ENAA_P5               (1 << 5)
#define EN_AA_ENAA_P4               (1 << 4)
#define EN_AA_ENAA_P3               (1 << 3)
#define EN_AA_ENAA_P2               (1 << 2)
#define EN_AA_ENAA_P1               (1 << 1)
#define EN_AA_ENAA_P0               (1 << 0)

#define EN_RXADDR 0x02
#define EN_RXADDR_ERX_P5            (1 << 5)
#define EN_RXADDR_ERX_P4            (1 << 4)
#define EN_RXADDR_ERX_P3            (1 << 3)
#define EN_RXADDR_ERX_P2            (1 << 2)
#define EN_RXADDR_ERX_P1            (1 << 1)
#define EN_RXADDR_ERX_P0            (1 << 0)

#define SETUP_AW 0x03
#define SETUP_AW_ADDR_BYTE_3        0x01
#define SETUP_AW_ADDR_BYTE_4        0x10
#define SETUP_AW_ADDR_BYTE_5        0x11

#define SETUP_RETR 0x04
#define SETUP_RETR_ARD              0xF0
#define SETUP_RETR_ARC              0x0F

#define RF_CH 0x05
#define RF_CH_RF_CH                 0x7F

#define RF_SETUP 0x06
#define RF_SETUP_CONT_WAVE          (1 << 7)
#define RF_SETUP_PLL_LOCK           (1 << 4)

// DATA RATE SELECT - SPEED SELECT - DBM SELECT -OUTPUT POWER SELECT - DISTANCE SELECT
#define RF_SETUP_250K_BPS_18_DBM   (1 << 5)
#define RF_SETUP_250K_BPS_12_DBM   ( (1 << 5) | (1 << 1) )
#define RF_SETUP_250K_BPS_06_DBM   ( (1 << 5) | (1 << 2) )
#define RF_SETUP_250K_BPS_00_DBM   ( (1 << 5) | (1 << 2) | (1 << 1) )

#define RF_SETUP_1M_BPS_18_DBM     0x0
#define RF_SETUP_1M_BPS_12_DBM     (1 << 1)
#define RF_SETUP_1M_BPS_06_DBM     (1 << 2)
#define RF_SETUP_1M_BPS_00_DBM     ( (1 << 2) | (1 << 1) )

#define RF_SETUP_2M_BPS_18_DBM     (1 << 3)
#define RF_SETUP_2M_BPS_12_DBM     ( (1 << 3) | (1 << 1) )
#define RF_SETUP_2M_BPS_06_DBM     ( (1 << 3) | (1 << 2) )
#define RF_SETUP_2M_BPS_00_DBM     ( (1 << 3) | (1 << 2) | (1 << 1) )

#define STATUS_REG 0x07
#define STATUS_RX_DR                (1 << 6)
#define STATUS_TX_DS                (1 << 5)
#define STATUS_MAX_RT               (1 << 4)
#define STATUS_RX_P_NO              ( (1 << 3) | (1 << 2) | (1 << 1) )
#define STATUS_TX_FULL              (1 << 0)

#define VOID_INT                    0
#define RX_DR_INT                   1
#define TX_DS_INT                   2
#define MAX_RT_INT                  3



#define OBSERVE_TX 0x08
#define OBSERVE_TX_PLOS_CNT         0xF0
#define OBSERVE_TX_ARC_CNT          0x0F

#define RPD 0x09
#define RPD_RPD                     (1 << 0)

// Receive address data pipe 0. 5 Bytes maximum length. 
// (LSByte is written first. 
// Write the number of bytes defined by SETUP_AW)
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C // Only LSB. MSBytes are equal to RX_ADDR_P1[39:8]
#define RX_ADDR_P3 0x0D // Only LSB. MSBytes are equal to RX_ADDR_P1[39:8]
#define RX_ADDR_P4 0x0E // Only LSB. MSBytes are equal to RX_ADDR_P1[39:8]
#define RX_ADDR_P5 0x0F // Only LSB. MSBytes are equal to RX_ADDR_P1[39:8]

#define MAX_ADDR_SIZE			5
#define P0				0
#define P1				1
#define P2				2
#define P3				3
#define P4				4
#define P5				5

#define PIPE_0    0
#define PIPE_1    1
#define PIPE_2    2
#define PIPE_3    3
#define PIPE_4    4
#define PIPE_5    5

#define RX_ADDR_PX 0x0A

// Transmit address. Used for a PTX device only.
// (LSByte is written first)
// Set RX_ADDR_P0 equal to this address to handle automatic acknowledge if this is a PTX device with
// Enhanced ShockBurstTM enabled  <<------BEWARE HERE
#define TX_ADDR 0x10

// Number of bytes in RX payload in data pipe 5 (1 to 32 bytes).0 Pipe not used
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16

#define RX_PW_PX 0x11

#define FIFO_STATUS 0x17
#define FIFO_STATUS_TX_REUSE        (1 << 6)
#define FIFO_STATUS_TX_FULL         (1 << 5)
#define FIFO_STATUS_TX_EMPTY        (1 << 4)
#define FIFO_STATUS_RX_FULL         (1 << 1)
#define FIFO_STATUS_RX_EMPTY        (1 << 0)

// Enable dynamic payload length data pipe X.
// (Requires EN_DPL and ENAA_PX )
#define DYNPD 0x1C
#define DYNPD_DPL_P5                (1 << 5)
#define DYNPD_DPL_P4                (1 << 4)
#define DYNPD_DPL_P3                (1 << 3)
#define DYNPD_DPL_P2                (1 << 2)
#define DYNPD_DPL_P1                (1 << 1)
#define DYNPD_DPL_P0                (1 << 0)

#define FEATURE 0x1D
#define FEATURE_EN_DPL              (1 << 2) // Enables Dynamic Payload Length
#define FEATURE_EN_ACK_PAY          (1 << 1) // Enables Payload with ACK
#define FEATURE_EN_DYN_ACK          (1 << 0) // Enables the W_TX_PAYLOAD_NOACK command



void nrf24l01_init(void);
void nrf24l01_init_from_eeprom(void);
void make_tx(void);
void make_rx(void);
void set_rx_addr_p_0_1(unsigned char x_0_1,unsigned char addr[5]);
void set_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5,unsigned char addr);
void set_tx_addr(unsigned char addr[5]);
void set_rx_pw_px(unsigned char pipe,unsigned char x_1_32); // x_1_32 = Number of bytes in RX payload in data pipe

void get_rx_addr_p_0_1(unsigned char x_0_1,unsigned char * addr); // 5 byte total
unsigned char get_rx_addr_p_2_3_4_5(unsigned char x_2_3_4_5);
void get_tx_addr(unsigned char * addr);

void nrf_write_buf(unsigned char * data,unsigned char size);
void nrf_read_buf(unsigned char * data,unsigned char size);
void nrf_write_reg(unsigned char reg,unsigned char data);
unsigned char nrf_read_reg(unsigned char reg);
void nrf_flush_tx(void);
void nrf_flush_rx(void);

void nrf_csn_low(void);
void nrf_csn_high(void);
void nrf_send(unsigned char * data , unsigned char size);
void nrf_get(unsigned char * data , unsigned char size);
unsigned char check_irq_status(void);
void second_nrf24l01_init(void);
void wait_for_second_nrf(void);





