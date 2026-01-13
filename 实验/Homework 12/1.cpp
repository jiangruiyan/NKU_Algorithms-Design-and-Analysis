#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[100]; // 存储每个仓库的原始库存

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 计算总库存，求平均值（每个仓库的目标库存）
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    int avg = sum / n;

    int d[100]; // 差值数组：每个仓库当前库存与目标库存的差值
    for (int i = 0; i < n; i++) {
        d[i] = a[i] - avg; // 正数表示需要移出货物，负数表示需要移入
    }

    int s[100]; // 前缀和数组：用于计算搬运量的累积分布
    s[0] = d[0];
    for (int i = 1; i < n; i++) {
        s[i] = s[i - 1] + d[i]; // 逐步累加差值，反映搬运的“净流动”
    }

    // 对前缀和数组排序（冒泡排序）
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j] > s[j + 1]) {
                int temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    // 取排序后的中位数，使总绝对差最小
    int median = s[n / 2];
    int ans = 0;
    // 计算所有前缀和与中位数的绝对差之和，即为最小搬运量
    for (int i = 0; i < n; i++) {
        ans += abs(s[i] - median);
    }

    cout << ans << endl;
    return 0;
}