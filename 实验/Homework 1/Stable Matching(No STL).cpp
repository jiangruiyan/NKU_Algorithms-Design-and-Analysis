#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

// 最大可能的人数
const int MAX_N = 1000;

// 动态数组结构体
struct DynamicArray {
    char** data;    // 存储字符串指针
    int capacity;   // 容量
    int size;       // 当前大小
};

// 初始化动态数组
void initArray(DynamicArray* arr, int initialCapacity) {
    arr->data = new char* [initialCapacity];
    arr->capacity = initialCapacity;
    arr->size = 0;
}

// 添加元素到动态数组
void pushArray(DynamicArray* arr, const char* s) {
    if (arr->size >= arr->capacity) {
        // 扩容
        int newCapacity = arr->capacity * 2;
        char** newData = new char* [newCapacity];
        memcpy(newData, arr->data, arr->size * sizeof(char*));
        delete[] arr->data;
        arr->data = newData;
        arr->capacity = newCapacity;
    }
    arr->data[arr->size] = new char[strlen(s) + 1];
    strcpy(arr->data[arr->size], s);
    arr->size++;
}

// 队列结构体（链表实现）
struct QueueNode {
    char* value;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
};

// 初始化队列
void initQueue(Queue* q) {
    q->front = q->rear = nullptr;
}

// 入队
void enqueue(Queue* q, const char* s) {
    QueueNode* newNode = new QueueNode;
    newNode->value = new char[strlen(s) + 1];
    strcpy(newNode->value, s);
    newNode->next = nullptr;
    if (q->rear == nullptr) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 出队
char* dequeue(Queue* q) {
    if (q->front == nullptr) return nullptr;
    QueueNode* temp = q->front;
    char* value = temp->value;
    q->front = q->front->next;
    if (q->front == nullptr) q->rear = nullptr;
    delete temp;
    return value;
}

// 哈希表结构体（简单实现，用于女性排名）
struct HashEntry {
    char* key;
    int value;
    HashEntry* next;
};

struct HashMap {
    HashEntry** table;
    int capacity;
};

// 初始化哈希表
void initHashMap(HashMap* map, int capacity) {
    map->table = new HashEntry * [capacity];
    memset(map->table, 0, capacity * sizeof(HashEntry*));
    map->capacity = capacity;
}

// 插入键值对
void hashPut(HashMap* map, const char* key, int value) {
    unsigned long hash = 5381;
    int c;
    const char* str = key;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c; // djb2 hash
    int index = hash % map->capacity;

    HashEntry* entry = new HashEntry;
    entry->key = new char[strlen(key) + 1];
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = map->table[index];
    map->table[index] = entry;
}

// 获取值
int hashGet(HashMap* map, const char* key) {
    unsigned long hash = 5381;
    int c;
    const char* str = key;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    int index = hash % map->capacity;

    HashEntry* entry = map->table[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return entry->value;
        entry = entry->next;
    }
    return -1; // 未找到
}

// 字符串分割函数
DynamicArray split(const char* s, char delim) {
    DynamicArray arr;
    initArray(&arr, 10);
    char buffer[1000];
    int j = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == delim) {
            buffer[j] = '\0';
            pushArray(&arr, buffer);
            j = 0;
        }
        else {
            buffer[j++] = s[i];
        }
    }
    buffer[j] = '\0';
    pushArray(&arr, buffer);
    return arr;
}

// 主函数
int main() {
    int n;
    cin >> n;
    cin.ignore(); // 跳过换行符

    // 男性偏好：名字 -> 偏好列表
    char* man_names[MAX_N];
    DynamicArray man_prefs[MAX_N];
    for (int i = 0; i < n; i++) {
        char line[1000];
        cin.getline(line, 1000);
        char* colon = strchr(line, ':');
        *colon = '\0';
        char* name = line;
        char* prefs = colon + 1;

        man_names[i] = new char[strlen(name) + 1];
        strcpy(man_names[i], name);
        man_prefs[i] = split(prefs, '>');
    }

    // 女性偏好：名字 -> 排名（哈希表）
    char* woman_names[MAX_N];
    HashMap woman_ranks[MAX_N];
    for (int i = 0; i < n; i++) {
        char line[1000];
        cin.getline(line, 1000);
        char* colon = strchr(line, ':');
        *colon = '\0';
        char* name = line;
        char* prefs = colon + 1;

        woman_names[i] = new char[strlen(name) + 1];
        strcpy(woman_names[i], name);
        DynamicArray prefs_arr = split(prefs, '>');
        HashMap ranks;
        initHashMap(&ranks, 100);
        for (int j = 0; j < prefs_arr.size; j++) {
            hashPut(&ranks, prefs_arr.data[j], j);
        }
        woman_ranks[i] = ranks;
    }

    // 初始化队列和配对关系
    Queue free_men;
    initQueue(&free_men);
    for (int i = 0; i < n; i++) enqueue(&free_men, man_names[i]);

    char* women_engaged_to[MAX_N] = { nullptr };
    char* men_engaged_to[MAX_N] = { nullptr };
    int next_proposal_index[MAX_N] = { 0 };

    // Gale-Shapley 算法
    while (free_men.front != nullptr) {
        char* m = dequeue(&free_men);
        int man_idx = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(man_names[i], m) == 0) {
                man_idx = i;
                break;
            }
        }
        if (man_idx == -1) continue;

        if (next_proposal_index[man_idx] >= man_prefs[man_idx].size) continue;
        char* w = man_prefs[man_idx].data[next_proposal_index[man_idx]];
        next_proposal_index[man_idx]++;

        int woman_idx = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(woman_names[i], w) == 0) {
                woman_idx = i;
                break;
            }
        }
        if (woman_idx == -1) continue;

        if (women_engaged_to[woman_idx] == nullptr) {
            women_engaged_to[woman_idx] = m;
            men_engaged_to[man_idx] = w;
        }
        else {
            char* current_m = women_engaged_to[woman_idx];
            int current_rank = hashGet(&woman_ranks[woman_idx], current_m);
            int new_rank = hashGet(&woman_ranks[woman_idx], m);
            if (new_rank < current_rank) {
                women_engaged_to[woman_idx] = m;
                men_engaged_to[man_idx] = w;
                // 找到被替换的男性的索引
                int replaced_man_idx = -1;
                for (int i = 0; i < n; i++) {
                    if (strcmp(man_names[i], current_m) == 0) {
                        replaced_man_idx = i;
                        break;
                    }
                }
                if (replaced_man_idx != -1) {
                    men_engaged_to[replaced_man_idx] = nullptr;
                    enqueue(&free_men, current_m);
                }
            }
            else {
                enqueue(&free_men, m);
            }
        }
    }

    // 按男性名字排序输出
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(man_names[i], man_names[j]) > 0) {
                swap(man_names[i], man_names[j]);
                swap(men_engaged_to[i], men_engaged_to[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "(" << man_names[i] << "," << men_engaged_to[i] << ")" << endl;
    }

    // 释放内存（略，实际需遍历所有动态分配的结构）

    return 0;
}