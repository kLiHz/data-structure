#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

template<typename ElemType>
class LinkStack {
public:
    struct element;
    LinkStack();
    ~LinkStack();
    void push(ElemType &);
    void pop();
    ElemType & top() {return _top->data;}
    bool empty() {return _top == nullptr;}
    int size() {return cnt;}
private:
    element * _top;
    int cnt;
};

template<typename ElemType>
struct LinkStack<ElemType>::element {
    ElemType data;
    LinkStack::element* next;
};

template<typename ElemType>
LinkStack<ElemType>::LinkStack() {
    _top = nullptr;
    cnt = 0;
}

template<typename ElemType>
LinkStack<ElemType>::~LinkStack() {
    while (_top != nullptr) {
        LinkStack::element * t = _top;
        _top = _top->next;
        delete t;
    }
}

template<typename ElemType>
void LinkStack<ElemType>::pop() {
    if (cnt < 1) return;
    else {
        LinkStack::element * t = _top;
        _top = _top->next;
        delete t;
        --cnt;
    }
}

template<typename ElemType>
void LinkStack<ElemType>::push(ElemType & elem) {
    LinkStack::element * t = new element;
    t->data = elem;
    t->next = _top;
    _top = t;
    ++cnt;
}

#endif
