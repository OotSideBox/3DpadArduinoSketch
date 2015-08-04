#ifndef SCRUTATION_H_
#define SCRUTATION_H_

#define EL_A 0
#define EL_B 3
#define EL_LEFT 2
#define EL_RIGHT 5
#define EL_TOP 1
#define EL_BOT 4

#define VCOMAX 16383
#define NODE 6

/*
 * Automate D'état de scrutation 
 * */
void Scrutation(void);
void Regulation(unsigned int BaseTempsRegulation, unsigned char Touch);

/*
 * Fonction de lecture des valeurs VCO en flash retourne 1 si maggic number OK sinon 0
 * */
unsigned char Lecture_Flash(void);

/*
 * Fonction de calcul de la moyenne glissante 
 * 
 * */
void Calcul_Moy_Glissante(void);


/*
 * Fonction d'écriture des valeur en Flash aprés autocal
 * */
void Write_VCO_Flash(void);


 /*Fonction d'initialisation des variables de scrutation 
 * */
 void Init_Scrutation(void);
 

#endif /*SCRUTATION_H_*/
