#ifndef IFDEF_H_
#define IFDEF_H_


#define REGUL //valide le calcul de régulation

#define CONSIGNE 155		//155 => 756mV consigne valeur repos electrodes
#define TIME_SCRUT_EL_A 300 //durées scrutation electrodes
#define TIME_SCRUT_EL_B 300
#define TIME_SCRUT_EL_TOP 220 //330
#define TIME_SCRUT_EL_BOT 220 //300
#define TIME_SCRUT_EL_LEFT 220 //300
#define TIME_SCRUT_EL_RIGHT 220 //300
#define SEUIL_PROX 70 //90		//seuil envoi des valeurs electrodes
#define SEUIL_FIELD 75 //90	//seuil blocage regul
#define FILTERLENGHT 6 //8		//taille des filtres a moyenne glissante
#define BDTREGUL 10			//base de temps régulation
#define CONSIGNE_SETUP CONSIGNE+100 
#define CONSIGNE_SETUPAUTO CONSIGNE-50
#define SATURATION 1100 //990 //valeur déclenchement setup automatique


//********************** DEFINITION DES IOs************************
#define CPF_OUT A0    // entrée analogique sortie du CPF
#define SCPF_CLEAR A1 // sortie clear du CPF
#define VCO_INH A2    // sortie inhibition VCO
#define LED1 A3
#define LED2 A4

#define SYNC_SCOPE 2  // entrée comptage impulsions prescaler
#define ENOSC_SENSE 3 // sortie Enable arrive impulsions prescaler
#define EN_BOT 4      // sortie enable electrodes Bottom 
#define EN_RIGHT 5    // sortie enable electrodes Right
#define EN_REFB 6     // sortie enable electrodes ReferenceB
#define EN_TOP 7      // sortie enable electrodes Top
#define EN_LEFT 8     // sortie enable electrodes Left
#define EN_REFA 9     // sortie enable electrodes ReferenceA
#define DAC_CS 10     // sortie chip select du DAC SPI
#define SPI_DATA 11   // sortie données SPI
#define SPI_CLK 13    // sortie horloge SPI


#endif /*IFDEF_H_*/
