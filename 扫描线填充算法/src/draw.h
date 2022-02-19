#pragma once
#include "Point.h"
#include <vector>
#include <graphics.h>

const int POINTSIZE = 6;

//画点
void DrawPoint(int x, int y);

//画关键点
void DrawKeyPoint(int x, int y);

//画所有点
void DrawAllPoints(std::vector<Point> drawPointSet);

//画所有关键点
void DrawAllPoints(std::vector<Point> drawKeyPointSet);


//画线
void DrawLine(Point& node1, Point& node2);

//画所有线
void DrawAllLine(std::vector<std::pair<Point, Point>>& drawLineSet);
void DrawAllLine(std::vector<Point>& drawPointSet);


//刷新
void refresh(std::vector<Point> drawPointSet, std::vector<Point> drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet);

void sleep(int milliseconds);