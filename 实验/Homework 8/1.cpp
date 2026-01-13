#include <iostream>
using namespace std;

int lenOfLCS(char* p1, char* p2, int m, int n) {
	if (m == 0 || n == 0) {
		return 0;
	}

	if (p1[m - 1] == p2[n - 1]) {
		return lenOfLCS(p1, p2, m - 1, n - 1) + 1;
	}

	if (p1[m - 1] != p2[n - 1]) {
		return lenOfLCS(p1, p2, m - 1, n) > lenOfLCS(p1, p2, m, n - 1) ? lenOfLCS(p1, p2, m - 1, n) : lenOfLCS(p1, p2, m, n - 1);
	}
}

void printLCS(char* p1, char* p2, int m, int n) {
	if (m == 0 || n == 0) {
		return;
	}

	if (p1[m - 1] == p2[n - 1]) {	
		printLCS(p1, p2, m - 1, n - 1);
		cout << p1[m - 1];
		return;
	}

	if (p1[m - 1] != p2[n - 1]) {
		if (lenOfLCS(p1, p2, m - 1, n) >= lenOfLCS(p1, p2, m, n - 1)) {
			printLCS(p1, p2, m - 1, n);
		}
		else {
			printLCS(p1, p2, m, n - 1);
		}
		return;
	}
}


int main() {
	int m, n;
	cin >> m >> n;
	char* p1 = new char[m + 1];
	char* p2 = new char[n + 1];
	cin >> p1;
	cin >> p2;
	p1[m] = p2[n] = '\0';

	printLCS(p1, p2, m, n);

	delete[] p1;
	delete[] p2;
}