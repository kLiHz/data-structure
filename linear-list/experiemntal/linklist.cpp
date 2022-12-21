template <typename T>
class LinkList {
private:
    struct Node {
        T data;
        Node * next = nullptr;
        Node(T val, Node * p) : data(val), next(p) {}
        ~Node() { delete next; }
    };

    Node base;

public:
    LinkList() : base(T{}, nullptr) {}
    ~LinkList() = default;

    void erase(int idx) {
        int i = 0;
        Node * p = base.next;
        Node * pre = &base;
        while (i < idx && p != nullptr) {
            pre = p;
            p = p->next;
            i++;
        }
        pre->next = p->next;
        p->next = nullptr;
        delete p;
    }

    using Comparator = bool(T const&, T const&);

    void sort(Comparator cmp) {
        bool swapped;
        Node* end = nullptr;
        do {
            Node* prev = &base;
            Node* t = base.next;
            Node* newEnd = nullptr;
            swapped = false;
            while (t != nullptr && t->next != end) {
                if (!cmp(t->data, t->next->data)) {
                    prev->next = t->next;
                    t->next = t->next->next;
                    prev->next->next = t;
                    swapped = true;
                    prev = prev->next;
                    newEnd = t;
                } else {
                    prev = t;
                    t = t->next;
                }
            }
            end = newEnd;
        } while (swapped);
    }

    void push_front(const T & val) {
        base.next = new Node(val, base.next);
    }

    class iterator {
        Node * p;
    public:
        iterator(Node* p_) : p(p_) {}
        iterator& operator++() {
            p = p->next;
            return *this;
        }
        iterator operator++(int) {
            auto t = p;
            p = p->next;
            return iterator(t);
        }
        bool operator==(const iterator & other) { return this->p == other.p; }
        bool operator!=(const iterator & other) { return this->p != other.p; }
        T & operator*() { return p->data; }
    };

    iterator begin() { return { base.next }; }
    iterator end() { return { nullptr }; }
};

#include <iostream>
#include <string>

enum class CharType {
    NUM = 0, LOWER = 1, UPPER = 2, OTHER = 3,
};

CharType charType(char c) {
    if ('0' <= c && c <= '9') {
        return CharType::NUM;
    } else if ('a' <= c && c <= 'z') {
        return CharType::LOWER;
    } else if ('A' <= c && c <= 'Z') {
        return CharType::UPPER;
    } else {
        return CharType::OTHER;
    }
}

bool cmp(char const& a, char const& b) {
    if (charType(a) == charType(b)) {
        return a < b;
    } else {
        return static_cast<int>(charType(a)) < static_cast<int>(charType(b));
    }
}

int main() {
    LinkList<char> list;
    std::string s;

    std::cin >> s;
    auto it = s.rbegin();
    while (it != s.rend()) {
        list.insertFront(*it);
        ++it;
    }

    list.sort(cmp);

    for (auto c : list) { std::cout << c; }

    std::cout << "\n";
}
