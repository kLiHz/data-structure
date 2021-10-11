
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

    BiStackMemory(size_t n) : ptr(new T[n]), len(n) {
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

    auto full() {
        return (top_pos[0] - 1) == top_pos[1];
    }

    auto empty() {
        return (top_pos[0] == 0) && (top_pos[1] == len - 1);
    }

    auto empty(GrowthDirection dir) {
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

    auto top(GrowthDirection dir) {
        if (dir == GrowthDirection::UP) {
            return ptr[top_pos[0]-1];
        } else {
            return ptr[top_pos[1]+1];
        }
    };
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
    auto empty() {
        return mem.empty(d);
    }
    auto full() {
        return mem.full();
    }
};

int main() {
    BiStackMemory<int> mem(10);
    SharedStack<int> s1(mem), s2(mem);
    for (int i = 1; i < 10; i += 2) {
        s1.push(i);
    }
    for (int i = 2; i <= 10; i += 2) {
        s2.push(i);
    }
    s1.pop();
    s2.pop();
    s1.pop();
    s2.pop();
}

