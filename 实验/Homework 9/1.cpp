#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int maxSum = -100000000;  // 初始化为一个足够小的负数
    int currentSum = 0;
    int x;

    for (int i = 0; i < n; i++) {
        cin >> x;
        currentSum += x;

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }

        if (currentSum < 0) {
            currentSum = 0;
        }
    }

    cout << maxSum << endl;

    return 0;
}
