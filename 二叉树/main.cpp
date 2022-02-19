#define _CRT_SECURE_NO_WARNINGS

#include "BinaryTree.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>


int main() {
	freopen("D:\\材料\\学堂课程资料\\大二上\\数据结构\\作业\\08 二叉树\\二叉树\\data.txt", "r", stdin);

	std::vector<int> preS, midS;
	int n;

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int tmp;
		std::cin >> tmp;
		preS.push_back(tmp);
	}
	for (int i = 0; i < n; ++i) {
		int tmp;
		std::cin >> tmp;
		midS.push_back(tmp);
	}

	BinaryTree<int> tree;
	tree.creatPreMid(preS, midS, preS);

	preorderTraversal(tree, [](int val) {
		printf("%d ", val);
		});
	printf("\n");
	inorderTraversal(tree, [](int val) {
		printf("%d ", val);
		});
	printf("\n");
	postorderTraversal(tree, [](int val) {
		printf("%d ", val);
		});
}
