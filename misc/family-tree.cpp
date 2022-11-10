#include <vector>
#include <queue>

#include "btree.hpp"
#include "utils.hpp"

using FamilyNode = BTreeNode<std::string>;

inline void trim_and_remove_empty(std::vector<std::string>& v) {
    auto i = v.begin();
    while (i != v.end()) {
        *i = trimmed(*i);
        if ((*i).empty()) {
            i = v.erase(i);
        }
        else { ++i; }
    }
}

FamilyNode* construct_family_from(std::string const& s) {
    // 用 depth 和 vector 模拟递归时栈帧

    // 递归深度
    int depth = 0;

    // 当前层包含所有节点内容的缓冲区;
    // 因为没有 token 化, 所以用字符串代替;
    std::vector<std::string> buf(1);

    // 来自当前层下面一层的节点指针: 下一层构建好节点后压入, 类似于存储递归的返回值.
    // 因为本例中为二叉树, 每个兄弟姐妹最多两个孩子,
    // 所以可以为定长数组, 并添加一个额外的变量用于记录当前压入了几个孩子,
    // 这样就可以区分孩子是哪个兄弟姐妹的. 为了方便可以使用 vector (同样的道理).
    // 这里使用 queue 队列, 使用 nullptr 将不同兄弟姐妹的孩子间隔开, 似乎这样更容易支持变长的情况?
    std::vector<std::queue<FamilyNode*>> p(1);

    for (auto const & c : s) {
        if (c == '(') {  // 识别到左括号, 准备开始 "递归"
            depth += 1;  // 深度 +1
            if (depth >= buf.size()) buf.emplace_back("");  // 模拟压栈
            if (depth >= p.size()) p.emplace_back();  // 模拟压栈
        } else if (c == ')') {  // 识别到右括号, 准备结束递归
            // 解析当前栈帧对应层次的内容 也就是若干个 names
            // 实际情况为逗号分隔的 token, 先 split, 再 trim
            auto names = split(buf[depth], ',');
            trim_and_remove_empty(names);
            buf[depth].clear();

            // q 为当前栈帧对应的孩子节点队列的引用; 使用引用减少代码量
            auto& q = p[depth];

            if (names.size() == 1) {  // 如果当前层只有一个 name
                // 为这个 name 创建它对应的节点
                auto n = new FamilyNode { names[0], nullptr, nullptr };
                // 将这个节点的孩子给它
                // 因为是二叉树所以最多只能拿两个孩子
                // 前提是没遇到 nullptr (用 nullptr 做了分隔符)
                if (!q.empty() && q.front() != nullptr) { n->l = q.front(); q.pop(); }  // 尝试取一个当作左孩子
                if (!q.empty() && q.front() != nullptr) { n->r = q.front(); q.pop(); }  // 尝试再取一个当作右孩子

                p[depth - 1].push(n);  // 把这个节点压到上个栈帧的队列中 (相当于返回到上一层递归调用)
                p[depth - 1].push(nullptr);  // 添加一个 nullptr 做间隔

            } else if (names.size() > 1) {  // 如果当前层多于一个 name: 由于二叉树最多只有两个分支, 多的 name 这里不管

                auto n1 = new FamilyNode { names[0], nullptr, nullptr };
                auto n2 = new FamilyNode { names[1], nullptr, nullptr };

                if (!q.empty() && q.front() != nullptr) { n1->l = q.front(); q.pop(); }
                if (!q.empty() && q.front() != nullptr) { n1->r = q.front(); q.pop(); }
                // 由于代码编写, 非队列最多只会有两个孩子 (不需要释放)
                if (!q.empty()) q.pop();  // 最后如果还有应该是遇到一个 nullptr, 丢掉, 方便下一个兄弟取

                if (!q.empty() && q.front() != nullptr) { n2->l = q.front(); q.pop(); }
                if (!q.empty() && q.front() != nullptr) { n2->r = q.front(); q.pop(); }

                p[depth - 1].push(n1);  // 把第一个节点压到上个栈帧的队列中 (相当于返回到上一层递归调用)
                p[depth - 1].push(n2);  // 把第二个节点压到上个栈帧的队列中 (相当于返回到上一层递归调用)
                p[depth - 1].push(nullptr);  // 添加一个 nullptr 做间隔
            }

            // 如果解析的字符串描述了更多的孩子, 也会出现在这里, 需要释放掉
            // 例如像这样 "root(Alan(Bob(Cedric),David),Edward(Fred,George),Henry(Ivan,Jason))"
            // 同时模拟的栈帧是共用的, 所以也需要保持干净 (清空)
            while (!q.empty()) { delete q.front(); q.pop(); }

            // 不弹出模拟栈帧
            depth -= 1;
        } else {  // 其他情况, 将内容存在当前栈帧的缓冲区中
            buf[depth].push_back(c);
        }
    }
    // depth 为 0 的层需要手动处理
    // 这里只取第一个
    auto root = new FamilyNode { trimmed(split(buf[depth], ',')[0]), nullptr, nullptr };
    auto& q = p[0];
    if (!q.empty() && q.front() != nullptr) { root->l = q.front(); q.pop(); }  // 尝试取一个当作左孩子
    if (!q.empty() && q.front() != nullptr) { root->r = q.front(); q.pop(); }  // 尝试再取一个当作右孩子
    // 如果解析的字符串描述了更多的孩子, 也会出现在这里, 需要释放掉
    while (!q.empty()) { delete q.front(); q.pop(); }

    return root;
}

#include <iostream>

int main() {
    std::string s =
        "root (         "
        "  Alan (       "
        "    Bob (      "
        "      Cedric   "
        "    ),         "
        "    David      "
        "  ),           "
        "  Edward (     "
        "    Fred,      "
        "    George     "
        "  )            "
        ")              ";

    // * * * * * * * * * * * * * * * * * * * * * * * * //
    // *                Visual Diagram               * //
    // *                                             * //
    // *                     root                    * //
    // *                /            \               * //
    // *             Alan           Edward           * //
    // *           /     \         /      \          * //
    // *         Bob    David    Fred   George       * //
    // *       /    \   /   \    /  \    /   \       * //
    // *    Cedric   ^ ^     ^  ^    ^  ^     ^      * //
    // *    /   \                                    * //
    // *   ^     ^                                   * //
    // * * * * * * * * * * * * * * * * * * * * * * * * //

    auto root = construct_family_from(s);

    std::cout << root->data << "\n";

    delete root;
}
