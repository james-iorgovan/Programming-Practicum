#pragma once
class Creature{
	public:
		int timeToBreedCounter;
		int timeToDeathCounter;
		int breedLimit;
		int liveLimit;
		char info;

		Creature();
		void eat(int);
		int move();
		bool breed();
		bool died();
		bool add();
};

