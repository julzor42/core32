#ifdef PIC32MX2
# define SFR_BASE_GPIO      0xBF886010
# define SFR_SIZE_GPIO      0x100
#else
# define SFR_BASE_GPIO      0xBF886000
# define SFR_SIZE_GPIO      0x40
#endif