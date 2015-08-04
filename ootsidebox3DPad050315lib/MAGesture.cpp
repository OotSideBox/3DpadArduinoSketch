
#include "math.h"
#include "MVariable.h"
#include "MFilter.h"
#include "MLinearisation.h"
#include "MCalculcoordonnees.h"
#include "MTransMMtoAff.h"
#include "MGesture.h"
#include "MGestureGlobale.h"
#include "MGestureTranslate.h"
#include "MLinearisation.h"
#include "MMagneticGrid.h"
#include "MAGesture.h"
#include "Parameters.h"

#include <Arduino.h>

extern FilterStruct Filter[10];
extern int GestState; 
extern int TranslateState ; 
extern int PushPullState; 

extern unsigned int Tab_Elec_Value[4];

bool Inside = false; //flag indiquent que l'on est dans le champ de perception
bool MoveXY = false; //flag indiquant mouvement en X ou Y
int OrdyX, OrdyY, OrdyZ;

extern struct CoordTypeAbs Curseur;
extern struct CoordTypeAbs Ordy;
extern struct CoordTypeAbs CurseurMm;
extern struct CoordTypeDyn CurseurDyn;

int Max_X;
int Max_Y;
int Min_X;
int Min_Y;

int CptInside =0; //compteur de gestion inside

int EvGesture =0;
int EvGestureOld=0;
char FlagGesture=0;
extern int ToursR;
extern int ToursL;

extern unsigned char Prox;

//Ordonanceur des operations
void AutomateGesture(int offsetX,int offsetY)
{ 
	
    extern char Flaginit; //flag de declenchement des initialisations

    int Tab_Value_Result[4]; //on y range les valeurs filtrees et linearisees
    int Zx =0;
    int Zy =0;
    int ValueFiltre=0;
    int CorrectionX;

	
	//insérer ici un appel des initialisation, conditionné par Flaginit qui passe à 1 ensuite (chargé à zero)
	if(!Flaginit)
	{
        ButMMtoAff();
        Filter_init(0, VAL_EL_BUFFER_LENGHT, EL0);
        Filter_init(0, VAL_EL_BUFFER_LENGHT, EL1);
        Filter_init(0, VAL_EL_BUFFER_LENGHT, EL2);
        Filter_init(0, VAL_EL_BUFFER_LENGHT, EL3);
        Filter_init(0, COORD_ORDY_BUFFER_LENGHT, ORDY_X);
        Filter_init(0, COORD_ORDY_BUFFER_LENGHT, ORDY_Y);
        Filter_init(0, COORD_ORDY_BUFFER_LENGHT, ORDY_Z);
		Filter_init(0, COORD_CURS_BUFFER_LENGHT, CURS_X); 
		Filter_init(0, COORD_CURS_BUFFER_LENGHT, CURS_Y);
		Filter_init(0, COORD_CURS_BUFFER_LENGHT, CURS_Z);
		GestState = VOID; 
		TranslateState = INIT; 
		PushPullState = INIT; 

		Flaginit=0xFF; 
	}
		
    //gestion Inside **********************************************************
   
	if(!Prox)
    {
        CptInside = 0;
    }
    else
    {
        if (CptInside < CPTINSIDEMAX)
        {
                    CptInside ++;
                    Filter_init(Tab_Elec_Value[EL0], VAL_EL_BUFFER_LENGHT, EL0);
                    Filter_init(Tab_Elec_Value[EL1], VAL_EL_BUFFER_LENGHT, EL1);
                    Filter_init(Tab_Elec_Value[EL2], VAL_EL_BUFFER_LENGHT, EL2);
                    Filter_init(Tab_Elec_Value[EL3], VAL_EL_BUFFER_LENGHT, EL3);
         }
    }
    if (CptInside == CPTINSIDEMAX)  Inside = true;
    else  Inside = false;

	
    //filtrage + linearisation **************************************************
    ValueFiltre = Filter_compute(Tab_Elec_Value[EL0], EL0);
    Tab_Value_Result[EL0] = Linearise(ValueFiltre);
    ValueFiltre = Filter_compute(Tab_Elec_Value[EL1], EL1);
    Tab_Value_Result[EL1] = Linearise(ValueFiltre);
    ValueFiltre = Filter_compute(Tab_Elec_Value[EL2], EL2);
    Tab_Value_Result[EL2] = Linearise(ValueFiltre);
    ValueFiltre = Filter_compute(Tab_Elec_Value[EL3], EL3);
    Tab_Value_Result[EL3] = Linearise(ValueFiltre);


    //calcul coordonnes X Y Z en mm *********************************************

	//coordonnees en X
    CoordXYcompute(Tab_Value_Result[EL3], Tab_Value_Result[EL1], L_AXE_X, &CurseurMm.X, &Zx);

	//coordonnees en Y
    CoordXYcompute(Tab_Value_Result[EL2], Tab_Value_Result[EL0], L_AXE_Y, &CurseurMm.Y, &Zy);

	//application butees
    if (CurseurMm.X > BUTMAX_X)	{ CurseurMm.X = BUTMAX_X;}
    if (CurseurMm.X < BUTMIN_X) { CurseurMm.X = BUTMIN_X;}
    if (CurseurMm.Y > BUTMAX_Y) { CurseurMm.Y = BUTMAX_Y;}
    if (CurseurMm.Y < BUTMIN_Y) { CurseurMm.Y = BUTMIN_Y;}
    CurseurMm.Z = CoordZcompute(Zx, Zy);

    //projection sur grille magnetique ********************************************
    MagnetGrid(&CurseurMm);

	//application d'un nouveau filtre pour lisser le deplacement hors grille
    CurseurMm.X = Filter_compute(CurseurMm.X, CURS_X); //ok
    CurseurMm.Y = Filter_compute(CurseurMm.Y, CURS_Y);
    CurseurMm.Z = Filter_compute(CurseurMm.Z, CURS_Z);


	if (CptInside < CPTINSIDEMAX) //ok
	{
       Filter_init(CurseurMm.X, COORD_CURS_BUFFER_LENGHT, CURS_X);
       Filter_init(CurseurMm.Y, COORD_CURS_BUFFER_LENGHT, CURS_Y);
       Filter_init(CurseurMm.Z, COORD_CURS_BUFFER_LENGHT, CURS_Z);
	}
	
    if((CptInside < CPTINSIDEMAX) || (CurseurMm.Z > SEUILZPERCEPT))//ok
    {
        Filter_init(CurseurMm.X, COORD_ORDY_BUFFER_LENGHT, ORDY_X);
        Filter_init(CurseurMm.Y, COORD_ORDY_BUFFER_LENGHT, ORDY_Y);
        Filter_init(CurseurMm.Z, COORD_ORDY_BUFFER_LENGHT, ORDY_Z);
    }

    //filtrage pour les coordonnes de ORDY ****************************************
    OrdyX = Filter_compute(CurseurMm.X, ORDY_X);
    OrdyY = Filter_compute(CurseurMm.Y, ORDY_Y);
    OrdyZ = Filter_compute(CurseurMm.Z, ORDY_Z);

    //calcul coordonnes dynamiques (cureur par rapport  ORDY) *********************
    CurseurDyn.X = ((float)(CurseurMm.X - OrdyX) / L_AXE_X);
    if (CurseurDyn.X > 1)  CurseurDyn.X = 1;
    if (CurseurDyn.X < -1) CurseurDyn.X = -1;

    CurseurDyn.Y = ((float)(CurseurMm.Y - OrdyY) / L_AXE_Y);
    if (CurseurDyn.Y > 1)  CurseurDyn.Y = 1;
    if (CurseurDyn.Y < -1) CurseurDyn.Y = -1;

    CurseurDyn.Z = ((float)(CurseurMm.Z - OrdyZ) / L_AXE_Z_MAX);
    if (CurseurDyn.Z > 1)  CurseurDyn.Z = 1;
    if (CurseurDyn.Z < -1) CurseurDyn.Z = -1;

     //calcul flag mouvement en X ou Y *********************************************
    if ((fabs ((float)CurseurDyn.X) > SEUILMOUVXYZ) || (fabs((float)CurseurDyn.Y) > SEUILMOUVXYZ)) MoveXY = true;
    else  MoveXY = false;

    //calcul positions curseurs en pourcentage ****************************************
    MMtoAff();

    // reconnaissance gestuelle
    EvGesture = GestureCompute(); 


}

