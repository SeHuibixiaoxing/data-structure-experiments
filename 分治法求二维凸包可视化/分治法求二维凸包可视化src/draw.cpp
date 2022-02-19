#include "draw.h"


//画点
void DrawPoint(int x, int y) {
	setfillcolor(BLUE);
	solidcircle(x, y, POINTSIZE);
}

//画关键点
void DrawKeyPoint(int x, int y) {
	setfillcolor(YELLOW);
	solidcircle(x, y, POINTSIZE);
}

//画所有点
void DrawAllPoints(std::vector<Point> drawPointSet) {
	for (std::vector<Point>::iterator it = drawPointSet.begin(); it != drawPointSet.end(); ++it) {
		DrawPoint(it->x, it->y);
	}
}

//画所有关键点
void DrawAllKeyPoints(std::vector<Point> drawKeyPointSet) {
	for (std::vector<Point>::iterator it = drawKeyPointSet.begin(); it != drawKeyPointSet.end(); ++it) {
		DrawPoint(it->x, it->y);
	}
}


//画线
void DrawLine(Point& node1, Point& node2) {
	setlinecolor(RED);
	line(node1.x, node1.y, node2.x, node2.y);
}

//画所有线
void DrawAllLine(std::vector<std::pair<Point, Point>>& drawLineSet) {
	for (std::vector<std::pair<Point, Point>>::iterator it = drawLineSet.begin(); it != drawLineSet.end(); ++it) {
		DrawLine((*it).first, (*it).second);
	}

}

//刷新
void refresh(std::vector<Point> drawPointSet, std::vector<Point> drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet) {
	cleardevice();
	DrawAllLine(drawLineSet);
	DrawAllPoints(drawPointSet);
	DrawAllKeyPoints(drawKeyPointSet);
}

void sleep(int milliseconds) {
	Sleep(milliseconds);
}
