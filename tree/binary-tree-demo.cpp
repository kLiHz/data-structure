#include "binary-tree.hpp"

template<typename T>
void preOrder(BinaryTree<T> & t) {
    std::cout << "preorder traversal: ";
    auto q = t.pre_traverse();
    for (auto i : q) std::cout << i->data << ' ';
    std::cout << std::endl;
}

template<typename T>
void midOrder(BinaryTree<T> & t) {
    std::cout << "midorder traversal: ";
    auto q = t.mid_traverse();
    for (auto i : q) std::cout << i->data << ' ';
    std::cout << std::endl;
}

template<typename T>
void postOrder(BinaryTree<T> & t) {
    std::cout << "postorder traversal: ";
    auto q = t.post_traverse();
    for (auto i : q) std::cout << i->data << ' ';
    std::cout << std::endl;
}

int main()
{
    typedef BinaryTree<char> BTchar;
    typedef BTchar::Node BTcharNode;
    BTcharNode * root = 
    new BTcharNode ('a',
        new BTcharNode ('b',
            new BTcharNode ('d'),
            new BTcharNode ('e')
        ),
        new BTcharNode ('c',
            new BTcharNode ('g',
                new BTcharNode('s')
            ),
            new BTcharNode ('f')
        )
    );
    BTchar tree(root);
    preOrder(tree);
    midOrder(tree);
    postOrder(tree);
}
