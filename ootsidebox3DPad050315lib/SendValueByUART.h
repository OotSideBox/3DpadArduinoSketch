#ifndef SENDVALUEBYUART_H_
#define SENDVALUEBYUART_H_

#include "Scrutation.h"
#include "Automate.h"
#include "Arduino.h"

#define ONLY_GESTURE 0
#define VALUES 1

extern unsigned int EL[NODE];
extern unsigned int VALF[NODE];
void SendValuesConsigne(void);
void SendValues(char mode);
void SendToTeensy(void);
void noteOn(int cmd, int pitch, int velocity);

#endif /*SENDVALUEBYUART_H_*/
