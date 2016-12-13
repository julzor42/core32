#ifndef _CN_H_
#define _CN_H_

#define CN_SetPins(Pins)	    CNEN = (Pins)
#define CN_SetPullUps(Pins)	    CNPUE = (Pins)
#define CN_Enable(e)		    CNCONbits.ON = (e)
#define CN_EnableInterrupt(e)	IEC1bits.CNIE = (e)
#define CN_ClearInterrupt()	    IFS1bits.CNIF = 0
#define CN_SetPriority(p)	    IPC6bits.CNIP = (p)
#define CN_SetSubPriority(p)	IPC6bits.CNIS = (p)

void CN_SetInterrupt(unsigned int Enabled, unsigned int Priority, unsigned int SubPriority);

#endif /* _CN_H_ */
