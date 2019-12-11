#include <ios>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <thread>
#include <dos.h> 
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "uilib.h"
#include <random>
#include <string>
#include <future>
#include <iomanip>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
using namespace std;
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define FRAMETOP 3
#define FRAMEBOTTOM 15
#define FRAMELEFT 3
#define FRAMERIGHT 43
bool ckUp = false;
bool ckDown = false;
bool ckLeft = false;
bool ckRight = false;
bool stop = 1;
bool checkThread = false;
int xP = 12, yP = 7;
struct point {
	int x;
	int y;
	struct point *pNext;
};
typedef struct point Point;
struct Hour {
	int hour;
	int minute;
	int second;
}; typedef struct Hour Hour;
struct list
{
	int size;
	point *pHead;
	point *pTail;

};
typedef struct list List;
struct PointRandom {
	int x;
	int y;
};
typedef struct PointRandom Prd;
void Create_List(List &l) {
	l.size = 0;
	l.pHead = l.pTail = NULL;
}
Point *Create_Point(int x, int y) {
	Point *p = new Point;
	if (p == NULL)
		return NULL;
	p->x = x;
	p->y = y;
	p->pNext = NULL;
	return p;
}
void Add_Head(List &l, Point *p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
	l.size++;
}
void Add_Tail(List &l, Point *p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		l.pTail->pNext = p;
		l.pTail = p;

	}
	l.size++;
}
void Delete_Head(List &l) {
	if (l.pHead == NULL) {
		return;
	}
	Point *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
	l.size--;
}
void Delete_Tail(List &l) {
	if (l.pHead == NULL)
		return;
	for (Point *p = l.pHead; p != NULL; p = p->pNext) {
		if (p->pNext == l.pTail) {
			delete l.pTail;
			p->pNext = NULL;
			l.pTail = p;
		}
	}
	l.size--;

}
void draw_frames() {
	for (int i = 2; i < 40; i++) {
		gotoXY(i, 5);
		cout << (char)220;
	}
	for (int i = 2; i <= 39; i++) {
		gotoXY(i, 15);
		cout << (char)223;
	}
	for (int i = 6; i <= 14; i++) {
		gotoXY(2, i);
		cout << (char)221;
	}
	for (int i = 6; i <= 14; i++) {
		gotoXY(39, i);
		cout << (char)222;

	}
}
int Random(int a, int b)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(a, b);
	return distr(eng);
}
void init_snake(List &l) {
	int x = 15, y = 8;
	while (x > 10)
	{
		Point *p = Create_Point(x, y);
		Add_Tail(l, p);
		x--;
	}
}
void show_snake(List l) {
	
	for (Point *p = l.pHead; p != NULL; p = p->pNext) {
		if (p == l.pHead) {
			SetColor(12);
			gotoXY(p->x, p->y);
			cout << (char)233;
		}
		else
		{
			SetColor(Random(0, 255));
			gotoXY(p->x, p->y);
			cout << (char)229;
		}
	}

}
void check_direction(int n) {
	switch (n)
	{
	case UP:
		ckUp = true;
		ckDown = ckRight = ckLeft = false;
		break;
	case DOWN:
		ckUp = ckDown = false;
		ckRight = ckLeft = true;

		break;
	case LEFT:
		ckLeft = true;
		ckUp = ckDown = ckRight = false;
		break;
	case RIGHT:
		ckDown = ckUp = true;
		ckLeft = ckRight = false;
		break;

	default:
		break;
	}

}
void direction(List &l, int direction, int numberPoint) {

	if (direction == RIGHT) {

		int xRight = l.pHead->x;
		int yRight = l.pHead->y;
		gotoXY(l.pHead->x, l.pHead->y);
		cout << " ";
		Delete_Head(l);
		int xRight1 = l.pHead->x;
		int yRight1 = l.pHead->y;
		for (Point *p = l.pHead; p != NULL; p = p->pNext) {
			if (p == l.pHead) {
				gotoXY(p->x, p->y);
				cout << " ";
				l.pHead->x = xRight;
				l.pHead->y = yRight;
			}
			else {
				gotoXY(p->x, p->y);
				cout << " ";
				int xRight2 = p->x;
				int yRight2 = p->y;
				p->x = xRight1;
				p->y = yRight1;
				xRight1 = xRight2;
				yRight1 = yRight2;
			}
		}
		Point * pRight = Create_Point(xRight + 1, yRight);
		Add_Head(l, pRight);


	}
	else if (direction == DOWN) {
		int xDown = l.pHead->x;
		int yDown = l.pHead->y;
		gotoXY(l.pHead->x, l.pHead->y);
		cout << " ";
		Delete_Head(l);
		int xDown1 = l.pHead->x;
		int yDown1 = l.pHead->y;
		for (Point *p = l.pHead; p != NULL; p = p->pNext) {
			if (p == l.pHead) {
				gotoXY(p->x, p->y);
				cout << " ";
				l.pHead->x = xDown;
				l.pHead->y = yDown;
			}
			else {
				gotoXY(p->x, p->y);
				cout << " ";
				int xDown2 = p->x;
				int yDown2 = p->y;
				p->x = xDown1;
				p->y = yDown1;
				xDown1 = xDown2;
				yDown1 = yDown2;
			}
		}
		Point * pDown = Create_Point(xDown, yDown + 1);
		Add_Head(l, pDown);
	}
	else if (direction == LEFT) {
		int xLeft = l.pHead->x;
		int yLeft = l.pHead->y;
		gotoXY(l.pHead->x, l.pHead->y);
		cout << " ";
		Delete_Head(l);
		int xLeft1 = l.pHead->x;
		int yLeft1 = l.pHead->y;
		for (Point *p = l.pHead; p != NULL; p = p->pNext) {
			if (p == l.pHead) {
				gotoXY(p->x, p->y);
				cout << " ";
				l.pHead->x = xLeft;
				l.pHead->y = yLeft;
			}
			else {
				gotoXY(p->x, p->y);
				cout << " ";
				int xLeft2 = p->x;
				int yLeft2 = p->y;
				p->x = xLeft1;
				p->y = yLeft1;
				xLeft1 = xLeft2;
				yLeft1 = yLeft2;
			}
		}
		Point * pLeft = Create_Point(xLeft - 1, yLeft);
		Add_Head(l, pLeft);

	}
	else if (direction == UP) {
		int xUp = l.pHead->x;
		int yUp = l.pHead->y;
		gotoXY(l.pHead->x, l.pHead->y);
		cout << " ";
		Delete_Head(l);
		int xUp1 = l.pHead->x;
		int yUp1 = l.pHead->y;
		for (Point *p = l.pHead; p != NULL; p = p->pNext) {
			if (p == l.pHead) {
				gotoXY(p->x, p->y);
				cout << " ";
				l.pHead->x = xUp;
				l.pHead->y = yUp;
			}
			else {
				gotoXY(p->x, p->y);
				cout << " ";
				int xUp2 = p->x;
				int yUp2 = p->y;
				p->x = xUp1;
				p->y = yUp1;
				xUp1 = xUp2;
				yUp1 = yUp2;
			}
		}
		Point * pUp = Create_Point(xUp, yUp - 1);
		Add_Head(l, pUp);

	}
}
void event_move(int &input) {
	int key = inputKey();
	input = key;
}
bool check_point_random(List l,int x,int y) {
	for (Point *p = l.pHead; p != NULL; p = p->pNext) {
		if (p->x == x && p->y == y) {
			return true;
		}
	}
	return false;
}
void point_random(List l,Prd &prd) {
	srand(time(NULL));
	int x = 15 + 1 + rand() % (39 - 15 - 1);
	int y = 5 + 1 + rand() % (15 - 5 - 1);
	if (!check_point_random(l, x, y)) {
		gotoXY(prd.x, prd.y);
		cout << " ";
		prd.x = xP = x;
		prd.y = yP = y;
		gotoXY(x, y);
		SetColor(15);
		cout << "$";
	}
	else
	{
		point_random(l,prd);
	}

}
bool check_coordinate_point(List &l,int &score) {
	if (l.pHead->x == xP && l.pHead->y == yP) {
		score += 5;
		gotoXY(17, 2);
		cout << setw(50) << " ";
		gotoXY(17, 2);
		SetColor(15);
		cout << "Diem: " << score;

		return true;
	}
	else {
		return false;
	}
}
void deleteList(Point *head) {
	if (head != NULL) {
		deleteList(head->pNext);
		delete head;
	}
}
bool changetime(Hour *h) {
	if (h->second > 0) --h->second;
	else if (h->minute > 0) {
		h->second = 59;
		--h->minute;
	}
	else if (h->hour > 0)
	{
		--h->hour;
		h->minute = 59;
		h->second = 59;
	}
	else return 0;
	return 1;
}
void printClock() {
	Hour h = { 0,1,00 };
	while (stop)
	{
		if (!changetime(&h)) stop = 0;
		gotoXY(10, 4);
		cout << setw(10) << " ";
		gotoXY(12, 4);
		SetColor(15);
		cout <<"Thoi gian: "<< h.hour << ":" << h.minute << ":" << h.second;
		Sleep(1000);
	}
	stop = 0;
	return;
}
bool game_over(List &l) {
	if (stop == 0) {
		return true;
	}
	else {
		for (Point *p = l.pHead->pNext; p != NULL; p = p->pNext) {
			if (p->x == l.pHead->x && p->y == l.pHead->y) {
				return true;
			}
		}
	}
	return false;
}
int startgame(List &l,int &score) {
	stop = 1;
	thread clock;
	clock = thread(printClock);
	system("cls");
	draw_frames();
	gotoXY(17, 2);
	cout << "Diem: " << score;
	int keyInput = RIGHT;
	int tX = 0, tY = 0;
	Prd prd;
	point_random(l, prd);
	while (l.pHead->x < 39 && l.pHead->y < 15 && l.pHead->y>5 && l.pHead->x>2)
	{
		direction(l, keyInput, l.size);
		show_snake(l);
		if (check_coordinate_point(l, score)) {
			Point * p = Create_Point(0, 0);
			Add_Tail(l, p);
			point_random(l, prd);
		}
		if (game_over(l)) {
			deleteList(l.pHead);
			break;
			
		}
		Sleep(150);
		if (_kbhit()) {
			char c = _getch();
			if (c == 's') {
				keyInput = DOWN;
				check_direction(DOWN);
			}
			else if (c == 'd') {
				if (keyInput != RIGHT) {
					keyInput = RIGHT;
					check_direction(RIGHT);

				}
			}
			else if (c == 'a') {
				if (ckLeft) {
					keyInput = LEFT;
					check_direction(LEFT);
				}
			}
			else if (c == 'w') {
				keyInput = UP;
				check_direction(DOWN);
			}
		}
	}
	stop = 0;
	clock.join();
	return 0;
	

}
int Menu(List &l, int &score) {
	SetColor(15);
	for (int i = 20; i < 50; i++) {
		gotoXY(i, 2);
		cout << (char)220;
	}
	for (int i = 20; i <= 49; i++) {
		gotoXY(i, 10);
		cout << (char)223;
	}
	for (int i = 3; i <= 9; i++) {
		gotoXY(20, i);
		cout << (char)221;
	}
	for (int i = 3; i <= 9; i++) {
		gotoXY(49, i);
		cout << (char)222;

	}
	gotoXY(30, 3);
	cout << "Huong dan";
	gotoXY(21, 5);
	cout << "Dieu khien: W A S D";
	gotoXY(21, 6);
	cout << "Luat choi : ";
	gotoXY(22, 7);
	cout << "- Di chuyen ran an cuc moi";
	gotoXY(22, 8);
	cout << "- Ran cham tuong => thua";
	gotoXY(22, 9);
	cout << "- Ran tu can duoi => thua";
	gotoXY(30, 12);
	cout << "Bat dau";
	gotoXY(30, 13);
	cout << "Diem cao";
	gotoXY(27, 12);
	cout << (char)254;
	int flag = 0;
	while (true)
	{
		if (_kbhit()) {
			char c = _getch();
			cout << c;
			if (c == 's' || c == 'w') {
				if (flag == 0)
				{
					gotoXY(27, 12);
					cout << "  ";
					gotoXY(27, 13);
					cout << (char)254;
					flag = 1;
				}
				else {
					gotoXY(27, 13);
					cout << "  ";
					gotoXY(27, 12);
					cout << (char)254;
					flag = 0;
				}

			}
			if (c == '\r') {
				break;
			}
		}
	}
	if (flag == 0) {
		Create_List(l);
		init_snake(l);
		score = 0;
		int a = startgame(l, score);
	
		return a;
	}
}
int main() {
	setDefaultConfig();
	List l;
	int score;
	ShowCur(false);
	int a = Menu(l, score);
	while (true)
	{
		if (a == 0) {
			SetBGColor(19);
			gotoXY(8, 7); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 8); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 9); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 10); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 11); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 12); for (int i = 0; i < 26; i++) cout << " ";
			gotoXY(8, 13); for (int i = 0; i < 26; i++) cout << " ";
			SetColor(15);
			gotoXY(17, 7);
			cout << "Game over";
			SetColor(0);
			gotoXY(18, 9);
			cout << "Diem so";
			gotoXY(21, 10);
			cout << score;
			gotoXY(18, 12);
			cout << "Choi lai";
			gotoXY(18, 13);
			cout << "Thoat";
			gotoXY(16, 12);
			cout << (char)254;
			int flag = 0;
			while (true)
			{

				if (_kbhit()) {
					char c = _getch();
					cout << c;
					if (c == 's' || c == 'w') {
						if (flag == 0)
						{
							gotoXY(16, 12);
							cout << "  ";
							gotoXY(16, 13);
							cout << (char)254;
							flag = 1;
						}
						else {
							gotoXY(16, 13);
							cout << "  ";
							gotoXY(16, 12);
							cout << (char)254;
							flag = 0;
						}
					}
					if (c == '\r') {
						break;
					}
				}
			}
			if (flag == 0) {
				SetBGColor(0);
				system("cls");
				a = Menu(l, score);
			}
			else {
				break;
			}
		}
	}
	return 0;

}