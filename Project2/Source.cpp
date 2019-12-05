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
using namespace std;

#define UP 1072 
#define DOWN 1080 
#define LEFT  1075
#define RIGHT 1077
#define FRAMETOP 3
#define FRAMEBOTTOM 15
#define FRAMELEFT 3
#define FRAMERIGHT 43
bool ckUp = false;
bool ckDown = false;
bool ckLeft = false;
bool ckRight = false;
struct point {
	int x;
	int y;
	struct point *pNext;
};
typedef struct point Point;
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
Point *Create_Point(int x,int y) {
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
	while (x>10)
	{
		Point *p = Create_Point(x, y);
		Add_Tail(l, p);
		x--;		
	}
	



}
void show_snake(List l) {
	for (Point *p = l.pHead; p != NULL; p = p->pNext) {
		if (p ==l.pHead) {
		
			gotoXY(p->x, p->y);
			cout << (char)233;
		}
		else
		{	
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
		ckLeft = ckRight= false;
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
		Point * pUp = Create_Point(xUp, yUp-1);
		Add_Head(l, pUp);

	}
}
void event_move(int &input) {
	int key = inputKey();
	input = key;
}
Prd poin_random() {
	srand(time(NULL));
	int x = 15 + 1 + rand() % (39 - 15 - 1);
	int y = 5 + 1 + rand() % (15 - 5 - 1);
	Prd prd;
	prd.x = x;
	prd.y = y;
	gotoXY(x, y);
	cout << "$";
	return prd;

}
bool check_coordinate_point(List &l,Prd prd) {
	if (l.pHead->x == prd.x && l.pHead->y == prd.y) {
		return true;
	}
	else {
		return false;
	}


}
int main() {
	List l;
	Create_List(l);
	init_snake(l);
	ShowCur(false);
	draw_frames();
	int keyInput = RIGHT;
	int tX=0, tY=0;
	Prd prd = poin_random();

	while (l.pHead->x < 39 && l.pHead->y < 15 && l.pHead ->y>5) 
	{	
		direction(l, keyInput,l.size);
		show_snake(l);
		if (check_coordinate_point(l, prd)) {
			Point * p = Create_Point(0, 0);
			Add_Tail(l, p);
			prd = poin_random();
			
			
		}
		Sleep(50);
		if (_kbhit()) {
			char c = _getch();
			if (c == 's') {
				keyInput = DOWN;
				check_direction(DOWN);
			}else if (c == 'd') {
				if (keyInput != RIGHT) {
					keyInput = RIGHT;
					check_direction(RIGHT);
				}
			}else if (c == 'a') {			
				if (ckLeft) {
					keyInput = LEFT;
					check_direction(LEFT);
				}				
			}else if (c == 'w') {
				keyInput = UP;
				check_direction(DOWN);
			}
		}
		
	}
	_getch();
	return 0;

}