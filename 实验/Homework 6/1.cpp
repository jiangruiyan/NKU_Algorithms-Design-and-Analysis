#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    // 邻接表：adj[u]存储u的邻接边，格式为 <邻接节点, 边权>
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w)); // 无向图，双向添加
        adj[v].push_back(make_pair(u, w));
    }

    vector<bool> visited(n + 1, false);
    // 优先队列：按边权从小到大排序，存储格式为 <边权, 目标节点>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 初始化：从节点1开始
    visited[1] = true;
    // 将节点1的邻接边加入队列
    for (int i = 0; i < adj[1].size(); ++i) {
        int neighbor = adj[1][i].first;
        int weight = adj[1][i].second;
        pq.push(make_pair(weight, neighbor));
    }

    int sum = 0;
    int count = 1; // 已加入生成树的节点数

    // 主循环：直到所有节点被加入
    while (count < n && !pq.empty()) {
        int w = pq.top().first;   // 当前边的权重
        int v = pq.top().second;  // 当前边指向的节点
        pq.pop();

        if (visited[v]) continue; // 跳过已访问的节点

        sum += w;
        visited[v] = true;
        count++;

        // 将新节点的未访问邻接边加入队列
        for (int i = 0; i < adj[v].size(); ++i) {
            int neighbor = adj[v][i].first;
            int weight = adj[v][i].second;
            if (!visited[neighbor]) {
                pq.push(make_pair(weight, neighbor));
            }
        }
    }

    cout << sum << endl;
    return 0;
}