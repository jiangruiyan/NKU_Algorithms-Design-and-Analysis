#include <iostream>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;

    int min_val;
    cin >> min_val;

    long long max_diff = LLONG_MIN;

    for (int i = 1; i < n; ++i) {
        int current;
        cin >> current;
        long long current_diff = (long long)current - min_val;
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        if (current < min_val) {
            min_val = current;
        }
    }

    cout << max_diff << '\n';
    return 0;
}