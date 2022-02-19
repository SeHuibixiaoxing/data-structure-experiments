#pragma once
#include "Point.h"
#include <vector>
#include <graphics.h>

const int POINTSIZE = 6;

//����
void DrawPoint(int x, int y);

//���ؼ���
void DrawKeyPoint(int x, int y);

//�����е�
void DrawAllPoints(std::vector<Point> drawPointSet);

//�����йؼ���
void DrawAllPoints(std::vector<Point> drawKeyPointSet);


//����
void DrawLine(Point& node1, Point& node2);

//��������
void DrawAllLine(std::vector<std::pair<Point, Point>>& drawLineSet);
void DrawAllLine(std::vector<Point>& drawPointSet);


//ˢ��
void refresh(std::vector<Point> drawPointSet, std::vector<Point> drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet);

void sleep(int milliseconds);