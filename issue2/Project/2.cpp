#include<iostream>
using namespace std;

typedef struct Node {

	int data;

	Node* next;

}LinkNode;

#define num 10
typedef int ElemType;
void CreatList(LinkNode*& L, ElemType a[], int n);
void DispList(LinkNode* L);
void sort(LinkNode* L);
LinkNode* combine(LinkNode* L, LinkNode* M);

int main() {
	//int A[6] = { 12, 1, 23, 35, 21, 60 };
	//int B[6] = { 90, 60, 10, 15, 25, 56 };
	int sample1[num];
	int sample2[num];
	srand(3);
	cout << "数组1：" << endl;
	for (int i = 0; i < num; i++)
	{
		sample1[i] = (int)rand() % 100;
		cout << sample1[i] << " ";
	}
	cout << endl;
	cout << "数组2：" << endl;
	for (int i = 0; i < num; i++)
	{
		sample2[i] = (int)rand() % 100;
		cout << sample2[i] << " ";
	}
	cout << endl;

	LinkNode* L, * M, * N;
	CreatList(L, sample1, num);
	CreatList(M, sample2, num);
	sort(L);
	sort(M);
	cout << "有序单链表1：" << endl;
	DispList(L);
	cout << "有序单链表2：" << endl;
	DispList(M);
	N = combine(L, M);
	cout << "合并后："<<endl;
	DispList(N);
}

void CreatList(LinkNode*& L, ElemType a[], int n) {
	LinkNode* s;
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

void DispList(LinkNode* L) {
	LinkNode* p = L->next;
	while (p != NULL) {
		cout << p->data<<" ";
		p = p->next;
	}
	cout << endl;
}

void sort(LinkNode* L) {
	LinkNode* p, * pre, * q;
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && pre->next->data < p->data)
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

LinkNode* combine(LinkNode* L, LinkNode* M) {
	LinkNode* N = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* a = L->next, * b = M->next, * c = N;
	while (a != NULL && b != NULL) {
		if (a->data < b->data) {
			c->next = a;
			a = a->next;
			c = c->next;
		}
		else {
			c->next = b;
			b = b->next;
			c = c->next;
		}
	}

	if (a == NULL)
		c->next = b;
	if (b == NULL)
		c->next = a;
	return N;
}