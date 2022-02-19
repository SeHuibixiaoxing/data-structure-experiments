#include "draw.h"


//����
void DrawPoint(int x, int y) {
	setfillcolor(BLUE);
	solidcircle(x, y, POINTSIZE);
}

//���ؼ���
void DrawKeyPoint(int x, int y) {
	setfillcolor(YELLOW);
	solidcircle(x, y, POINTSIZE);
}

//�����е�
void DrawAllPoints(std::vector<Point> drawPointSet) {
	for (std::vector<Point>::iterator it = drawPointSet.begin(); it != drawPointSet.end(); ++it) {
		DrawPoint(it->x, it->y);
	}
}

//�����йؼ���
void DrawAllKeyPoints(std::vector<Point> drawKeyPointSet) {
	for (std::vector<Point>::iterator it = drawKeyPointSet.begin(); it != drawKeyPointSet.end(); ++it) {
		DrawPoint(it->x, it->y);
	}
}


//����
void DrawLine(Point& node1, Point& node2) {
	setlinecolor(RED);
	line(node1.x, node1.y, node2.x, node2.y);
}

//��������
void DrawAllLine(std::vector<std::pair<Point, Point>>& drawLineSet) {
	for (std::vector<std::pair<Point, Point>>::iterator it = drawLineSet.begin(); it != drawLineSet.end(); ++it) {
		DrawLine((*it).first, (*it).second);
	}

}

//ˢ��
void refresh(std::vector<Point> drawPointSet, std::vector<Point> drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet) {
	cleardevice();
	DrawAllLine(drawLineSet);
	DrawAllPoints(drawPointSet);
	DrawAllKeyPoints(drawKeyPointSet);
}

void sleep(int milliseconds) {
	Sleep(milliseconds);
}
