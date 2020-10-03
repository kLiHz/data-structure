#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include<iostream>

#define bool int
#define true 1
#define false 0

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkNode;

LinkNode * InitList();
void ReleaseList(LinkNode * head);
void EmptyList(LinkNode * head);
bool IsEmptyList(LinkNode * L);
int ListLength(LinkNode * p);
void DisplayList(LinkNode * p);
bool GetElem(LinkNode * p, int i, ElemType * e);
int LocateElem(LinkNode * p, ElemType e);
bool ListInsert(LinkNode *p, int i, ElemType e);
bool ListDelete(LinkNode *p, int i, ElemType * e);
void InsertArrayListFront(LinkNode *L, ElemType a[], int n);
void InsertArrayListRear(LinkNode *L, ElemType a[], int n);

//示例（1）已知单链表L中所有元素均为整数，试编写算法在值为x的元素之前插入值为y的元素。
bool InsertXY(LinkNode * p, ElemType x, ElemType y);
//示例 （2）已知单链表L中所有元素均为整数，试编写算法逆置单链表。
//思路：从头至尾依次将每个元素头插到单链表中
void ReverseList(LinkNode * L);
//（3）已知单链表(无序)L中所有元素均为整数，试编写算法中清除多余的重复元素。
void Deduplication(LinkNode * L);

//说明，这个demo里面，一个节点可以是一个链表的头结点(编号为0)
//数据从1开始编号
//即一个节点是一个链表
//一个空节点是一个空链表
//空链表是一个为空的节点
//一个链表里的节点拿出来又是一个链表，真棒
//mdzz，这谁整的明白啊&%……$#!&

//每日diss教材：非要浪费一个空间来做这件事吗? 用一个指针不就好了
//还有List，Node不分家好吗?不太方便理解吧...至少也说明白吧
//其实你直接弄出来的L还不是个头指针，所以tmd有必要弄个什么神必的头节点吗?
//所以还是用一个指针指向首节点吧...存储指针记为链表
//或者再建一个链表的struct是不是可行?
//老师把ListNode定义成LinkList也是 用心良苦 了,,,..
//总之这概念就很混乱好不好，学个鬼的数据结构啊
//vc6和这本书都给我西内吧啊啊啊！！！

//typedef struct {
//    int length;
//    LNode * head_ptr = NULL; //头指针
//};

//所以再定义一个List的结构不好吗?
//就tm离谱离谱离谱！！

//而且还是要diss这阴间的指针的引用，
//你tm带头在函数里改指针鬼知道别人写代码时会发生什么错误??
//所以和顺序表一样，这里的代码和教材上不会完全相同

//（4）已知两个单链表按值递增有序存储，试编写算法利用归并法将两个单链表合并成一个。
void AscMerge(LinkNode * LA, LinkNode * LB, LinkNode * LC); //C = A + B

//1. 已知单链表L为按值递增有序的，编写算法将数据元素e插入到单链表L中，使之仍有序。
void AscListInsert(LinkNode * p, ElemType e);
//2. 编写算法删除单链表L中最后一个值为e的数据元素。
bool DeleteLastE(LinkNode * p, ElemType e);
//3. 已知单链表L为按值递增有序的，编写算法将数据元素值在区间[low , high]内的所有结点取出建立一个按值递增的新单链表L1。
void ValueAB(LinkNode * p, ElemType low, ElemType high, LinkNode * L1);
//4. 已知两个集合分别按值递增有序存储在单链表La和Lb中，
//编写算法利用归并法分别求出两个集合的交集、并集和差集，皆为按值递增有序。
//(要求：保留La和Lb两个链表，建立新的链表存储结果)。
void AscListUnion(LinkNode *La, LinkNode * Lb, LinkNode * Lc);
void AscListIntersection(LinkNode *La, LinkNode * Lb, LinkNode * Lc);
void AscListSubtract(LinkNode *La, LinkNode * Lb, LinkNode * Lc);

#endif