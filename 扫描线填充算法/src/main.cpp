#include "geometry.h"
#include "draw.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <Windows.h>
#include <vector>

const int HIGHTSIZE = 960;
const int WIDTHSIZE = 1280;
const int WATETIME = 5;
const int FASTTIME = 1;

int TIME = WATETIME;

//清空输入缓存
void clearInput() {
	while (_kbhit()) {
		char c = _getch();
	}
}



void scanLinePolygonFilling(const std::vector<Point>& point) {

	class Edge {
	public:
		Line x;
		double nowX, m, minY, maxY;

		Edge* next, *pre;

		Edge(const Point& a, const Point& b) {
			this->next = this->pre = nullptr;
			this->x = Line(Vector(a, b));
			printf("%lf\n", this->x.getK());
			this->m = (double)1.0 / x.getK();
			if (dcmp(a.y - b.y) == -1) {
				this->nowX = a.x;
				this->minY = a.y;
				this->maxY = b.y;
			}
			else {
				this->nowX = b.x;
				this->minY = b.y;
				this->maxY = a.y;
			}
		}

		Edge() {
			this->nowX = this->m = this->minY = this->maxY = 0;
			this->next = this->pre = nullptr;
		}

		void copy(const Edge& edge) {
			this->m = edge.m;
			this->maxY = edge.maxY;
			this->minY = edge.minY;
			this->next = this->pre = nullptr;
			this->nowX = edge.nowX;
			this->x = edge.x;
		}

		void add(int addY = 1) {
			nowX += m;
		}
	};

	class EdgeList {
	public:
		Edge* head;

		EdgeList() {
			head = nullptr;
		}
		
		void insert(Edge edge, Edge* p) {
			Edge* newEdge = new Edge();
			newEdge->copy(edge);

			if (p == nullptr && head != nullptr) {
				newEdge->next = head;
				head->pre = newEdge;
				newEdge->pre = nullptr;
				head = newEdge;
			}
			else if (p == nullptr && head == nullptr) {
				head = newEdge;
				newEdge->next = newEdge->pre = nullptr;
			}
			else {
				newEdge->next = p->next;
				newEdge->pre = p;
				if (p->next != nullptr) {
					p->next->pre = newEdge;
				}
				p->next = newEdge;
			}
		}

		
		void delt(Edge* p)                                                                                        {
			if (p == nullptr) return;
			if (p->pre == nullptr) {
				head = p->next;
			}
			else {
				p->pre->next = p->next;
			}

			if (p->next != nullptr) {
				p->next->pre = p->pre;
			}
			delete p;
		}
	};

	EdgeList edgeList;
	std::vector<Edge> edge;

	for (int i = 1; i < point.size(); ++i) {
		if (dcmp(point[i - 1].x - point[i].x) != 0) {
			edge.push_back(Edge(point[i - 1], point[i]));
		}
	}
	if (dcmp(point[point.size() - 1].x - point[0].y) != 0) {
		edge.push_back(Edge(point[point.size() - 1], point[0]));
	}

	std::sort(edge.begin(), edge.end(), [&](const Edge& a, const Edge& b) {
		int a1 = dcmp(a.minY - b.minY), a2 = dcmp(a.nowX - b.nowX);
		if (a1 == 0 && a2 == 0) {
			Point tmp1 = Point(a.nowX, a.minY);
			Point tmp2 = Point(a.nowX + (a.maxY - a.minY) * a.m, a.maxY);
			Point tmp3 = Point(a.nowX + (b.maxY - b.minY) * b.m, b.maxY);
			return dcmp(cross(tmp1, tmp2, tmp1, tmp3)) == -1;
		}
		else if (a1 == 0) {
			return a2 == -1;
		}

		return a1 == -1;
	});

	for (int i = 0, now = 0; i <= HIGHTSIZE; ++i) {
		if (edgeList.head != NULL) {		

			for (Edge* now = edgeList.head; now != nullptr; now = now->next) {
				now->add();
			}
			
			for (Edge* now = edgeList.head; now != nullptr; ) {
				if (dcmp(i - now->maxY) == 0) {
					Edge* tmp = now->next;
					edgeList.delt(now);
					now = tmp;
				}
				else {
					now = now->next;
				}
			}		

			bool sortTag = true;
			/*while (sortTag) {
				sortTag = false;*/
				for (Edge* now = edgeList.head; now != nullptr && now->next != nullptr; now = now->next) {
					if (dcmp(now->nowX - now->next->nowX) == 1) {
						Edge* tmp1 = now->next->next;
						Edge* tmp2 = now->pre;

						Edge* a1 = now;
						Edge* a2 = now->next;

						if (tmp2 == nullptr) {
							edgeList.head = a2;
						}
						if (a1 != nullptr) {
							a1->next = tmp1;
							a1->pre = a2;
						}
						if (a2 != nullptr) {
							a2->pre = tmp2;
							a2->next = a1;
						}
						if (tmp2 != nullptr) {
							tmp2->next = a2;
						}
						if (tmp1 != nullptr) {
							tmp1->pre = a1;
						}

						sortTag = true;
					}
				}
			//}
			

		}

		for (; (now < edge.size()) && (dcmp(i - edge[now].minY) == 0); ++now) {
			if (edgeList.head == nullptr) {
				edgeList.insert(edge[now], nullptr);
			}
			else if (dcmp(edge[now].nowX - edgeList.head->nowX) == -1) {
				edgeList.insert(edge[now], nullptr);
			}
			else {
				Edge* nowEdge = edgeList.head;
				bool tag = true;
				for (; nowEdge->next != nullptr; nowEdge = nowEdge->next) {
					if ((dcmp(nowEdge->nowX - edge[now].nowX) <= 0) && (dcmp(nowEdge->next->nowX - edge[now].nowX) >= 1)) {
						edgeList.insert(edge[now], nowEdge);
						tag = false;
						break;
					}
				}
				if (tag && dcmp(nowEdge->nowX - edge[now].nowX) <= 0) {
					edgeList.insert(edge[now], nowEdge);
				}
			}			
		}

		for (Edge* nowEdge = edgeList.head; nowEdge != nullptr && nowEdge->next != nullptr; nowEdge = nowEdge->next->next) {
			setlinecolor(BLUE);
			Point a(nowEdge->nowX, i);
			Point b(nowEdge->next->nowX, i);
			DrawLine(a, b);
			Sleep(TIME);
		}
	}
}

int main() {
	initgraph(WIDTHSIZE, HIGHTSIZE);

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


	std::vector<Point> point;

	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if ((c == 'D' || c == 'd' || c == 'F' || c == 'f') && point.size() > 2) {

				bool continueDraw = false;

				if (c == 'D' || c == 'd') {
					TIME = WATETIME;
				}
				else if (c == 'F' || c == 'f') {
					TIME = FASTTIME;
				}

				DrawLine(point[point.size() - 1], point[0]);
				scanLinePolygonFilling(point);

				clearInput();
				while (true) {
					if (_kbhit()) {
						char a = _getch();
						if (a == 'D' || a == 'd') {
							cleardevice();

							DrawAllPoints(point);
							DrawAllLine(point);
							DrawLine(point[point.size() - 1], point[0]);

							TIME = WATETIME;
							scanLinePolygonFilling(point);

							clearInput();
						}
						else if (a == 'F' || a == 'f') {
							cleardevice();

							DrawAllPoints(point);
							DrawAllLine(point);
							DrawLine(point[point.size() - 1], point[0]);

							TIME = FASTTIME;
							scanLinePolygonFilling(point);

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
					DrawAllPoints(point);
					DrawAllLine(point);
					continue;
				}
				point.clear();
				cleardevice();
				FlushMouseMsgBuffer();
				clearInput();
			}
			else if (c == 27) {
				return 0;
			}
			else if (c == 'C' || c == 'c') {
				point.clear();
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
				for (std::vector<Point>::iterator it = point.begin(); it != point.end(); ++it) {
					if (dcmp(it->x - x) == 0 && dcmp(it->y - y) == 0) {
						hasMark = true;
						break;
					}
				}
				if (hasMark) {
					continue;
				}
				DrawPoint(x, y);
				point.push_back(Point(x, y));
				if (point.size() > 1) {
					DrawLine(point[point.size() - 1], point[point.size() - 2]);
				}
			}
		}
	}
	closegraph();

	

	return 0;
}

