#ifndef _TCS3471_H_
#define _TCS3471_H_

#define TCS3471_ADDRESS_1   0x29
#define TCS3471_ADDRESS_2   0x39

#define TCS3471_ENABLE_REG  0x00
#define TCS3471_ATIME_REG   0x01
#define TCS3471_WTIME_REG   0x03
#define TCS3471_AILTL_REG   0x04
#define TCS3471_AILTH_REG   0x05
#define TCS3471_AIHTL_REG   0x06
#define TCS3471_AIHTH_REG   0x07
#define TCS3471_PERS_REG    0x0c
#define TCS3471_CONFIG_REG  0x0d
#define TCS3471_CONTROL_REG 0x0f
#define TCS3471_ID_REG      0x12
#define TCS3471_STATUS_REG  0x13
#define TCS3471_CDATA_REG   0x14
#define TCS3471_CDATAH_REG  0x15
#define TCS3471_RDATA_REG   0x16
#define TCS3471_RDATAH_REG  0x17
#define TCS3471_GDATA_REG   0x18
#define TCS3471_GDATAH_REG  0x19
#define TCS3471_BDATA_REG   0x1a
#define TCS3471_BDATAH_REG  0x1b

typedef union
{
  struct {

  };
  struct {
    unsigned char buffer[6];
  };
} __TCS3471_BUFFER;

void TCS3471_Initialize (unsigned int Port, unsigned int Freq);
void TCS3471_Read       (unsigned int Port, unsigned char* pOutput);

#endif /* _TCS3471_H_ */
