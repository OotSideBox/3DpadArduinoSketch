#include "MFilter.h"
#include "Arduino.h"

extern FilterStruct Filter[10]; 

void Filter_init(int Value,int Lenght, int Num)
{
    int i;
    Filter[Num].Index=0;    //initialise l'index de remplissage  0
    Filter[Num].Lenght=Lenght;
    for(i=0;i<Lenght;i++)
    {
        Filter[Num].Buffer[i]=Value;
    } 
}

int Filter_compute(unsigned int Value,int Num)
{
    //Value est la nouvelle valeur  intgrer dans le filtre
    //Num est le N d'instance du fitre concern
    //la fonction renverra la valeur de moyenne glissante

        long Accu=0;
        int Index;
        int i;
		
        Index = Filter[Num].Index;  //remplit la case indexe

        Filter[Num].Buffer[Index] = Value;
		
        Index ++; //gere l'index
        if(Index >= Filter[Num].Lenght)
            Index = 0;
        Filter[Num].Index = Index;


        for(i=0;i<Filter[Num].Lenght;i++)//somme de toutes les cases du filtre
        {
            Accu += (long)Filter[Num].Buffer[i];
        }
        Accu = (Accu / (long)Filter[Num].Lenght); 
        return((int)Accu);
}
