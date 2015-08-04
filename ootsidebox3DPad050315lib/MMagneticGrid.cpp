#include "stdlib.h"
#include "MMagneticGrid.h"
#include "MVariable.h"

//Rem application du curseur sur la grille magnetique
void MagnetGrid(  struct CoordTypeAbs *Point)
{
static int LastX =0;//contient les dernieres coordonnees sur la grille
static int LastY =0;
static int lastZ =0;
int InputX; 
int InputY; 
int InputZ; 
int Ecart; 

InputX = Point->X;
InputY = Point->Y;
InputZ = Point->Z;


//Rem voir si nouvelle coordonnee a une distance suffisante de l'ancienne
Ecart = abs(InputX - LastX);
if (Ecart > (GRIDSTEP * GRIDCOEF)) Point->X = FindNearGridPoint(InputX);
else    Point->X = LastX;

Ecart = abs(InputY - LastY);
if (Ecart > (GRIDSTEP * GRIDCOEF)) Point->Y = FindNearGridPoint(InputY);
else    Point->Y = LastY;

/*
Ecart = abs(InputZ - lastZ);
if (Ecart > (GRIDSTEP * GRIDCOEF)) Point->Z = FindNearGridPoint(InputZ);
else    Point->Z = lastZ;
*/
//Rem sauve les dernieres coordonnes
LastX = Point->X;
LastY = Point->Y;
lastZ = Point->Z;

}


//Function FindNearGridPoint(ByVal Coord As Integer) As Integer

int FindNearGridPoint(int Coord)
{
//Rem renvoie le point de grille le plus proche
int Temp;
int Inf;
int Sup;
int Result; 

Temp = Coord / GRIDSTEP;
Inf = Temp * GRIDSTEP; //Inf = point entier inférieur
Sup = Inf + GRIDSTEP;  //Sup = pount entier superieur
if ( abs(Coord - Inf) < abs(Coord - Sup) )  Result = Inf;
else Result = Sup;

return(Result);

}
