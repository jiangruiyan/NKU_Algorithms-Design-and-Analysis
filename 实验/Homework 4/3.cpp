#include <iostream>
using namespace std;

class Job {
public:
	int startTime;
	int processingTime;
	int deadline;
};

// 判断是否所有job都被探测
bool isAllDetected(bool* p, int n) {
	for (int i = 0; i < n; i++) {
		if (p[i] == false) {
			return false;
		}
	}
	return true;
}

// 返回截止时间最早且未被探测的job的下标
int earliestDDL(Job* p, bool* isDetected, int n) {
	int index = 0;
	int earliesDllTime = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (isDetected[i] == false && p[i].deadline < earliesDllTime) {
			earliesDllTime = p[i].deadline;
			index = i;
		}
	}
	isDetected[index] = true;
	return index;
}

// 返回延迟的最大值
int maxLateness(Job* p, int n) {
	int lateness = 0;
	int finish = 0; // 目前已经安排了的job的总的结束时间
	bool* isDetected = new bool[n];
	for (int i = 0; i < n; i++) {
		isDetected[i] = false;
	}
	while (!isAllDetected(isDetected, n)) {
		int a = earliestDDL(p, isDetected, n);
		p[a].startTime = finish; // 将目前job的总的结束时间赋给下一个job的开始时间
		finish += p[a].processingTime; // 更新job的总的结束
	}

	// 计算延迟的最大值
	for (int i = 0; i < n; i++) {
		if (lateness < p[i].startTime + p[i].processingTime - p[i].deadline) {
			lateness = p[i].startTime + p[i].processingTime - p[i].deadline;
		}
	}

	delete[] isDetected;
	return lateness;
}

int main() {
	int n;
	cin >> n;
	Job* pJob = new Job[n];
	int pi, ddl;
	for (int i = 0; i < n; i++) {
		cin >> pi >> ddl;
		pJob[i].processingTime = pi;
		pJob[i].deadline = ddl;
	}

	cout << maxLateness(pJob, n) << endl;

	delete[] pJob;
}