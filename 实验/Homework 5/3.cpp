#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> parent;

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]); // 路径压缩
    }
    return parent[u];
}

void unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        parent[rootU] = rootV;
    }
}

int main() {
    int n, e;
    cin >> n >> e;
    vector<Edge> edges(e);
    for (int i = 0; i < e; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    // 按边的权重从小到大排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
        });
    // 初始化并查集
    parent.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
    int sum = 0;
    int count = 0;
    for (const Edge& edge : edges) {
        if (count == n - 1) break;
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;
        if (find(u) != find(v)) {
            unite(u, v);
            sum += w;
            count++;
        }
    }
    cout << sum << endl;
    return 0;
}