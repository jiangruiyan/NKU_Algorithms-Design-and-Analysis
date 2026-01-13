#include <iostream>
using namespace std;

struct Interval {
    int start;
    int finish;
};

void swap(Interval& a, Interval& b) {
    Interval temp = a;
    a = b;
    b = temp;
}

int partition(Interval* arr, int left, int right) {
    Interval pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j].start < pivot.start) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSort(Interval* arr, int left, int right) {
    if (left >= right) return;
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
}

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;

    void resize() {
        int newCapacity = capacity * 2;
        int* newHeap = new int[newCapacity];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void percolateUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void percolateDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;
            if (smallest == index) break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    MinHeap() : capacity(10), size(0) {
        heap = new int[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void push(int value) {
        if (size >= capacity)
            resize();
        heap[size] = value;
        percolateUp(size);
        size++;
    }

    int top() {
        return heap[0];
    }

    void pop() {
        heap[0] = heap[size - 1];
        size--;
        percolateDown(0);
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

int main() {
    int n;
    cin >> n;
    Interval* intervals = new Interval[n];
    for (int i = 0; i < n; ++i)
        cin >> intervals[i].start >> intervals[i].finish;

    quickSort(intervals, 0, n - 1);

    MinHeap heap;
    for (int i = 0; i < n; ++i) {
        int start = intervals[i].start;
        int finish = intervals[i].finish;

        if (!heap.empty() && heap.top() <= start)
            heap.pop();
        heap.push(finish);
    }

    cout << heap.getSize() << endl;

    delete[] intervals;
    return 0;
}