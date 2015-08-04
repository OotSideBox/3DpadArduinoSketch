#include "SendValueByUART.h"
#include "Scrutation.h"
#include "MGesture.h"
#include "Automate.h"
#include "MVariable.h"
#include "ifdef.h"



void SendVal(unsigned int EL)
{
			int Temp;
			Temp=VALF[EL]; 
			if(Temp<1000) Serial.print('0');
			if(Temp<100) Serial.print('0');
			if(Temp<10) Serial.print('0');
			Serial.print(Temp,DEC);	
			Serial.print("|");
}

void SendCurs(int Curs)
{
			if(Curs<1000) Serial.print('0');
			if(Curs<100) Serial.print('0');
			if(Curs<10) Serial.print('0');
			Serial.print(Curs,DEC);	
			Serial.print("|");
}

void SendCursHex(int Curs)
{
			if(Curs<0x1000) Serial.print('0');
			if(Curs<0x100) Serial.print('0');
			if(Curs<0x10) Serial.print('0');
			Serial.print(Curs,HEX);	
}

void SendValHex(unsigned int EL)
{
			int Temp;
			extern unsigned char Prox;
			if(Prox)
			{
				Temp=VALF[EL]; 
				if(Temp<0x1000) Serial.print('0');
				if(Temp<0x100) Serial.print('0');
				if(Temp<0x10) Serial.print('0');
				Serial.print(Temp,HEX);
			}
			else
			{
				Serial.print("0000");
			}
}
	
void SendToTeensy(void)
{
extern struct CoordTypeAbs Curseur;
extern unsigned char Prox;
//Serial.print("\r\n");
Serial.print(">");
Serial.print("V");
SendCursHex(Curseur.X);
SendCursHex(Curseur.Y);
SendCursHex(Curseur.Z);
if (Prox) SendCursHex(0xFF);
else SendCursHex(0);
Serial.print("<");
}

void SendValues(char mode)
{
extern unsigned char Prox;
extern int EvGesture;
extern int EvGestureOld;
extern char FlagGesture;
extern int ToursR;
extern int ToursL;	
extern struct _Automate AutomateData;
extern struct CoordTypeAbs Curseur;
extern struct CoordTypeAbs Ordy;
extern struct CoordTypeAbs CurseurMm;

if (mode==VALUES)
{
	// envoi des 4 Valeurs d'electrodes
	Serial.print("\r\n>V");
	SendVal(EL_TOP);
	SendVal(EL_BOT);
	SendVal(EL_LEFT);
	SendVal(EL_RIGHT);
	//envoi coordonnées Curseur
	SendCurs(Curseur.X);
	SendCurs(Curseur.Y);
	if (Prox) SendCurs(Curseur.Z);
	else SendCurs(300);
	//envoi coordonnées Origine Dynamique
	SendCurs(Ordy.X);
	SendCurs(Ordy.Y);
	SendCurs(Ordy.Z);
	SendCurs(ToursL);
	SendCurs(ToursR);
	
	
}

// envoi evenements Gesture	
	if ((FlagGesture) && ( (EvGestureOld!=EvGesture)|| (ToursL>0) || (ToursR>0) ) && (AutomateData.State==_RUN))
	{
		if (mode==ONLY_GESTURE) Serial.print("\r\n>G");
		else Serial.print(" >G");

		switch(EvGesture)
		{
		case VOID:	Serial.print("0: Gesture = OUT");
					digitalWrite(LED2, LOW);
					digitalWrite(LED1, HIGH);
							
		break;
		case MOVING:Serial.print("1: Gesture = IN");
					digitalWrite(LED2, HIGH);
					digitalWrite(LED1, LOW);
					
		break;
		case RIGHT: Serial.print("2: Gesture = RIGHT");
		break;
		case LEFT:	Serial.print("3: Gesture = LEFT");
		break;
		case UP:	Serial.print("4: Gesture = UP");
		break;
		case DOWN:	Serial.print("5: Gesture = DOWN");
		break;
		case ROTATE_LEFT: 
			Serial.print("6: Gesture = RL/");
			Serial.print(ToursL);
		break;
		case ROTATE_RIGHT: 
			Serial.print("7: Gesture = RR/");
			Serial.print(ToursR);
		break;
		case PUSH: Serial.print("8: Gesture = PUSH");
		break;
		}
		FlagGesture=0;
		EvGestureOld=EvGesture;
	} 

}