#ifndef AUTOMATE_H_
#define AUTOMATE_H_

#include <Scrutation.h>

#define _INIT 0
#define _AUTOCAL1 1
#define _AUTOCAL2 2 
#define _SAVECONSFLASH 3
#define _LOADCONSFLASH 4
#define _SETUP 5
#define _SETUP1 7
#define _RUN 6
#define BDTAUTOCAL1 1
#define BDTAUTOCAL2 1
#define BDTSETUP 1
#define DELTA 50


struct _Automate
{
	unsigned int State;		
	unsigned int OldState;
	unsigned int FlagChange : 1;
};


extern struct _Automate AutomateData;
extern unsigned int ConsigneValue;
extern unsigned int VAL[NODE];
extern unsigned int BaseTempsRegulation;
extern struct _Drapeaux Drapeaux;

void AutomateDeroulement(void);
unsigned int CheckElectInScope(unsigned int Consigne,unsigned int Delta);
unsigned int CheckSetupRQ(unsigned int Consigne);

#endif /*AUTOMATE_H_*/
