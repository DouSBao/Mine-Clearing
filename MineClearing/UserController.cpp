#include "UserController.h"

Controller::Controller(GameMap gameMap, GameWindow gameWindow)
{
	xButtonNumber = gameWindow.getXButtonNumber();
	yButtonNumber = gameWindow.getYBUttonNumber();
	buttonSize = gameWindow.getButtonSize();
	numbers = gameMap.getNumbers();
	mines = gameMap.getMines();
	color = gameWindow.getColor();
	xLength = gameWindow.getXLength();
	book.resize(numbers.size());
	flag.resize(numbers.size());

	textC = gameWindow.getTIndex();
	timerTColor = gameWindow.getTimerTColor();
	tim = gameWindow.getTime();
	timer = gameWindow.getTimerSize();
	timerBColor = gameWindow.getTimerBColor();

	for (int i = 0; i < (int)book.size(); i++) {
		book[i].resize(numbers[0].size());
		flag[i].resize(numbers[0].size());
	}
}

void Controller::update()
{
	MOUSEMSG mouse;
	SYSTEMTIME timeF, timeB;
	GetLocalTime(&timeF);
	bool flag = false;

	while (1) {
		if (flag) {
			GetLocalTime(&timeB);
			if (timeB.wSecond - timeF.wSecond >= 1 || (timeB.wSecond == 0 && timeF.wSecond == 59)) {
				updateTimer();
				timeF = timeB;
			}
		}

		if (MouseHit()) {
			mouse = GetMouseMsg();
			if (isOnButton(mouse)) {
				if (mouse.uMsg == WM_LBUTTONDOWN) {
					revealNumber(mouse);
					hideUselessNumber();
					winGame();
					flag = true;
				}
				else if (mouse.uMsg == WM_RBUTTONDOWN) {
					markButton(mouse);
				}
			}
		}
		Sleep(1);
	}
}

void Controller::markButton(MOUSEMSG mouse)
{
	index button = getButtonVectorIndex(mouse);
	buttonIndex button1 = getButtonIndex(mouse);
	if (flag[button.x][button.y] == UNUSED) {
		IMAGE pic;
		loadimage(&pic, "./flag.png", buttonSize.x, buttonSize.y);
		putimage(button1.left, button1.top, &pic);
		flag[button.x][button.y] = ISUSED;
	}
	else {
		flag[button.x][button.y] = UNUSED;
		setfillcolor(WHITE);
		solidrectangle(button1.left, button1.top, button1.right, button1.bottom);
	}
}

bool Controller::isOnButton(MOUSEMSG mouse)
{
	bool result = false;
	index button = getButtonVectorIndex(mouse);

	if (0 <= button.x && button.x < (int)book.size() && 0 <= button.y && button.y < (int)book[0].size()) {
		if (book[button.x][button.y] == UNUSED) {
			result = true;
		}
	}
	
	return result;
}

void Controller::updateTimer()
{
	tim.secSec++;
	if (tim.secSec >= 10) {
		tim.secSec = 0;
		tim.firSec++;
		if (tim.firSec >= 6) {
			tim.firSec = 0;
			tim.secMin++;
			if (tim.secMin >= 10) {
				tim.secMin = 0;
				tim.firMin++;
				if (tim.firMin >= 6) {
					tim.firMin = 0;
					tim.firSec = 0;
					tim.secMin = 0;
					tim.secSec = 0;
				}
			}
		}
	}

	settextcolor(timerTColor);
	setfillcolor(timerBColor);
	settextstyle(standInfoSize.x / 2 - 10, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);

	solidrectangle(timer.left, timer.top, timer.right, timer.bottom);

	char c[6];
	c[0] = tim.firMin + '0';
	c[1] = tim.secMin + '0';
	c[2] = ':';
	c[3] = tim.firSec + '0';
	c[4] = tim.secSec + '0';
	c[5] = '\0';
	std::string s = c;
	outtextxy(textC.x, textC.y, s.c_str());
}

index Controller::getButtonVectorIndex(MOUSEMSG mouse)
{
	index result;

	result.y = mouse.x / (buttonSize.x + 5);
	result.x = (mouse.y - infoSize) / (buttonSize.y + 5);

	return result;
}

buttonIndex Controller::getButtonIndex(MOUSEMSG mouse)
{
	buttonIndex result;
	index temp = getButtonVectorIndex(mouse);
	temp.x++;
	temp.y++;

	result.bottom = temp.x * (buttonSize.y + 5) + infoSize - 5;
	result.top = result.bottom - buttonSize.y;
	result.right = temp.y * (buttonSize.x + 5) - 5;
	result.left = result.right - buttonSize.x;

	return result;
}

void Controller::revealNumber(MOUSEMSG mouse)
{
	index temp1 = getButtonVectorIndex(mouse);
	buttonIndex temp2 = getButtonIndex(mouse);

	settextcolor(RGB(70, 70, 70));
	settextstyle(20, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(155, 155, 155));

	char c = numbers[temp1.x][temp1.y] + '0';
	book[temp1.x][temp1.y] = ISUSED;

	if (numbers[temp1.x][temp1.y] == 0) {
		expandMap(temp1.x, temp1.y);
	}
	else if (mines[temp1.x][temp1.y] == isMine) {
		failGame(mouse);
	}

	solidrectangle(temp2.left, temp2.top, temp2.right, temp2.bottom);
	outtextxy(temp2.left + 6, temp2.top + 3, c);
}

void Controller::revealNumber(int x, int y)
{
	buttonIndex temp2 = getButtonIndex(getGIndexOfVectorIndex(x, y));

	settextcolor(RGB(70, 70, 70));
	settextstyle(20, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(155, 155, 155));

	solidrectangle(temp2.left, temp2.top, temp2.right, temp2.bottom);
	char c = numbers[x][y] + '0';

	outtextxy(temp2.left + 6, temp2.top + 3, c);
}

void Controller::expandMap(int x, int y)
{
	int move[4][2] = {
		{0, 1}, // right
		{0, -1}, // left
		{1, 0}, // down
		{-1, 0} //up
	};

	for (int i = 0; i < 4; i++) {
		int nextX = x + move[i][0];
		int nextY = y + move[i][1];
		if (nextX < (int)numbers.size() && nextX >= 0 && nextY < (int)numbers[0].size() && nextY >= 0) {
			if (numbers[nextX][nextY] == 0 && book[nextX][nextY] == UNUSED && flag[nextX][nextY] == UNUSED) {
				book[nextX][nextY] = ISUSED;
				revealNumber(nextX, nextY);
				expandMap(nextX, nextY);
			}
		}
	}
}

MOUSEMSG Controller::getGIndexOfVectorIndex(int x, int y)
{
	MOUSEMSG result;
	
	result.y = (x + 1) * (buttonSize.x + 5) + infoSize - 7;
	result.x = (y + 1) * (buttonSize.y + 5) - 7;
	
	return result;
}

void Controller::failGame(MOUSEMSG mouse)
{
	buttonIndex temp2 = getButtonIndex(mouse);

	settextcolor(RED);
	settextstyle(20, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(170, 170, 170));

	solidrectangle(temp2.left, temp2.top, temp2.right, temp2.bottom);

	outtextxy(temp2.left + 6, temp2.top + 3, 'X');

	failWindow();

	char c = getchar();

	closegraph();

	exit(0);
}

void Controller::failWindow()
{
	closegraph();
	initgraph(650, 200);
	setbkcolor(color);
	cleardevice();

	settextcolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	TCHAR c[] = _T("You Fail, Game Over !!!");
	TCHAR c1[] = _T("Type shift to leave the game !!!");
	outtextxy(20, 40, c);
	outtextxy(20, 80, c1);
}

void Controller::hideUselessNumber()
{
	int next[8][2]{
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0},
		{1, 1},
		{1, -1},
		{-1, 1},
		{-1, -1}
	};

	for (int i = 0; i < (int)numbers.size(); i++) {
		for (int j = 0; j < (int)numbers[i].size(); j++) {
			bool isUseLess = true;
			if (book[i][j] == ISUSED) {
				for (int k = 0; k < 8; k++) {
					int nextX = i + next[k][0];
					int nextY = j + next[k][1];
					if (nextX < (int)numbers.size() && nextX >= 0 && nextY < (int)numbers[0].size() && nextY >= 0) {
						if (book[nextX][nextY] == UNUSED) {
							isUseLess = false;
						}
					}
				}
			}
			else {
				isUseLess = false;
			}
			if (isUseLess) {
				buttonIndex temp = getButtonIndex(getGIndexOfVectorIndex(i, j));
				setfillcolor(RGB(155, 155, 155));
				solidrectangle(temp.left, temp.top, temp.right, temp.bottom);
			}
		}
	}
}

void Controller::winGame()
{
	bool isWin = true;

	for (int i = 0; i < (int)numbers.size(); i++) {
		for (int j = 0; j < (int)numbers[i].size(); j++) {
			if (mines[i][j] != isMine && book[i][j] == UNUSED) {
				isWin = false;
			}
		}
	}

	if (isWin) {
		closegraph();
		winWindow();

		char c = getchar();

		closegraph();

		exit(0);
	}
}

void Controller::winWindow()
{
	closegraph();
	initgraph(650, 300);
	setbkcolor(color);
	cleardevice();

	settextcolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	TCHAR c[] = _T("You won the game!!!");
	TCHAR c1[] = _T("Type shift to leave the game !!!");
	TCHAR c2[6];
	TCHAR c3[] = _T("Time use: ");
	c2[0] = tim.firMin + '0';
	c2[1] = tim.secMin + '0';
	c2[2] = ':';
	c2[3] = tim.firSec + '0';
	c2[4] = tim.secSec + '0';
	c2[5] = '\0';

	outtextxy(20, 40, c);
	outtextxy(20, 80, c1);
	outtextxy(20, 120, c3);
	outtextxy(200, 120, c2);
}