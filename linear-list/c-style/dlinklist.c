#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	struct Node *prev, *next;
    int located_times; //被访问(locate)次数; 排序、插入后记得归0
    //LocateElem()会增加元素的访问次数，并且上浮元素的位置。
} DLinkList;

typedef DLinkList DLinkNode;

#define bool  int
#define true  1
#define false 0

DLinkList* CreateDLinkList()
{
	DLinkNode * node = (DLinkNode *)malloc(sizeof(DLinkList));
	//为了编程方便，用一个空节点作为双向链表的头/尾节点，不存数据
	//这个双向链表可以理解为一个循环的结构
	if (node != NULL) {
        node->prev = node;
        node->next = node;
        node->located_times = -1;
    }
    return node;
}

void ReleaseDLinkList(DLinkList * L) {
    DLinkNode *p = L->next, *t;
    while (p != L) {
        t = p;
        p = p->next;
        free(t);
    }
    free(p);
}

void EmptyDLinkList(DLinkList * L) {
    DLinkNode *p = L->next, *t;
    while (p != L) {
        t = p;
        p = p->next;
        free(t);
    }
}

//将数组插入循环双向链表
void InsertArray(DLinkNode * L, int a[], int n)
{
    DLinkNode * future_tail = L;
    DLinkNode * p = L->prev;
    int cnt = 0;
    while (cnt < n) {
        p->next = (DLinkNode*)malloc(sizeof(DLinkNode));
        p->next->prev = p;
        p = p->next;
        p->value = a[cnt];
        ++cnt;
    }
    //最后再将链表接在一起可以减少循环中的赋值！
    p->next = future_tail;
    future_tail->prev = p;
    //归零所有元素访问次数
    DLinkNode * i = p->prev, * j = p;
    while (i->located_times != -1) { //locate_times为-1的节点是头节点
        i->located_times = 0;
        i = i->prev;
    }
    while (j->located_times != -1) {
        j->located_times = 0;
        j = j->next;
    }
    //体会循环链表所带来的的相同作用的不同写法
	/*DLinkList *s;
	for (int i = 0; i < n; i++)
	{
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->value = a[i];
		s->next = L;
		s->prev = L->prev;
		L->prev->next = s;
		L->prev = s;
	}*/
}

//其实应该再写一个将链表插入链表的函数的

//返回链表中值为elem的元素的位置, 访问频度元素高的元素会被前移
DLinkNode* LocateElem(DLinkList * L, int elem)
{
    DLinkNode * p = L->next;
    DLinkNode * n = L->next;
    while (p != L && p->value != elem) {
        if (p->located_times != n->located_times) {
            n = p;
        }
        p = p->next;
    }
    if (p == L) return NULL;
    else {
        if (n != p) {
            //将p插入到n->prev和n之间的位置
            p->prev->next = p->next;
            p->next->prev = p->prev;
            n->prev->next = p;
            p->prev = n->prev;
            p->next = n;
            n->prev = p;
        }
        ++(p->located_times);
        return p;
    }
}

//在节点p之前插入一个元素
void InsertDLinkNode(DLinkNode * p, int elem)
{
    DLinkNode * s = (DLinkNode*)malloc(sizeof(DLinkNode));
    s->value = elem;
    p->prev->next = s;
    s->prev = p->prev;
    s->next = p;
    p->prev = s;
    //归0所有元素被访问次数
    DLinkNode * i = s->prev, * j = s;
    while (i->located_times != -1) { //locate_times为-1的节点是头节点
        i->located_times = 0;
        i = i->prev;
    }
    while (j->located_times != -1) {
        j->located_times = 0;
        j = j->next;
    }
}

//删除节点p
void DeleteDLinkNode(DLinkNode * p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

//示例：判断双向循环链表是否按值对称
bool IsSymmetricalDLinkList(DLinkList *L)
{
	DLinkList *p, *q;
	p = L->next;
	q = L->prev;
	while (p != q && q->next != p) {
        if (p->value == q->value){
			p = p->next;
			q = q->prev;
		}
        else return false;
    }
    return true;
}

void PrintDLinkList(DLinkList * L)
{
    DLinkNode * p = L->next;
    while (p != L) {
        printf("%d ", p->value);
        //printf("%d(%d) ", p->value, p->located_times);
        p = p->next;
    }
    printf("\n");
}

int main()
{
	DLinkList *L = CreateDLinkList();
	int a[] = {11, 22, 33, 44, 55, 66, 77};
    InsertArray(L,a,7);
    LocateElem(L,44); printf("After locating %d: ",44); PrintDLinkList(L);
    LocateElem(L,55); printf("After locating %d: ",55); PrintDLinkList(L);
    LocateElem(L,55); printf("After locating %d: ",55); PrintDLinkList(L);
    LocateElem(L,55); printf("After locating %d: ",55); PrintDLinkList(L);
    LocateElem(L,66); printf("After locating %d: ",66); PrintDLinkList(L);
    LocateElem(L,66); printf("After locating %d: ",66); PrintDLinkList(L);
    LocateElem(L,66); printf("After locating %d: ",66); PrintDLinkList(L);
    LocateElem(L,66); printf("After locating %d: ",66); PrintDLinkList(L);
    LocateElem(L,66); printf("After locating %d: ",66); PrintDLinkList(L);
    ReleaseDLinkList(L);
    return 0;
}
