#include<iostream>
using namespace std;

int main() {
	int originalBalance = 0;
	int balanceAfterUsingGift = 0;
	cin >> originalBalance;
	if (originalBalance >= 0) { // 如果原先的余额比0大，则删去一位数字显然会让余额变少，故不删去
		balanceAfterUsingGift = originalBalance;
	}
	else {
		int temp = -originalBalance;
		// 去掉最后一位之后的绝对值
		int removeLastOne = temp / 10;
		// 去掉倒数第二位之后的绝对值
		int removeBeforeLast = (temp / 100) * 10 + temp % 10;
		balanceAfterUsingGift = -(removeBeforeLast < removeLastOne ? removeBeforeLast : removeLastOne);
	}
	cout << balanceAfterUsingGift;
	return 0;
}
