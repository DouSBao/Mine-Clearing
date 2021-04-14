#include "InitWindow.h"

template <class T>
Window::Window(T xLength, T yLength, COLORREF color)
{
	windowSize.x = yLength * 20 + yLength * 5 - 5;
	windowSize.y = xLength * 20 + xLength * 5 - 5;
	this->color = color;
	initWindow();
}

void Window::initWindow()
{
	initgraph(windowSize.x, windowSize.y + infoSize);
	setbkcolor(color);
	cleardevice();
}

Buttons::Buttons(int xLength, int yLength)
{
	buttonSize.x = standButtonSize.x;
	buttonSize.y = standButtonSize.y;
	xButtonNumber = xLength;
	yButtonNumber = yLength;
	initButtons();
}

void Buttons::initButtons()
{
	for (int i = 0; i < xButtonNumber; i++) {
		for (int j = 0; j < yButtonNumber; j++) {
			solidrectangle(j * (buttonSize.x + 5), i * (buttonSize.y + 5) + infoSize, j * (buttonSize.x + 5) + buttonSize.x, i * (buttonSize.y + 5) + buttonSize.y + infoSize);
		}
	}
}

Info::Info(int yLength)
{
	int xSize = yLength * 20 + yLength * 5 - 5;
	int xGap = (xSize - standInfoSize.x) / 2;
	int yGap = (infoSize - standInfoSize.y) / 2;
	timer.left = xGap;
	timer.right = xGap + standInfoSize.x;
	timer.top = yGap;
	timer.bottom = yGap + standInfoSize.y;
	timerBColor = RGB(170, 170, 170);
	timerTColor = BLACK;
	text.x = xGap + 4;
	text.y = yGap + standInfoSize.y / 3 - 5;
	t.firMin = 0;
	t.firSec = 0;
	t.secMin = 0;
	t.secSec = 0;
	initTimer();
}

void Info::initTimer()
{
	setfillcolor(timerBColor);
	settextcolor(timerTColor);
	settextstyle(standInfoSize.x / 2 - 10, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	
	solidrectangle(timer.left, timer.top, timer.right, timer.bottom);
	char c[6];
	c[0] = t.firMin + '0';
	c[1] = t.secMin + '0';
	c[2] = ':';
	c[3] = t.firSec + '0';
	c[4] = t.secSec + '0';
	c[5] = '\0';
	std::string s = c;
	outtextxy(text.x, text.y, s.c_str());
}

GameWindow::GameWindow(int xLength, int yLength, COLORREF color) : Window(xLength, yLength, color), Buttons(xLength, yLength), Info(yLength)
{

}

Set::Set(int &xLength, int &yLength, int &mineNumber, COLORREF color) : Window(xLength, yLength, color) 
{
	initWindow();

	setfillcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);

	outtextxy(windowSize.x / 10, windowSize.y / 6, _T("The x-axis length: "));
	solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
	
	outtextxy(windowSize.x / 10, windowSize.y / 2, _T("The y-axis Length: "));
	solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
	
	outtextxy(windowSize.x / 10, windowSize.y / 6 * 5, _T("The mines number: "));
	solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);


	outtextxy(windowSize.x / 10, windowSize.y / 6 * 2, getString(yLength).c_str());
	outtextxy(windowSize.x / 10, windowSize.y / 6 * 4, getString(xLength).c_str());

	char c;
	bool selX = false;
	bool selY = false;
	bool selM = false;
	bool colorX = false;
	bool colorY = false;
	bool colorM = false;
	while (1) {
		if (MouseHit()) {
			MOUSEMSG mouse = GetMouseMsg();
			if (getpixel(mouse.x, mouse.y) == WHITE && mouse.uMsg == WM_LBUTTONDOWN) {
				if (mouse.y < windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8) {
					selX = true;
					selY = false;
					selM = false;
					colorX = true;
				}
				else if (mouse.y < windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8) {
					selX = false;
					selY = true;
					selM = false;
					colorY = true;
				}
				else if (mouse.y < windowSize.y + (windowSize.x - windowSize.x / 5) / 8) {
					selX = false;
					selY = false;
					selM = true;
					colorM = true;
				}
			}
		}
		if (_kbhit()) {
			c = _getch();
			if (c == 'w') {
				if (selX && yLength < 60) {
					yLength++;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y / 6 * 2 + 5));
					solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
				}
				else if (selY && xLength < 25) {
					xLength++;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y / 6 * 4 + 5));
					solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
				}
				else if (selM && mineNumber < xLength * yLength / 2) {
					mineNumber++;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y + 5));
					solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);
				}
			}
			else if (c == 's') {
				if (selX && yLength > 10) {
					yLength--;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y / 6 * 2 + 5));
					solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
				}
				else if (selY && xLength > 10) {
					xLength--;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y / 6 * 4 + 5));
					solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
				}
				else if (selM && mineNumber > 1) {
					mineNumber--;
					setfillcolor(getpixel(windowSize.x - windowSize.x / 10 - 10, windowSize.y + 5));
					solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);
				}
			}
			else if (c == '\r') {
				break;
			}
		}
		if (colorX == true) {
			setfillcolor(RGB(198, 198, 198));
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
			setfillcolor(WHITE);
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
			solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);
			colorX = false;
		}
		else if (colorY == true) {
			setfillcolor(RGB(198, 198, 198));
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
			setfillcolor(WHITE);
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
			solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);
			colorY = false;
		}
		else if (colorM == true) {
			setfillcolor(RGB(198, 198, 198));
			solidrectangle(windowSize.x / 10, windowSize.y, windowSize.x - windowSize.x / 10, windowSize.y + (windowSize.x - windowSize.x / 5) / 8);
			setfillcolor(WHITE);
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 2, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 2 + (windowSize.x - windowSize.x / 5) / 8);
			solidrectangle(windowSize.x / 10, windowSize.y / 6 * 4, windowSize.x - windowSize.x / 10, windowSize.y / 6 * 4 + (windowSize.x - windowSize.x / 5) / 8);
			colorM = false;
		}
		Sleep(1);
		outtextxy(windowSize.x / 10, windowSize.y / 6 * 2, getString(yLength).c_str());
		outtextxy(windowSize.x / 10, windowSize.y / 6 * 4, getString(xLength).c_str());
		outtextxy(windowSize.x / 10, windowSize.y, getString(mineNumber).c_str());
	}

	closegraph();
}

std::string Set::getString(int number)
{
	std::vector<int> temp;
	int xCopy = number;
	while (xCopy > 0) {
		temp.push_back(xCopy % 10);
		xCopy /= 10;
	}

	std::string str;
	for (int i = (int)temp.size() - 1; i >= 0; i--) {
		str.push_back((char)(temp[i] + '0'));
	}

	return str;
}

int GameWindow::getXButtonNumber()
{
	return xButtonNumber;
}

int GameWindow::getYBUttonNumber()
{
	return yButtonNumber;
}

sqrSize GameWindow::getButtonSize()
{
	return buttonSize;
}

COLORREF GameWindow::getColor()
{
	return color;
}

int GameWindow::getXLength()
{
	return windowSize.x;
}

TIndex GameWindow::getTIndex()
{
	return text;
}

COLORREF GameWindow::getTimerTColor()
{
	return timerTColor;
}

MTime GameWindow::getTime()
{
	return t;
}

recSize GameWindow::getTimerSize()
{
	return timer;
}

COLORREF GameWindow::getTimerBColor()
{
	return timerBColor;
}