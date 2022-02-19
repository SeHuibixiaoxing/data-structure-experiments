#define _CRT_SECURE_NO_WARNINGS

#include "Stack.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <graphics.h>
#include <windows.h>
#include <conio.h>


const int INF = 0x3f3f3f3f;
const double eps = 1e-8;
const int POINTSIZE = 6;
const int WATETIME = 500;
const int FASTTIME = 50;

class Point {
public:
	double x, y;
	int num;
	Point(int num, double x, double y) : x(x), y(y), num(num) {}
	Point() { x = y = 0; num = 0; }
};

class Line {
public:
	Point a, b;
	double theta;
	Line() {}
	Line(Point node1, Point node2) {
		a = node1;
		b = node2;
		theta = atan2(b.y - a.y, b.x - a.x);
	}
};

bool cmp(Line& a, Line& b) {
	return a.theta < b.theta;
}

Point vec(int num, Point node1, Point node2) {
	Point re(num, (node2.x - node1.x), (node2.y - node1.y));
	return re;
}

double cross(Point vec1, Point vec2) {
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

double distance(Point node1, Point node2) {
	return sqrt((node1.x - node2.x) * (node1.x - node2.x) + (node1.y - node2.y) * (node1.y - node2.y));
}


void DrawPoint(int x, int y) {
	setfillcolor(BLUE);
	solidcircle(x, y, POINTSIZE);
}

void DrawKeyPoint(int x, int y) {
	setfillcolor(YELLOW);
	solidcircle(x, y, POINTSIZE);
}

void DrawAllPoints(DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY) {
	Iterator<int> iteratorX = listX.begin();
	Iterator<int> iteratorY = listY.begin();
	for (; iteratorX != listX.end(); ++iteratorX, ++iteratorY) {
		DrawPoint(iteratorX.get(), iteratorY.get());
	}
	DrawPoint(iteratorX.get(), iteratorY.get());
}

void DrawLine(Point& node1, Point& node2, DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY, Point& keyPoint) {
	setlinecolor(RED);
	line(node1.x, node1.y, node2.x, node2.y);
	DrawAllPoints(listX, listY);
	DrawKeyPoint(keyPoint.x, keyPoint.y);
}

void DrawAllLine(Stack<Point> stack, DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY, Point& keyPoint) {
	Point node1 = stack.top();
	stack.pop();
	for (; stack.size() > 0;) {
		Point node2 = stack.top();
		DrawLine(node1, node2, listX, listY, keyPoint);
		stack.pop();
		node1 = node2;
	}
}

void DrawLine(Point& node1, Point& node2, DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY) {
	setlinecolor(RED);
	line(node1.x, node1.y, node2.x, node2.y);
	DrawAllPoints(listX, listY);
}

void ClearLine(Point& node1, Point& node2, DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY, Point& keyPoint) {
	setlinecolor(getbkcolor());
	line(node1.x, node1.y, node2.x, node2.y);
	DrawAllPoints(listX, listY);
	DrawKeyPoint(keyPoint.x, keyPoint.y);
}

void ConvexHull(int n, double x[], double y[], DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY, int drawtime = WATETIME) {
	Point* node = new Point[n];
	Point minNode(0, x[0], y[0]);
	for (int i = 0; i < n; ++i) {
		node[i] = Point(i, x[i], y[i]);
		if (y[i] - minNode.y < 0) {
			minNode = node[i];
		}
		else if ((abs(y[i] - minNode.y) <= eps) && x[i] - minNode.x < 0) {
			minNode = node[i];
		}
	}

	Line* line = new Line[n - 1];
	int tot = 0;

	for (int i = 0; i < n; ++i) {
		if (minNode.num == i) continue;
		line[tot++] = Line(minNode, node[i]);
	}

	std::sort(line, line + tot, cmp);

	Stack<Point> stack;
	stack.push(minNode);

	for (int i = 0; i < n - 1; ++i) {
		Point now = line[i].b;
		DrawKeyPoint(now.x, now.y);
		Sleep(drawtime);

		if (stack.size() == 1) {
			Point tmp = stack.top();
			stack.push(now);

			DrawAllLine(stack, listX, listY, now);
			Sleep(drawtime);
		}
		else {
			while (stack.size() >= 2) {
				Point node2 = stack.top();
				stack.pop();
				Point node1 = stack.top();
				stack.push(node2);

				Point vec1 = vec(-1, node1, node2);
				Point vec2 = vec(-1, node2, now);
				double mul = cross(vec1, vec2);

				if (abs(mul) > eps && mul < 0) {
					Point tmp1 = stack.top();
					stack.pop();
					Point tmp2 = stack.top();
					ClearLine(tmp2, tmp1, listX, listY, now);
					DrawAllLine(stack, listX, listY, now);
					Sleep(drawtime);
				}
				else break;
			}
			Point tmp = stack.top();
			stack.push(now);
			DrawAllLine(stack, listX, listY, now);
			Sleep(drawtime);
		}
		DrawPoint(now.x, now.y);
	}

	Point tmp = stack.top();
	DrawLine(tmp, minNode, listX, listY);
	Sleep(drawtime);
}


void DrawHull(int n, DoubleLinkedList<int>& listX, DoubleLinkedList<int>& listY, int drawtime = WATETIME) {
	double* x = new double[n];
	double* y = new double[n];
	Iterator<int> iteratorX = listX.begin();
	Iterator<int> iteratorY = listY.begin();
	for (int i = 0; i < n; ++i, ++iteratorX, ++iteratorY) {
		x[i] = iteratorX.get();
		y[i] = iteratorY.get();
	}
	ConvexHull(n, x, y, listX, listY, drawtime);
}

void clearInput() {
	while (_kbhit()) {
		char c = _getch();
	}
}

int main() {
	initgraph(1000, 700);


	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("微软雅黑"));
	settextcolor(WHITE);

	outtextxy(120, 200, _T("初始状态：鼠标点击画布画点，D：开始绘制，F：快速绘制"));
	outtextxy(120, 300, _T("完成状态：D：再次绘制，F:再次快速绘制，C：清空绘制"));
	outtextxy(120, 400, _T("         P：继续加点，ESC：退出"));
	outtextxy(420, 500, _T("按任意键继续"));
	_getch();


	setbkcolor(WHITE);
	cleardevice();

	clearInput();
	FlushMouseMsgBuffer();

	DoubleLinkedList<int> listX;
	DoubleLinkedList<int> listY;
	int n = 0;

	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if ((c == 'D' || c == 'd' || c == 'F' || c == 'f') && n >= 3) {

				bool continueDraw = false;

				if(c == 'D' || c == 'd') DrawHull(n, listX, listY);
				else DrawHull(n, listX, listY, FASTTIME);
				clearInput();
				while (true) {
					if (_kbhit()) {
						char a = _getch();
						if (a == 'D' || a == 'd') {
							cleardevice();
							DrawAllPoints(listX, listY);
							DrawHull(n, listX, listY);
							clearInput();
						}
						else if (a == 'F' || a == 'f') {
							cleardevice();
							DrawAllPoints(listX, listY);
							DrawHull(n, listX, listY, FASTTIME);
							clearInput();
						}
						else if (a == 'C' || a == 'c') {
							clearInput();
							break;
						}
						else if (a == 27) {
							clearInput();
							return 0;
						}
						else if (a == 'P' || a == 'p') {
							continueDraw = true;
							clearInput();
							break;
						}
					}
				}
				if (continueDraw) {
					cleardevice();
					DrawAllPoints(listX, listY);
					continue;
				}
				while (!listX.isEmpty()) {
					--n;
					listX.removeBack();
					listY.removeBack();
				}
				cleardevice();
				FlushMouseMsgBuffer(); 
				clearInput();
			}
			else if (c == 27) {
				return 0;
			}
			else if (c == 'C' || c == 'c') {
				while (!listX.isEmpty()) {
					--n;
					listX.removeBack();
					listY.removeBack();
				}
				cleardevice();
				FlushMouseMsgBuffer();
				clearInput();
			}
		}
		else if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				int x = msg.x, y = msg.y;
				Iterator<int> iteratorX = listX.begin();
				Iterator<int> iteratorY = listY.begin();
				bool hasMark = false;
				for (; iteratorX != listX.end(); ++ iteratorX, ++iteratorY) {
					if (iteratorX.get() == x && iteratorY.get() == y) {
						hasMark = true;
						break;
					}
				}
				if (!listX.isEmpty()) {
					if (iteratorX.get() == x && iteratorY.get() == y) {
						hasMark = true;
					}
				}
				if (hasMark) {
					continue;
				}
				DrawPoint(x, y);
				listX.insertBack(x);
				listY.insertBack(y);
				++ n;
			}
		}
	}


	closegraph();
	return 0;
}

