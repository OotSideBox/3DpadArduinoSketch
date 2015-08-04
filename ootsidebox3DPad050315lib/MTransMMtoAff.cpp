#include "MTransMMtoAff.h"
#include "MVariable.h"
#include "MAGesture.h"
#include "MCalculcoordonnees.h"
#include "Arduino.h"

extern struct CoordTypeAbs Curseur;
extern struct CoordTypeAbs CurseurMm;
extern struct CoordTypeAbs Ordy;
extern int OrdyX;
extern int OrdyY;
extern int OrdyZ;

extern int Max_X;
extern int Max_Y;
extern int Min_X;
extern int Min_Y;


void MMtoAff(void) //calcule les positions de Curseur et Ordy en pourcentage des longuers d'axes
{
    Curseur.X = (CurseurMm.X * 100) / L_AXE_X;
    Curseur.Y = (CurseurMm.Y * 100) / L_AXE_Y;
	if(Curseur.X > 100) Curseur.X =100;
	if(Curseur.Y > 100) Curseur.Y =100;

    Curseur.Z =CurseurMm.Z-L_AXE_Z_MIN;
	//Curseur.Z =(CurseurMm.Z -80) *40;
    //if(Curseur.Z <300)
    //    Curseur.Z =300;

    Ordy.X = (OrdyX * 100) / L_AXE_X;
    Ordy.Y = (OrdyY * 100) / L_AXE_Y;
    if (Ordy.X > 100) Ordy.X = 100;
    if (Ordy.Y > 100) Ordy.Y = 100;

    //Ordy.Z = OrdyZ * 15;
	Ordy.Z = OrdyZ-L_AXE_Z_MIN;
}
void ButMMtoAff(void)
{
    Max_X = (BUTMAX_X * 100) / L_AXE_X;
    Max_Y = (BUTMAX_Y * 100) / L_AXE_Y;
    Min_X = (BUTMIN_X * 100) / L_AXE_X;
    Min_Y = (BUTMIN_Y * 100) / L_AXE_Y;
}
