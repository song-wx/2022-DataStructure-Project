#include<iostream>
#include<string>
using namespace std;

typedef char ElemType;
#define MaxSize 100
typedef struct {
	ElemType data[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack*& s);
bool Push(SqStack*& s, ElemType e);
bool Pop(SqStack*& s);
bool GetTop(SqStack* s, ElemType& e);
bool StackEmpty(SqStack* s);
void DestroyStack(SqStack*& s);
bool Judge_Bracket(string input);


int main() {
	
	string input;
	getline(cin, input);
	cout << input<<endl;
	if (Judge_Bracket(input))
		cout << "correct";
	else cout << "error";

}


bool Judge_Bracket(string input) {
	SqStack* s;
	InitStack(s);
	int input_len = input.length();
	for (int i = 0; i < input_len; i++) {
		if (input[i] == '(' || input[i] == '[' || input[i] == '{')
			Push(s, input[i]);
		if (input[i] == ')') {
			char e;
			if (GetTop(s, e))
				if (e == '(')Pop(s);
				else return false;
			else return false;
		}
		if (input[i] == ']') {
			char e;
			if (GetTop(s, e))
				if (e == '[')Pop(s);
				else return false;
			else return false;
		}
		if (input[i] == '}') {
			char e;
			if (GetTop(s, e))
				if (e == '{')Pop(s);
				else return false;
			else return false;
		}
	}
	return true;
}


	void InitStack(SqStack * &s){
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

bool Push(SqStack*& s, ElemType e) {
	if (s->top == (MaxSize - 1))
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack*& s) {
	if (s->top == - 1)
		return false;
	s->top--;
	return true;
}

bool StackEmpty(SqStack* s) {
	return (s->top == -1);
}

void DestroyStack(SqStack*& s) {
	free(s);
}

bool GetTop(SqStack* s, ElemType& e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}