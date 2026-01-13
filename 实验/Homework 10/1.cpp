#include <iostream>
using namespace std;

int orderPlans(int M, int* a, int N) {
    if (M > 10000) {
        return -1;
    }
    int dp[10001]{}; // dp[j]表示凑出金额j的方案数，初始化为0
    dp[0] = 1; // 初始化：凑0元只有一种方案（不选任何菜）
    for (int i = 0; i < N; i++) {
        for (int j = M; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];
        }
    }
    return dp[M];
}

int main() {
    int N, M;
    cin >> N >> M;

    int* a = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    cout << orderPlans(M, a, N) << endl;

    delete[] a;
    return 0;
}