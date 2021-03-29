#ifndef GLIST_HPP
#define GLIST_HPP

template<typename T>
class GListElement {
public:
    enum GListElementType {ATOM, LIST};
    GListElement(GListElementType _type) : 
        element_type(_type) {}
    virtual ~GListElement() = default;
    GListElementType type() { return element_type; }
    bool equal_type(const GListElement<T> & a) { return this->type() == a.type(); }
    virtual T& data() = 0;
protected:
    GListElementType element_type;
};

template<typename T>
class GAtom : public GListElement<T>
{
private:
    T element;
public:
    GAtom() : 
        GListElement<T>(GListElement<T>::ATOM) {}
    // GAtom(T && e) : 
    //     GListElement<T>(GListElement<T>::ATOM), T(e) {}
    GAtom(const T & e) : 
        GListElement<T>(GListElement<T>::ATOM), element(e) {}
    ~GAtom() {};
    GAtom & operator=(const T & val) { element = val; return *this; } 
    T& data() { return element; };
};

template<typename T>
class GList : public GListElement<T> 
{
    struct node {
        GListElement<T>* element_ptr;
        node* next;
        node* prior;
        node() : 
            element_ptr(nullptr), next(this), prior(this) {};
        node(GListElement<T>* _ptr, node * _n = nullptr, node * _p = nullptr) : 
            element_ptr(_ptr), next(_n), prior(_p) {};
        ~node() { delete element_ptr; }
    };
    node * head;
public:
    GList() : GListElement<T>(GListElement<T>::LIST) { head = new node(); }
    GList(const GList & glist) : 
        GListElement<T>(GListElement<T>::LIST) {
        head = new node();
        GListElement<T>* item_ptr = nullptr;
        for (auto item : glist) {
            switch (item->type())
            {
            case GListElement<T>::ATOM:
                item_ptr = new GAtom<T>(*dynamic_cast<GAtom<T>*>(item)); break;
            case GListElement<T>::LIST:
                item_ptr = new GList<T>(*dynamic_cast<GList<T>*>(item)); break;
            }
            auto last = head->prior;
            auto new_node = new node(item_ptr, head, last);
            last->next = new_node;
            head->prior = new_node;
        }
    } 
    ~GList() {
        auto node_ptr = head->next;
        while (node_ptr != head) {
            auto tmp = node_ptr; node_ptr = node_ptr->next; delete tmp;
        }
        delete head;
    }
    T& data() { return head->next->element_ptr->data(); }

    friend class iterator;
    class iterator {
        node * the_node;
    public:
        iterator(const GList & glist) {
            the_node = (glist.head)->next;
        }
        iterator(node * _node) : the_node(_node) {}
        // pre increment
        iterator & operator++() {
            the_node = the_node->next; 
            return *this;
        }
        // post increment
        iterator operator++(int) {
            auto tmp = *this;
            the_node = the_node->next;
            return tmp;
        }
        bool operator==(const iterator & rhs) { 
            return the_node == rhs.the_node || 
                (the_node->element_ptr == nullptr && rhs.the_node->element_ptr == nullptr); 
        } 
        bool operator!=(const iterator & rhs) { return the_node != rhs.the_node; } 
        GListElement<T>* operator*() { return (the_node->element_ptr); }
    };
    iterator end() const { return iterator(head); };
    iterator begin() const { return iterator(*this); };
    void push_back(const T & item) {
        GListElement<T>* item_ptr = nullptr;
        item_ptr = new GAtom<T>(item);
        auto last = head->prior;
        auto new_node = new node(item_ptr, head, last);
        last->next = new_node;
        head->prior = new_node;
    }
    void push_back(const GList<T> & item) {
        GListElement<T>* item_ptr = nullptr;
        item_ptr = new GList<T>(item);
        auto last = head->prior;
        auto new_node = new node(item_ptr, head, last);
        last->next = new_node;
        head->prior = new_node;
    }
    // void push_back(const GAtom<T> & item) {
    //     GListElement<T>* item_ptr = nullptr;
    //     item_ptr = new GAtom<T>(item);
    //     auto last = head->prior;
    //     auto new_node = new node(item_ptr, head, last);
    //     last->next = new_node;
    //     head->prior = new_node;
    // }
    int depth() {
        int depth = 0;
        for (auto i : *this) {
            if (i->type() == GListElement<T>::LIST) {
                auto sublist_ptr = dynamic_cast<GList<T>*>(i);
                auto t = sublist_ptr->depth();
                if (t > depth) depth = t;
            }
        }
        return depth + 1;
    }
};

#endif
