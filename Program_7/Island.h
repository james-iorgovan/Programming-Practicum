#pragma once
#include "Creature.h"
#include "Ant.h"
#include "Doodlebug.h"
class Island
{
	public:
		Island(Creature *creatures[20][20]);

		void initialize(Creature *creatures[20][20]);
		void printMatrix(Creature *creatures[20][20]);
		bool isFinished(Creature *creatures[20][20]);
		void doTurn(Creature *creatures[20][20]);
};

