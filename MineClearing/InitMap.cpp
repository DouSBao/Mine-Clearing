#include "InitMap.h"

Map::Map(int xLength, int yLength)
{
	this->xLength = xLength;
	this->yLength = yLength;
}

NumMap::NumMap(int xLength, int yLength) : Map(xLength, yLength)
{
	// initialize the 2d vector
	numbers.resize(xLength);
	for (int i = 0; i < xLength; i++) {
		numbers[i].resize(yLength);
	}

	// change the 2d vector through the mines
	for (int i = 0; i < (int)origiMinesC.size(); i++) {
		coordinate temp = origiMinesC[i];
		if (temp.x - 1 >= 0 && temp.y - 1 >= 0)
			numbers[temp.x - 1][temp.y - 1]++; // left up
		if (temp.x - 1 >= 0)
			numbers[temp.x - 1][temp.y]++; // up
		if (temp.x - 1 >= 0 && temp.y + 1 < yLength)
			numbers[temp.x - 1][temp.y + 1]++; // right up
		if (temp.y - 1 >= 0)
			numbers[temp.x][temp.y - 1]++; // left
		numbers[temp.x][temp.y]++; // mid
		if (temp.y + 1 < yLength)
			numbers[temp.x][temp.y + 1]++; // right
		if (temp.x + 1 < xLength && temp.y - 1 >= 0)
			numbers[temp.x + 1][temp.y - 1]++; // left down
		if (temp.x + 1 < xLength)
			numbers[temp.x + 1][temp.y]++; // down
		if (temp.x + 1 < xLength && temp.y + 1 < yLength)
			numbers[temp.x + 1][temp.y + 1]++; // right down
	}

#if(0) // debug
	for (int i = 0; i < (int)numbers.size(); i++) {
		for (int j = 0; j < (int)numbers[i].size(); j++) {
			std::cout << numbers[i][j] << ' ';
		}
		std::cout << '\n';
	}
#endif
}

MineMap::MineMap(int xLength, int yLength, int mineNumber) : Map(xLength, yLength)
{
	std::default_random_engine engine((unsigned int)time(0));
	std::uniform_int_distribution<unsigned int> xRandom(0, xLength - 1);
	std::uniform_int_distribution<unsigned int> yRandom(0, yLength - 1);

	// initialize the 2d vector
	mines.resize(xLength);
	for (int i = 0; i < xLength; i++) {
		mines[i].resize(yLength);
	}
	
	// get random legal coordinate of mine
	while (mineNumber != 0) {
		int x = xRandom(engine);
		int y = yRandom(engine);
		if (mines[x][y] == unMine) {
			mines[x][y] = isMine;
			coordinate temp = { x, y };
			origiMinesC.push_back(temp);
			--mineNumber;
		}
	}
	
#if(0) // debug
	for (int i = 0; i < (int)mines.size(); i++) {
		for (int j = 0; j < (int)mines[i].size(); j++) {
			std::cout << mines[i][j] << ' ';
		}
		std::cout << '\n';
	}
#endif	
}

GameMap::GameMap(int xLength, int yLength, int mineNumber) : MineMap(xLength, yLength, mineNumber), NumMap(xLength, yLength), Map(xLength, yLength)
{

}

std::vector<std::vector<mine>> GameMap::getMines()
{
	return mines;
}

std::vector<std::vector<mineNumber>> GameMap::getNumbers()
{
	return numbers;
}