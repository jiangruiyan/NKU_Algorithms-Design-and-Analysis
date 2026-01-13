#include<iostream>
using namespace std;

// 运用二分查找使时间复杂度降低至O(n^2*log n)
int binarySearch(int* arr, int left, int right, int target) {
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == target) {
			return mid;
		}
		else {
			if (arr[mid] > target) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
	}
	return -1;
}

void myFunc(int* pA, int n, int sum) {
	int index = 0;
	int tempIndex = 0;
	while (index < n - 2) {
		for (int i = index + 1; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int pos = binarySearch(pA, index + 1, n - 1, sum - pA[index] - pA[i]);
				if (pos != -1) {
					cout << pA[index] << " " << pA[i] << " " << pA[pos];
					return;
				}
			}
		}
		index++;
	}
	cout << "Numbers meet the requirements are not found!";
	return;
}

int main() {
	int n, T;
	cin >> n >> T;
	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	myFunc(p, n, T);
	delete[] p;
}