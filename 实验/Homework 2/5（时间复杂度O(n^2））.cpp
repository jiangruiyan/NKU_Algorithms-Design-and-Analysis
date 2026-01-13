#include<iostream>
using namespace std;

// 运用双指针使时间复杂度降低至O(n^2)
void myFunc(int* pA, int n, int sum) {
	int index = 0;
	int tempIndex = 0;
	while (index < n - 2) {
		int left = index + 1, right = n - 1;
		while (left < right) {
			int sum1 = pA[left] + pA[right];
			if (sum1 == sum - pA[index]) {
				cout << pA[index] << " " << pA[left] << " " << pA[right];
				return;
			}
			if (sum1 < sum - pA[index]) {
				left++;
			}
			else {
				right--;
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