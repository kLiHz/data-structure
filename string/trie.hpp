#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <string>
#include <map>
#include <stack>

namespace trie
{
    template<typename CHAR_TYPE>
    struct node {
        CHAR_TYPE ch;
        size_t cnt;
        std::map<CHAR_TYPE, node *> children;
        node() : ch(' '), cnt(0) {}
        node(CHAR_TYPE _ch) : ch(_ch), cnt(0) {}
        ~node() {
            for (auto i : children) { delete i.second; }
        }
        void traverse(std::string & str) {
            if (cnt > 0) 
                std::cout << str << " cnt: " << cnt << std::endl;
            for (auto i : children) {
                str += i.second->ch;
                i.second->traverse(str);
                str.pop_back();
            }
            return;
        };
    };
    template<typename CHAR_TYPE>  
    class Trie {
    private:
        node<CHAR_TYPE>  root;
    public:
        node<CHAR_TYPE>* insert(const std::string & str);
        node<CHAR_TYPE>* find(const std::string & str);
        bool             erase(const std::string & str);
        void             output();
    };
    template<typename CHAR_TYPE> 
    node<CHAR_TYPE>* Trie<CHAR_TYPE>::insert(const std::string & str) {
        node<CHAR_TYPE> * now = &root;
        for (auto i : str) {
            auto j = now->children.find(i);
            if (j != now->children.end()) {
                now = j->second;
            }
            else { // str not found
                auto t = new node<CHAR_TYPE>(i);
                now->children.insert({i,t});
                now = t;
            }
        }
        ++(now->cnt);
        return now;
    }
    template<typename CHAR_TYPE> 
    node<CHAR_TYPE>* Trie<CHAR_TYPE>::find(const std::string & str) {
        node<CHAR_TYPE> * now = &root;
        for (auto i : str) {
            auto j = now->children.find(i);
            if (j != now->children.end()) {
                now = j->second;
            }
            else return nullptr;
        }
        if (now->cnt > 0) return now;
        else return nullptr; // str not found
    }
    template<typename CHAR_TYPE> 
    bool Trie<CHAR_TYPE>::erase(const std::string & str) {
        typedef node<CHAR_TYPE>* node_ptr;
        node_ptr now = &root;
        std::stack<node_ptr> history_node_ptr;
        history_node_ptr.push(&root);
        for (auto i : str) {
            auto j = now->children.find(i);
            if (j != now->children.end()) {
                now = j->second;
                history_node_ptr.push(now);
            }
            else return false; // cannot found str
        }
        if (now->cnt > 0) { // found
            now->cnt = 0; // remove the word from the tree
            while (history_node_ptr.size() > 1) {
                auto i = history_node_ptr.top();
                history_node_ptr.pop();
                if (i->children.empty() && i->cnt == 0) {
                    (history_node_ptr.top())->children.erase(i->ch);
                    delete i;
                }
                else break;
            }
            return true;
        }
        else return false; //cannot find str
    }
    template<typename CHAR_TYPE> 
    void Trie<CHAR_TYPE>::output()
    {
        std::string s;
        root.traverse(s);
    }
}

#endif
