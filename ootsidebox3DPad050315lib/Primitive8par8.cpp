#include "Arduino.h"
#include "ifdef.h"
#include "Primitive8par8.h"
#include <SPI.h>
#include "Scrutation.h"

void SPIsendForDac(unsigned int Data  )
	{
                unsigned char Val;             
		digitalWrite(DAC_CS, LOW);      
                Val=(char)(Data>>8);
		SPI.transfer(Val); 
                Val=(char)(Data & 0x00FF);  
                SPI.transfer(Val);
		digitalWrite(DAC_CS, HIGH); 
	}


void SelectE(int NumElec)
{
	digitalWrite(EN_REFA, LOW);
	digitalWrite(EN_REFB, LOW);
	digitalWrite(EN_LEFT, LOW);
	digitalWrite(EN_RIGHT, LOW);
    digitalWrite(EN_TOP, LOW);
	digitalWrite(EN_BOT, LOW);
    
	switch(NumElec)
	{
		case EL_A:
					digitalWrite(EN_REFA, HIGH);
			break;
		case EL_B: 
					digitalWrite(EN_REFB, HIGH);
			break;
		case EL_LEFT: 
					digitalWrite(EN_LEFT, HIGH);
			break;
		case EL_RIGHT:
					digitalWrite(EN_RIGHT, HIGH);
			break;
		case EL_TOP: 
					digitalWrite(EN_TOP, HIGH);
			break;
		case EL_BOT: 
					digitalWrite(EN_BOT, HIGH);
			break;
		case -1:

			break;
	}
}
