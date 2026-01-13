#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> freqs(n); // 存储符号频率的向量
    for (int i = 0; i < n; ++i) {
        cin >> freqs[i];
    }

    // 边界情况处理：若只有1个符号，平均编码长度为0
    if (n == 1) {
        cout << "0.00" << endl;
        return 0;
    }

    // 计算总频率
    int sum_freq = 0;
    for (auto f : freqs) {
        sum_freq += f;
    }

    // 构建最小优先队列（哈夫曼算法的核心数据结构）
    priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
    for (auto f : freqs) {
        pq.push(f);
    }

    // 构建哈夫曼树并计算总权重
    int total = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int c = a + b;
        total += c;
        pq.push(c);
    }

    // 计算并输出平均编码长度
    double avg = static_cast<double>(total) / sum_freq;
    cout << fixed << setprecision(2) << avg << endl;

    return 0;
}