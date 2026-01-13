#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 205;                // 最大顶点数
const long long INF = 1LL << 60;    // 无限大，用于初始化最小残量

// cap[u][v] 表示 u -> v 的容量
// flow[u][v] 表示 u -> v 当前的流量
long long cap[MAXN][MAXN];
long long flow[MAXN][MAXN];
int pre[MAXN];         // pre[v] 表示在增广路径中 v 的前驱节点
bool visited[MAXN];    // BFS 中判断是否访问过
int queue[MAXN];       // 队列用于 BFS
int n, m, s, t;        // n: 顶点数, m: 边数, s: 源点, t: 汇点

// 使用 BFS 找到一条增广路径，返回是否存在
bool bfs() {
    memset(visited, 0, sizeof(visited));
    memset(pre, -1, sizeof(pre));
    int front = 0, rear = 0;

    queue[rear++] = s;
    visited[s] = true;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; ++v) {
            // 如果 v 未访问，且 u->v 存在残余容量
            if (!visited[v] && cap[u][v] - flow[u][v] > 0) {
                visited[v] = true;
                pre[v] = u;
                queue[rear++] = v;
                if (v == t) return true;  // 找到汇点，返回成功
            }
        }
    }
    return false;  // 未找到增广路径
}

// 求最大流的主过程（Edmonds-Karp 算法）
long long maxFlow() {
    memset(flow, 0, sizeof(flow));  // 初始化所有流为 0
    long long maxflow = 0;

    // 不断找增广路径
    while (bfs()) {
        long long minCap = INF;

        // 从 t 回溯到 s，找路径中的最小残余容量
        for (int v = t; v != s; v = pre[v]) {
            int u = pre[v];
            minCap = min(minCap, cap[u][v] - flow[u][v]);
        }

        // 更新路径上的流量
        for (int v = t; v != s; v = pre[v]) {
            int u = pre[v];
            flow[u][v] += minCap;
            flow[v][u] -= minCap;  // 反向边更新残量
        }

        maxflow += minCap;  // 累加总流量
    }

    return maxflow;
}

int main() {
    cin >> n >> m >> s >> t;
    memset(cap, 0, sizeof(cap));  // 初始化容量为 0

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        cap[u][v] += w;  // 支持重边：累加容量
    }

    cout << maxFlow() << endl;  // 输出最大流
    return 0;
}
