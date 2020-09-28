//顺序表 递增有序
//从下标为0处开始存储 
#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 30

typedef struct
{
	int length;
	int data[MAX_SIZE]; //从下标为0处开始存储 
} SqAscList;

void CreateList(SqAscList * L, int a[], int n)
//将数组a[]中n个数据存储在顺序表L中，L初始为空表。
{
	int i;
	for (i = 0; i < n; i++) L->data[i] = a[i];
	L->length = n;
}
SqAscList * InitList()
//顺序表L初始化
{
	//申请空间用于存储顺序表L，返回指针变量ptr，指向空间首地址。
	SqAscList* ptr = (SqAscList*)malloc(sizeof(SqAscList)); 
	ptr->length = 0;
	return ptr;
}

int FindElem(SqAscList * L, int target) 
//顺序表元素升序，二分查找，返回元素的下标；可升级为返回指针或者引用（C++）
{
	int x = 0, y = L->length;
	while (x <= y)
	{
		int mid = (x+y)/2;
		if (L->data[mid] == target) return mid;
		else if (L->data[mid] < target) x = mid + 1;
		else y = mid - 1;
	}
	return -1;
}

bool InsertElem(SqAscList * L, int target)
//已知顺序表按值递增有序, 将元素插入到顺序表, 使其仍然有序。
{
	if (L->length == MAX_SIZE) return false;
	int i = 0;
	while(i < L->length && target >= L->data[i]) ++i; 
	for (int j = L->length; j > i; --j)
	{
		L->data[j] = L->data[j-1];
	}
	L->data[i] = target; 
	++(L->length);
	return true;
}

void Deduplication(SqAscList* L)
{
//	int i;
//	for(i = 0; i < L->length; ++i)
//	{
//		int j = i;
//		while (j < L->length && L->data[j] == L->data[i-1]) ++j;
//		for (; j < L->length; ++j)
//		{
//			L->data[i] = L->data[j];
//			++i;
//		}
//	}
	int new_length = 1, i = 1;
	while (i < L->length)
	{
		if (L->data[i] != L->data[i-1]) {
			L->data[new_length] = L->data[i];
			++new_length;
		}
		++i;
	}
	L->length = new_length;
}

void ReleaseSqList(SqAscList * ptr)
{
	free(ptr);
}

void PrintSqList(SqAscList * ptr)
{
	for (int i = 0; i < ptr->length; ++i) printf("%d ",ptr->data[i]);
	printf("\n");
}

bool SqAscListUnion(SqAscList * La, SqAscList * Lb, SqAscList * Lc) 
//Lc存储La和Lb的并集, 并自动去重
{
	Lc->length = 0;
	int i = 0, j = 0; //设置两个下标变量分别循环La, Lb
	while(i < La->length && j < Lb->length) 
	{
		if (Lc->length == MAX_SIZE) return false;
		//两个顺序表已有序且递增，依次放入新的表
		//如果之后有相邻的元素，全部跳过
		while(i < La->length - 1 && La->data[i] == La->data[i+1]) ++i;
		while(j < Lb->length - 1 && Lb->data[j] == Lb->data[j+1]) ++j;
		if (La->data[i] == Lb->data[j]) {
			++j;
			while(j < Lb->length - 1 && Lb->data[j] == Lb->data[j+1]) ++j;
		}
		if (La->data[i] < Lb->data[j]) {
			Lc->data[Lc->length] = La->data[i];
			++i; 
		}
		else {
			Lc->data[Lc->length] = Lb->data[j];
			++j; 
		}
		++(Lc->length); 
	}
	//处理某一顺序表剩余的部分
	while(i < La->length) {
		Lc->data[(Lc->length)++] = La->data[i];
		++i;
		while(i < La->length && La->data[i] == La->data[i-1]) ++i;
	}
	while(j < Lb->length) {
		Lc->data[(Lc->length)++] = Lb->data[j];
		++j;
		while(j < Lb->length && Lb->data[j] == Lb->data[j-1]) ++j;
	}
	return true;
}

bool SqAscListMerge(SqAscList * La, SqAscList * Lb, SqAscList * Lc) 
//Lc存储La和Lb的合并
{
	Lc->length = 0;
	int i = 0, j = 0; //设置两个下标变量分别循环La, Lb
	while(i < La->length && j < Lb->length) 
	{
		if (Lc->length == MAX_SIZE) return false;
		//两个顺序表已有序且递增，依次放入新的表
		if (La->data[i] < Lb->data[j]) {
			Lc->data[Lc->length] = La->data[i];
			++i; 
		}
		else {
			Lc->data[Lc->length] = Lb->data[j];
			++j; 
		}
		++(Lc->length); 
	}
	//处理某一顺序表剩余的部分
	while(i < La->length) {
		Lc->data[(Lc->length)++] = La->data[i];
		++i;
	}
	while(j < Lb->length) {
		Lc->data[(Lc->length)++] = Lb->data[j];
		++j;
	}
	return true;
}

void SqAscListSubtract(SqAscList * La, SqAscList * Lb, SqAscList * Lc)
{
	Lc->length = 0;
	for (int i = 0; i < La->length; ++i) {
		bool exist_in_B = false;
		for (int j = 0; j < Lb->length; ++j) {
			if (Lb->data[j] == La->data[i]) {
				exist_in_B = true;
				break;
			}
		}
		if (!exist_in_B) {
			Lc->data[Lc->length] = La->data[i];
			++(Lc->length); 
		}
	}
}

/*void SqAscListIntersection(SqAscList * La, SqAscList * Lb, SqAscList * Lc)
//集合有序，可简化到O(n)的复杂度
{
	int i = 0, j = 0;
	if (La->length == 0 || Lb->length == 0) 
	{ //集合有一个为空，返回空集
		Lc->length = 0;
		return;
	}
	Lc->length = 0;
	while (i < La->length && j < Lb->length)
	{
		while(i < La->length - 1 && La->data[i] == La->data[i+1]) ++i;
		while(j < Lb->length - 1 && Lb->data[j] == Lb->data[j+1]) ++j;
		if (La->data[i] == Lb->data[j]) Lc->data[(Lc->length)++] = La->data[i];
		else if (La->data[i] < Lb->data[j]) ++i;
		else ++j; 
	}
}*/

//bool SqAscListDiff(SqAscList * La, SqAscList * Lb, SqAscList * Lc);

int main()
{
	int a[] = {2,3,4,4,5,5,6,6,6,7,8,8,8};
	int b[] = {3,3,4,4,4,8,9,10,11,12,12};
	SqAscList * L1 = InitList();
	SqAscList * L2 = InitList();
	CreateList(L1,a,13);
	CreateList(L2,b,11);
	
	Deduplication(L1);
	printf("L1: ");
	PrintSqList(L1);
	printf("L2: ");
	PrintSqList(L2);

	SqAscList * L3 = InitList();
	SqAscListSubtract(L1,L2,L3);
	printf("L1 - L2: ");
	PrintSqList(L3);
	
	InsertElem(L3,4);
	printf("L3 <- 4: ");
	PrintSqList(L3);
	
	SqAscListUnion(L1,L2,L3);
	printf("L1 + L2: ");
	PrintSqList(L3);
	
	SqAscListMerge(L1,L2,L3);
	printf("L1 ++ L2: ");
	PrintSqList(L3);

	//SqAscListIntersection(L1,L2,L3);
	printf("L1 ^ L2: ");
	PrintSqList(L3);

	ReleaseSqList(L1);
	ReleaseSqList(L2);
	ReleaseSqList(L3);
}