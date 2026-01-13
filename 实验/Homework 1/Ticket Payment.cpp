#include<iostream>
using namespace std;

int main() {
	int n, m, a, b;
	int mincost = 0;
	cin >> n >> m >> a >> b;
	if (b / m >= a) { // 若m次票均摊下来的单价比一次票高，则全部买一次票
		mincost = a * n;
	}
	else {
		int num_of_m_ride_ticket = n / m;
		int num_of_one_ride_ticket = n - num_of_m_ride_ticket * m;
		int cost1, cost2 = 0;
		// cost1代表用多少买多少，买最多的m次票，剩余的买一次票
		// cost2代表允许买多浪费，全部买m次票，直到够用为止
		cost1 = a * num_of_one_ride_ticket + b * num_of_m_ride_ticket;
		cost2 = b * (n % m == 0 ? n / m : n / m + 1);
		// 取cost1和cost2最小的作为最低票价
		mincost = cost1 <= cost2 ? cost1 : cost2;
	}
	cout << mincost;
	return 0;
}
