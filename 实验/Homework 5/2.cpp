#include <iostream>
using namespace std;

const int MAXN = 100;
const int INF = 0x3f3f3f3f;
int graph[MAXN + 1][MAXN + 1]; // 邻接矩阵（节点编号从1开始）
int dist[MAXN + 1];            // 最短距离数组
int prev_node[MAXN + 1];       // 前驱节点数组
bool visited[MAXN + 1];        // 标记节点是否已处理


int main() {
    int n, e, S;
    cin >> n >> e >> S;

    // 初始化邻接矩阵为INF
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            graph[i][j] = INF;

    // 读取边并更新邻接矩阵（保留最短边）
    for (int i = 0; i < e; ++i) {
        int x_i, x_j, l;
        cin >> x_i >> x_j >> l;
        if (l < graph[x_i][x_j])
            graph[x_i][x_j] = l;
    }

    // 初始化距离、前驱和访问标记
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        prev_node[i] = -1;
        visited[i] = false;
    }
    dist[S] = 0;

    // Dijkstra算法主过程
    for (int count = 0; count < n; ++count) {
        int u = -1, min_dist = INF;
        // 选择未处理的节点中距离最小的
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break; // 剩余节点不可达
        visited[u] = true;

        // 更新相邻节点的距离
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && graph[u][v] != INF) {
                if (dist[v] > dist[u] + graph[u][v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev_node[v] = u;
                }
            }
        }
    }

    // 输出所有节点的最短距离
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << " ";
        cout << dist[i];
    }
    cout << endl;

    return 0;
}