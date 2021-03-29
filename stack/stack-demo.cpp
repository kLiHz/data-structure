#include <iostream>
//#include <stack>
#include <string>
#include "linkstack.hpp"

//已知表达式存储在字符串中，其中可以有大括号、中括号和小括号，试编写算法判断表达式中括号是否匹配。

bool paired_brackets(char left, char right) {
    return 
        (left == '(' && right == ')') 
        || (left == '[' && right == ']') 
        || (left == '{' && right == '}');
}

bool is_matched(const std::string & str) 
{
    //std::stack<char> l;
    LinkStack<char> l;
    auto i = str.begin();
    bool all_bracket_paired = true;
    while (i != str.end() && all_bracket_paired) {
        switch (*i) 
        {
        case '(':  case '[':  case '{':
            l.push(*i);
            break;
        case ')':  case ']':  case '}':
            if ( !l.empty() && paired_brackets( l.top(),  *i) ) l.pop();
            else { 
                all_bracket_paired = false;
            }
            break;
        }
        ++i;
    }
    if (!l.empty() || !all_bracket_paired) { 
        std:: cout << l.top() << " doesn't match!\n";
        return false; 
    }
    return true;
}

int main() 
{
    std::string brackets;
    std::getline(std::cin, brackets);
    if (is_matched(brackets)) std::cout << "All matched!" << std::endl; 
    else std::cout << "Brackets doesn't match!" << std::endl;
    return 0;
}
