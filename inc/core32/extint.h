#ifndef _EXTINT_H_
#define _EXTINT_H_

#define INT_0 0
#define INT_1 1
#define INT_2 2
#define INT_3 3
#define INT_4 4
#define INT_5 5

void                INT_SetExternalInterrupt(unsigned int Int, unsigned int Enabled, unsigned int Polarity, unsigned int Priority, unsigned int SubPriority);
void                INT_EnableExternalInterrupt(unsigned int Int, unsigned int Enabled);
void                INT_ClearExternalInterrupt(unsigned int Int);

#endif /* _EXTINT_H_ */