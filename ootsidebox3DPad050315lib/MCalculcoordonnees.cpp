#include "math.h"
#include "MCalculcoordonnees.h"


void CoordXYcompute(int c,int a,int b,int * AH,int * Z)
{
    //parametres d'entre:
    //c = mesure electrode du cot origine de l'axe
    //a = mesure electrode du cot extrmit de l'axe
    //b = longeur de l'axe en mm
    //en resultat, la fonction place inscrit la cote en X dans AH et la valeur Z (les 2 sont en mm)
    long R1,R2,R3,R4;
    //calcul de la position en X (resultat dans AH)
    R1 = (long)b*(long)b;
    R2 = (long)a*(long)a;
    R3 = (long)c*(long)c;
    R4 = (R1-(R2-R3))/(2 * (long)b);
    if (R4<0)
    {
            R4 = 0;
    }
    *AH=(int)(R4);

    //calcul de Z
    R1=(R3-(R4*R4));
    if(R1<=0)
    {
        *Z=0;
    }
    else
    {
     *Z=(int)(sqrt((double)R1));
    }

}

int CoordZcompute(int Zx, int Zy)
{
    //calcule un Z moyen en fonction de Zx et Zy fournis en entre
    int Z=0;
    Z = (Zx+Zy)/2;

    if(Z<L_AXE_Z_MIN)  Z = L_AXE_Z_MIN;
    if(Z >L_AXE_Z_MAX) Z=  L_AXE_Z_MAX;
    
	return(Z);
}
