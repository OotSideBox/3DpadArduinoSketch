#include "math.h"
#include "MGestureTranslate.h"
#include "MAGesture.h"
#include "MVariable.h"
#include "MGesture.h"
#include "Arduino.h"
#include <stdlib.h>

extern struct CoordTypeAbs CurseurMm;
extern struct CoordTypeAbs Curseur;
extern struct CoordTypeDyn CurseurDyn;

extern int TranslateState;
extern int ClickState;
extern int TranslateResult ;
extern int GestState;
extern int Timer;
extern int PushPullState;
extern int PushPullResult;
extern int GestureResult;
extern char FlagGesture;

static int TempoPush=0;

bool focus;

void GestureTranslate(void)
{
    //Rem automate translations *****************************************
    bool Outside ;
	bool TranslateEnd;
    static int Ztube=0;
    static int FocusedX;
    static int FocusedY;
    static int FocusedZ;
    static int TimeoutClick;

    if(CurseurMm.Z > SEUILZPERCEPT-30) Outside = true;
    else Outside = false;


	 
if (   (GestState == REST)  || (GestState == VOID) || Outside) 
	{
		TranslateEnd = true;
	}
	else  TranslateEnd = false;


    switch(TranslateState)
    {
   
	case INIT:
        if( (CurseurDyn.Y > 0.25) && (fabs(CurseurDyn.X) < 0.3) && (CurseurMm.Y>L_AXE_Y/2))  TranslateState = UP;
        if( (CurseurDyn.Y < -0.25) && (fabs(CurseurDyn.X) < 0.3) && (CurseurMm.Y<L_AXE_Y/2))  TranslateState = DOWN;
        if( (CurseurDyn.X > 0.25) && (fabs(CurseurDyn.Y) < 0.3) && (CurseurMm.X>L_AXE_X/2))  TranslateState = RIGHT;
        if( (CurseurDyn.X < -0.25) && (fabs(CurseurDyn.Y) < 0.3) && (CurseurMm.X<L_AXE_X/2))  TranslateState = LEFT;
        break;
 

    case RIGHT:
        if( (CurseurDyn.X < -0.1))  TranslateState = DUMMY;
        if( (CurseurMm.Y<=(BUTMIN_Y+5)) || (CurseurMm.Y>=(BUTMAX_Y-5))) TranslateState = DUMMY;
        if( (fabs(CurseurDyn.Y) > 0.3))  TranslateState = INIT;

		if((TranslateEnd) || ( Curseur.X > 90))
		{
			TranslateResult = RIGHT;
            TranslateState = COMPLETE;
		}
        break;

    case LEFT:

        if((CurseurDyn.X > 0.1)) TranslateState = DUMMY;
        if( (CurseurMm.Y<=(BUTMIN_Y+5)) || (CurseurMm.Y>=(BUTMAX_Y-5))) TranslateState = DUMMY;
        if((fabs(CurseurDyn.Y) > 0.3)) TranslateState = INIT;

		if((TranslateEnd) || ( Curseur.X < 10))
		{
            TranslateResult = LEFT;
            TranslateState = COMPLETE;
		}
        break;

    case UP:
        if((CurseurDyn.Y < -0.1))  TranslateState = DUMMY;
        if( (CurseurMm.X<=(BUTMIN_X+5)) || (CurseurMm.X>=(BUTMAX_X-5)) ) TranslateState = DUMMY;
        if((fabs(CurseurDyn.X) > 0.3))  TranslateState = INIT;
                
		if((TranslateEnd) || ( Curseur.Y > 90))
		{
            TranslateResult = UP;
            TranslateState = COMPLETE;
		}
        break;

    case DOWN:
        if(CurseurDyn.Y > 0.1) TranslateState = DUMMY;
        if( (CurseurMm.X<=(BUTMIN_X+5)) || (CurseurMm.X>=(BUTMAX_X-5)) ) TranslateState = DUMMY;
        if(fabs(CurseurDyn.X) > 0.3)  TranslateState = INIT;
        
		if((TranslateEnd) || ( Curseur.Y < 10))
		{
            TranslateResult = DOWN;
            TranslateState = COMPLETE;
		}
        break;

    case DUMMY:
        TranslateState = INIT;
        break;

    case COMPLETE:
        switch(TranslateResult)
        {
        case UP:
            GestureResult = UP;
            break;
        case DOWN:
            GestureResult = DOWN;
            break;
        case RIGHT:
            GestureResult = RIGHT;
            break;
        case LEFT:
            GestureResult = LEFT;
            break;
        }
        TranslateState = INIT;
	
		FlagGesture=1;
        break;

    }
    //*****************************************************************************
    //Rem automate Push 
    switch(PushPullState)
    {
		case INIT:
					TempoPush=0;
					if ((CurseurDyn.Z < -0.1) && (CurseurMm.Z < 100)) PushPullState = PUSH;
		break;
		case PUSH:
					if ((CurseurDyn.Z > 0.05) || (CurseurMm.Z > 100)) PushPullState = INIT;

					if ((abs(Curseur.X - 50) > 20) && (abs(Curseur.Y - 50) > 20)) PushPullState = INIT;

					if ((abs(CurseurDyn.Y) > 0.2) || (abs(CurseurDyn.X) > 0.2))  PushPullState = INIT;

					if ((abs(Curseur.X - 50) < 20) && (abs(Curseur.Y - 50) < 20) && (CurseurMm.Z < 40) && (abs(CurseurDyn.Z) < 0.05)) TempoPush++;

					if ((TempoPush >= 20) && (abs(CurseurDyn.Y) < 0.05) && (abs(CurseurDyn.X) < 0.05)) PushPullState = COMPLETE;
		break;
		case COMPLETE:
					GestureResult = PUSH;
					FlagGesture=1;
					PushPullState = INIT;
		break;
    }

}
