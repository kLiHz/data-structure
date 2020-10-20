#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkNode;

typedef LinkNode LinkList;

#define bool  int
#define true  1
#define false 0

LinkNode * CreateCLinkList() { //设置rear指向链表的尾结点且唯一确定此有序循环单链表
    LinkNode * node = (LinkNode*)malloc(sizeof(LinkNode));
    node->next = node;
    return node;
}

LinkNode * ConstructCLinkList(ElemType a[], int n) {
    LinkNode * rear = CreateCLinkList();
    LinkNode * p = rear;
    for (int i = 0; i < n - 1; ++i) {
        p->next = (LinkNode*)malloc(sizeof(LinkNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = rear;
    p = p->next;
    p->data = a[n - 1];
    return rear;
}

void DisplayCLinkList(LinkNode * rear)
{
    if (rear == NULL) return;
    LinkNode * p = rear->next;
    while (p != rear) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("%d \n", rear->data);
}

LinkNode * ReleaseCLinkList(LinkList * rear) {
    if (rear == NULL) return NULL;
    LinkNode * p = rear->next;
    while (p != rear) {
        LinkNode * t = p;
        p = p->next;
        free(t);
    }
    free(rear);
    return NULL;
}

//循环单链表的插入法排序；升序
LinkNode * SortCLiinkList(LinkNode * rear) { 
    if (rear == NULL) return NULL;
    //r 指针记录有序区间的最末一个元素，用来优化排序速度
    LinkNode * r = rear->next;
    //l 指针记录链表初始位置，用于递归终止条件的判断
    LinkNode * l = rear->next;
    //p2 用来遍历循环单链表
    if (rear == r) return rear;  //只有一个元素，直接return
    while (r != rear) {
        LinkNode * s = r->next;
        //因为链表没有头节点，所以rear结点需要单独讨论
        if (s->data < r->data) {
            if (s == rear) rear = r;
            //数据小于有序区间末端时才查找插入位置
            LinkNode * i = rear; //i 用来循环有序区间寻找插入位置
            while (i != r && s->data > i->next->data) {
                i = i->next;
            }
            //数据应该插入在i和i->next之间
            r->next = s->next;
            s->next = i->next;
            i->next = s;
            //有序区间末端为r保持不变
        }
        else {
            if (s == rear) r = rear;
            else r = s; //准备讨论下一个元素
        }
    }
    return rear;
}

LinkNode * FindElement(LinkNode * rear, ElemType elem)
{
    LinkNode * i = rear->next;
    while(i != rear && i->data != elem) { i = i->next; }
    if (i == rear) {
        if (i->data == elem) return i;
        else return NULL;
    }
    else return i;
}

LinkList * SubCLinkList(LinkNode * a, LinkNode * b)
{
    if (a == NULL || b == NULL) return NULL;
    LinkNode * rear = (LinkNode *)malloc(sizeof(LinkNode));
    LinkNode * i = rear;
    while (a != b) {
        i->next = (LinkNode *)malloc(sizeof(LinkNode));
        i->next->data = a->data;
        a = a->next;
        i = i->next;
    }
    i->next = rear;
    rear->data = b->data;
    return rear;
}

LinkList * AscCLinkListInsert(LinkList * rear, ElemType elem)
{
    LinkNode * i = rear->next;
    while(i != rear && i->next->data < elem) { i = i->next; }
    LinkNode * t = (LinkNode*)malloc(sizeof(LinkNode));
    t->data = elem;
    t->next = i->next;
    i->next = t;
    if (rear == i) rear = t;
    return rear;
}

LinkNode * AscCLinkListDeleteAll(LinkList * rear, ElemType elem)
{
    LinkNode * i = rear;
    while(i->next != rear && i->next->data != elem) { i = i->next; }
    if (i->next == rear) {
        if (i->next->data != elem) return rear;
    }
    LinkNode * left = i->next;
    LinkNode * right = left;
    while (right != rear && right->data == elem) {
        LinkNode * t = right;
        right = right->next;
        free(t);
    }
    i->next = right;
    if (rear->data == elem) {
        i->next = rear->next;
        free(rear);
        rear = i;
    }
    return rear;
}

int main()
{
    int a[]= {5,3,2,2,8,4,5,3,7,8,2,1};
    LinkList* o = ConstructCLinkList(a, 12);
    DisplayCLinkList(o);
    o = SortCLiinkList(o);
    DisplayCLinkList(o);
    o = AscCLinkListInsert(o, 9);
    DisplayCLinkList(o);
    o = AscCLinkListDeleteAll(o, 9);
    DisplayCLinkList(o);
    o = AscCLinkListDeleteAll(o, 8);
    DisplayCLinkList(o);
    LinkList* p = SubCLinkList(FindElement(o,2), FindElement(o,7));
    DisplayCLinkList(p);
    ReleaseCLinkList(o);
    ReleaseCLinkList(p);
    return 0;
}

