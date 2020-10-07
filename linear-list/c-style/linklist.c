#include "linklist.h"

LinkNode * InitList() //创建头节点
{
    LinkNode * t = (LinkNode *)malloc(sizeof(LinkNode));
    t->data = 0; //非必要
    t->next = NULL;
    return t;
}

void ReleaseList(LinkNode * head)
{
    LinkNode * node = head->next; //从头节点指向的next开始释放
    free(head); //释放头结点
    while (node != NULL) {
        LinkNode * t = node; //留住当前node的地址用于free
        node = node->next; //node指向下一个节点
        free(t);
    }
    //感觉可以尝试递归法释放空间...?
}

void EmptyList(LinkNode * head)
{
    LinkNode * node = head->next; //从头节点指向的next开始释放
    head->next = NULL; //头结点的next改为空
    while (node != NULL) {
        LinkNode * t = node; //留住当前node的地址用于free
        node = node->next; //node指向下一个节点
        free(t);
    }
}

bool IsEmptyList(LinkNode * L)
{
    return L->next == NULL;
}

int ListLength(LinkNode * p)
{
    if (p == NULL) return 0;
    int cnt = 0;
    while (p->next != NULL){
        ++cnt;
        p = p->next;
    }
    return cnt;
}

void DisplayList(LinkNode * p)
{
    if (p == NULL) return;
    p = p->next;
    while (p != NULL) {
        printf("%d ", p->data);
        //std::cout << p->data <<' ';
        p = p->next;
    }
    printf("\n");
    //std::cout << std::endl;
}

bool GetElem(LinkNode * p, int i, ElemType * e)
{
    if (i < 0) return false;
    int j = 0;
    while (j < i && p != NULL) {
        ++j;
        p = p->next;
    }
    if (p == NULL) return false;
    else {
        *e = p->data;
        return true;
    }
}
//之前也想diss这里，总觉得get一个值应该作为返回值返回给调用处……
//而判断是否成功的标志倒是应该通过参数返回，且给一个默认值，设置成可选的选项

int LocateElem(LinkNode * p, ElemType e)
{
    p = p->next;
    int i = 1;
    while (p != NULL && p->data != e)
    {
        p = p->next;
        ++i;
    }
    if (p == NULL) return 0;
    else return i;
}

bool ListInsert(LinkNode *p, int i, ElemType e)
{
    if (i < 1) return false;
    int j = 0;
    //因为是单链表，要想将数据插入在i位置，需要修改i-1的next指针
    while (j < i - 1 && p != NULL) {
        ++j;
        p = p->next;
    }
    if (p == NULL) return false;
    else {
        LinkNode * new_node = (LinkNode*) malloc(sizeof(LinkNode));
        new_node->data = e;
        new_node->next = p->next;
        p->next = new_node;
        return true;
    }
}

bool ListDelete(LinkNode *p, int i, ElemType * e)
{
    if (i < 1) return false;
    int j = 0;
    //因为是单链表，要删除在i位置的数据，需要修改i-1的next指针
    while (j < i - 1 && p != NULL) {
        ++j;
        p = p->next;
    }
    if (p == NULL) return false;
    else {
        LinkNode * t = p->next;
        if (t == NULL) return false; //不存在第i个节点
        else {
            *e = t->data;
            p->next = t->next;
            free(t);
            return true;
        }
    }
}

//从a数组获取n个数据，采用头插法插入
void InsertArrayListFront(LinkNode *L, ElemType a[], int n)
{
    if (!IsEmptyList(L)) EmptyList(L);
    //L->next = NULL;
    for(int i = 0; i < n; i++) {
        LinkNode * new_node = (LinkNode *) malloc(sizeof(LinkNode));
        new_node->data = a[i];
        new_node->next = L->next;
        L->next = new_node;
    }
}

//从a数组获取n个数据，采用尾插法插入
void InsertArrayListRear(LinkNode *L, ElemType a[], int n)
{
    if (!IsEmptyList(L)) EmptyList(L);
    LinkNode * rear = L;
    for(int i = 0; i < n; i++) {
        LinkNode * new_node = (LinkNode *) malloc(sizeof(LinkNode));
        new_node->data = a[i];
        rear->next = new_node;
        rear = new_node;
    }
    rear->next = NULL;
}

//示例（1）已知单链表L中所有元素均为整数，试编写算法在值为x的元素之前插入值为y的元素。
bool InsertXY(LinkNode * p, ElemType x, ElemType y)
{
    p = p->next;
    LinkNode * previous_p = p;
    while (p != NULL && p->data != x)
    {
        previous_p = p;
        p = p->next;
    }
    if (p == NULL) return false;
    else {
        LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
        new_node->data = y;
        previous_p->next = new_node;
        new_node->next = p;
        return true;
    }
}

//示例 （2）已知单链表L中所有元素均为整数，试编写算法逆置单链表。
//思路：从头至尾依次将每个元素头插到单链表中
void ReverseList(LinkNode * L)
{
    LinkNode * i = L->next;
    L->next = NULL;
    while (i != NULL) {
        LinkNode * t = i;
        i = i->next; //相当于i++
        t->next = L->next;
        L->next = t;
    }
}

//（3）已知单链表(无序)L中所有元素均为整数，试编写算法中清除多余的重复元素。
void Deduplication(LinkNode * L)
{
    LinkNode * i, * pre_j, *j;
    i = L->next;
    while (i != NULL)
    {
        pre_j = i;
        j     = i->next;
        while (j != NULL)
        {
            if (j->data != i->data) {
                pre_j = j;
                j     = j->next;
            }
            else {
                pre_j->next = j->next;
                free(j);
                j = pre_j->next; //j指向的位置后移一个
            }
        }
        i = i->next; //相当于i++;
    }
    return;
}

//-----顺序递增链表-----//

/*//（3）已知单链表L中所有元素均为整数，试编写算法中清除多余的重复元素。
void AscDeduplication(LinkNode * L)
{
}*/

//（4）已知两个单链表按值递增有序存储，试编写算法利用归并法将两个单链表合并成一个。
void AscMerge(LinkNode * pa, LinkNode * pb, LinkNode * pc) //C = A + B
{
    if (!IsEmptyList(pc)) EmptyList(pc);
    pa = pa->next;
    pb = pb->next;
    while (pa != NULL && pb != NULL) {
        LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
        if (pa->data < pb->data) {
            new_node->data = pa->data;
            pa = pa->next; //pa++;
        }
        else {
            new_node->data = pb->data;
            pb = pb->next; //pb++
        }
        pc->next = new_node;
        pc = pc->next;
    }
    while (pa != NULL) {
        LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
        new_node->data = pa->data;
        pc->next = new_node;
        pc = pc->next;
        pa = pa->next; //pa++;
    }
    while (pb != NULL) {
        LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
        new_node->data = pb->data;
        pc->next = new_node;
        pc = pc->next;
        pb = pb->next; //pb++
    }
    pc->next = NULL; //注意收尾
} //一定要注意头插法和尾插法的区别，这里一开始写成了头插法...

//1. 已知单链表L为按值递增有序的，编写算法将数据元素e插入到单链表L中，使之仍有序。
void AscListInsert(LinkNode * p, ElemType e)
{
    LinkNode * pre_i = p;
    p = p->next;
    while (p != NULL) {
        if (p->data > e) {
            LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
            new_node->data = e;
            pre_i->next = new_node;
            new_node->next = p;
            return;
        }
        pre_i = p;
        p = p->next;
    }
    if (p == NULL) {
        LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
        new_node->data = e;
        pre_i->next = new_node;
        new_node->next = p;
        return;
    }
}

//2. 编写算法删除单链表L中最后一个值为e的数据元素。
bool DeleteLastE(LinkNode * p, ElemType e)
{
    LinkNode * pre_p = NULL;
    p = p->next;
    //从正向访问链表
    bool is_deleted = false;
    while (p != NULL)
    {
        if (p->data == e) {
            if (p->next != NULL && p->next->data != e) {
                pre_p->next = p->next;
                is_deleted = true;
                free(p);
                break;
            } //要先判断next指针是不是null
            else if (p->next == NULL) {
                pre_p->next = p->next;
                is_deleted = true;
                free(p);
                break;
            }
        }
        pre_p = p;
        p = p->next;
    }
    return is_deleted;
}

//3. 已知单链表L为按值递增有序的，编写算法将数据元素值在区间[low , high]内的所有结点取出建立一个按值递增的新单链表L1。
void ValueAB(LinkNode * p, ElemType low, ElemType high, LinkNode * L)
{
    p = p->next;
    while (p != NULL)
    {
        if (low <= p->data && p->data <= high) {
            LinkNode * new_node = (LinkNode *)malloc(sizeof(LinkNode));
            new_node->data = p->data;
            L->next = new_node;
            L = L->next;
        }
        if (p->data > high) break;
        p = p->next;
    }
    L->next = NULL;
}

//4. 已知两个集合分别按值递增有序存储在单链表La和Lb中，
//编写算法利用归并法分别求出两个集合的交集、并集和差集，皆为按值递增有序。
//(要求：保留La和Lb两个链表，建立新的链表存储结果)。

void AscListUnion(LinkNode *La, LinkNode * Lb, LinkNode * Lc)
{
    if (!IsEmptyList(Lc)) EmptyList(Lc);
    La = La->next;
    Lb = Lb->next;
    while (La != NULL && Lb != NULL) {
        Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
        if (La->data < Lb->data) {
            Lc->next->data = La->data;
            La = La->next; //抽象的La++;
        }
        else {
            Lc->next->data = Lb->data;
            Lb = Lb->next; //抽象的Lb++;
        }
        Lc = Lc->next;
    }
    while (La != NULL) {
        Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
        Lc->next->data = La->data;
        Lc = Lc->next;
        La = La->next; //抽象的La++;
    }
    while (Lb != NULL) {
        Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
        Lc->next->data = Lb->data;
        Lc = Lc->next;
        Lb = Lb->next; //抽象的Lb++;
    }
    Lc->next = NULL;
}

#define __min(a,b) (((a) < (b)) ? (a) : (b))

void AscListUnion_1(LinkNode *p, LinkNode *s, LinkNode *r)
{
    p = p->next;
    s = s->next;
    int previous_value = __min(p->next->data, s->next->data) - 1; 
    //用一个值存储下前一个值来判断是否为重复元素
    while (p != NULL && s != NULL) {
        if (p->data < s->data) {
            if (previous_value != p->data) {
                r->next = (LinkNode *)malloc(sizeof(LinkNode));
                r->next->data = previous_value = p->data;
                r = r->next;
            }
            p = p->next;
        } else {
            if (previous_value != p->data) {
                r->next = (LinkNode *)malloc(sizeof(LinkNode));
                r->next->data = previous_value = s->data;
                r = r->next;
            }
            s = s->next;
        }
    }
    while (s != NULL) {
        if (s->data > previous_value) {
            r->next = (LinkNode *)malloc(sizeof(LinkNode));
            r->next->data = previous_value = s->data;
            r = r->next;
        }
        s = s->next;
    }
    while (p != NULL) {
        if (p->data > previous_value) {
            r->next = (LinkNode *)malloc(sizeof(LinkNode));
            r->next->data = previous_value = p->data;
            r = r->next;
        }
        p = p->next;
    }
    r->next = NULL;
} //@zsq写的; 觉得添加一个变量用来去重的思路还不错，故添加进来

void AscListIntersection(LinkNode *La, LinkNode * Lb, LinkNode * Lc)
{
    if (!IsEmptyList(Lc)) EmptyList(Lc);
    La = La->next;
    Lb = Lb->next;
    //用这样的while循环实现每次找到相同元素的最后一个
    while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
    while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
    while (La != NULL && Lb != NULL) {
        if (La->data == Lb->data) {
            Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
            Lc->next->data = La->data;
            Lc = Lc->next;
            La = La->next;
            Lb = Lb->next;
            while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
            while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
        }
        else if (La->data < Lb->data) {
            La = La->next;
            while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
        }
        else {
            Lb = Lb->next;
            while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
        }
    }
    Lc->next = NULL;
}

void AscListSubtract(LinkNode *La, LinkNode * Lb, LinkNode * Lc)
{
    if (!IsEmptyList(Lc)) EmptyList(Lc);
    La = La->next;
    Lb = Lb->next;
    //用这样的while循环实现每次找到相同元素的最后一个
    while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
    while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
    while (La != NULL && Lb != NULL) {
        while (La->data < Lb->data) {
            Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
            Lc->next->data = La->data;
            Lc = Lc->next;
            La = La->next;
            while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
        }
        if (La->data == Lb->data) {
            La = La->next;
            while (La != NULL && La->next != NULL && La->data == La->next->data) La = La->next;
        }
        Lb = Lb->next;
        while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
    }
    while (La != NULL) {
        Lc->next = (LinkNode*)malloc(sizeof(LinkNode));
        Lc->next->data = La->data;
        Lc = Lc->next;
        La = La->next;
        while (Lb != NULL && Lb->next != NULL && Lb->data == Lb->next->data) Lb = Lb->next;
    }
    Lc->next = NULL;
}

/*void AscListDiff()
{
    //遍历两个表
    //归并法插入元素，相等的时候同时++，不插入
}*/
