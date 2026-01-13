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

void BFS(int** graph, int n, int beginV) {
	bool* pIsDetected = new bool[n]; // 每个节点是否已被探测
	for (int i = 0; i < n; i++) {
		pIsDetected[i] = false; // 初始化为false
	}
	pIsDetected[beginV] = true;

	MyCircularQueue myQueue(n); // 创建一个队列
	myQueue.enQueue(beginV);
	cout << beginV;
	while (!myQueue.isEmpty()) {
		for (int i = 0; i < n; i++) {
			if (graph[myQueue.Front()][i] == 1 && pIsDetected[i] == false) {
				pIsDetected[i] = true;
				myQueue.enQueue(i);
				cout << " " << i;
			}
		}
		myQueue.deQueue();
	}
	cout << endl;
	delete[] pIsDetected;
}

void DFSprint(int** graph, int n, int beginV, bool* pIsDetected) {
	pIsDetected[beginV] = true;
	cout << beginV << " ";
	for (int i = 0; i < n; i++) {
		if (graph[beginV][i] == 1 && pIsDetected[i] == false) {
			DFSprint(graph, n, i, pIsDetected);
		}
	}
}
void DFS(int** graph, int n, int beginV) {
	bool* pIsDetected = new bool[n]; // 每个节点是否已被探测
	for (int i = 0; i < n; i++) {
		pIsDetected[i] = false; // 初始化为false
	}
	DFSprint(graph, n, beginV, pIsDetected);
}

int main() {
	int n; // 图的节点数
	int m; // 图的边数
	int beginVertex; // BFS和DFS的开始节点
	cin >> n >> m >> beginVertex;

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

	// 以下开始BFS宽度优先搜索
	BFS(myGraph, n, beginVertex);
	// 以下开始DFS深度优先搜索
	DFS(myGraph, n, beginVertex);

	for (int i = 0; i < n; i++) {
		delete[] myGraph[i];
	}
	delete[] myGraph;
}