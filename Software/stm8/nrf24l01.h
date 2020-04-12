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
// underconstruction

