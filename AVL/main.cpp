#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "AVL.h"
#include <queue>


int main() {

	AVL<int> avl;

	//printf("�����ʼԪ�ظ���:\n");
	//int n;
	//scanf("%d", &n);
	//printf("�����ʼԪ��:\n");
	//for (int i = 0; i < n; ++i) {
	//	int tmp;
	//	scanf("%d", &tmp);
	//	avl.insert(tmp);
	//}
	//inorderTraversal(avl, [](int val, int cnt) {
	//	printf("value = %d, cnt = %d\n", val, cnt);
	//	});
	//while (true) {
	//	printf("1:����;2:ɾ��;3:������������;4:��ѯx������;5:��ѯ����Ϊx����;6:��x��ǰ��;7:��x�ĺ��;����:�˳�\n");
	//	int tag = 0;
	//	scanf("%d", &tag);
	//	if (tag == 1) {
	//		printf("�������Ԫ��(����)��\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.insert(num);
	//	}
	//	else if (tag == 2) {
	//		printf("����ɾ��Ԫ��(����)��\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.delt(num);
	//	}
	//	else if (tag == 3) {
	//		printf("���������\n");
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

	freopen("D:\\����\\ѧ�ÿγ�����\\�����\\���ݽṹ\\��ҵ\\10 AVL\\AVL\\data.txt", "r", stdin);
	//freopen("D:\\����\\ѧ�ÿγ�����\\�����\\���ݽṹ\\��ҵ\\10 AVL\\AVL\\out.txt", "w", stdout);
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