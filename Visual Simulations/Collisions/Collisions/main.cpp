#include <iostream>

#include "game.h"

void drawProgramInfo()
{
	// Set color to magenta
	ConsoleColorizer::getInstance().SetTextColor(FONT_MAGENTA);

	printf("+================================================+\n");
	printf("\t    Crazy Collisions & Marvelous Momentum\n\n");
	printf("\t\t    Date\n");
	printf("\t\t  3/31/2021\n\n");
	printf("+================================================+\n");
	printf("\t\t Information\n");
	printf("+================================================+\n\n");
	printf("Description:\n");
	printf("\tThis project explores collisions between circles and how to ~accurately~ simulate them.\n\n");
	printf("Tips:\n");
	printf("\t-At any point you can press 'esc' to quit!\n\n");
	printf("+================================================+\n");
	printf("\t\tStarting Sim\n");
	printf("+================================================+\n");
	printf(" \n");

	// Set color back to default
	ConsoleColorizer::getInstance().SetTextColor();
}

int main()
{
	drawProgramInfo();

	Game game;

	game.Begin();

	return 1;
}