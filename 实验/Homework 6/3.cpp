#include <iostream>
using namespace std;

void merge(int* p, int left, int mid, int right) {
    int* temp = new int[right - left + 1];
    int i = left, j = mid + 1, k = 0;

    // 合并左右两部分
    while (i <= mid && j <= right) {
        if (p[i] <= p[j]) {
            temp[k++] = p[i++];
        }
        else {
            temp[k++] = p[j++];
        }
    }

    // 处理左半剩余元素
    while (i <= mid) {
        temp[k++] = p[i++];
    }

    // 处理右半剩余元素
    while (j <= right) {
        temp[k++] = p[j++];
    }

    // 将合并结果拷贝回原数组
    for (int idx = 0; idx < k; idx++) {
        p[left + idx] = temp[idx];
    }

    delete[] temp;
}

void mergeSort(int* p, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(p, left, mid);
        mergeSort(p, mid + 1, right);
        merge(p, left, mid, right);
    }
}

int main() {
    int n;
    cin >> n;
    int* p = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    mergeSort(p, 0, n - 1);

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << p[i];
    }
    cout << endl;

    delete[] p;
    return 0;
}