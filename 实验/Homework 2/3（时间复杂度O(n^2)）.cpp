#include<iostream>
using namespace std;

void myFunc(int* pA, int n, int sum) {
	int index = 0;
	int tempIndex = 0;
	while (pA[index] <= sum / 2) {
		for (int i = index + 1; i < n; i++) {
			if (pA[index] + pA[i] == sum) {
				cout << pA[index] << " " << pA[i];
				return;
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