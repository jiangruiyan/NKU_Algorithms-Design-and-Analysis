#include<iostream>
using namespace std;

// 二分查找
int binarySearch(int n, int* p, int target) {
	int left = 0;
	int right = n - 1;
	int mid = 0;
	while (left <= right) {
		mid = left + (right - left) / 2; // 应使用 mid = left + (right - left) / 2，避免 left + right 溢出
		if (p[mid] == target) {
			return mid;
		}
		else {
			if (p[mid] > target) {
				right = mid - 1; // 注意赋值时有+1或者-1，否则可能出现死循环
			}
			else {
				left = mid + 1;
			}
		}
	}
	return -1;
}

int main() {
	int n;
	int target;
	cin >> n >> target;
	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	cout << binarySearch(n, p, target);
	delete[] p;
	return 0;
}
