#include "MGestureRotate.h"
#include "MGesture.h"
#include "MVariable.h"
#include "Arduino.h"

extern struct CoordTypeDyn CurseurDyn;
extern int GestState;
extern int TranslateState;
extern int GestureResult;
extern char FlagGesture;

int		Rotate = 0;
int		Rwheel = -1;
int		OldRwheel = -1;
int		CptRwheel = 0;
bool	ChangeRwheel = false;
int		Lwheel = -1;
int		OldLwheel = -1;
int		CptLwheel = 0;
bool	ChangeLwheel = false;
int		ToursR = 0;
int		ToursL = 0;



//Rem ANALYSE ROTATIONS

void GestureRotate(void)
{
int Temp;

if( (GestState == REST) || (GestState == VOID) ) 
	{
                Rotate = ROTATION_VOID;
		Rwheel = -1;
		OldRwheel = -1;
		CptRwheel = 0;
		ChangeRwheel = false;
		Lwheel = -1;
		OldLwheel = -1;
		CptLwheel = 0;
		ChangeLwheel = false;
		ToursR = 0;
		ToursL = 0;
	}

//*********************************************************************************
//Rem Analyse rotation droite

    ChangeRwheel = false;
	if((CurseurDyn.X > SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y > SEUIL_SENSIBILITE_ROTATE) && ((OldRwheel == 3) || (OldRwheel == -1))) 
		{
			if(OldRwheel >= 0)	ChangeRwheel = true;
			Rwheel = 0;
			OldRwheel = Rwheel;
			CptRwheel++;
		}

	if((CurseurDyn.X > SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y < -SEUIL_SENSIBILITE_ROTATE) && ((OldRwheel == 0) || (OldRwheel == -1)))
		{
			if(OldRwheel >= 0) 	ChangeRwheel = true;
			Rwheel = 1;
			OldRwheel = Rwheel;
			CptRwheel ++;
		}

	if((CurseurDyn.X < -SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y < -SEUIL_SENSIBILITE_ROTATE) && ((OldRwheel == 1) || (OldRwheel == -1)))
		{
			if(OldRwheel >= 0 )	ChangeRwheel = true;
			Rwheel = 2;
			OldRwheel = Rwheel;
			CptRwheel++;
		}

	if((CurseurDyn.X < -SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y > SEUIL_SENSIBILITE_ROTATE) && ((OldRwheel == 2) || (OldRwheel == -1))) {
		if(OldRwheel >= 0 ){
		    ChangeRwheel = true;
		}
		Rwheel = 3;
		OldRwheel = Rwheel;
		CptRwheel ++;
	}
 
//*********************************************************************************
//Rem Analyse rotation Gauche
	ChangeLwheel = false;
	if((CurseurDyn.X > SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y > SEUIL_SENSIBILITE_ROTATE) && ((OldLwheel == 1) || (OldLwheel == -1)))
		{
			if(OldLwheel >= 0) 	ChangeLwheel = true;
			Lwheel = 0;
			OldLwheel = Lwheel;
			CptLwheel ++;
		}
	if((CurseurDyn.X > SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y < -SEUIL_SENSIBILITE_ROTATE) && ((OldLwheel == 2) || (OldLwheel == -1))) 
		{
		   if(OldLwheel >= 0 )	ChangeLwheel = true;
			Lwheel = 1;
			OldLwheel = Lwheel;
			CptLwheel ++;
		}
	if((CurseurDyn.X < -SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y < -SEUIL_SENSIBILITE_ROTATE) && ((OldLwheel == 3) || (OldLwheel == -1))) 
		{
			if(OldLwheel >= 0) 	ChangeLwheel = true;
			Lwheel = 2;
			OldLwheel = Lwheel;
			CptLwheel ++;
		}
	if((CurseurDyn.X < -SEUIL_SENSIBILITE_ROTATE) && (CurseurDyn.Y > SEUIL_SENSIBILITE_ROTATE) && ((OldLwheel == 0) || (OldLwheel == -1)))
		{
			if(OldLwheel >= 0) 	ChangeLwheel = true;
			Lwheel = 3;
			OldLwheel = Lwheel;
			CptLwheel ++;
		}
   
 
//*********************************************************************************
//Rem interaction d'une roue sur l'autre

	if(ChangeLwheel == true) 
	{
		Rwheel = -1;
		CptRwheel = 0;
		OldRwheel = Lwheel;
	}
	if(ChangeRwheel == true )
	{
		Lwheel = -1;
		CptLwheel = 0;
		OldLwheel = Rwheel;
	}

	if(CptRwheel >= 5) 
	{
        Rotate = ROTATION_RIGHT ;
		ToursL = 0;
        TranslateState = INIT;
	}
	if(CptLwheel >= 5) 
	{
        Rotate = ROTATION_LEFT;
		ToursR = 0;
        TranslateState = INIT;
	}
        
        
	if((ChangeLwheel == true) && (Rotate == ROTATION_LEFT) && (((CptLwheel - 5) %4) == 0) ) 
	{
		ToursL++;
		FlagGesture=1;
	}
	if((ChangeRwheel == true) && (Rotate == ROTATION_RIGHT) && (((CptRwheel - 5) % 4) == 0) ) 
	{
		ToursR++;
		FlagGesture=1;
	}

	switch(Rotate)
	{
		case ROTATION_VOID: 
		break;
		case ROTATION_RIGHT: 
				GestureResult = ROTATE_RIGHT;
		break;
		case ROTATION_LEFT: 
				GestureResult = ROTATE_LEFT;
		break;
	}
}
