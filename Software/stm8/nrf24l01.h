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










