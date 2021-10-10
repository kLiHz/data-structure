#include <algorithm>

template <class ElemType>
class SqList {
private:
    int size;
    ElemType* data;
public:
    SqList(int n) : size(n) { data = new ElemType[size]; }
    ~SqList() { delete data; }
    ElemType & operator[] (int n) { return data[n]; }
    ElemType operator[] (int n) const { return data[n]; }
    void sort() { std::sort(data, data + size); }
    int length() const { return size; }

    class iterator {
        int size;
        int idx;
        ElemType* data;
    public:
        iterator(ElemType * addr, int size_, int idx_ = 0) : data(addr), size(size_), idx(idx_) {}
        ElemType & operator*() { return *(data + idx); }
        iterator operator+(int offset) {
            auto t_idx = idx + offset;
            if (t_idx >= size) t_idx = size;
            return iterator(data, size, t_idx);
        } 
        iterator operator-(int offset) {
            auto t_idx = idx - offset;
            if (t_idx < 0) t_idx = 0;
            return iterator(data, size, t_idx);
        }
        iterator operator++(int) {
            if (idx == size) return *this;
            ++idx;
            return iterator(data, size, idx - 1);
        }
        iterator& operator++() {
            if (idx == size) return *this;
            ++idx;
            return *this;
        }
        bool operator==(iterator other) { return data + idx == other.data + other.idx; }
        bool operator!=(iterator other) { return data + idx != other.data + other.idx; }
    };

    iterator begin() { return iterator(data, size, 0); }
    iterator end() { return iterator(data, size, size); }

    void insert(iterator pos) {
        
    }
};

