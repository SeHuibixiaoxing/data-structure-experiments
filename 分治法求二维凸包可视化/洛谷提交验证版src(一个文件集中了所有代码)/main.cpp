
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class Point {
public:
	double x, y;
	Point(const double& x, const double& y):x(x), y(y) {}
	Point();
};

Point::Point() {
	this->x = this->y = 0;
}


class Vector
{
public:
	Point s, e;
	Vector(const Point& s, const Point& e) :s(s), e(s){}
	Vector(const double& x1, const double& y1, const double& x2, const double& y2);
	Vector() {}
};

Vector::Vector(const double& x1, const double& y1, const double& x2, const double& y2)
{
	s = Point(x1, y1);
	e = Point(x2, y2);
}


class Line
{
private:
	double k, b, angle;
	Vector vec;

public:
	Line(const Point& a, const Point& b);
	Line(const double& k, const double& b);
	Line(const Vector& vec);
	Line();

	double getY(const double& x);
	double getX(const double& y);
	double getK();
	double getB();
};
Line::Line(const Point& a, const Point& b) {
	vec = Vector(a, b);
	this->angle = atan2(b.y - a.y, b.x - a.x);
	this->k = tan(angle);
	this->b = b.y - b.x * k;
}

Line::Line(const double& k, const double& b)
{
	this->k = k;
	this->b = b;
	this->angle = atan(k);
	this->vec = Vector(1, k + b, 0, b);
}

Line::Line(const Vector& vec)
{
	Line(vec.s, vec.e);
}

Line::Line()
{
	k = b = angle = 0;
}

double Line::getY(const double& x) {
	return this->k * x + this->b;
}

double Line::getX(const double& y) {
	return (y - this->b) / this->k;
}

double Line::getK() {
	return this->k;
}

double Line::getB() {
	return this->b;
}

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


void ConvexHull::copyPointSet(const std::vector<Point>& pointSet)
{
	this->point = pointSet;
	n = pointSet.size();
	now_rank = 0;
}

ConvexHull::ConvexHull()
{
	n = now_rank = 0;
	point.clear();
}

Point ConvexHull::get(const int& rank) const {
	return point[rank];
}

Point ConvexHull::getPre()
{
	return this->point[(this->now_rank - 1 + n) % n];
}

Point ConvexHull::getPre(int x)
{
	while (x > n) x -= n;
	return this->point[(this->now_rank - (x % n) + n) % n];
}

Point ConvexHull::getNext()
{
	return this->point[(this->now_rank + 1) % n];
}

Point ConvexHull::getNext(int x)
{
	return this->point[(this->now_rank + (x % n) + n) % n];
}

Point ConvexHull::getNow()
{
	return this->point[this->now_rank];
}

int ConvexHull::getNowRank()
{
	return this->now_rank;
}

int ConvexHull::getNextRank()
{
	return (this->now_rank + 1) % n;
}

int ConvexHull::getPreRank()
{
	return (this->now_rank - 1 + n) % n;
}

int ConvexHull::getNextRank(int x)
{
	return (this->now_rank + (x % n) + n) % n;
}

int ConvexHull::getPreRank(int x)
{
	return (this->now_rank - (x % n) + n) % n;
}

//void ConvexHull::insert(const Point& x) {
//
//}
//
//void ConvexHull::erase(const int& rank) {
//
//}

void ConvexHull::next() {
	this->now_rank = (this->now_rank + 1) % n;
}

void ConvexHull::next(const int& x) {
	this->now_rank = (this->now_rank + (x % n)) % n;
}

void ConvexHull::pre() {
	this->now_rank = (this->now_rank - 1 + n) % n;
}

void ConvexHull::pre(const int& x) {
	this->now_rank = (this->now_rank - (x % n) + n) % n;
}

void ConvexHull::adjust(const int& rank) {
	this->now_rank = rank;
}

int ConvexHull::size() {
	return n;
}

bool ConvexHull::empty() {
	return n == 0;
}



double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);	//计算直线s1e1与直线s2e2的叉积
double doubleDistance(const Point& a, const Point& b);					//计算点a到点b距离的平方
double distance(const Point& a, const Point& b);						//计算点a到点b距离
int dcmp(double x);
double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);
double doubleDistance(const Point& a, const Point& b);
double distance(const Point& a, const Point& b);
bool Collinear(const Point& p1, const Point& p2, const Point& p3);
std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull);
std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull);
ConvexHull MergeSeparateConvexHull(ConvexHull& hull1, ConvexHull& hull2);
ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r);
ConvexHull GetConvexHull(const std::vector<Point>& pointSet);

const double eps = 1e-10;

int dcmp(double x) {
	if (fabs(x) < eps) {
		return 0;
	}
	else if(x < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2) {
	double x1 = e1.x - s1.x;
	double y1 = e1.y - s1.y;
	double x2 = e2.x - s2.x;
	double y2 = e2.y - s2.y;
	return x1 * y2 - y1 * x2;
}

double doubleDistance(const Point& a, const Point& b) {
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	return dx * dx + dy * dy;
}

double distance(const Point& a, const Point& b) {
	return sqrt(doubleDistance(a, b));
}

//判断三点是否共线
bool Collinear(const Point& p1, const Point& p2, const Point& p3) {
	Line l1(p1, p2), l2(p2, p3);
	return dcmp(l1.getK() - l2.getK()) == 0;
}

//求一条点到凸包的全部切线,返回全部切点在hull中的位置
std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull) {
	std::vector<int> re;
	int n = hull.size();
	for (int i = 0; i < n; ++i, hull.next()) {
		if (dcmp(cross(point, hull.getNow(), point, hull.getPre()) * cross(point, hull.getNow(), point, hull.getNext())) >= 0) {
				 re.push_back(hull.now_rank);			
		}
	}
	return re;
}

//求一条点到凸包的全部切线,返回全部切点
std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull) {
	std::vector<int> rank = TangentPointRank(point, hull);
	std::vector<Point> re;
	int n = rank.size();
	for (int i = 0; i < n; ++i) {
		re.push_back(hull.point[rank[i]]);
	}
	return re;
}


//合并两个分离的凸包
ConvexHull MergeSeparateConvexHull(ConvexHull& hull1_tmp, ConvexHull& hull2_tmp) {
	ConvexHull hull1;
	ConvexHull hull2;
	if (hull1_tmp.size() > hull2_tmp.size()) {
		hull1 = hull2_tmp;
		hull2 = hull1_tmp;
	}
	else {
		hull1 = hull1_tmp;
		hull2 = hull2_tmp;
	}
	ConvexHull re;
	if (hull1.size() == 1) {
		if (hull2.size() == 1) {
			re.point.push_back(hull1.point[0]);
			re.point.push_back(hull2.point[0]);
			re.n = 2;
			re.now_rank = 0;
		}
		else if (hull2.size() == 2) {
			Point& now = hull1.point[0];
			Point& p1 = hull2.point[0];
			Point& p2 = hull2.point[1];
			//如果三点共线
			if (Collinear(now, p1, p2)) {
				std::vector<Point> tmp;
				tmp.push_back(now);
				tmp.push_back(p1);
				tmp.push_back(p2);
				std::sort(tmp.begin(), tmp.end(), [](const Point& p1, const Point& p2) {
					return (dcmp(p1.x - p2.x) == 0) ? (dcmp(p1.y - p2.y) == -1) : (dcmp(p1.x - p2.x) == -1);
					});
				re.point.push_back(tmp[0]);
				re.point.push_back(tmp[2]);
				re.n = 2;
				re.now_rank = 0;
			}
			else {
				if (dcmp(cross(now, p1, p1, p2)) == -1) {
					re.point.push_back(hull1.point[0]);
					re.point.push_back(hull2.point[0]);
					re.point.push_back(hull2.point[1]);
				}
				else {
					re.point.push_back(hull2.point[1]);
					re.point.push_back(hull2.point[0]);
					re.point.push_back(hull1.point[0]);
				}
				re.n = 3;
				re.now_rank = 0;
			}
		}
		else {
			int p1Rank = -1, p2Rank = -1, hull2_size = hull2.size();
			Point& now = hull1.point[0];
			//求切点集合
			std::vector<int> rank = TangentPointRank(now, hull2);
			//没有切点
			if (rank.size() == 0) {
				re = hull2;
			}
			else {
				//如果点在凸包上，忽略
				int n2 = hull2.size();
				for (int i = 0; i < n2; ++i, hull2.next()) {
					if (Collinear(now, hull2.getNow(), hull2.getNext())) {
						re = hull2;
						return re;
					}
				}

				//确定一个切点，尝试找到下一个不共线的切点。因为hull2.size>2，必然不是直线(已经缩为两个点)，且由于点在凸包外，必有两个切点
				p1Rank = rank[0], p2Rank = -1;
				Point p1 = hull2.point[p1Rank];
				int rank_size = rank.size();

				for (int i = 1; i < rank_size; ++i) {
					if (!Collinear(now, p1, hull2.point[rank[i]])) {
						p2Rank = rank[i];
					}
				}

				Point p2 = hull2.point[p2Rank];

				if (dcmp(cross(now, p1, now, p2)) == 1) {
					std::swap(p1Rank, p2Rank);
				}

				re.n = 0;

				p1 = hull2.point[p1Rank];
				p2 = hull2.point[p2Rank];
				hull2.adjust(p1Rank);

				re.point.push_back(now);
				++re.n;
				for (; hull2.now_rank != p2Rank; hull2.next()) {
					if (re.size() >= 2 && Collinear(re.point[re.size() - 2], re.point[re.size() - 1], hull2.getNow())) {
						re.point.pop_back();
						--re.n;
					}
					re.point.push_back(hull2.getNow());
					++re.n;
				}
				re.point.push_back(hull2.getNow());
				++re.n;
				re.now_rank = 0;
			}
		}
	}
	else if (hull1.size() == 2 && hull2.size() == 2 && Collinear(hull1.point[0], hull1.point[1], hull2.point[0]) && Collinear(hull1.point[1], hull2.point[0], hull2.point[1])) {
		std::vector<Point> tmp;
		tmp.push_back(hull1.point[0]);
		tmp.push_back(hull1.point[1]);
		tmp.push_back(hull2.point[0]);
		tmp.push_back(hull2.point[1]);
		std::sort(tmp.begin(), tmp.end(), [](const Point& p1, const Point& p2) {
			return (dcmp(p1.x - p2.x) == 0) ? (dcmp(p1.y - p2.y) == -1) : (dcmp(p1.x - p2.x) == -1);
			});
		re.point.push_back(tmp[0]);
		re.point.push_back(tmp[3]);
		re.n = 3;
		re.now_rank = 0;
	}
	else if (hull1.size() == 2 && hull2.size() == 2) {
		ConvexHull hulltmp;
		hulltmp.n = 1; 
		hulltmp.now_rank = 0;
		hulltmp.point.push_back(hull1.point[0]);
		ConvexHull tmp = MergeSeparateConvexHull(hulltmp, hull2);
		hulltmp.point[0] = hull1.point[1];
		re = MergeSeparateConvexHull(hulltmp, tmp);
	}
	else {
		int n1 = hull1.size(), n2 = hull2.size();

		int p1Rank, p2Rank;

		hull1.adjust(0);
		Point p1 = hull1.getNow();
		p1Rank = hull1.getNowRank();
		for (int i = 0; i < n1;++ i, hull1.next()) {
			const Point& now = hull1.getNow();
			if (dcmp(p1.x - now.x) < 0) {
				p1 = now;
				p1Rank = hull1.getNowRank();
			}
		}

		hull2.adjust(0);
		Point p2 = hull2.getNow();
		p2Rank = hull2.getNowRank();
		for (int i = 0; i < n2; ++i, hull2.next()) {
			const Point& now = hull2.getNow();
			if (dcmp(p2.x - now.x) < 0) {
				p2 = now;
				p2Rank = hull2.getNowRank();
			}
		}

		if (dcmp(p1.x - p2.x) == 1) {
			std::swap(hull1, hull2);
			std::swap(p1Rank, p2Rank);
			std::swap(p1, p2);
			std::swap(n1, n2);
		}

		hull2.adjust(0);
		p2 = hull2.getNow();
		p2Rank = hull2.getNowRank();
		for (int i = 0; i < n2; ++i, hull2.next()) {
			const Point& now = hull2.getNow();
			if (dcmp(p2.x - now.x) > 0) {
				p2 = now;
				p2Rank = hull2.getNowRank();
			}
		}


		//hull1逆时针走，hull2顺时针走
		bool hull1Walk = false;

		int p1RankTop, p2RankTop;
		int p1RankBtm, p2RankBtm;

		hull1.adjust(p1Rank);
		hull2.adjust(p2Rank);
		p1 = hull1.getNow();
		p2 = hull2.getNow();
		while (true) {
			if (hull1Walk) {
				while (dcmp(cross(p2, hull1.getNow(), p2, hull1.getPre()) * cross(p2, hull1.getNow(), p2, hull1.getNext())) == -1 || 
					dcmp(cross(p2, hull1.getNow(), hull1.getNow(), hull1.getPre())) == -1) {
					hull1.pre();
				}
				p1 = hull1.getNow();
				if (dcmp(cross(p1, hull2.getNow(), p1, hull2.getPre()) * cross(p1, hull2.getNow(), p1, hull2.getNext())) > -1 && 
					dcmp(cross(p1, hull2.getNow(), hull2.getNow(), hull2.getNext())) < 1) {
					p1RankTop = hull1.getNowRank();
					p2RankTop = hull2.getNowRank();
					break;
				}
			}
			else {
				while (dcmp(cross(p1, hull2.getNow(), p1, hull2.getNext()) * cross(p1, hull2.getNow(), p1, hull2.getPre())) == -1 ||
					dcmp(cross(p1, hull2.getNow(), hull2.getNow(), hull2.getNext())) == 1) {
					hull2.next();
				}
				p2 = hull2.getNow();
				if (dcmp(cross(p2, hull1.getNow(), p2, hull1.getPre()) * cross(p2, hull1.getNow(), p2, hull1.getNext())) > -1 &&
					dcmp(cross(p2, hull1.getNow(), hull1.getNow(), hull1.getPre())) > -1) {
					p1RankTop = hull1.getNowRank();
					p2RankTop = hull2.getNowRank();
					break;
				}
			}
			hull1Walk ^= 1;
		}

		//hull1顺时针走，hull2逆时针走
		hull1.adjust(p1Rank);
		hull2.adjust(p2Rank);
		p1 = hull1.getNow();
		p2 = hull2.getNow();
		hull1Walk = false;
		while (true) {
			if (hull1Walk) {
				while (dcmp(cross(p2, hull1.getNow(), p2, hull1.getPre()) * cross(p2, hull1.getNow(), p2, hull1.getNext())) == -1 || 
					dcmp(cross(p2, hull1.getNow(), hull1.getNow(), hull1.getNext())) == 1) {
					hull1.next();
				}
				p1 = hull1.getNow();
				if (dcmp(cross(p1, hull2.getNow(), p1, hull2.getPre()) * cross(p1, hull2.getNow(), p1, hull2.getNext())) > -1 &&
					dcmp(cross(p1, hull2.getNow(), hull2.getNow(), hull2.getPre())) > -1) {
					p1RankBtm = hull1.getNowRank();
					p2RankBtm = hull2.getNowRank();
					break;
				}
			}
			else {
				while (dcmp(cross(p1, hull2.getNow(), p1, hull2.getNext()) * cross(p1, hull2.getNow(), p1, hull2.getPre())) == -1 || 
					dcmp(cross(p1, hull2.getNow(), hull2.getNow(), hull2.getPre())) == -1) {
					hull2.pre();
				}
				p2 = hull2.getNow();
				if (dcmp(cross(p2, hull1.getNow(), p2, hull1.getPre()) * cross(p2, hull1.getNow(), p2, hull1.getNext())) > -1 &&
					dcmp(cross(p2, hull1.getNow(), hull1.getNow(), hull1.getNext())) < 1) {
					p1RankBtm = hull1.getNowRank();
					p2RankBtm = hull2.getNowRank();
					break;
				}
			}
			hull1Walk ^= 1;
		}

		re.point.push_back(hull1.point[p1RankTop]);
		++re.n;
		re.point.push_back(hull2.point[p2RankTop]);
		++re.n;
		hull2.adjust(p2RankTop);
		if (p2RankTop != p2RankBtm) {
			hull2.next();
			for (; hull2.getNowRank() != p2RankBtm; hull2.next()) {
				if (Collinear(re.point[re.size() - 2], re.point[re.size() - 1], hull2.getNow())) {
					re.point.pop_back();
					--re.n;
				}
				re.point.push_back(hull2.getNow());
				++re.n;
			}
			re.point.push_back(hull2.point[p2RankBtm]);
			++re.n;
		}
		
		if (p1RankTop != p1RankBtm) {
			hull1.adjust(p1RankBtm);
			if (Collinear(re.point[re.size() - 2], re.point[re.size() - 1], hull1.getNow())) {
				re.point.pop_back();
				--re.n;
			}
			re.point.push_back(hull1.getNow());
			++re.n;
			hull1.next();
			for (; hull1.getNowRank() != p1RankTop; hull1.next()) {
				if (Collinear(re.point[re.size() - 2], re.point[re.size() - 1], hull1.getNow())) {
					re.point.pop_back();
					--re.n;
				}
				re.point.push_back(hull1.getNow());
				++re.n;
			}
		}
		re.now_rank = 0;
	}
	return re;
}

//计算点集[l, r]凸包
ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r) {
	if (l == r) {
		ConvexHull re;
		std::vector<Point> tmp;
		tmp.push_back(pointSet[l]);			
		re.copyPointSet(tmp);
		return re;
	}
	int mid = (l + r) >> 1;
	ConvexHull hull1 = GetConvexHull(pointSet, l, mid);
	ConvexHull hull2 = GetConvexHull(pointSet, mid + 1, r);
	return MergeSeparateConvexHull(hull1, hull2);

}

ConvexHull GetConvexHull(const std::vector<Point>& pointSet) {
	std::vector<Point> pointSetTemp = pointSet;
	std::sort(pointSetTemp.begin(), pointSetTemp.end(), [](const Point& p1, const Point& p2) {
		return (dcmp(p1.x - p2.x) == 0) ? (dcmp(p1.y - p2.y) == -1) : (dcmp(p1.x - p2.x) == -1);
		});
	std::vector<Point> pointSetFinal;
	pointSetFinal.push_back(pointSetTemp[0]);
	for (std::vector<Point>::iterator it = pointSetTemp.begin() + 1; it != pointSetTemp.end(); ++it) {
		if (dcmp(it->x - (it - 1)->x) == 0 && dcmp(it->y - (it - 1)->y) == 0) {
			continue;
		}
		pointSetFinal.push_back(*it);
	}

	return GetConvexHull(pointSetFinal, 0, pointSetFinal.size() - 1);
}

int main() {
	int n;
	scanf("%d", &n);
	std::vector<Point> point;
	for (int i = 0; i < n; ++i) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		point.push_back(Point(x, y));
	}
	ConvexHull ans = GetConvexHull(point);
	double sum = 0;
	ans.adjust(0);
	for (; ans.getNextRank() != 0; ans.next()) {
		sum += distance(ans.getNow(), ans.getNext());
	}
	sum += distance(ans.getNow(), ans.getNext());

	printf("%.2lf", sum);
}

