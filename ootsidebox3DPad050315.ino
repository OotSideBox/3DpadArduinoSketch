
//*********************************************************************************/
//
// Elektor Labs - OOTSIDEBOX project
//
// Touchless - Gesture 3D-pad 
//
// JN Lefebvre 5 Mars 2015
// https://twitter.com/Ootsidebox
// https://www.facebook.com/3D.Pad
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
//*********************************************************************************/

#include <SPI.h>
#include <EEPROM.h>
//**************************** lib d'acquisition
#include <Automate.h>
#include <SendValueByUART.h>
#include <ifdef.h>
#include <Primitive8par8.h>
#include <GestionDonneeFlash.h>
#include <Regulation.h>
//**************************** lib coordonnÃ©es 3D / gesture
#include <MFilter.h>
#include <MVariable.h>
#include <MMagneticGrid.h>
#include <MCalculcoordonnees.h>
#include <MGestureTranslate.h>
#include <MTransMMtoAff.h>
#include <MGesture.h>
#include <MLinearisation.h>
#include <MGestureRotate.h>
#include <MGestureGlobale.h>
#include <Parameters.h>
#include <MAGesture.h>

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
//

struct _Automate AutomateData;

void Run(void);
void SetupFct(void);
unsigned int EL[NODE]; //tableau des consignes VCO
unsigned int VAL[NODE]; //tableau des valeurs resultantes
unsigned int FILTER[NODE][FILTERLENGHT];
unsigned int VALF[NODE];
unsigned int Tab_Elec_Value[4]; //valeurs pour le calcul coordonnÃ©es et gesture
struct CoordTypeAbs Curseur;
struct CoordTypeAbs Ordy;
struct CoordTypeAbs CurseurMm;
struct CoordTypeDyn CurseurDyn;
FilterStruct Filter[10];
unsigned int Node;
unsigned int ConsigneValue=CONSIGNE;

unsigned int BaseTempsRegulation=BDTREGUL;
unsigned char Prox=0;
unsigned char OldProx;
unsigned char IntoField=0;
char Flaginit=0; 
char ModeComSerie=ONLY_GESTURE;

void Run(void);
void Filters(void);
void Regulation(unsigned int BaseTempsRegulation, unsigned char Touch);


void setup() /***********************************************************************/
{                
    pinMode(CPF_OUT, INPUT);   
    pinMode(SCPF_CLEAR, OUTPUT);
    pinMode(VCO_INH, OUTPUT);
    pinMode(SYNC_SCOPE, INPUT);
    pinMode(ENOSC_SENSE, OUTPUT);
    pinMode(EN_BOT, OUTPUT); 
    pinMode(EN_RIGHT, OUTPUT);
    pinMode(EN_REFB, OUTPUT);
    pinMode(EN_TOP, OUTPUT);
    pinMode(EN_LEFT, OUTPUT);
    pinMode(EN_REFA, OUTPUT);
    pinMode(DAC_CS, OUTPUT);
    pinMode(SPI_DATA, OUTPUT);
    pinMode(VCO_INH, OUTPUT);
    pinMode(SPI_CLK, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    
    digitalWrite(SCPF_CLEAR, HIGH);
    digitalWrite(ENOSC_SENSE, HIGH);
    digitalWrite(EN_BOT, LOW);
    digitalWrite(EN_RIGHT, LOW);
    digitalWrite(EN_REFB, LOW);
    digitalWrite(EN_TOP, LOW);
    digitalWrite(EN_LEFT, LOW);
    digitalWrite(EN_REFA, LOW);
    digitalWrite(DAC_CS, HIGH);
    digitalWrite(VCO_INH, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    
    //configuration SPI pour le DAC
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE1);  
    SPI.setClockDivider(SPI_CLOCK_DIV2); 
    SPI.begin();
    
    Serial.begin(115200);
    analogReference(DEFAULT);
    // faster ADC
    // uses div factor of 8.  standard arduino read is 128.
    sbi(ADCSRA,ADPS2) ;
    cbi(ADCSRA,ADPS1) ;
    sbi(ADCSRA,ADPS0) ;
    	
    InitTableau(VCOMAX);
     
    Serial.print("\n\r OOTSIDEBOX / Elektor 3D-Pad by @junowhynot");
    Serial.println();
    Serial.print("\n\r commandes: A= Autocalibration, S= Setup");
    Serial.print("\n\r commandes: G= Ev. Gesture,     V= Values");	
    Serial.print("\n\r");
    AutomateData.OldState=255;
    AutomateData.State=_INIT;/*Positionement de l'automate*/  
    
}


void loop() /***********************************************************************/
{  
  char incomingByte = 0;   // for incoming serial data
  Run(); //********************************************
  if (Serial.available() > 0)
  {
    incomingByte = (char)Serial.read();
    switch(incomingByte)
	{
	  case 'A':
	  case 'a':
		    EraseMaggicWordFlash();
		    AutomateData.State=_INIT;
	  break;
	  case 'S':
	  case 's':
		    AutomateData.State=_SETUP1;
	  break;
          case 'V':
          case 'v':
                    ModeComSerie=VALUES;
          break;
          case 'G':
          case 'g':
                    ModeComSerie=ONLY_GESTURE;
          break;
	}
  }
  AutomateDeroulement(); //automate d'acquisition
  Filters();
  //Passage des valeurs a l'automate de coordonnÃ©es/gesture                   
  Tab_Elec_Value[0]=VALF[EL_TOP];
  Tab_Elec_Value[1]=VALF[EL_RIGHT];
  Tab_Elec_Value[2]=VALF[EL_BOT];
  Tab_Elec_Value[3]=VALF[EL_LEFT];
  
  AutomateGesture(0,0); //automate coordonnÃ©es 3D/gesture
  
  // envoi des donnees sur le port USC (virtual COM port)
  SendValues(ModeComSerie);
}


void Run(void) /***********************************************************************/
{
  int temp;
  int BoucleScrut;
  delayMicroseconds(50);
  SPIsendForDac(0);

  for(BoucleScrut=0; BoucleScrut<NODE;BoucleScrut++)   //boucle de scrutation
	{
	  switch(BoucleScrut)
		{
			case 0: Node=EL_A; 
				break;
			case 1: Node=EL_B;
				break;
			case 2: Node=EL_LEFT;
				break;
			case 3: Node=EL_RIGHT;
				break;
			case 4: Node=EL_TOP;
				break;
			case 5: Node=EL_BOT;
				break;	
		}
	  Scrutation();	//*************************************************
	}	
	SPIsendForDac(VCOMAX);
	delayMicroseconds(30);
	if(IntoField) SPIsendForDac(VCOMAX); //signal indiquant arrete regulation
	else SPIsendForDac(VCOMAX/2);
	
	/*Calcul de la condition IntoField*/
	IntoField=0;
	for(Node=0; Node<NODE; Node++)
	{
		temp = (VAL[Node]-CONSIGNE);
		if(temp >  SEUIL_FIELD ) 
		{IntoField++;}
	}		
	OldProx=Prox;
	Prox=0;
	for(Node=0; Node<NODE; Node++)
	{
	  temp = (VALF[Node]-CONSIGNE);
	  if(temp >  SEUIL_PROX ) 
	  {Prox++;}		
	}
        //boucle de rÃ©gulation
	if(BaseTempsRegulation) BaseTempsRegulation--;
	Regulation(BaseTempsRegulation, Prox);
}




