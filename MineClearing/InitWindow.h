#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>

/*
 * File: InitWindow.h
 * ---------------------
 * Coder: DouSBao
 * Time: 12 April 2021
 * Function: Create a interactive window for mineclearing game
 */

struct sqrSize {
	int x = 0;
	int y = 0;
};

struct recSize {
	int top;
	int bottom;
	int left;
	int right;
};

struct TIndex {
	int x;
	int y;
};

struct MTime {
	int firMin;
	int secMin;
	int firSec;
	int secSec;
};

// size of the button
const sqrSize standButtonSize = { 20, 20 };
// size of the upper infomation part of the window
const int infoSize = 100;
// size of the timer
const sqrSize standInfoSize = { 100, 70 };
const sqrSize standPreSettingSize = { 200, 200 };

class Window {
public:
	template<class T>
	Window(T xLength, T yLength, COLORREF color);
protected:
	// the size of whole game window
	sqrSize windowSize;
	COLORREF color;

	// draw the window
	void initWindow();
};

class Buttons {
public:
	Buttons(int xLength, int yLength);
protected:
	// the size of each button
	sqrSize buttonSize;
	int xButtonNumber;
	int yButtonNumber;

	// draw thw buttons
	void initButtons();
};

class Info {
public:
	Info(int yLength);
protected:
	recSize timer;
	TIndex text;
	COLORREF timerBColor;
	COLORREF timerTColor;
	MTime t;

	// draw timer
	void initTimer();
};

class GameWindow : public Window, public Buttons, public Info {
public:
	GameWindow(int xLength, int yLength, COLORREF color);

	int getXButtonNumber();
	int getYBUttonNumber();
	int getXLength();
	recSize getTimerSize();
	COLORREF getTimerBColor();
	TIndex getTIndex();
	COLORREF getTimerTColor();
	MTime getTime();
	COLORREF getColor();
	sqrSize getButtonSize();
};

// pre setting window
class Set : public Window {
public:
	Set(int &xLength, int &yLength, int &mineNumber, COLORREF color);
private:
	std::string getString(int number);
};

#endif