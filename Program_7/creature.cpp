#include "Creature.h"
#include <time.h>
#include <cstdlib>


Creature::Creature(){
	timeToBreedCounter = 0;
	timeToDeathCounter = 0;
}


void Creature::eat(int x){
	if((info == 'D') && (x == 1)){
		timeToDeathCounter = 0;
	}
	else{
		timeToDeathCounter++;
	}
}

int Creature::move(){
	return ((rand() % 4) + 1);
}


bool Creature::breed(){
	if(info == 'A' && timeToBreedCounter == breedLimit){
		timeToBreedCounter = 0;
		return true;
	}

	else if(info == 'D' && timeToBreedCounter == breedLimit){
		timeToBreedCounter = 0;
		return true;
	}
	timeToBreedCounter++;
	return false;
}

bool Creature::add(){
	if(timeToDeathCounter >= liveLimit){
		return true;
	}
	return false;
}
