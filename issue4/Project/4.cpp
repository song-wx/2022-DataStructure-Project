#include<iostream>
#include<string>
using namespace std;

#define MaxSize 10
typedef char ElemType;
typedef struct node {
	ElemType data;
	struct node* lchild;
	struct node* rchild;
}BTNode;

typedef BTNode* ElemType1;
typedef struct {
	ElemType1 data[MaxSize];
	int top;
}SqStack;


void CreateBTree(BTNode*& b, string s);
void PreOrder(BTNode* b);
void PreOrder1(BTNode* b);
void BTWidth(BTNode* b, int k, int* width, int& max);
//栈相关函数，用于非递归先序遍历
void InitStack(SqStack*& s);
bool Push(SqStack*& s, ElemType1 e);
bool Pop(SqStack*& s, ElemType1 &e);
bool GetTop(SqStack* s, ElemType1& e);
bool StackEmpty(SqStack* s);
void DestroyStack(SqStack*& s);

int main() {
	string input; //= "A(B(D(,G),),C(E,F))";
	getline(cin, input);
	BTNode* n;
	CreateBTree(n, input);
	cout << "递归先序遍历：";
	PreOrder(n);
	cout << endl;
	cout << "非递归先序遍历：";
	PreOrder1(n);
	int width[MaxSize] = {0};
	int max = 0;
	BTWidth(n, 0, width, max);
	cout << endl;
	cout << "二叉树的宽度为：" << max;
}

//二叉树的括号表示法创建
void CreateBTree(BTNode*& b, string s) {
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;
	ch = s[j];
	while (ch != '\0') {
		switch (ch) {
		case'(':top++; St[top] = p; k = 1; break;
		case')':top--; break;
		case',':k = 2; break;
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)
				b = p;
			else {
				switch (k) {
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = s[j];

	}

}

//先序遍历递归
void PreOrder(BTNode* b) {
	if (b != NULL) {
		cout << b->data << " ";
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

//先序遍历非递归
void PreOrder1(BTNode* b) {
	BTNode* p;
	SqStack* st;
	InitStack(st);
	if (b != NULL) {
		Push(st, b);
		while (!StackEmpty(st)) {
			Pop(st, p);
			cout << p->data << " ";
			if (p->rchild != NULL)
				Push(st, p->rchild);
			if (p->lchild != NULL)
				Push(st, p->lchild);
		}
		cout << endl;
	}
	DestroyStack(st);
}



void InitStack(SqStack*& s) {
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

bool Push(SqStack*& s, ElemType1 e) {
	if (s->top == (MaxSize - 1))
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack*& s, ElemType1 &e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool StackEmpty(SqStack* s) {
	return (s->top == -1);
}

void DestroyStack(SqStack*& s) {
	free(s);
}

bool GetTop(SqStack* s, ElemType1& e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

void BTWidth(BTNode* b, int k, int* width, int& max){
	if (b == NULL) 
		return;
	width[k]++;
	max = max < width[k] ? width[k] : max;
	BTWidth(b->lchild, k + 1, width, max);
	BTWidth(b->rchild, k + 1, width, max);
}