#include "Automate.h"
#include "ifdef.h"
#include "GestionDonneeFlash.h"
#include "Arduino.h"

void AutomateDeroulement(void)
{
	unsigned int i;
	static unsigned int TempopAffAutocal=0;

	if(AutomateData.OldState!=AutomateData.State)
	{	
		AutomateData.OldState=AutomateData.State;
		AutomateData.FlagChange=1;
	}
	else
	{
		AutomateData.FlagChange=0;
	}



	switch(AutomateData.State)
	{
		case _INIT:
			if(AutomateData.FlagChange)
			{
				InitTableau(VCOMAX);
			}
			if(MaggicWordPresentInFlash()==1)
			{
				AutomateData.State=_LOADCONSFLASH;
			}else
			{
				AutomateData.State=_AUTOCAL1;	
			}
		break;
		case _AUTOCAL1:
			if(AutomateData.FlagChange)
			{
				ConsigneValue=CONSIGNE_SETUP;
				BaseTempsRegulation=BDTAUTOCAL1;
				Serial.print("\n\r>A0: Autocalibration started ");
				
			}
			if(!BaseTempsRegulation) 
			{
				BaseTempsRegulation=BDTAUTOCAL1;
			}
			if(CheckElectInScope(ConsigneValue,DELTA))
			{
				AutomateData.State=_AUTOCAL2;
			}
		break;
		case _AUTOCAL2:
			if(AutomateData.FlagChange)
			{				
				ConsigneValue=CONSIGNE;
				BaseTempsRegulation=BDTAUTOCAL2;
				
			}
			if(!BaseTempsRegulation) 
			{
				BaseTempsRegulation=BDTAUTOCAL2;
			}
			if(CheckElectInScope(ConsigneValue,DELTA))
			{
				AutomateData.State=_SAVECONSFLASH;
			}
		break;
		case _SAVECONSFLASH:
			WriteTableauFlash();
			WriteMaggicWordFlash();
			AutomateData.State=_LOADCONSFLASH;
		break;
		case _LOADCONSFLASH:
			
			ReadTableauFlash();
			AutomateData.State=_SETUP;
		break;
		case _SETUP:
			
			if(AutomateData.FlagChange)
			{
				ConsigneValue=CONSIGNE_SETUP;
				BaseTempsRegulation=BDTSETUP;
				
			}
			if(!BaseTempsRegulation) 
			{
				BaseTempsRegulation=BDTSETUP;
			}
			if(CheckElectInScope(ConsigneValue,DELTA))
			{
				AutomateData.State=_SETUP1;
			}
		break;
		case _SETUP1:
			if(AutomateData.FlagChange)
			{
				ConsigneValue=CONSIGNE;
				BaseTempsRegulation=1;
				Serial.print("\n\r>A2: Setup started ");
				
			}
			if(!BaseTempsRegulation) 
			{
				BaseTempsRegulation=10;
			}
			if(CheckElectInScope(ConsigneValue,DELTA) )
			{
				
				Serial.print("\n\r>A3: Setup Done: RUN");
				AutomateData.State=_RUN;
			}
		break;
		case _RUN:
			if(AutomateData.FlagChange)
			{
				BaseTempsRegulation=BDTREGUL;
				ConsigneValue=CONSIGNE;
				
			}
			if(!BaseTempsRegulation) 
			{
				BaseTempsRegulation=BDTREGUL;
			}
			if(CheckSetupRQ(CONSIGNE_SETUPAUTO)) 
			{
				#ifdef REGUL
				AutomateData.State=_SETUP1;
				#endif
			}
		break;
	}
	if (AutomateData.State!=_RUN)
	{
		TempopAffAutocal++;
		if (TempopAffAutocal > 200) 
		{
			TempopAffAutocal=0;
			Serial.print(".");
		}
	}
}
unsigned int CheckSetupRQ(unsigned int Consigne)
{
	unsigned int node=0;
	unsigned int valResult=0;
	
	for(node=0; node<NODE; node++)
	{
		if(VAL[node]>= SATURATION)
		{
			valResult++;
		}
	}	
	if (valResult ==4) return valResult;
	
	valResult=0;
	for(node=0; node<NODE; node++)
	{
		if(VAL[node]<Consigne-100)
		{
			valResult=1;
		}
	}	
	return valResult;
}

unsigned int CheckElectInScope(unsigned int Consigne,unsigned int Delta)
{
	unsigned int Cons;
	unsigned int node=0;
	unsigned int valResult=0;
	Cons = Consigne;
	for(node=0; node<NODE; node++)
	{		
		if((VAL[node]<Cons+Delta)&& (VAL[node]>(Cons-Delta)) ) valResult++;
		else	valResult=0;	
	}		
	if(valResult==NODE) valResult=1;
	else valResult=0;	
	return valResult;
}


