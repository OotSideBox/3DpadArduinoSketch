#ifndef Mgesture_
#define Mgesture_

#define INIT 0
#define VOID 1
#define REST 2
#define MOVING 3
#define RIGHT 4
#define LEFT 5
#define UP 6
#define DOWN 7
#define RIGHT_OUT  8
#define LEFT_OUT 9
#define UP_OUT 10
#define DOWN_OUT 11
#define DUMMY 12
#define COMPLETE 13
#define ROTATE_LEFT 14
#define ROTATE_RIGHT 15
#define PUSH 16
#define FOCUS 17

#define CKDOWN 18
#define CKUP 19
#define CKREADY 20
#define CLICK 21

#define SEUILMOVEGESTURE 0.05
#define TEMPSAFFICHAGE 2
#define TEMPSAFFICHAGE_RAPIDE 10//35
#define MOUVOKX 0.1
#define MOUVOKY 0.1
#define MOUVOKZ 0.08
#define MOUVDUMMY 0.3

void GestureInit(void);
int GestureCompute(void);
   

#endif
