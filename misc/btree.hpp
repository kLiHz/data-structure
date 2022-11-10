#ifndef DS_PROJECT_BTREE_HPP
#define DS_PROJECT_BTREE_HPP

template<typename T>
struct BTreeNode {
    T data;
    BTreeNode * l = nullptr;
    BTreeNode * r = nullptr;
    ~BTreeNode() {
        delete l;
        delete r;
    }
};

#endif
