#ifndef _NUNCHUCK_H_
#define _NUNCHUCK_H_

void Nunchuk_Initialize (unsigned int Port, unsigned int Freq);
void Nunchuk_Read       (unsigned int Port, unsigned char* pOutput);

typedef union
{
  struct {
    unsigned JoystickX:8;
    unsigned JoystickY:8;
    unsigned AccelX:8;
    unsigned AccelY:8;
    unsigned AccelZ:8;
    unsigned ButtonZ:1;
    unsigned ButtonC:1;
    unsigned AccelXExt:2;
    unsigned AccelYExt:2;
    unsigned AccelZExt:2;
  };
  struct {
    unsigned char buffer[6];
  };
} __NUNCHUK_BUFFER;

#endif /* _NUNCHUCK_H_ */
