#include "MGesture.h"
#include "MVariable.h"
#include "MGestureGlobale.h"
#include "MGestureTranslate.h"
#include "MGestureRotate.h"
#include "math.h"
#include "Arduino.h"

extern int Rotate;
extern bool Pushed;

int GestState; 
int TranslateState; 
int PushPullState; 
int ClickState;
int Timer; 
int TranslateResult ;
int PushPullResult; 
bool MoveFlag ;
int Temp ;
int GestureResult;
float X ;
float Y ;

extern struct CoordTypeDyn CurseurDyn;

void GestureInit(void)
{
    GestState = VOID;
    TranslateState = INIT;
}

int GestureCompute(void)
{    
    if ( (fabs(CurseurDyn.X) > SEUILMOVEGESTURE) || (fabs(CurseurDyn.Y) > SEUILMOVEGESTURE) || (fabs(CurseurDyn.Z) > SEUILMOVEGESTURE) )
	{
       MoveFlag = true;
    }
	else
	{
        MoveFlag = false;
	}
    
    //*****************************************************************************
	GestureGlobale();

	//*****************************************************************************
	GestureTranslate();

	//*****************************************************************************
	GestureRotate();

	//*****************************************************************************
       
	return (GestureResult);
}
