#include <iostream>
#include <graphics.h>
#include "InitMap.h"
#include "InitWindow.h"
#include "UserController.h"

int main(void)
{
	int xLength = 15;
	int yLength = 20;
	int mineNumber = 20;
	COLORREF winColor = RGB(138, 138, 138);
	Set set(xLength, yLength, mineNumber, winColor);
	GameMap gameMap(xLength, yLength, mineNumber);
	GameWindow gameWindow(xLength, yLength, winColor);
	Controller controller(gameMap, gameWindow);
	
	controller.update();

	return 0;
}