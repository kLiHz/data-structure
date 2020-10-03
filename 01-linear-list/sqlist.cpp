//顺序表的基本运算
//数据元素从下标为1的位置开始存储
//源代码太阴间了！！！且不说对指针的引用，动态分配的内存也不释放...
//重写改写了一下...
//清华大学出版社 数据结构教程 第5版
//https://tieba.baidu.com/p/2166453720
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#define MAX_SIZE 30
#define bool int
#define true 1
#define false 0

typedef int ElemType;
typedef struct
{
	int length;
	ElemType data[MAX_SIZE + 1]; //注意：为了讲课方便顺序表中从data[1]开始存储，data[0]不用了。
} SqList;

void CreateList(SqList * L, ElemType a[], int n)
//将数组a[]中n个数据存储在顺序表L中，L初始为空表。
{
	int i;
	for (i = 1; i <= n; i++) L->data[i] = a[i];
	L->length = n;
}
SqList * InitList() //顺序表L初始化
{
	//申请空间用于存储顺序表L，返回指针变量ptr，指向空间首地址。
	SqList* ptr = (SqList*)malloc(sizeof(SqList)); 
	//记得将存储的数据个数改为0
	ptr->length = 0; 
	//在初始化时将顺序表清零，可选
	//memset(ptr,0,sizeof(SqList)); 
	return ptr;
}

void ReleaseSqList(SqList * ptr)
{
	free(ptr);
}

int ListLength(SqList *L)
//求顺序表L的长度
{
	return L->length;
}
bool GetElem(SqList *L, int i, ElemType * e)
//取出顺序表L中的第i个元素，将值存储在参数e指向的地址里
{
	if (i < 1 || i > L->length) return false; //索引越界
	else *e = L->data[i];
	return true;
}
int LocateElem(SqList *L, ElemType e)
//定位函数：确定值为e的元素在顺序表L中的位置
{
	int i = 1;
	while (i <= L->length && L->data[i] != e) i++;
	if (i <= L->length) return i; //若找到则返回下标i
	else return 0; //否则返回0
}
bool ListInsertElem(SqList * L, int i, ElemType e)
//将元素e插入到顺序表L中第i个位置
{
	if (i < 1 || i > L->length + 1 || L->length == MAX_SIZE)
		return false; //不能插入的情况1、2、3
	int j;
	for (j = L->length; j >= i; j--)
	{
		L->data[j + 1] = L->data[j];
	}
	L->data[i] = e;
	L->length++;
	return true;
}
bool ListDeleteElem(SqList * L, int i, ElemType * e)
//将顺序表L中第i个元素删除
{
	if (i < 1 || i > L->length)
		return false;
	*e = L->data[i];
	int j;
	for (j = i + 1; j <= L->length; j++)
	{
		L->data[j - 1] = L->data[j];
	}
	//for (j = i; i < L->length; ++j) L->data[j] = L->data[j + 1];
	L->length--;
	return true;
}
bool InsertXY(SqList * L, ElemType x, ElemType y)
//示例（1）试编写算法在值为x的元素之后插入值为y的元素。
{
	if (L->length == MAX_SIZE) return false;
	int i = 1;
	while (i <= L->length && L->data[i] != x) i++;
	if (i > L->length) return false;

	int j;
	for (j = L->length; j > i; j--)
	{ //将数据向后搬运
		L->data[j + 1] = L->data[j];
	}
	L->data[i + 1] = y;
	L->length++;
	return true;
}
//示例（2）试编写算法删除最后一个值为e的元素。
bool DeleteLastElem(SqList * L, ElemType e)
{
	int i = L->length;
	while (i > 0 && L->data[i] != e) i--;
	if (i == 0) return false;
	
	int j;
	for (j = i + 1; j <= L->length; j++)
	{ //将数据向前搬运
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	return true;
}
//示例（3）已知集合以顺序表方式存储，试编写算法求出两个集合的并集。
bool SqListUnion(SqList * La, SqList * Lb, SqList * Lc) //Lc存储La和Lb的并集
{
	int i, j;
	for (i = 1; i <= La->length; i++) //将集合La中所有元素存入Lc中
		Lc->data[i] = La->data[i];
	Lc->length = La->length;
	for (i = 1; i <= Lb->length; i++) //依次处理集合Lb中所有元素
	{
		if (Lc->length == MAX_SIZE) return false;
		//当前处理集合Lb中元素data[i]
		j = 1;
		while (j <= La->length && La->data[j] != Lb->data[i]) j++;
		//判断在集合La中是否有与其相同的元素
		if (j > La->length) //若集合La中没有相同的，则将Lb中元素data[i]添加在Lc最后。
		{
			Lc->length++;
			Lc->data[Lc->length] = Lb->data[i];
		}
		//另一种写法
		//if(!LocateElem(La,Lb->data[i])) ListInsertElem(Lc,Lc->length,Lb->data[i]);
	}
	return true;
}
void Deduplication(SqList * ptr)
//删除列表中重复元素
{
	int k = 1, i = 1; 
	//两个变量，k代表当前要写入的位置，i用来遍历顺序表
	while (i <= ptr->length) 
	{
		//当前讨论data[i]这个数据
		bool isExist = false; //记录当前元素是否已经存在。假设不存在
		for (int j = k - 1; j > 0; j--) //遍历之前的元素
		{ 
			if (ptr->data[i] == ptr->data[j]) 
			{
				isExist = true; //存在相同的元素
				break;
			}
		}
		//之前不存在相同的元素，则将data[i]写在k位置
		if (!isExist) {ptr->data[k] = ptr->data[i]; ++k;}
		++i; //循环变量+1
	}
	ptr->length = k - 1; //修改顺序表的长度
}

bool SqListIntersection(SqList * La, SqList * Lb, SqList * Lc) //求两个集合的交集
{
	int i, j;
	Lc->length = 0; //C用来存放结果，先将长度截为0
	for (i = 1; i <= La->length; i++) //依次处理集合La中所有元素
	{
		if (Lc->length == MAX_SIZE) return false;
		//当前处理集合La中元素data[i]
		//判断在集合Lb中是否有与其相同的元素
		bool exist_in_B = false; //假设B中没有该数据
		for (int j = 1; j <= Lb->length; ++j)
		{
			if (Lb->data[j] == La->data[i]) {
				exist_in_B = true;
				break;
			}
		}
		if (exist_in_B) //若集合Lb中有相同的
		{
			++(Lc->length); 
			Lc->data[Lc->length] = La->data[i]; //则将La中元素data[i]添加在Lc最后
		}
		//另一种写法
		//if(LocateElem(La,Lb->data[i])) ListInsertElem(Lc,Lc->length,Lb->data[i]);
	}
	Deduplication(Lc);
	return true;
}

bool SqListSubtract(SqList * La, SqList * Lb, SqList * Lc)
//求顺序表A-B，即从顺序表A中减去B中出现过的元素
{
	int i, j;
	Lc->length = 0; //C用来存放结果，先将长度截为0
	for (int i = 1; i <= La->length; i++)  //依次处理集合A中所有元素
	{
		if (Lc->length == MAX_SIZE) return false;
		bool not_exist_in_B = true; //先假设B中不含有该数据
		for (int j = 1; j <= Lb->length; ++j)
		{
			if (Lb->data[j] == La->data[i]) {
				not_exist_in_B = false;
				break;
			}
		}
		if (not_exist_in_B) //如果B中不含有该数据
		{ 
			++(Lc->length); 
			Lc->data[Lc->length] = La->data[i];
		}
	}
	return true;
}

void SqListDiff(SqList * La, SqList * Lb, SqList * Lc)
//求差集; 另，作业的差集指的是A-B...我..$#%..@*#%...
{
	SqList *L1,*L2;
	L1 = InitList();
	L2 = InitList();
	//一种方法
	//SqListUnion(La,Lb,L1);        //求并集
	//SqListIntersection(La,Lb,L2); //求交集
	//SqListSubtract(L1,L2,Lc);     //相减
	//另一种方法
	SqListSubtract(La,Lb,L1); //L1 = A - B
	SqListSubtract(Lb,La,L2); //L2 = B - A
	SqListUnion(L1,L2,Lc);    //C  = L1 + L2
	ReleaseSqList(L1); //记得释放内存
	ReleaseSqList(L2); //记得释放内存
}

void PrintSqList(SqList * ptr)
{
	for (int i = 1; i <= ptr->length; ++i) printf("%d ",ptr->data[i]);
	printf("\n");
}

/*
int main()
{
	SqList *La, *Lb, *Lc;
	ElemType a1[] = {0, 7, 2, 5, 8, 6};
	ElemType b1[] = {0, 3, 5, 9, 2};

	La = InitList();       //建立顺序表La
	CreateList(La, a1, 5); //La存储集合A
	PrintSqList(La);

	Lb = InitList();       //建立顺序表Lb
	CreateList(Lb, b1, 4); //Lb存储集合B
	PrintSqList(Lb);

	Lc = InitList();
	SqListUnion(La, Lb, Lc); //求并集Lc
	PrintSqList(Lc);

	SqList *L;
	ElemType a[] = {0, 11, 33, 44, 55, 77, 88, 99, 99};
	ElemType e;

	L = InitList();
	CreateList(L, a, 8);
	bool b;
	b = InsertXY(L, 44, 100);
	b = InsertXY(L, 55, 100);
	PrintSqList(L);
	b = DeleteLastElem(L, 444);
	PrintSqList(L);
	int len;
	len = ListLength(L);
	b = GetElem(L, 3, &e);
	int position;
	e = 55;
	position = LocateElem(L, e);
	b = ListInsertElem(L, 3, 100);
	PrintSqList(L);

	Deduplication(L);
	PrintSqList(L);

	b = ListDeleteElem(L, 4, &e);
	printf("e: %d\n", e);
	PrintSqList(L);

	ReleaseSqList(La);
	ReleaseSqList(Lb);
	ReleaseSqList(Lc);
	ReleaseSqList(L);

	return 0;
}*/

int main()
{
	int a[] = {0,3,4,4,5,5,6,6,6,7,8,8,8};
	int b[] = {0,3,4,4,4,8,9,10,11,12,12};
	SqList * L1 = InitList();
	SqList * L2 = InitList();
	CreateList(L1,a,12);
	CreateList(L2,b,10);
	
	Deduplication(L1);
	printf("L1: ");
	PrintSqList(L1);
	Deduplication(L2);
	printf("L2: ");
	PrintSqList(L2);

	SqList * L3 = InitList();
	SqListSubtract(L1,L2,L3);
	printf("L1 - L2: ");
	PrintSqList(L3);
	
	SqListUnion(L1,L2,L3);
	printf("L1 + L2: ");
	PrintSqList(L3);

	SqListIntersection(L1,L2,L3);
	printf("L1 ^ L2: ");
	PrintSqList(L3);

	SqListDiff(L1,L2,L3);
	printf("L1+L2 - (L1^L2): ");
	PrintSqList(L3);

	ReleaseSqList(L1);
	ReleaseSqList(L2);
	ReleaseSqList(L3);
}
