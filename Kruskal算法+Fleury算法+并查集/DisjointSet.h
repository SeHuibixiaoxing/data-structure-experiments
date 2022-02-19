#pragma once
#include <vector>

class DisjointSet
{
	int n;
	std::vector<int> fa;
	std::vector<int> height;
	int setNum;



public:
	DisjointSet(int n);
	int size();
	int getSetNum();
	bool empty();
	int find(int x);
	void merge(int a, int b);
	bool isSame(int a, int b);
	void reset(int n);

};

