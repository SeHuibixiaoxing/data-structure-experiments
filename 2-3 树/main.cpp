#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "TwoThreeTree.h"

//#define DEBUG_MODE

int main() {

	TwoThreeTree<int> tree;
	tree.insert(8);
	tree.insert(6);
	tree.insert(12);
	tree.insert(14);
	tree.insert(1);
	tree.insert(7);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});
	tree.insert(9);
	tree.insert(10);
	tree.insert(13);
	tree.insert(185);
	tree.insert(-10);
	tree.insert(77);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});
	tree.insert(36);
	tree.insert(55);
	tree.insert(11);
	tree.insert(33);
	tree.insert(-20);
	tree.insert(-88);
	tree.insert(76);
	tree.insert(23);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});

	tree.delt(12);
	tree.delt(8);
	tree.delt(14);
	tree.delt(1);
	tree.delt(-20);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});
	tree.delt(6);
	tree.delt(10);
	tree.delt(36);
	tree.delt(23);
	tree.delt(77);
	tree.delt(33);
	tree.delt(185);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});
	tree.delt(-88);
	tree.delt(11);
	tree.delt(9);
	tree.delt(55);
	tree.delt(7);
	tree.delt(76);
	tree.delt(13);inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});

	tree.insert(-10);
	tree.delt(-10);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});

	tree.insert(185);
	tree.insert(-88);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});
	tree.insert(33);
	tree.insert(22);
	tree.insert(36);
	tree.insert(23);
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});


	printf("%d\n", tree.size());
	inorderTraversal(tree, [](int data, int cnt) {
		printf("data:%d, cnt:%d\n", data, cnt);
		});




	return 0;
}
