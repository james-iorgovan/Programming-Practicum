#include "Island.h"

#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;


Island::Island(Creature *creatures[20][20])
{
	/* Initialize all to zero */
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			creatures[i][j] = NULL;
		}
	}
}


/*********************************************************************
 *  ** Function: initialize(Critter *critters[20][20])
 *   ** Description: Randomly place ants and doodlebugs into the matrix
 *    ** Parameters: Matrix, can't place two critters in one space
 *     *********************************************************************/
void Island::initialize(Creature *creatures[20][20])
{
	int i = 0;

	/* Plant 5 doodle bugs on random places in the matrix */
	while (i < 5)
	{
		int m = 0, n = 0;

		/* Run until an empty space is found */
		while (creatures[m][n] != NULL)
		{
			m = rand() % 20;
			n = rand() % 20;
		}

		/* Put new doodlebug in empty space */
		creatures[m][n] = new Doodlebug;

		i++;
	}

	i = 0;				/* Reset counter */

	/* Do the same for 100 ants */
	while (i < 100)
	{
		int m = 0, n = 0;

		while (creatures[m][n] != NULL)
		{
			m = rand() % 20;
			n = rand() % 20;
		}

		creatures[m][n] = new Ant;

		i++;
	}
}


/*********************************************************************
 *  ** Function: printMatrix(Critter *critters[20][20])
 *   ** Description: Prints the matrix
 *    ** Parameters: Position of critters in matrix
 *     *********************************************************************/
void Island::printMatrix(Creature *creatures[20][20])
{
	for (int i = 0; i < 20; i++)
	{
		cout << "\t";
		for (int j = 0; j < 20; j++)
		{
			if (creatures[i][j] != NULL)
			{
				if (creatures[i][j]->info == 'A')
					cout << "A ";
				else cout << "D ";
			}
			else cout << ". ";
		}
	cout << "" << endl;
	}

	cout << endl << endl;
}


/*********************************************************************
 *  ** Function: isFinished(Critter *critters[20][20])
 *   ** Description: Runs through the matrix, if it finds a doodlebug it returns false.
 *    ** I elaborate on this in my design document, but I found under the conditions given
 *     ** in the end only the ants survive.
 *      ** Parameters: Critters in matrix.
 *       *********************************************************************/
bool Island::isFinished(Creature *creatures[20][20])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (creatures[i][j] != NULL)
				if (creatures[i][j]->info == 'D')
					return false;
		}
	}

	return true;
}


/*********************************************************************
 *  ** Function: doTurn(Critter *critters[20][20])
 *   ** Description: Handles the turn. Starts by breeding as appropriate.
 *    ** Then goes through moving and eating. This implementation is discussed
 *     ** in my design document.
 *      ** Parameters: Critter positions, breed counters.
 *       *********************************************************************/
void Island::doTurn(Creature *creatures[20][20])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (creatures[i][j] != NULL)
			{
				bool b = creatures[i][j]->breed();

				if (b)
				{
					/* Try to place another critter above current one */
					if ((i != 0) && (creatures[i - 1][j] == NULL))
					{
						if (creatures[i][j]->info == 'D')
							creatures[i - 1][j] = new Doodlebug;
						else
							creatures[i - 1][j] = new Ant;
					}
					else if ((j != 19) && (creatures[i][j + 1] == NULL))
					{
						/* Try to place new critter to the right */
						if (creatures[i][j]->info == 'D')
							creatures[i][j + 1] = new Doodlebug;
						else
							creatures[i][j + 1] = new Ant;
					}
					else if ((i != 19) && (creatures[i + 1][j] == NULL))
					{
						/* Try to place beneath */
						if (creatures[i][j]->info == 'D')
							creatures[i + 1][j] = new Doodlebug;
						else
							creatures[i + 1][j] = new Ant;
					}
					else if ((j != 0) && (creatures[i][j - 1] == NULL))
					{
						/* Try to place to the left */
						if (creatures[i][j]->info == 'D')
							creatures[i][j - 1] = new Doodlebug;
						else
							creatures[i][j - 1] = new Ant;
					}
				}
				/* This concludes the breeding */

				int m = creatures[i][j]->move();

				if (creatures[i][j]->info == 'D')
				{
					switch (m)
					{
						case 0:
							if (i != 0)
							{
								if (creatures[i - 1][j] != NULL)
								{
									if (creatures[i - 1][j]->info == 'A')
									{
										/* Move object, Doodlebug "eats" Ant above itself */
										delete creatures[i - 1][j];
										creatures[i][j]->eat(1);
									}
									else
									{
										creatures[i][j]->eat(0);
									}
								}
								else
								{
									creatures[i][j]->eat(0);
								}
								creatures[i - 1][j] = new Doodlebug(creatures[i][j]);
								delete creatures[i][j];
								creatures[i][j] = NULL;
							}
							else
								creatures[i][j]->eat(0);
							break;
						case 1:
							if (j != 19)
							{
								/* Move object. Doodlebug eats ant to the right of itself */
								if (creatures[i][j + 1] != NULL)
								{
									if (creatures[i][j + 1]->info == 'A')
									{
										delete creatures[i][j + 1];
										creatures[i][j]->eat(1);
									}
									else
									{
										creatures[i][j]->eat(0);
									}
								}
								else
								{
									creatures[i][j]->eat(0);
								}
								creatures[i][j + 1] = new Doodlebug(creatures[i][j]);
								delete creatures[i][j];
								creatures[i][j] = NULL;
							}
							else
								creatures[i][j]->eat(0);
							break;

							/*
							 * 							 ** Try to move down and see if it's possible
							 * 							 							 */
						case 2:
							if (i != 19)
							{
								if (creatures[i + 1][j] != NULL)
								{
									if (creatures[i + 1][j]->info == 'A')
									{
										delete creatures[i + 1][j];
										creatures[i][j]->eat(1);
									}
									else
									{
										creatures[i][j]->eat(0);
									}
								}
								else
								{
									creatures[i][j]->eat(0);
								}
								creatures[i + 1][j] = new Doodlebug(creatures[i][j]);
								delete creatures[i][j];
								creatures[i][j] = NULL;
							}
							else
								creatures[i][j]->eat(0);
							break;

							/*
							 * 							 ** Try to move left and see if it's possible
							 * 							 							 */
						case 3:
							if (j != 0)
							{
								if (creatures[i][j - 1] != NULL)
								{
									if (creatures[i][j - 1]->info == 'A')
									{
										delete creatures[i][j - 1];
										creatures[i][j]->eat(1);
									}
									else
									{
										creatures[i][j]->eat(0);
									}
								}
								else
								{
									creatures[i][j]->eat(0);
								}
								creatures[i][j - 1] = new Doodlebug(creatures[i][j]);
								delete creatures[i][j];
								creatures[i][j] = NULL;
							}
							else
								creatures[i][j]->eat(0);
							break;
					}
				}
			}
		}
	}
}	
