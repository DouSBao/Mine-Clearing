#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <graphics.h>
#include <stdlib.h>
#include "InitMap.h"
#include "InitWindow.h"

#define ISUSED true
#define UNUSED false

/*
 * File: UserController.h
 * ---------------------
 * Coder: DouSBao
 * Time: 12 April 2021
 * Function: Allow the user to input
 */

struct index {
	int x;
	int y;
};

struct buttonIndex {
	int top;
	int bottom;
	int left;
	int right;
};

class Controller {
public:
	Controller(GameMap gameMap, GameWindow gameWindow);

	void update();
protected:

	int yButtonNumber;
	int xButtonNumber;
	int xLength;
	sqrSize buttonSize;
	COLORREF color;
	std::vector<std::vector<mineNumber>> numbers;
	std::vector<std::vector<mine>> mines;
	std::vector<std::vector<bool>> book;
	std::vector<std::vector<bool>> flag;

	// timer
	TIndex textC;
	COLORREF timerTColor;
	MTime tim;
	recSize timer;
	COLORREF timerBColor;

	bool isOnButton(MOUSEMSG mouse);

	void updateTimer();
	// get the index of the button in the vector
	index getButtonVectorIndex(MOUSEMSG mouse);
	// get the cooridinate of the button
	buttonIndex getButtonIndex(MOUSEMSG mouse);
	// reveal number
	void revealNumber(MOUSEMSG mouse);
	void revealNumber(int x, int y); // dfs only
	void markButton(MOUSEMSG mouse);
	// when get 0, reaveal all zero number behind
	void expandMap(int x, int y);
	MOUSEMSG getGIndexOfVectorIndex(int x, int y);
	void failGame(MOUSEMSG mouse);
	void failWindow();
	void hideUselessNumber();
	void winGame();
	void winWindow();
	
};

#endif