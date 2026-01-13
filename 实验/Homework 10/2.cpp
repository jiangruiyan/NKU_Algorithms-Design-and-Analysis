#include <iostream>
using namespace std;

const int MAXN = 21;
long long dp[MAXN][MAXN];
bool blocked[MAXN][MAXN];

int horse_moves[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
};

int main() {
    int n, m; // 终点坐标 B(n, m)
    int hx, hy; // 马的位置 C(hx, hy)

    cin >> n >> m >> hx >> hy;

    // 标记马的位置和控制点
    blocked[hx][hy] = true;
    for (int i = 0; i < 8; ++i) {
        int x = hx + horse_moves[i][0];
        int y = hy + horse_moves[i][1];
        if (x >= 0 && x <= n && y >= 0 && y <= m) {
            blocked[x][y] = true;
        }
    }

    // 初始化
    dp[0][0] = blocked[0][0] ? 0 : 1;

    // 动态规划求解路径数
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (blocked[i][j]) {
                continue;
            }
            if (i > 0 && !blocked[i - 1][j]) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0 && !blocked[i][j - 1]) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    cout << dp[n][m] << endl;
    return 0;
}