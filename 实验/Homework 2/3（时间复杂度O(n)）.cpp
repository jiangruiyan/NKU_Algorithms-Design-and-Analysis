#include<iostream>
using namespace std;

// 运用双指针使时间复杂度降低至O(n)
void myFunc(int* pA, int n, int sum) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int sum1 = pA[left] + pA[right];
		if (sum1 == sum) {
			cout << pA[left] << " " << pA[right];
			return;
		}
		if (sum1 < sum) {
			left++;
		}
		else {
			right--;
		}
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