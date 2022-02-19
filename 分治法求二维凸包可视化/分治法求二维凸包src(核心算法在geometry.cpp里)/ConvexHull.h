#pragma once

#include <vector>
#include "Point.h"

//规定ConvexHull按顺时针顺序排列，三点以上共线只保留两端的点，可能在大多数应用场景中不会产生严重影响
class ConvexHull
{
private:
	int n;							//凸包大小
	int now_rank;					//凸包当前指向
	std::vector<Point> point;		//凸包内所有顶点（顺时针排布
	void copyPointSet(const std::vector<Point>& pointSet);
	
public:
	ConvexHull();

	Point get(const int& rank) const;		//获取第x个点
	//void insert(const Point& x);			//在末尾追加点x
	//void erase(const int& rank);			//删除点

	Point getPre();							//获取逆时针移动一个点
	Point getPre(int x);					//获取逆时针移动x个点
	Point getNext();						//获取顺时针移动一个点
	Point getNext(int x);					//获取顺时针移动一个点
	Point getNow();							//获取当前位置点
	int getNowRank();						//获取当前位置
	int getNextRank();						//获取顺时针移动一个位置
	int getPreRank();						//获取逆时针移动一个位置
	int getNextRank(int x);
	int getPreRank(int x);

	void next();							//顺时针移动一个点
	void next(const int& x);				//顺时针移动x个点
	void pre();								//逆时针移动一个点
	void pre(const int& x);					//逆时针移动x个点

	void adjust(const int& rank);			//将当前指向调整到rank位置


	int size();								//返回大小
	bool empty();							//判空

	friend ConvexHull GetConvexHull(const std::vector<Point>& pointSet);
	friend ConvexHull MergeSeparateConvexHull(ConvexHull& hull1, ConvexHull& hull2);
	friend ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r);
	friend std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull);
	friend std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull);
};

