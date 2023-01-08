#include<iostream>
using namespace std;

typedef struct
{
	int key;
}RecType;

void InsertSort(RecType R[], int n);
void BinInsertSort(RecType R[], int n);
void ShellSort(RecType R[], int n);
void BubbleSort(RecType R[], int n);
int partition(RecType R[], int s, int t);
void QuickSort(RecType R[], int s, int t);
void Merge(RecType R[], int low, int mid, int high);
void MergePass(RecType R[], int length, int n);
void MergeSort(RecType R[], int n);

#define num 10000
RecType sequence1[num];
RecType sequence2[num];
RecType sequence3[num];

int main() {
	//cout << "待排序数据：" << endl;
	for (int i = 0; i < num; i++)
	{
		sequence1[i].key = (int)rand() % 1000;
		sequence2[i].key = (int)rand() % 1000;
		sequence3[i].key = (int)rand() % 1000;
		//cout << sequence1[i].key<<" ";
	}
	//cout << endl;

	clock_t start, end;
	float time1, time2, time3;

	cout << "二路归并排序：" << "排序数量为" << num << endl;

	start = clock();
	MergeSort(sequence1, num);
	end = clock();
	time1 = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "第一次排序耗时：" << time1 << endl;

	start = clock();
	MergeSort(sequence2, num);
	end = clock();
	time2 = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "第二次排序耗时：" << time2 << endl;

	start = clock();
	MergeSort(sequence3, num);
	end = clock();
	time3 = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "第三次排序耗时：" << time3 << endl;

	cout << "平均耗时：" << (time1 + time2 + time3) / 3;


	//BinInsertSort(sequence1, num);
	//ShellSort(sequence, num);
	//BubbleSort(sequence, num);
	//QuickSort(sequence, 0, num-1);
	//MergeSort(sequence, num-1);

	/*cout << "排序后数据：" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << sequence1[i].key<<" ";
	}*/
}



void InsertSort(RecType R[], int n) {
	int i, j; RecType temp;
	for (i = 1; i < n; i++) {
		if (R[i].key < R[i - 1].key) {
			temp = R[i];
			j = i - 1;
			do {
				R[j + 1] = R[j];
				j--;
			} while (j >= 0 && R[j].key > temp.key);
			R[j + 1] = temp;

		}
	}
}



void BinInsertSort(RecType R[], int n) {
	int i, j, low, high, mid;
	RecType temp;
	for (i = 1; i < n; i++) {
		if (R[i].key < R[i - 1].key) {
			temp = R[i];
			low = 0; high = i - 1;
			while (low <= high) {
				mid = (low + high) / 2;
				if (temp.key < R[mid].key)
					high = mid - 1;
				else
					low = mid + 1;
			}
			for (j = i - 1; j >= high + 1; j--)
				R[j + 1] = R[j];
			R[high + 1] = temp;
		}
	}
}


void ShellSort(RecType R[], int n) {
	int i, j, d;
	RecType temp;
	d = n / 2;
	while (d > 0) {
		for (i = d; i < n; i++) {
			temp = R[i];
			j = i - d;
			while (j >= 0 && temp.key < R[j].key)
			{
				R[j + d] = R[j];
				j = j - d;
			}
			R[j + d] = temp;
		}
		d = d / 2;

	}
}

void BubbleSort(RecType R[], int n) {
	int i, j;
	bool exchange;
	for (i = 0; i < n - 1; i++)
	{
		exchange = false;
		for (j = n - 1; j > i; j--)
			if (R[j].key < R[j - 1].key)
			{
				swap(R[j], R[j - 1]);
				exchange = true;
			}
		if (!exchange)
			return;
	}
}

int partition(RecType R[], int s, int t) {
	int i = s, j = t;
	RecType temp = R[i];
	while (i < j) {
		while (j > i && R[j].key >= temp.key)
			j--;
		R[i] = R[j];
		while (i < j && R[i].key <= temp.key)
			i++;
		R[j] = R[i];

	}
	R[i] = temp;
	return i;
}

void QuickSort(RecType R[], int s, int t) {
	int i;
	if (s < t) {
		i = partition(R, s, t);
		QuickSort(R, s, i - 1);
		QuickSort(R, i + 1, t);
	}
}

void Merge(RecType R[], int low, int mid, int high)
{
	RecType* R1;
	int i = low, j = mid + 1, k = 0;

	R1 = (RecType*)malloc((high - low + 1) * sizeof(RecType));
	while (i <= mid && j <= high)
		if (R[i].key <= R[j].key)
		{
			R1[k] = R[i];
			i++; k++;
		}
		else {
			R1[k] = R[j];
			j++; k++;
		}
	while (i <= mid)
	{
		R1[k] = R[i];
		i++; k++;
	}
	while (j <= high) {
		R1[k] = R[j];
		j++; k++;
	}
	for (k = 0, i = low; i <= high; k++, i++)
		R[i] = R1[k];
	free(R1);
}

void MergePass(RecType R[], int length, int n) {
	int i;
	for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length)
		Merge(R, i, i + length - 1, i + 2 * length - 1);
	if (i + length - 1 < n - 1)
		Merge(R, i, i + length - 1, n - 1);

}

void MergeSort(RecType R[], int n) {
	int length;
	for (length = 1; length < n; length = 2 * length)
		MergePass(R, length, n);

}