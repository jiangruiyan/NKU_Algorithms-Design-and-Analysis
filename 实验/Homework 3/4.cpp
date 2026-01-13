#include <iostream>
using namespace std;

// 返回下一个待排序的节点
int firstToBeSortedNode(int** myGraph, int n, bool* pIsSorted) {
	bool isToBeSorted = true;
	for (int i = 0; i < n; i++) {
		if (pIsSorted[i] == true) {
			continue;
		}
		isToBeSorted = true;
		for (int j = 0; j < n; j++) {
			if (myGraph[j][i] == 1 && pIsSorted[j] == false) {
				isToBeSorted = false;
			}
		}
		if (isToBeSorted) {
			pIsSorted[i] = true;
			for (int j = 0; j < n; j++) {
				myGraph[i][j] = (i == j ? 0 : -1); // 一定记得取消链接
			}
			return i;
		}
	}
	return -1; // 排序完成
}
void topologicalSortPrint(int** myGraph, int n, bool* pIsSorted) {
	while (true) {
		int tempNode = firstToBeSortedNode(myGraph, n, pIsSorted);
		if (tempNode != -1) {
			cout << tempNode << " ";
		}
		else {
			break;
		}
	}
	cout << endl;
}
// 拓扑排序
void topologicalSort(int** myGraph, int n) {
	bool* pIsSorted = new bool[n];
	for (int i = 0; i < n; i++) {
		pIsSorted[i] = false;
	}
	topologicalSortPrint(myGraph, n, pIsSorted);
}

int main() {
	int n; // 图的节点数
	int m; // 图的边数
	cin >> n >> m;

	int** myGraph = new int* [n]; // 用邻接矩阵（二维数组）存储图
	for (int i = 0; i < n; i++) {
		myGraph[i] = new int[n];
	}

	// 初始化邻接矩阵（先全为0，后面再将有边的地方改为1）
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			myGraph[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		int vertex1, vertex2;
		cin >> vertex1 >> vertex2;
		myGraph[vertex1][vertex2] = 1;
	}

	topologicalSort(myGraph, n);

	for (int i = 0; i < n; i++) {
		delete[] myGraph[i];
	}
	delete[] myGraph;
}