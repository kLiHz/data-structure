#include <iostream>
#include <list>

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
