#include <iostream>
#include <list>
#include <stack>
#include <queue>

template<typename ElemType>
class BinaryTree 
{
public:
    struct Node {
        ElemType data;
        Node* left;
        Node* right;
        Node() : left(nullptr), right(nullptr) {}
        Node(
            ElemType&&  _elem, 
            Node *      _left = nullptr, 
            Node *      _right = nullptr)
        : data(_elem), left(_left), right(_right) {};
        ~Node() {};
        int degree() {
            return 2 - (!left) - (!right);
        }
    };
    class iterator {
    public:
        enum IterStatus { THIS, LEFT, RIGHT };
        enum IterStrategy { PRE, POST, MID };
        //void        operator++(int) = 0; // i++
        virtual iterator &  operator++()    = 0; // ++i
        //void        operator--(int) = 0; // i--
        //void        operator--()    = 0; // --i
        ElemType&   operator*() {        // dereference
            return this->the_node->data; 
        }
        ElemType*   operator->() {
            return &(this->the_node->data);
        }
        bool operator!=(const iterator & i) { 
            return this->the_node != i.the_node;
        } 
        iterator( IterStrategy _strategy, Node * _the_node ) 
        : strategy(_strategy), the_node(_the_node), status(THIS) {}
    protected:
        Node * the_node;
        std::stack<Node*> previous;
        IterStatus status;
        IterStrategy strategy;
    };
    class pre_iterator : public iterator {
    public:
        pre_iterator( Node * _the_node = nullptr ) : iterator( iterator::PRE, _the_node ) {} 
        virtual iterator & operator++() {
            if (iterator::the_node->left) {
                iterator::previous.push(iterator::the_node);
                iterator::the_node = iterator::the_node->left;
            }
            else if (iterator::the_node->right) {
                iterator::previous.push(iterator::the_node);
                iterator::the_node = iterator::the_node->right;
            }
            else {
                if (iterator::previous.empty()) {
                    iterator::the_node = nullptr;
                    return *this;
                }
                iterator::the_node = iterator::previous.top(); 
                iterator::previous.pop();
                iterator::the_node = iterator::the_node->right;
                while (!iterator::the_node) {
                    iterator::the_node = iterator::previous.top(); 
                    iterator::previous.pop();
                    iterator::the_node = iterator::the_node->right;
                }
            }
            return *this;
        }
    };
    BinaryTree() : root(nullptr) {};
    BinaryTree(const ElemType & _elem) { root = new Node(_elem); };
    BinaryTree(Node * p) { root = p; };
    ~BinaryTree() { clear(); };
    //void    makeTree(const ElemType & x, const BinaryTree & lt, const BinaryTree & rt);
    int     size()   const { return size(root);   };
    int     height() const { return height(root); };
    void    clear() { 
        if(root) clear(root); 
        root = nullptr; 
    }
    Node *  get_root() { return root; }
    std::list<Node*> pre_traverse() const {
        std::list<Node*> q;
        preOrder(root, q);
        return q;
    }
    std::list<Node*> mid_traverse() const {
        std::list<Node*> q;
        midOrder(root, q);
        return q;
    }
    std::list<Node*> post_traverse() const {
        std::list<Node*> q;
        postOrder(root, q);
        return q;
    }
    std::list<Node*> pre_traverse_nr() const;
    std::list<Node*> mid_traverse_nr() const;
    std::list<Node*> post_traverse_nr() const;
    std::list< std::pair<Node*,int> > layer_traverse() const;
private:
    static void preOrder(Node * t, std::list<Node*> & q) {
        if (t) {
            q.push_back(t);
            preOrder(t->left, q);
            preOrder(t->right, q);
        }
    }
    static void midOrder(Node * t, std::list<Node*> & q) {
        if (t) {
            midOrder(t->left, q);
            q.push_back(t);
            midOrder(t->right, q);
        }
    }
    static void postOrder(Node * t, std::list<Node*> & q) {
        if (t) {
            postOrder(t->left, q);
            postOrder(t->right, q);
            q.push_back(t);
        }
    }
    //static void layerOrder(Node * t, std::list<Node*> & q) {
    //    if (t) q.push_back(t);
    //    if (t->left) q.push_back(t);
    //    if (t->right) q.push_back(t);
    //}
    void    clear(Node * t) {
        if (t) {
            if (t->left) clear(t->left);
            if (t->right) clear(t->right);
            delete t;
        }
    }
    int     size(Node * t) const {
        if (t == nullptr) return 0;
        return 1 + size(t->left) + size(t->right);
    };
    int     height(Node * t) const {
        if (t == nullptr) return 0;
        else {
            int lt = height(t->left);
            int rt = height(t->right);
            return 1 + (lt > rt ? lt : rt);
        }
    };

    Node * root;
};

template<typename ElemType>
std::list< typename BinaryTree<ElemType>::Node* > 
BinaryTree<ElemType>::pre_traverse_nr() const
{
    std::stack<Node*> s;
    std::list<Node*> result;
    if (root) s.push(root);
    while (!s.empty()) {
        Node * current = s.top(); s.pop();
        result.push_back(current);
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
    return result;
}

template<typename ElemType>
std::list< typename BinaryTree<ElemType>::Node* > 
BinaryTree<ElemType>::mid_traverse_nr() const
{
    std::stack<Node*> s;
    std::list<Node*> result;
    s.push(root);
    do {
        Node * current = s.top();
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
        s.pop();
        result.push_back(current);
    } while (!s.empty());
    return result;
}

template<typename ElemType>
std::list< std::pair< typename BinaryTree<ElemType>::Node*, int> > 
BinaryTree<ElemType>::layer_traverse() const {
    std::list < std::pair<Node*, int> > result;
    std::queue< std::pair<Node*, int> > q;
    if (root) q.push( std::pair<Node*, int>(root,1) );
    while (!q.empty()) {
        auto t = q.front();
        result.push_back(t);
        q.pop();
        if (t.first->left) q.push(std::pair<Node*, int>(t.first->left, t.second + 1) );
        if (t.first->right) q.push(std::pair<Node*, int>(t.first->right, t.second + 1) );
    }
    return result;
} 
