#include "string.hpp"

String::String()
{
    length = 0;
    arraySize = 32;
    ptr = new char[32];
}

String::String(int _size) : arraySize(_size) {
    if (arraySize > 0) {
        length = 0;
        ptr = new char[arraySize];
    }
    else {
        ptr = nullptr;
        length = arraySize = 0;
    }
}

String::String(const char * str)
{
    int len = strlen(str);
    arraySize = len + 1;
    ptr = new char[len + 1];
    memcpy(ptr, str, sizeof(char) * (len + 1));
    length = len;
}

String::String(const char * str, int _length)
{
    length = _length;
    arraySize = _length + 1;
    ptr = new char[arraySize];
    memcpy(ptr, str, sizeof(char) * (_length));
    ptr[_length] = '\0';
    length = _length;
}

String::~String()
{
    if (ptr) delete[] ptr;
}

String & String::operator= (const String & str)
{
    if (ptr == str.ptr) return *this;
    if (str.length > 0) {
        length = str.length;
        if (str.length + 1 > arraySize) {
            if (ptr != nullptr) delete[] ptr;
            arraySize = str.arraySize;
            ptr = new char[arraySize];
        }
        memcpy(ptr, str.ptr, sizeof(char) * (str.length + 1));
    }
    else {
        length = 0;
    }
    return *this;
}

// 如何更好地理解和掌握 KMP 算法? - 海纳的回答 - 知乎
// https://www.zhihu.com/question/21923021/answer/281346746

void String::get_next(int next[]) const
{
    next[0] = -1;
    int i = 0, j = -1;
    while (i < length)
    {
        if (j == -1 || ptr[i] == ptr[j]) {
            ++i; ++j;
            next[i] = j;
        }
        else j = next[j];
    }
}

int String::KMP(const String & p, int pos) const
{
    int i = pos, j = 0;
    int * next = new int[p.length];
    p.get_next(next);
    while (i < this->length && j < p.length)
    {
        if (j == -1 || this->ptr[i] == p.ptr[j]) {
            i++; j++;
        }
        else j = next[j];
    }
    if (j == p.length) return i - j;
    else return -1;
}

int String::find(const String & s, int pos) const
{
    return KMP(s, pos);
}

int String::size() const { return length;}

void String::print()
{
    std::cout << ptr;
}

void String::append(const String & str)
{
    int expect_length = this->length + str.size() + 1;
    if (expect_length > arraySize) {
        if (2 * arraySize >= expect_length) enlarge();
        else enlarge (2 * expect_length);
    }
    memcpy(ptr + length, str.ptr, sizeof(char) * str.length);
    length += str.length;
    ptr[length] = '\0';
}

void String::append(const String& str, int subpos, int sublen)
{
    int expect_length = this->length + sublen + 1;
    if (expect_length > arraySize) {
        if (2 * arraySize >= expect_length) enlarge();
        else enlarge (2 * expect_length);
    }
    memcpy(ptr + length, str.ptr + subpos, sizeof(char) * sublen);
    length += sublen;
    ptr[length] = '\0';
}

void String::enlarge(){
    arraySize = arraySize * 2;
    char * newPtr = new char[arraySize];
    memcpy(newPtr, ptr, sizeof(int) * length);
    if (ptr != nullptr) delete[] ptr;
    ptr = newPtr;
}

void String::enlarge(int _inc){
    arraySize += _inc;
    char * newPtr = new char[arraySize];
    memcpy(newPtr, ptr, sizeof(int) * length);
    if (ptr != nullptr) delete[] ptr;
    ptr = newPtr;
}

void String::replace_all(const String & str1, const String & str2)
{
    int pos = 0, pos_before = 0;
    String new_str(2 * this->length);
    while ((pos = this->find(str1, pos)) != -1) {
        new_str.append(*this, pos_before, pos - pos_before);
        new_str.append(str2);
        pos += str1.size();
        pos_before = pos;
    }
    new_str.append(*this, pos_before, this->size() - pos_before);
    *this = new_str;
}

