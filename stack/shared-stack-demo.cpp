#include <cstddef>

template <typename T>
class BiStackMemory
{
    int top_pos[2];
    int usage;
    T *ptr;
    int len;
public:
    enum class GrowthDirection { UP, DOWN };

    BiStackMemory() = delete;
    BiStackMemory(const BiStackMemory &) = delete;

    BiStackMemory(std::size_t n) : ptr(new T[n]), len(n) {
        usage = 0;
        top_pos[0] = 0;
        top_pos[1] = len - 1;
    }

    ~BiStackMemory() { delete[] ptr; }

    BiStackMemory& operator=(const BiStackMemory & ) = delete;

    auto add_user() {
        usage += 1;
        return usage == 1 ? GrowthDirection::UP : GrowthDirection::DOWN;
    }

    bool occupied() { return usage == 2; };

    void remove_user(GrowthDirection dir) {
        usage -= 1;
        if (dir == GrowthDirection::UP) {
            top_pos[0] = 0;
        } else if (dir == GrowthDirection::DOWN) {
            top_pos[1] = len - 1;
        }
    }

    auto full() const {
        return (top_pos[0] - 1) == top_pos[1];
    }

    auto empty() const {
        return (top_pos[0] == 0) && (top_pos[1] == len - 1);
    }

    auto empty(GrowthDirection dir) const {
        return dir == GrowthDirection::UP ?
            (top_pos[0] == 0) :
            (top_pos[1] == len - 1);
    }

    auto push(GrowthDirection dir, const T& val) {
        if (this->full()) return false;
        if (dir == GrowthDirection::UP) {
            ptr[top_pos[0]] = val;
            top_pos[0]++;
        } else {
            ptr[top_pos[1]] = val;
            top_pos[1]--;
        }
        return true;
    };

    auto pop(GrowthDirection dir) {
        if (this->empty(dir)) return false;
        if (dir == GrowthDirection::UP) {
            top_pos[0]--;
        } else {
            top_pos[1]++;
        }
        return true;
    };

    auto top(GrowthDirection dir) const {
        if (dir == GrowthDirection::UP) {
            return ptr[top_pos[0]-1];
        } else {
            return ptr[top_pos[1]+1];
        }
    };
    
    auto size(GrowthDirection dir) const {
        if (dir == GrowthDirection::UP) {
            return top_pos[0];
        } else {
            return len - (top_pos[1] + 1);
        }
    };

    auto capacity() const { return len; }
    auto data() const { return ptr; }
};

template<typename T>
class SharedStack {
    BiStackMemory<T>& mem;
    typename BiStackMemory<T>::GrowthDirection d;
public:
    SharedStack(BiStackMemory<T>& m) : mem(m) {
        d = mem.add_user();
    }
    ~SharedStack() {
        mem.remove_user(d);
    }
    auto pop() {
        return mem.pop(d);
    };
    auto top() {
        return mem.top(d);
    };
    auto push(const T& val) {
        return mem.push(d, val);
    };
    auto empty() const {
        return mem.empty(d);
    }
    auto full() const {
        return mem.full();
    }
};

#include <iostream>
#include <string>

template<typename T>
std::ostream& operator<<(std::ostream& os, BiStackMemory<T> const & mem) {
    auto x1 = mem.size(BiStackMemory<T>::GrowthDirection::UP);
    auto x2 = mem.size(BiStackMemory<T>::GrowthDirection::DOWN);
    std::string data_line;
    std::string indicator_line;
    auto len = mem.capacity();
    for (int i = 0; i < len; i++) {
        auto val = std::to_string(mem.data()[i]);
        data_line += val + ' ';
        auto blank = std::string(val.length() + 1, ' ');
        if (x1 - 1 == i || len - x2 == i) {
            blank[0] = '^';
        }
        indicator_line += blank;
    }
    os << data_line << "\n" << indicator_line;
    return os;
}

int main() {
    BiStackMemory<int> mem(10);
    SharedStack<int> s1(mem), s2(mem);

    std::cout << "Memory allocated.\n";
    std::cout << std::boolalpha;
    std::cout << "s1.empty(): " << s1.empty() << "\n";
    std::cout << "s2.empty(): " << s2.empty() << "\n\n";

    for (int i = 1; i < 10; i += 2) { s1.push(i); }
    std::cout << mem << "\n";
    std::cout << "s1.empty(): " << s1.empty() << "\n";
    std::cout << "s2.empty(): " << s2.empty() << "\n\n";
    
    for (int i = 2; i <= 10; i += 2) { s2.push(i); }
    std::cout << mem << "\n";
    std::cout << "s1.empty(): " << s1.empty() << "\n";
    std::cout << "s2.empty(): " << s2.empty() << "\n";
    std::cout << "s1.full(): " << s1.full() << "\n";
    std::cout << "s2.full(): " << s2.full() << "\n\n";

    std::cout << "s1.pop():\n";
    s1.pop();
    std::cout << mem << "\n";
    std::cout << "s1.empty(): " << s1.empty() << "\n";
    std::cout << "s2.empty(): " << s2.empty() << "\n";
    std::cout << "s1.full(): " << s1.full() << "\n";
    std::cout << "s2.full(): " << s2.full() << "\n\n";

    std::cout << "s2.pop():\n";
    s2.pop();
    std::cout << mem << "\n";

    std::cout << "s1.pop():\n";
    s1.pop();
    std::cout << mem << "\n";

    std::cout << "s2.pop():\n";
    s2.pop();
    std::cout << mem << "\n";
}

