#include<iostream>
using namespace std;

// 合并数组并输出
void mergeArray(int m, int n, int* arrayA, int* arrayB) {
	int indexA = 0;
	int indexB = 0;
	int* mergedArr = new int[m + n];
	int indexMA = 0;
	while (indexA < m || indexB < n) {
		// 以下几行用于当其中一个数组率先合并完成的情况
		if (indexA == m) {
			mergedArr[indexMA] = arrayB[indexB];
			indexB++;
			indexMA++;
			continue; // 不要忘了终止此次循环
		}
		if (indexB == n) {
			mergedArr[indexMA] = arrayA[indexA];
			indexA++;
			indexMA++;
			continue;
		}

		// 以下几行用于正常插入操作
		if (arrayA[indexA] <= arrayB[indexB]) {
			mergedArr[indexMA] = arrayA[indexA];
			indexA++;
		}
		else {
			mergedArr[indexMA] = arrayB[indexB];
			indexB++;
		}
		indexMA++;
	}
	for (int i = 0; i < m + n - 1; i++) {
		cout << mergedArr[i] << " ";
	}
	cout << mergedArr[m + n - 1];
	delete[] mergedArr;
}

int main() {
	int m, n;
	cin >> m >> n;
	int* paA = new int[m];
	int* paB = new int[n];
	for (int i = 0; i < m; i++) {
		cin >> paA[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> paB[i];
	}
	mergeArray(m, n, paA, paB);
	delete[] paA;
	delete[] paB;
}