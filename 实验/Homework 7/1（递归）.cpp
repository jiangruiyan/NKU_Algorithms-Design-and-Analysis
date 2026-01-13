#include <iostream>
using namespace std;

int knapsack(int* pv, int* pw, int i, int j) {
    // 考虑前i个物品，背包总容量为j

    if (i == 0 || j == 0) {
        return 0;
    }

    int not_get_i_j = knapsack(pv, pw, i - 1, j);
    if (j < pv[i - 1]) {
        return not_get_i_j;
    }
    else {
        int get_i_j = knapsack(pv, pw, i - 1, j - pv[i - 1]) + pw[i - 1];
        return not_get_i_j > get_i_j ? not_get_i_j : get_i_j;
    }
}

int main() {
    int v, n; // 容量、个数
    cin >> v >> n;
    int* pv = new int[n]; // 空间
    int* pw = new int[n]; // 价值
    for (int i = 0; i < n; i++) {
        cin >> pv[i] >> pw[i];
    }

    cout << knapsack(pv, pw, n, v) << endl;

    delete[] pv;
    delete[] pw;
}