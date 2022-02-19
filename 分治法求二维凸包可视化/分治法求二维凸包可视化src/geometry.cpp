#include "geometry.h"


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
ConvexHull MergeSeparateConvexHull(ConvexHull& hull1_tmp, ConvexHull& hull2_tmp, std::vector<Point>& drawPointSet, std::vector<Point>&  drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet) {
	ConvexHull hull1;
	ConvexHull hull2;

	////=====绘制部分=====
	//for (int i = 0; i < hull1_tmp.size(); ++i) {
	//	drawKeyPointSet.push_back(hull1_tmp.point[i]);
	//}
	//for (int i = 0; i < hull1_tmp.size(); ++i) {
	//	drawKeyPointSet.push_back(hull1_tmp.point[i]);
	//}
	////=================

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

			////=====绘制部分=====
			//drawLineSet.push_back(std::make_pair(hull1.point[0], hull2.point[1]));
			//refresh(drawPointSet, drawKeyPointSet, drawLineSet);
			////=================

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

				////=====绘制部分=====
				//drawLineSet.erase(remove(drawLineSet.begin(), drawLineSet.end(), std::make_pair(hull2.point[0], hull2.point[1])));
				//drawLineSet.erase(remove(drawLineSet.begin(), drawLineSet.end(), std::make_pair(hull2.point[1], hull2.point[0])));
				//drawLineSet.push_back(std::make_pair(re.point[0], re.point[1]));
				//refresh(drawPointSet, drawKeyPointSet, drawLineSet);
				////=================

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

				////=====绘制部分=====
				//drawLineSet.erase(remove(drawLineSet.begin(), drawLineSet.end(), std::make_pair(hull2.point[0], hull2.point[1])));
				//drawLineSet.erase(remove(drawLineSet.begin(), drawLineSet.end(), std::make_pair(hull2.point[1], hull2.point[0])));
				//drawLineSet.push_back(std::make_pair(re.point[0], re.point[1]));
				//drawLineSet.push_back(std::make_pair(re.point[1], re.point[2]));
				//drawLineSet.push_back(std::make_pair(re.point[2], re.point[0]));
				//refresh(drawPointSet, drawKeyPointSet, drawLineSet);
				////=================

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
		ConvexHull tmp = MergeSeparateConvexHull(hulltmp, hull2, drawPointSet, drawKeyPointSet, drawLineSet);
		hulltmp.point[0] = hull1.point[1];
		re = MergeSeparateConvexHull(hulltmp, tmp, drawPointSet, drawKeyPointSet, drawLineSet);
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


	////=====绘制部分=====
	//for (int i = 0; i < hull1_tmp.size(); ++i) {
	//	drawKeyPointSet.pop_back();
	//}
	//for (int i = 0; i < hull1_tmp.size(); ++i) {
	//	drawKeyPointSet.pop_back();
	//}
	////=================

	return re;
}

void addDrawHull(ConvexHull& hull, std::vector<std::pair<Point, Point>>& drawLineSet) {
	for (int i = 0; i < hull.size(); hull.next(), ++i) {
		drawLineSet.push_back(std::make_pair(hull.getNow(), hull.getNext()));
	}
}
void clearDrawHull(ConvexHull& hull, std::vector<std::pair<Point, Point>>& drawLineSet) {
	for (int i = 0; i < hull.size(); hull.next(), ++i) {
		drawLineSet.erase(remove(drawLineSet.begin(), drawLineSet.end(), std::make_pair(hull.getNow(), hull.getNext())));
	}
}

//计算点集[l, r]凸包
ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r, std::vector<Point>& drawPointSet, std::vector<Point>& drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet, int milliseconds) {
	if (l == r) {
		ConvexHull re;
		std::vector<Point> tmp;
		tmp.push_back(pointSet[l]);			
		re.copyPointSet(tmp);
		return re;
	}
	int mid = (l + r) >> 1;
	ConvexHull hull1 = GetConvexHull(pointSet, l, mid, drawPointSet, drawKeyPointSet, drawLineSet, milliseconds);
	if (hull1.size() > 1) {
		addDrawHull(hull1, drawLineSet);
		refresh(drawPointSet, drawKeyPointSet, drawLineSet);
		sleep(milliseconds);
	}
	
	ConvexHull hull2 = GetConvexHull(pointSet, mid + 1, r, drawPointSet, drawKeyPointSet, drawLineSet, milliseconds);
	if (hull2.size() > 1) {
		addDrawHull(hull2, drawLineSet);
		refresh(drawPointSet, drawKeyPointSet, drawLineSet);
		sleep(milliseconds);
	}

	if (hull1.size() > 1) {
		clearDrawHull(hull1, drawLineSet);
	}
	if (hull2.size() > 1) {
		clearDrawHull(hull2, drawLineSet);
	}
	refresh(drawPointSet, drawKeyPointSet, drawLineSet);

	return MergeSeparateConvexHull(hull1, hull2, drawPointSet, drawKeyPointSet, drawLineSet);
}

ConvexHull GetConvexHull(const std::vector<Point>& pointSet, std::vector<Point>& drawPointSet, std::vector<Point>& drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet, int milliseconds) {
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

	ConvexHull re = GetConvexHull(pointSetFinal, 0, pointSetFinal.size() - 1, drawKeyPointSet, drawPointSet, drawLineSet, milliseconds);
	addDrawHull(re, drawLineSet);
	refresh(drawPointSet, drawKeyPointSet, drawLineSet);

	return re;
}


