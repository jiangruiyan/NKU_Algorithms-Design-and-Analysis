#include <iostream>
using namespace std;

// 合并两个子数组并计算逆序数
int merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    // 将数据复制到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    int inv_count = 0;

    // 合并过程统计逆序对
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
            inv_count += n1 - i; // 左半剩余元素均构成逆序对
        }
    }

    // 处理剩余元素
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
    return inv_count;
}

// 归并排序并返回逆序数
int mergeSort(int arr[], int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += mergeSort(arr, left, mid);    // 左半逆序数
        inv_count += mergeSort(arr, mid + 1, right); // 右半逆序数
        inv_count += merge(arr, left, mid, right);  // 合并时的逆序数
    }
    return inv_count;
}

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << mergeSort(arr, 0, n - 1) << endl;

    delete[] arr;
    return 0;
}