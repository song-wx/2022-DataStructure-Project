#include<iostream>
using namespace std;

#define num 7
#define MaxSize 2*num-1
typedef struct {
	int data;
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;

typedef HTNode ElemType;
typedef struct {
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;

void CreateHT(HTNode ht[], int n0);
void BFS(HTNode ht[], int v);
void InitQueue(SqQueue*& q);
void DestroyQueue(SqQueue*& q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue*& q, ElemType e);
bool deQueue(SqQueue*& q, ElemType& e);


int main() {
	HTNode ht[2 * num - 1];
	int weight[num] = { 11, 1, 15, 33, 19, 41, 7};
	cout << "初始的序列为：";
	for (int i = 0; i < num; i++) {
		ht[i].weight = weight[i];
		cout << weight[i] << " ";
	}
	CreateHT(ht, num);
	cout <<endl<< "使用广度优先搜索输出的哈夫曼树为：";
	BFS(ht, 2*num-2);
}

void CreateHT(HTNode ht[], int n0) {
	int i, k, lnode, rnode;
	double min1, min2;
	for (i = 0; i < 2 * n0 - 1; i++)
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	for (i = n0; i <= 2 * n0 - 2; i++) {
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for(k=0;k<=i-1;k++)
			if (ht[k].parent == -1) {
				if (ht[k].weight < min1) {
					min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight < min2) {
					min2 = ht[k].weight;
					rnode = k;
				}
			}
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[i].lchild = lnode;
		ht[i].rchild = rnode;
		ht[lnode].parent = i;
		ht[rnode].parent = i;
	}
}

void BFS(HTNode ht[], int v) {
	int i;
	HTNode w;
	SqQueue* qu;
	InitQueue(qu);
	int visited[MaxSize];
	for (i = 0; i < (MaxSize); i++)visited[i] = 0;
	cout << ht[v].weight << " ";
	visited[v] = 1;
	enQueue(qu, ht[v]);
	while (!QueueEmpty(qu)) {
		deQueue(qu, w);//由于哈夫曼树每个节点相邻的只有父节点和左右子节点，所以只需考虑这三种情况
		if ((visited[w.parent] != 1) && (w.parent != -1)) {
			cout << ht[w.parent].weight << " ";
			visited[w.parent] = 1;
			enQueue(qu, ht[w.parent]);
		}
		if ((visited[w.lchild] != 1) && (w.lchild != -1)) {
			cout << ht[w.lchild].weight << " ";
			visited[w.lchild] = 1;
			enQueue(qu, ht[w.lchild]);
		}
		if ((visited[w.rchild] != 1) && (w.rchild != -1)) {
			cout << ht[w.rchild].weight << " ";
			visited[w.rchild] = 1;
			enQueue(qu, ht[w.rchild]);
		}
	}
}

void InitQueue(SqQueue*& q) {
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
}

void DestroyQueue(SqQueue*& q) {
	free(q);
}

bool QueueEmpty(SqQueue* q) {
	return(q->front == q->rear);
}

bool enQueue(SqQueue*& q, ElemType e) {
	if ((q->rear + 1) % (MaxSize) == q->front)
		return false;
	q->rear = (q->rear + 1) % (MaxSize);
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue*& q, ElemType &e) {
	if (q->rear == q->front)
		return false;
	q->front = (q->front + 1) % (MaxSize);
	e = q->data[q->front];
	return true;
}