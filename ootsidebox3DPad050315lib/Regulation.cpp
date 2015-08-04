#include "Regulation.h"
#include "Scrutation.h"
#include "Automate.h"
#include "ifdef.h"

extern unsigned int EL[]; //tableau des consignes VCO
extern unsigned int VAL[]; //tableau des valeurs mesurees
extern unsigned int ConsigneValue;
extern struct _Automate AutomateData;
extern unsigned char IntoField;

void Regulation(unsigned int BaseTempsRegulation, unsigned char Touch) 
{ 
signed int SensRegul_1=0;
signed int SensRegul_2=0;
signed int SensRegul_4=0;
signed int SensRegul_5=0;
unsigned int Node;

	if(AutomateData.State!=_RUN)
	{
		for(Node=0; Node<NODE; Node++)
		{
			if((VAL[Node]< ConsigneValue)&& (EL[Node]>4)) EL[Node]-=2;
			if((VAL[Node]> ConsigneValue)&& (EL[Node]<VCOMAX-4)) EL[Node]+=2;
		}	
	}
	#ifdef REGUL
	if ((AutomateData.State==_RUN))
	{ 
		
		if(VAL[EL_A]< ConsigneValue) 
			 {
			 	if(EL[EL_A] > 0) EL[EL_A]--;
			 	SensRegul_1--;
			 	SensRegul_2--;
			 }
		if(VAL[0]> ConsigneValue) 
			 {
			 	if(EL[EL_A]<VCOMAX) EL[EL_A]++;
			 	SensRegul_1++;
			 	SensRegul_2++;
			 }
		if(VAL[3]< ConsigneValue) 
			 {
			 	if(EL[EL_B] > 0) EL[EL_B]--;
			 	SensRegul_4--;
			 	SensRegul_5--;
			 }
		if(VAL[3]> ConsigneValue) 
			 {
			 	if(EL[EL_B]<VCOMAX) EL[EL_B]++;
			 	SensRegul_4++;
			 	SensRegul_5++;
			 }

		if((!IntoField))
			{	
				if(VAL[EL_TOP]< ConsigneValue-30)SensRegul_1--;
				if((!BaseTempsRegulation)&&(VAL[EL_TOP]< ConsigneValue))SensRegul_1--;
				if((!BaseTempsRegulation)&&(VAL[EL_TOP]> ConsigneValue))SensRegul_1++;
				if(VAL[EL_LEFT]< ConsigneValue-30)SensRegul_2--;
				if((!BaseTempsRegulation)&&(VAL[EL_LEFT]< ConsigneValue))SensRegul_2--;
				if((!BaseTempsRegulation)&&(VAL[EL_LEFT]> ConsigneValue))SensRegul_2++;
				
				if(VAL[EL_BOT]< ConsigneValue-30)SensRegul_4--;
				if((!BaseTempsRegulation)&&(VAL[EL_BOT]< ConsigneValue))SensRegul_4--;
				if((!BaseTempsRegulation)&&(VAL[EL_BOT]> ConsigneValue))SensRegul_4++;
				if(VAL[EL_RIGHT]< ConsigneValue-30)SensRegul_5--;
				if((!BaseTempsRegulation)&&(VAL[EL_RIGHT]< ConsigneValue))SensRegul_5--;
				if((!BaseTempsRegulation)&&(VAL[EL_RIGHT]> ConsigneValue))SensRegul_5++;
			}
		
		if((SensRegul_1 < 0)&&(EL[EL_TOP] > 0)) EL[EL_TOP]--;
		if((SensRegul_1 > 0)&&(EL[EL_TOP] <VCOMAX)) EL[EL_TOP]++;
		if((SensRegul_2 < 0)&&(EL[EL_LEFT] > 0)) EL[EL_LEFT]--;
		if((SensRegul_2 > 0)&&(EL[EL_LEFT] <VCOMAX)) EL[EL_LEFT]++;
		
		if((SensRegul_4 < 0)&&(EL[EL_BOT] > 0)) EL[EL_BOT]--;
		if((SensRegul_4 > 0)&&(EL[EL_BOT] <VCOMAX)) EL[EL_BOT]++;
		if((SensRegul_5 < 0)&&(EL[EL_RIGHT] > 0)) EL[EL_RIGHT]--;
		if((SensRegul_5 > 0)&&(EL[EL_RIGHT] <VCOMAX)) EL[EL_RIGHT]++; 
	}
	#endif
}
	