#include <iostream>

#include "Island.h"
#include <time.h>
#include <cstdlib>

using namespace std;

int main()
{
cout << "Please press enter to go to the next Day\n";
	/* 20x20 array of critters */
	Creature* c[20][20];
	Island grid(c);

	/* Random seed for critter placement */
	srand(time(NULL));

	grid.initialize(c);

	/* Print matrix */
	grid.printMatrix(c);

	/* End of initialization */


	/*
	 * 	** While the game is still in progress, keep making turns and printing the matrix
	 * 		*/
	while (!grid.isFinished(c))
	{
		grid.doTurn(c);

		grid.printMatrix(c);

		cin.get();
	}

	/* Deallocating all allocated memory */
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (c[i][j] != NULL)
			{
				delete c[i][j];
			}
		}
	}

	return 0;
}
