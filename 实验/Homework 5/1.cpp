#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main() {
    int k, n, s;
    cin >> k >> n >> s;

    vector<int> initial(n);
    for (int i = 0; i < n; i++) {
        cin >> initial[i];
    }

    vector<int> requests(s);
    for (int i = 0; i < s; i++) {
        cin >> requests[i];
    }

    // 预处理每个块的出现位置
    unordered_map<int, vector<int>> pos_map;
    for (int i = 0; i < s; i++) {
        pos_map[requests[i]].push_back(i);
    }

    unordered_set<int> cache;
    unordered_map<int, int> last_used;
    int timestamp = 0;

    // 初始化缓存
    for (int block : initial) {
        if (cache.size() < k && cache.find(block) == cache.end()) {
            cache.insert(block);
            last_used[block] = timestamp;
        }
    }
    timestamp = 0;

    vector<int> evictions;

    for (int i = 0; i < s; i++) {
        int current = requests[i];
        if (cache.find(current) != cache.end()) {
            last_used[current] = ++timestamp;
            continue;
        }

        if (cache.size() < k) {
            // 缓存未满，直接加入
            cache.insert(current);
            last_used[current] = ++timestamp;
        }
        else {
            // 需要替换
            vector<int> candidates;
            int max_next = -1;

            for (int x : cache) {
                vector<int>& positions = pos_map[x];
                auto it = upper_bound(positions.begin(), positions.end(), i);
                int next_pos = (it != positions.end()) ? *it : s;

                if (next_pos > max_next) {
                    max_next = next_pos;
                    candidates.clear();
                    candidates.push_back(x);
                }
                else if (next_pos == max_next) {
                    candidates.push_back(x);
                }
            }

            // 选择最后访问时间最早的块
            int selected = candidates[0];
            int min_time = last_used[selected];
            for (int x : candidates) {
                if (last_used[x] < min_time) {
                    selected = x;
                    min_time = last_used[x];
                }
            }

            evictions.push_back(selected);
            cache.erase(selected);
            last_used.erase(selected);

            cache.insert(current);
            last_used[current] = ++timestamp;
        }
    }

    // 输出替换序列
    for (size_t i = 0; i < evictions.size(); ++i) {
        if (i > 0) cout << " ";
        cout << evictions[i];
    }
    cout << endl;

    return 0;
}