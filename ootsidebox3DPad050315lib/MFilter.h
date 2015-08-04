#ifndef Mfilter_
#define Mfilter_
#include "Parameters.h"

#define EL0 0 //constantes pour nommer le Numero de filtre
#define EL1 1
#define EL2 2
#define EL3 3
#define ORDY_X 4
#define ORDY_Y 5
#define ORDY_Z 6
#define CURS_X 7 //ok
#define CURS_Y 8
#define CURS_Z 9


struct FilterStruct
{
        int Index;      //index pour le remplissage du tableau
        int Buffer[COORD_ORDY_BUFFER_LENGHT];//capacit max du filtre
        int Lenght;     //longueur utilile du filtre
};


void Filter_init(int Value,int Lenght, int Num);
int Filter_compute(unsigned int Value,int Num);

#endif
