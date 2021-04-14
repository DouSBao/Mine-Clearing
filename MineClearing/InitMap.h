#ifndef INIT_MAP_H
#define INIT_MAP_H

#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <graphics.h>

/*
 * File: IniMap.h
 * ---------------------
 * Coder: DouSBao
 * Time: 12 April 2021
 * Function: Create a initial mineclearing game map
 */

typedef bool mine;
typedef int mineNumber;

struct coordinate {
	int x;
	int y;
};

const bool isMine = true;
const bool unMine = false;

// original mines' coordinates
static std::vector<coordinate> origiMinesC;

// Father class
class Map {
public:
	Map(int xLength, int yLength);

protected:
	// The column
	int xLength = 0;
	// The row
	int yLength = 0;
};

// Storage of numbers
class NumMap : virtual public Map {
public:
	NumMap(int xLength, int yLength);
	
protected:
	std::vector<std::vector<mineNumber>> numbers;
};

// Storage of mines
class MineMap : virtual public Map {
public:
	MineMap(int xLength, int yLength, int mineNumber);
	
protected:
	std::vector<std::vector<mine>> mines;
};

// real map
class GameMap : public MineMap, public NumMap {
public:
	GameMap(int xLength, int yLength, int mineNumber);

	std::vector<std::vector<mine>> getMines();
	std::vector<std::vector<mineNumber>> getNumbers();
};

#endif