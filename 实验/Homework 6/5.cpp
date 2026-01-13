#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

// 计算两点间欧氏距离的平方
double distSq(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 暴力求解小规模点集的最近距离平方
double bruteForce(Point points[], int n) {
    double min_dist = 1e20;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = distSq(points[i], points[j]);
            if (d < min_dist) min_dist = d;
        }
    }
    return min_dist;
}

// 归并排序（按x坐标排序）
void mergeSortX(Point arr[], int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSortX(arr, l, mid);
    mergeSortX(arr, mid + 1, r);

    // 合并
    int n1 = mid - l + 1;
    int n2 = r - mid;
    Point* L = new Point[n1];
    Point* R = new Point[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].x <= R[j].x) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

// 归并排序（按y坐标排序）
void mergeSortY(Point arr[], int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSortY(arr, l, mid);
    mergeSortY(arr, mid + 1, r);

    // 合并
    int n1 = mid - l + 1;
    int n2 = r - mid;
    Point* L = new Point[n1];
    Point* R = new Point[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].y <= R[j].y) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

// 分治求解最近点对
double closestUtil(Point points[], int n) {
    if (n <= 3) return bruteForce(points, n);

    int mid = n / 2;
    Point midPoint = points[mid];

    // 递归处理左右子集
    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);
    double d = (dl < dr) ? dl : dr;

    // 收集中间区域的点（距离中线不超过d）
    Point* strip = new Point[n];
    int stripSize = 0;
    for (int i = 0; i < n; ++i) {
        if ((points[i].x - midPoint.x) * (points[i].x - midPoint.x) < d) {
            strip[stripSize++] = points[i];
        }
    }

    // 按y坐标排序中间区域的点
    mergeSortY(strip, 0, stripSize - 1);

    // 检查中间区域内的点对
    double min_strip = d;
    for (int i = 0; i < stripSize; ++i) {
        for (int j = i + 1; j < stripSize && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < min_strip; ++j) {
            double current_dist = distSq(strip[i], strip[j]);
            if (current_dist < min_strip) min_strip = current_dist;
        }
    }

    delete[] strip;
    return (d < min_strip) ? d : min_strip;
}

double closestPair(Point points[], int n) {
    mergeSortX(points, 0, n - 1); // 按x坐标排序
    return closestUtil(points, n);
}

int main() {
    int n;
    cin >> n;
    Point* points = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    double min_dist_sq = closestPair(points, n);
    cout << min_dist_sq << endl;

    delete[] points;
    return 0;
}