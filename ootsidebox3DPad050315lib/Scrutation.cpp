#include "Scrutation.h"
#include "Arduino.h"
#include "Primitive8par8.h"
#include "ifdef.h"

extern unsigned int EL[NODE]; //tableau des consignes VCO
extern unsigned int VAL[NODE]; //tableau des valeurs resultantes
extern unsigned int Node;
extern unsigned char Prox;

void Scrutation(void)
{	
	unsigned int CountScrut;
	delayMicroseconds(40);
	
	switch (Node) 
	{
		case EL_A:		
						CountScrut =TIME_SCRUT_EL_A;
			break;
		case EL_B:  	
						CountScrut =TIME_SCRUT_EL_B;
			break;
		case EL_LEFT: 	
						CountScrut =TIME_SCRUT_EL_LEFT; 
			break;
		case EL_RIGHT:	
						CountScrut =TIME_SCRUT_EL_RIGHT; 
			break;
		case EL_TOP: 	
						CountScrut =TIME_SCRUT_EL_TOP; 
			break;
		case EL_BOT: 	
						CountScrut =TIME_SCRUT_EL_BOT; 
			break;
	}
	
	noInterrupts();
	SPIsendForDac(EL[Node]);
	digitalWrite(SCPF_CLEAR, LOW);
	
	
	digitalWrite(ENOSC_SENSE, LOW);
	SelectE(Node); 
	
    digitalWrite(VCO_INH, LOW);
	
    interrupts();
	
	delayMicroseconds(CountScrut);
	VAL[Node]=analogRead(CPF_OUT); //valeur lue a SCRUTTIME + 40uS
	digitalWrite(SCPF_CLEAR, HIGH);
	digitalWrite(ENOSC_SENSE, HIGH);
	SelectE(-1);
	digitalWrite(VCO_INH, HIGH);
	delayMicroseconds(20);
}






