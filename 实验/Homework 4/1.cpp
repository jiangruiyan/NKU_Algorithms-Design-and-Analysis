#include <iostream>
using namespace std;

class Job {
public:
	int startTime;
	int finishTime;
};

// 判断j1和j2是否冲突
bool isConflict(Job j1, Job j2) {
	if (j1.startTime <= j2.startTime) {
		if (j1.finishTime > j2.startTime) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (j2.finishTime > j1.startTime) {
			return true;
		}
		else {
			return false;
		}
	}
}

// 判断是否所有job都被探测
bool isAllDetected(bool* p, int n) {
	for (int i = 0; i < n; i++) {
		if (p[i] == false) {
			return false;
		}
	}
	return true;
}

// 返回结束时间最早且未被探测的job的下标
int earliestFinish(Job* p, bool* isDetected, int n) {
	int minFinishTime = INT_MAX;
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (isDetected[i] == false) {
			if (p[i].finishTime < minFinishTime) {
				minFinishTime = p[i].finishTime;
				index = i;
			}
		}
	}
	// 把所有冲突job的isDetected设为true（包括它自己）
	for (int i = 0; i < n; i++) {
		if (isConflict(p[index], p[i])) {
			isDetected[i] = true;
		}
	}
	return index;
}

int main() {
	int n;
	cin >> n;
	Job* pJob = new Job[n];
	bool* isDetected = new bool[n];
	int si, fi;
	for (int i = 0; i < n; i++) {
		cin >> si >> fi;
		pJob[i].startTime = si;
		pJob[i].finishTime = fi;
		isDetected[i] = false;
	}
	int numOfJobs = 0;
	while (!isAllDetected(isDetected, n)) {
		int a = earliestFinish(pJob, isDetected, n);
		numOfJobs++;
	}

	cout << numOfJobs << endl;

	delete[] isDetected;
	delete[] pJob;
}