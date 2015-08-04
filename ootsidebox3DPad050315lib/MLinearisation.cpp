#include "MLinearisation.h"


//D = (900 - M) * 0.32

int Linearise(unsigned int M) //renverra la valeur de l'Ecart Mesure-Consigne linarise
{
	if(M >1000) M=1000;
	return((unsigned int)((1000-M)*0.33));
	
}
