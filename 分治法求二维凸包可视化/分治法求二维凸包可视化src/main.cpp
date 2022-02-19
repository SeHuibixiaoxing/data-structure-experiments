#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "geometry.h"
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <utility>
#include "draw.h"



std::vector<Point> drawPointSet;
std::vector<Point> drawKeyPointSet;
std::vector<std::pair<Point, Point>> drawLineSet;


//清空输入缓存
void clearInput() {
	while (_kbhit()) {
		char c = _getch();
	}
}

void DrawHull(std::vector<Point>& point, int TIME = WATETIME) {
	printf("DrawHull has run\n");
	drawLineSet.clear();
	drawKeyPointSet.clear();
	GetConvexHull(point, drawPointSet, drawKeyPointSet, drawLineSet, TIME);
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

	int n = 0;

	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if ((c == 'D' || c == 'd' || c == 'F' || c == 'f')) {

				bool continueDraw = false;

				if (c == 'D' || c == 'd') {
					DrawHull(drawPointSet);
				}
				else {
					DrawHull(drawPointSet, FASTTIME);
				}
				clearInput();
				while (true) {
					if (_kbhit()) {
						char a = _getch();
						if (a == 'D' || a == 'd') {
							cleardevice();
							DrawAllPoints(drawPointSet);
							DrawHull(drawPointSet);
							clearInput();
						}
						else if (a == 'F' || a == 'f') {
							cleardevice();
							DrawAllPoints(drawPointSet);
							DrawHull(drawPointSet, FASTTIME);
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
					DrawAllPoints(drawPointSet);
					continue;
				}
				drawPointSet.clear();
				drawKeyPointSet.clear();
				drawLineSet.clear();
				cleardevice();
				FlushMouseMsgBuffer();
				clearInput();
			}
			else if (c == 27) {
				return 0;
			}
			else if (c == 'C' || c == 'c') {
				drawPointSet.clear();
				drawKeyPointSet.clear();
				drawLineSet.clear();
				cleardevice();
				FlushMouseMsgBuffer();
				clearInput();
			}
		}
		else if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				int x = msg.x, y = msg.y;
				
				bool hasMark = false;
				for (std::vector<Point>::iterator it = drawPointSet.begin(); it != drawPointSet.end(); ++it) {
					if (dcmp(it->x - x) == 0 && dcmp(it->y - y) == 0) {
						hasMark = true;
						break;
					}
				}
				if (hasMark) {
					continue;
				}
				DrawPoint(x, y);
				drawPointSet.push_back(Point(x, y));
			}
		}
	}
	closegraph();
	return 0;

}

