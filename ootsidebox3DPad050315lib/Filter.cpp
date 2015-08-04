#include "Filter.h"
#include "Scrutation.h"
#include "Automate.h"
#include "Arduino.h"
#include "ifdef.h"

extern unsigned int FILTER[NODE][FILTERLENGHT];
extern unsigned int VALF[NODE];

void Filters(void) 
{
	static unsigned int Index =0;
	unsigned int node;
	unsigned int Cpt;
	unsigned long Accu;
	static unsigned int VALFILTER[NODE];
	
	for(node=0; node<NODE; node++) 
	{
		FILTER[node][Index]= VAL[node];
		Accu=0;
		for (Cpt=0; Cpt<FILTERLENGHT; Cpt++)
		{
				Accu += FILTER[node][Cpt];
		}
		VALFILTER[node]=(unsigned int)(Accu/FILTERLENGHT);
		 
		VALF[node]=VALFILTER[node];
	}
	Index++;
	if(Index == FILTERLENGHT) Index=0;
}