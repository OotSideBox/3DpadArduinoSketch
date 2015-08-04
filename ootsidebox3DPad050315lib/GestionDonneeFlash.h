#ifndef GESTIONDONNEEFLASH_H_
#define GESTIONDONNEEFLASH_H_

#include "Scrutation.h"


#define MAGGICWORD 0x55
#define MAGGICWORDADDR 0x00

#define ADRTABLEAU 0x01

extern unsigned int EL[NODE];
/*
 * Fonction qui ecrit le mot magique en flash
 */
void WriteMaggicWordFlash(void);
/*
 * Fonction Qui lit l'adresse du mot maggic en flash et retourne 1 si il est présent ou 0 si absent
 */
unsigned int MaggicWordPresentInFlash(void);


void EraseMaggicWordFlash(void);


/*
 * Initialise le tableau avec valeur croissante pour test
 */
void InitTableau(unsigned int Value);
/*
 * Ecriture du tableau en flash
 */
void WriteTableauFlash(void);
/*
 * Lecture de la flash pour remplir le tableau
 */
void ReadTableauFlash(void);

#endif /*GESTIONDONNEEFLASH_H_*/
