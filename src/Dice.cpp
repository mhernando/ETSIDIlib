#include "Dice.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

bool Dice::initialized=false;
#define __DICE_INIT if(!initialized){srand ((unsigned int)time(NULL));initialized=true;}

double Dice::Double(double max, double min)
{
	__DICE_INIT
	return min+(max-min)*((double)rand())/RAND_MAX;
}
int Dice::Int(int max, int min)
{
	__DICE_INIT
	return rand()%(max-min)+min;
}
bool Dice::Bool()
{
	__DICE_INIT
	return bool(rand()%2==1);
}

