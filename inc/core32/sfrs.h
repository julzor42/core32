// GPIO
#ifdef PIC32MX2
# define SFR_GPIO_BASE      0xBF886010
# define SFR_GPIO_SIZE      0x100
#else
# define SFR_GPIO_BASE      0xBF886000
# define SFR_GPIO_SIZE      0x40
#endif

// DMA
#define  SFR_DMA_BASE       0xBF883060
#define  SFR_DMA_SIZE       0xC0

// SPI
#define  SFR_SPI_BASE       0xBF805800
#define  SFR_SPI_SIZE       0x200

// Timer
#define  SFR_TIMER_BASE     0xBF800600
#define  SFR_TIMER_SIZE     0x200

// UART
#define  SFR_UART_BASE      0xBF806000
#define  SFR_UART_SIZE      0x200

// I2C
#define  SFR_I2C_BASE       0xBF805000
#define  SFR_I2C_SIZE       0x100

// OC
#define  SFR_OC_BASE        0xBF803000
#define  SFR_OC_SIZE        0x200
