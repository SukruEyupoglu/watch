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
#define RF_SETUP_250K_MBPS_18_DBM   (1 << 5)
#define RF_SETUP_250K_MBPS_12_DBM   ( (1 << 5) | (1 << 1) )
#define RF_SETUP_250K_MBPS_06_DBM   ( (1 << 5) | (1 << 2) )
#define RF_SETUP_250K_MBPS_00_DBM   ( (1 << 5) | (1 << 2) | (1 << 1) )

#define RF_SETUP_1M_MBPS_18_DBM     0x0
#define RF_SETUP_1M_MBPS_12_DBM     (1 << 1)
#define RF_SETUP_1M_MBPS_06_DBM     (1 << 2)
#define RF_SETUP_1M_MBPS_00_DBM     ( (1 << 2) | (1 << 1) )

#define RF_SETUP_2M_MBPS_18_DBM     (1 << 3)
#define RF_SETUP_2M_MBPS_12_DBM     ( (1 << 3) | (1 << 1) )
#define RF_SETUP_2M_MBPS_06_DBM     ( (1 << 3) | (1 << 2) )
#define RF_SETUP_2M_MBPS_00_DBM     ( (1 << 3) | (1 << 2) | (1 << 1) )

#define STATUS 0x07
#define STATUS_RX_DR                (1 << 6)
#define STATUS_TX_DS                (1 << 5)
#define STATUS_MAX_RT               (1 << 4)
#define STATUS_RX_P_NO              ( (1 << 3) | (1 << 2) | (1 << 1) )
#define STATUS_TX_FULL              (1 << 0)

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

// Transmit address. Used for a PTX device only.
// (LSByte is written first)
// Set RX_ADDR_P0 equal to this address to handle automatic acknowledge if this is a PTX device with
// Enhanced ShockBurstTM enabled  <<------BEWARE HERE
#define TX_ADDR 0x10

// Number of bytes in RX payload in data pipe 5 (1 to 32 bytes).0 Pipe not used
#define RX_PW_P0 0x11
#define RX_PW_P0 0x12
#define RX_PW_P0 0x13
#define RX_PW_P0 0x14
#define RX_PW_P0 0x15
#define RX_PW_P0 0x16

#define FIFO_STATUS 0x17
#define FIFO_STATUS_TX_REUSE        (1 << 6)
#define FIFO_STATUS_TX_FULL         (1 << 5)
#define FIFO_STATUS_TX_EMPTY        (1 << 4)
#define FIFO_STATUS_RX_FULL         (1 << 1)
#define FIFO_STATUS_RX_EMPTY        (1 << 0)

















