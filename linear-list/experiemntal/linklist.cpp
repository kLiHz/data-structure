
template <typename ElemType>
class LinkList {
public:
    struct LLNode {
        ElemType val;
        LLNode * next;
        LLNode(const ElemType & e, LLNode * next_) : val(e), next(next_) {}
        ~LLNode() { delete next; }
    };

    LinkList() : base(ElemType{}, nullptr) {}
    void erase(int idx) {
        int i = 0;
        LLNode * ptr = base.next;
        LLNode * pre_ptr = &base;
        while (i < idx && ptr != nullptr) {
            pre_ptr = pre_ptr->next;
            ptr = ptr->next;
            i++;
        }
        pre_ptr->next = ptr->next;
        delete ptr;
    }
    LLNode * get_node(int idx) {
        int i = 0;
        LLNode * ptr = base.next;
        while (i < idx && ptr != nullptr) {
            ptr = ptr->next;
            i++;
        }
        return ptr;
    }
    void push_front(const ElemType & val) {
        LLNode * new_node = new LLNode(val, base.next);
        base.next = new_node;
    }
    class iterator {
        LLNode * current;
        LLNode * previous;
    public:
        iterator() : current(nullptr), previous(nullptr) {}
        iterator(LLNode * pre, LLNode * cur) : current(cur), previous(pre) {}
        iterator & operator++() {
            if (current == nullptr) return *this;
            previous = current;
            current = current->next;
            return *this;
        }
        iterator operator++(int) {
            if (current == nullptr) return *this;
            auto tmp = iterator(previous, current);
            previous = current;
            current = current->next;       
            return tmp;
        }
        bool operator==(const iterator & other) { return current == other.current; }
        bool operator!=(const iterator & other) { return current != other.current; }
        ElemType & operator*() { return (*current).val; }
    };
    iterator begin() { return iterator(&base, base.next); }
    iterator end() { return iterator(); }
private:
    LLNode base;
};

#include <iostream>

int main() {
    LinkList<int> a;
    a.push_front(11);
    a.push_front(12);
    a.push_front(13);
    auto p = a.get_node(1);
    while (p != nullptr) {
        std::cout << p->val;
        p = p->next;
    }
    std::cout << '\n';
    for (auto i : a) {
        std::cout << i;
    }
}
