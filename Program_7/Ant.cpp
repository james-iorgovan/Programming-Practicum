#include "Ant.h"

Ant::Ant()
{
	liveLimit = 10;
	breedLimit = 3;

	timeToBreedCounter = 0;
	timeToDeathCounter = 0;
	info = 'A';
}
