#define NUM_PLAYERS 5
#define NUM_WORDS 12
#define NUM_CALLED 4
#define NUM_ITERATIONS 10000
#define NUM_CELLS 9

#include <time.h>
#include <iostream>

// dir:
/*
	0 = up
	1 = left
	2 = down
	3 = right
*/
bool checkWinningMove(int* arr, int pos, int lastPos, int dir, int len)
{
	if (arr[pos] == 1 && pos != lastPos)
	{
		if (len + 1 == 3)
			return true;
		else
		{
			if (dir == -1)
			{
				// Up
				if (pos - 3 >= 0 && pos - 3 != lastPos && checkWinningMove(arr, pos - 3, pos, 0, len + 1))
					return true;

				// Left
				if (pos % 3 != 0 && pos - 1 != lastPos && checkWinningMove(arr, pos - 1, pos, 1, len + 1))
					return true;

				// Down
				if (pos < 6 && pos + 3 != lastPos && checkWinningMove(arr, pos + 3, pos, 2, len + 1))
					return true;

				// Right
				if (pos % 3 != 2 && pos + 1 != lastPos && checkWinningMove(arr, pos + 1, pos, 3, len + 1))
					return true;
			}
			else 
			{

				if (dir == 0)
				{
					if (pos - 3 >= 0 && pos - 3 != lastPos && checkWinningMove(arr, pos - 3, pos, 0, len + 1))
						return true;
				}
				else if (dir == 1)
				{
					if (pos % 3 != 0 && pos - 1 != lastPos && checkWinningMove(arr, pos - 1, pos, 1, len + 1))
						return true;
				}
				else if (dir == 2)
				{
					if (pos < 6 && pos + 3 != lastPos && checkWinningMove(arr, pos + 3, pos, 2, len + 1))
						return true;
				}
				else if (dir == 3)
				{
					if (pos % 3 != 1 && pos + 1 != lastPos && checkWinningMove(arr, pos + 1, pos, 3, len + 1))
						return true;
				}

					
			}
		}
	}

	return 0;
}

struct card {
	int cells[NUM_CELLS];
	int checked[NUM_CELLS];

	card()
	{
		reset();
	}

	void reset()
	{
		for (int i = 0; i < NUM_CELLS; i++)
		{
			int safe = 0;
			while (1)
			{
				cells[i] = rand() % NUM_WORDS;

				if (i == 0)
					break;

				for (int j = 0; j < i; j++)
				{
					if (j == i - 1 && cells[i] != cells[j])
					{
						safe = 1;
						break;
					}

					if (cells[i] == cells[j])
						break;
				}

				if (safe)
					break;
			}
			checked[i] = 0;
		}
	}

	// Returns 1 if a win is found
	bool checkArray(int n)
	{
		int loc = -1;

		// Locate if on board
		for(int i = 0; i < NUM_CELLS; i++)
			if (n == cells[i])
			{
				loc = i;
				checked[loc] = 1;
				break;
			}
		
		// Not on board
		if (loc == -1)
			return 0;

		for (int i = 0; i < 9; i++)
			if (checkWinningMove(checked, i, -1, -1, 0))
				return 1;
		return 0;
	}

	void printCard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << cells[j + i*3] << " ";
			}
			std::cout << std::endl;
		}
	}

	void printCheck()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << checked[j + i * 2] << " ";
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	srand(time(NULL));

	card* cards[NUM_PLAYERS];

	int calledWords[NUM_CALLED];
	int avgWinTurn = 0;
	int gamesWithWins = 0;
	int gamesWithoutWins = 0;

	for (int i = 0; i < NUM_PLAYERS; i++)
		cards[i] = new card();
	
	for (int k = 0; k < NUM_ITERATIONS; k++) 
	{

		for (int i = 0; i < NUM_PLAYERS; i++)
			cards[i]->reset();

		for (int i = 0; i < NUM_CALLED; i++)
		{
			int safe = 0;
			while (1)
			{
				calledWords[i] = rand() % NUM_WORDS;

				if (i == 0)
					break;

				for (int j = 0; j < i; j++)
				{
					if (j == i - 1 && calledWords[i] != calledWords[j])
					{
						safe = 1;
						break;
					}

					if (calledWords[i] == calledWords[j])
						break;
				}

				if (safe)
					break;
			}
		}

		bool stopGame = 0;
		for (int i = 0; i < NUM_CALLED; i++)
		{
			for (int j = 0; j < NUM_PLAYERS; j++)
			{
				if (cards[j]->checkArray(calledWords[i]))
				{
					//printf("Winner Found on turn %i\n", i + 1);
					avgWinTurn += i + 1;
					gamesWithWins++;
					stopGame = 1;
					break;
				}
			}
			if (stopGame)
				break;
		}

		if (!stopGame)
			gamesWithoutWins++;
	}

	printf("Average Win Turn is %f in %i won games of %i games total\n\n", ((float)avgWinTurn/(float)gamesWithWins), gamesWithWins, gamesWithWins+gamesWithoutWins);
	printf("Games without a winner: %i", gamesWithoutWins);
}