#include "MGesture.h"
#include "MGestureGlobale.h"
#include "MVariable.h"
#include "Arduino.h"
#include "Parameters.h"

extern int CptInside;
extern int GestState;
extern bool Inside;
extern bool MoveFlag ;
extern int GestureResult;
extern char FlagGesture;


// automate gestuelle globale **********************************************
void GestureGlobale(void)
{
	
	
	if (CptInside == CPTINSIDEMAX-1) 
			{
					GestureResult=MOVING;
					FlagGesture=1;
			}

	switch(GestState)
	{
        case VOID:
			
            if(CptInside!=0)
            {
                if(MoveFlag) 
				{
					GestState = MOVING;
				}
                else 
				{
					GestState = MOVING;
				}
			}
        break;

        case REST:
            if(!Inside)	
			{
				GestState = VOID;
				GestureResult=VOID;
				FlagGesture=1;
			}
            else
            {
                if(MoveFlag) 
				{
					GestState = MOVING;
				}
            }
        break;

        case MOVING:
            if(!Inside) 
			{
				GestState = VOID;
				GestureResult=VOID;
				FlagGesture=1;
			}
            else
            {
                if(!MoveFlag) 
				{
					GestState = REST;
				}
            }
	    break;
    }

}    
