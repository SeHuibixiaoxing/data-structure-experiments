#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "AVL.h"
#include <queue>


int main() {

	AVL<int> avl;

	//printf("输入初始元素个数:\n");
	//int n;
	//scanf("%d", &n);
	//printf("输入初始元素:\n");
	//for (int i = 0; i < n; ++i) {
	//	int tmp;
	//	scanf("%d", &tmp);
	//	avl.insert(tmp);
	//}
	//inorderTraversal(avl, [](int val, int cnt) {
	//	printf("value = %d, cnt = %d\n", val, cnt);
	//	});
	//while (true) {
	//	printf("1:插入;2:删除;3:输出正中序遍历;4:查询x的排名;5:查询排名为x的数;6:求x的前驱;7:求x的后继;其它:退出\n");
	//	int tag = 0;
	//	scanf("%d", &tag);
	//	if (tag == 1) {
	//		printf("输入插入元素(整数)：\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.insert(num);
	//	}
	//	else if (tag == 2) {
	//		printf("输入删除元素(整数)：\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.delt(num);
	//	}
	//	else if (tag == 3) {
	//		printf("正中序遍历\n");
	//		inorderTraversal(avl, [](int val, int cnt) {
	//			printf("value = %d, cnt = %d\n", val, cnt);
	//			});
	//	}
	//	else if (tag == 4) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getRank(num));
	//	}
	//	else if (tag == 5) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getK(num));
	//	}
	//	else if (tag == 6) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getPre(num));
	//	}
	//	else if (tag == 7) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getSuc(num));
	//	}
	//	else {
	//		break;
	//	}
	//}

	freopen("D:\\材料\\学堂课程资料\\大二上\\数据结构\\作业\\10 AVL\\AVL\\data.txt", "r", stdin);
	//freopen("D:\\材料\\学堂课程资料\\大二上\\数据结构\\作业\\10 AVL\\AVL\\out.txt", "w", stdout);
	int t = 0;
	scanf("%d", &t);

	while (t) {
		--t;
		int tag = 0;
		/*if (avl._getTag() >= 2 || avl._getTag() <= -2) {
			int a;
			a = 1;
			printf("~~~~%d~~~\n", tmp);
		}*/
		scanf("%d", &tag);
		if (tag == 1) {
#ifdef TEST_MODE
			/*if (avl.size() == 741) {
				int a;
				a = 0;
			}*/
#endif // TEST_MODE
			int num;
			scanf("%d", &num);
			avl.insert(num);
#ifdef TEST_MODE
			if (avl.testAll()) {
				int a;
				a = 0;
			}
#endif // TESTMODE
		}
		else if (tag == 2) {
#ifdef TEST_MODE
			if (avl.size() == 64) {
				int a;
				a = 0;
			}
#endif // TEST_MODE
			int num;
			scanf("%d", &num);
			avl.delt(num);
#ifdef TEST_MODE
			if (avl.testAll()) {
				int a;
				a = 0;
			}
#endif // TESTMODE			

		}
		else if (tag == 3) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getRank(num));
		}
		else if (tag == 4) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getK(num));
		}
		else if (tag == 5) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getPre(num));
		}
		else if (tag == 6) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getSuc(num));
		}
	}

	return 0;
}