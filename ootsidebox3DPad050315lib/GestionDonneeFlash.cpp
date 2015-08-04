#include "GestionDonneeFlash.h"
#include <EEPROM.h>

void WriteMaggicWordFlash(void)
{
	EEPROM.write(MAGGICWORDADDR, MAGGICWORD); 
}
unsigned int MaggicWordPresentInFlash(void)
{
	unsigned char value;
	unsigned int valreturn=0;
	value= EEPROM.read(MAGGICWORDADDR);
	if(value==MAGGICWORD)
	{
		valreturn=1;
	}
	return valreturn;
}

void EraseMaggicWordFlash(void)
{
	EEPROM.write(MAGGICWORDADDR, 0);
}

void InitTableau(unsigned int Value)
{
	unsigned int i;

	for(i=0;i<NODE;i++)
	{
			EL[i]=Value;		
	}
}

void WriteTableauFlash(void)
{
	unsigned int i;
	unsigned char Hbyte, Lbyte;
	unsigned int Temp;
	unsigned int Adresse=ADRTABLEAU;

	for(i=0;i<NODE;i++)
	{
		Temp=EL[i] & 0x00FF; //le byte de poids faible
		Lbyte=(char)Temp;
		
		Temp=EL[i]>>8;  //le byte poids fort
		Temp &= 0x00FF;
		Hbyte=(char)Temp;

		EEPROM.write(Adresse, Lbyte);
		Adresse++;
		EEPROM.write(Adresse, Hbyte);
		Adresse++;
	}
	
}

void ReadTableauFlash(void)
{
	unsigned int i;
	unsigned char Hbyte, Lbyte;
	unsigned int Temp;
	unsigned int Adresse=ADRTABLEAU;

	for(i=0;i<NODE;i++)
	{
		
		Lbyte=EEPROM.read(Adresse);
		Adresse++;
		Hbyte=EEPROM.read(Adresse);
		Adresse++;

		EL[i]=0;
		Temp=(int)Hbyte;
		EL[i]= Temp<<8;
		Temp=(int)Lbyte;
		EL[i]+=Temp;
	}
}





