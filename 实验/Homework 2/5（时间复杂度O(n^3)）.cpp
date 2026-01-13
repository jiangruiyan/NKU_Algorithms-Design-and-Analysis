#include<iostream>
using namespace std;

int distanceSquare(int x1, int x2, int y1, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
	int n;
	cin >> n;
	int* pX = new int[n];
	int* pY = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> pX[i] >> pY[i];
	}
	int minDistance = INT_MAX;
	int minX1 = 0, minX2 = 0;
	int minY1 = 0, minY2 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (distanceSquare(pX[i], pX[j], pY[i], pY[j]) < minDistance) {
				minDistance = distanceSquare(pX[i], pX[j], pY[i], pY[j]);
				minX1 = pX[i];
				minX2 = pX[j];
				minY1 = pY[i];
				minY2 = pY[j];
			}
		}
	}
	if ((minX1 > minX2) || (minX1 == minX2 && minY1 > minY2)) {
		swap(minX1, minX2);
		swap(minY1, minY2);
	}
	cout << minX1 << " " << minY1 << endl;
	cout << minX2 << " " << minY2;
	delete[] pX;
	delete[] pY;
}