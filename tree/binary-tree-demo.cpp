#include "binary-tree.hpp"
#include <cmath>

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
    //auto l = tree.pre_traverse_nr();
    //for (auto i : l) std::cout << i->data;
    //BTchar::pre_iterator i(root);
    //while(i != BTchar::pre_iterator()) {
    //    std::cout << *i << ' ';
    //    ++i;
    //}
    auto s = tree.layer_traverse();
    // 计算第k层的节点数目
    int layer_num = 3, layer_cnt = 0;
    for (auto i : s) {
        if (i.second == layer_num) ++layer_cnt;
    }
    std::cout << layer_cnt << std::endl;
    // 判断是否为二叉树
    int current_layer = s.front().second, cnt = 0;
    for (auto i : s) {
        if (i.second == current_layer) ++cnt;
        else if (i.second > current_layer) {
            cnt = 0;
            current_layer = i.second;
        }
    }
    std::cout << "The tree " << ((cnt == pow(2,current_layer)) ? "is" : "is not") << " a complete binary tree.";
}
