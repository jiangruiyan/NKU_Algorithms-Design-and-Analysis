#include <iostream>
using namespace std;

int main() {
    int V, n;
    cin >> V >> n;

    // 手动分配动态数组替代vector
    int* dp = new int[V + 1];
    for (int j = 0; j <= V; ++j) dp[j] = 0; // 初始化

    // 处理每个物品
    for (int i = 0; i < n; ++i) {
        int v_i, w_i;
        cin >> v_i >> w_i;

        // 逆序遍历容量（避免覆盖）
        for (int j = V; j >= v_i; --j) {
            if (dp[j - v_i] + w_i > dp[j]) {
                dp[j] = dp[j - v_i] + w_i;
            }
        }
    }

    cout << dp[V] << endl;

    delete[] dp; // 释放内存
    return 0;
}