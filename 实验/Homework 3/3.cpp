#include <iostream>
using namespace std;

// 创建一个队列类（环形队列）
class MyCircularQueue {
public:
	// 构造函数
	MyCircularQueue(int k) {
		Maxsize = k + 1; // 数组大小Maxsize为队列大小k再加1，用于区分队列空和队列满的情况
		queue = new int[Maxsize];
		front = rear = 0;
	}
	//析构函数
	~MyCircularQueue() {
		delete[]queue;
	}
	bool enQueue(int value); // 将元素value插入至队列尾部。若队列满，则插入失败，返回false；否则返回true
	bool deQueue(); // 删除队首元素。如果队列为空，则删除失败，返回false；否则返回true
	bool isEmpty(); // 判断队列是否为空
	bool isFull(); // 判断队列是否已满
	int Front(); // 获取队首元素。如果队列为空，则返回-1
private:
	int front;
	int rear;
	int Maxsize;
	int* queue;
};
bool MyCircularQueue::enQueue(int value) {
	if (isEmpty()) {
		queue[0] = value;
		rear++;
		return true;
	}
	if (isFull()) {
		return false;
	}
	queue[rear] = value;
	rear = (rear + 1) % Maxsize;
	return true;
}
bool MyCircularQueue::deQueue() {
	if (isEmpty()) {
		return false;
	}
	front = (front + 1) % Maxsize;
	return true;
}
bool MyCircularQueue::isEmpty() {
	return front == rear ? true : false;
}
bool MyCircularQueue::isFull() {
	return front == (rear + 1) % Maxsize ? true : false;
}
int MyCircularQueue::Front() {
	if (isEmpty()) {
		return  -1;
	}
	return queue[front];
}

// 使用BFS遍历+涂色法判断是否是二部图
bool isBipartiteGraph(int** myGraph, int n) {
	int* color = new int[n]; // color数组，-1代表未访问，0代表涂红，1代表涂蓝
	for (int i = 0; i < n; i++) {
		color[i] = -1;
	}
	color[0] = 0; // 这里选取0号节点作为BFS的开始节点，涂红

	MyCircularQueue myQueue(n); // 创建一个队列
	myQueue.enQueue(0);

	while (!myQueue.isEmpty()) {
		for (int i = 0; i < n; i++) {
			if (myGraph[myQueue.Front()][i] == 1 && color[i] == -1) {
				color[i] = 1 - color[myQueue.Front()]; // 把i号节点涂成和队首的节点（myQueue.Front()）相反的颜色
				myQueue.enQueue(i);
			}
			if (myGraph[myQueue.Front()][i] == 1 && color[i] != -1) {
				if (color[i] + color[myQueue.Front()] != 1) {
					delete[] color;
					return false; // 颜色冲突
				}
			}
		}
		myQueue.deQueue();
	}
	delete[] color;
	return true;
}

int main() {
	int n; // 图的节点数
	int m; // 图的边数
	cin >> n >> m;

	int** myGraph = new int* [n]; // 用邻接矩阵（二维数组）存储图
	for (int i = 0; i < n; i++) {
		myGraph[i] = new int[n];
	}

	// 初始化邻接矩阵（先全为0，后面再将有边的地方改为1）
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			myGraph[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		int vertex1, vertex2;
		cin >> vertex1 >> vertex2;
		myGraph[vertex1][vertex2] = myGraph[vertex2][vertex1] = 1; // 无向图的邻接矩阵是对称矩阵
	}

	cout << (isBipartiteGraph(myGraph, n) ? "Yes" : "No") << endl;

	for (int i = 0; i < n; i++) {
		delete[] myGraph[i];
	}
	delete[] myGraph;
}