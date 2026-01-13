#include <iostream>       // 引入输入输出流库
#include <vector>         // 引入向量容器库
#include <queue>          // 引入队列库（含优先队列）
#include <algorithm>      // 引入算法库（如排序）

using namespace std;      // 使用标准命名空间，避免std::前缀

int main() {
    int n;                // 声明变量n，表示课程/区间的数量
    cin >> n;             // 从标准输入读取n的值

    // 定义一个存储区间的向量，每个元素是pair<开始时间, 结束时间>
    vector<pair<int, int>> intervals;

    // 循环读取n个区间的起止时间
    for (int i = 0; i < n; ++i) {
        int start, finish;
        cin >> start >> finish;              // 读取当前区间的开始和结束时间
        intervals.emplace_back(start, finish); // 将区间存入向量（避免复制构造）
    }

    // 按区间开始时间升序排序（pair默认按第一元素升序，第二元素升序）
    sort(intervals.begin(), intervals.end());

    // 定义最小堆（优先队列），用于维护当前各教室的最早结束时间
    priority_queue<int, vector<int>, greater<int>> pq;

    // 遍历每个排序后的区间
    for (const auto& interval : intervals) {
        int start = interval.first;    // 当前区间的开始时间
        int finish = interval.second;  // 当前区间的结束时间

        // 若堆非空且堆顶（最早结束时间）<= 当前区间的开始时间
        // 说明可以复用该教室，移除堆顶的旧结束时间
        if (!pq.empty() && pq.top() <= start) {
            pq.pop();
        }

        // 将当前区间的结束时间加入堆（新增教室或更新复用教室的结束时间）
        pq.push(finish);
    }

    // 堆的大小即为所需的最小教室数（每个元素代表一个教室的结束时间）
    cout << pq.size() << endl;

    return 0; // 程序正常结束
}