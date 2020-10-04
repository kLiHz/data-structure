#include "linklist.h"

int main()
{
    //ElemType a[] = {11,22,33,44,44,55,66,77,44}, e;
    ElemType a[] = {1,2,3,5,6,7,8,8,9};
    ElemType b[] = {2,4,5,6,8,9,9,10,13};

    LinkNode * L1 = InitList();
    InsertArrayListRear(L1,a,9);
    DisplayList(L1);

    LinkNode * L2 = InitList();
    InsertArrayListRear(L2,b,9);
    DisplayList(L2);

    /*ListInsert(L1,1,10);
    ListInsert(L1,5,10);
    DisplayList(L1);
    ListDelete(L1,1,&e);
    ListDelete(L1,5,&e);
    DisplayList(L1);
    ReverseList(L1);
    DisplayList(L1);
    InsertXY(L1,77,68);
    DisplayList(L1);
    Deduplication(L1);
    DisplayList(L1);*/

    LinkNode * L3 = InitList();
    AscMerge(L1,L2,L3); DisplayList(L3);
    AscListInsert(L1,3); DisplayList(L1);
    DeleteLastE(L1,3); DisplayList(L1);

    ValueAB(L1,2,8,L3); DisplayList(L3);
    EmptyList(L3);
    AscListUnion(L1,L2,L3); DisplayList(L3);
    EmptyList(L3);
    AscListIntersection(L1,L2,L3); DisplayList(L3);
    EmptyList(L3);
    AscListSubtract(L1,L2,L3); DisplayList(L3);

    ReleaseList(L1);
    ReleaseList(L2);
    ReleaseList(L3);
    return 0;
}
