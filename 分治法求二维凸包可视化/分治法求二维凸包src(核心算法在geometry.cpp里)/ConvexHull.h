#pragma once

#include <vector>
#include "Point.h"

//�涨ConvexHull��˳ʱ��˳�����У��������Ϲ���ֻ�������˵ĵ㣬�����ڴ����Ӧ�ó����в����������Ӱ��
class ConvexHull
{
private:
	int n;							//͹����С
	int now_rank;					//͹����ǰָ��
	std::vector<Point> point;		//͹�������ж��㣨˳ʱ���Ų�
	void copyPointSet(const std::vector<Point>& pointSet);
	
public:
	ConvexHull();

	Point get(const int& rank) const;		//��ȡ��x����
	//void insert(const Point& x);			//��ĩβ׷�ӵ�x
	//void erase(const int& rank);			//ɾ����

	Point getPre();							//��ȡ��ʱ���ƶ�һ����
	Point getPre(int x);					//��ȡ��ʱ���ƶ�x����
	Point getNext();						//��ȡ˳ʱ���ƶ�һ����
	Point getNext(int x);					//��ȡ˳ʱ���ƶ�һ����
	Point getNow();							//��ȡ��ǰλ�õ�
	int getNowRank();						//��ȡ��ǰλ��
	int getNextRank();						//��ȡ˳ʱ���ƶ�һ��λ��
	int getPreRank();						//��ȡ��ʱ���ƶ�һ��λ��
	int getNextRank(int x);
	int getPreRank(int x);

	void next();							//˳ʱ���ƶ�һ����
	void next(const int& x);				//˳ʱ���ƶ�x����
	void pre();								//��ʱ���ƶ�һ����
	void pre(const int& x);					//��ʱ���ƶ�x����

	void adjust(const int& rank);			//����ǰָ�������rankλ��


	int size();								//���ش�С
	bool empty();							//�п�

	friend ConvexHull GetConvexHull(const std::vector<Point>& pointSet);
	friend ConvexHull MergeSeparateConvexHull(ConvexHull& hull1, ConvexHull& hull2);
	friend ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r);
	friend std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull);
	friend std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull);
};

