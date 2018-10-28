#include "Doodlebug.h"

Doodlebug::Doodlebug()
{
	liveLimit = 3;
	breedLimit = 8;

	timeToBreedCounter = 0;
	timeToDeathCounter = 0;

	info = 'D';
}

Doodlebug::Doodlebug(const Creature *c)
{

	liveLimit = c->liveLimit;
	breedLimit = c->breedLimit;

	timeToBreedCounter = c->timeToBreedCounter;
	timeToDeathCounter = c->timeToDeathCounter;

	info = 'D';

}
