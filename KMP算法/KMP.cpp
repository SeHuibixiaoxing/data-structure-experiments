#define _CRT_SECURE_NO_WARNINGS
 
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

// ����ģʽ��P������next����
std::vector<int>* buildNext(const std::string& P) {
	std::vector<int>* next = new std::vector<int>();
	next->push_back(-1);
	for (int i = 1, j = -1; i < P.size(); ++i) {
		while (j >= 0 && P[j + 1] != P[i]) {
			j = (*next)[j];
		}
		if (P[j + 1] == P[i]) {
			++j;
		}
		next->push_back(j);
	}
	return next;
}

//����ĸ��T��ģʽ��P��next���飬������������λ��, ƥ��ʧ�ܷ���-1
std::vector<int>* KMP(const std::string&T, const std::string& P, std::vector<int>* next = NULL) {
	bool ifDel = false;
	if (next == NULL) {
		next = buildNext(P);
		ifDel = true;
	}
	std::vector<int>* pos = new std::vector<int>();
	for (int i = 0, j = -1; i < T.size(); ++ i) {
		while (j >= 0 && P[j + 1] != T[i]) {
			j = (*next)[j];
		}
		if (P[j + 1] == T[i]) {
			++j;
		}
		if (j == P.size() - 1) {
			pos->push_back(i - j);
			j = (*next)[j];
		}
	}
	if (ifDel) {
		delete next;
	}
	return pos;
}

int main() {
	freopen("C:\\Users\\������\\Downloads\\P3375_11.in", "r", stdin);
	freopen("C:\\Users\\������\\Downloads\\P3375_12.out", "w", stdout);

	std::string P, T;

	std::cin >> T;
	std::cin >> P;

	std::vector<int>* next = buildNext(P);
	std::vector<int>* pos = KMP(T, P, next);

	for (int i = 0; i < (*pos).size(); ++i) {
		std::cout << (*pos)[i] + 1 << std::endl;
	}
	for (int i = 0; i < P.size(); ++i) {
		std::cout << (*next)[i] + 1 << " ";
	}

	return 0;
}



