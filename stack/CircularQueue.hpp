// 顺序表存储的队列一般采用循环方式实现
// 有时也称作循环缓冲区
// 入队时，end 指针递增
// 出队时，front 指针递增

// _ _ _ a b c d _ _ _
//       ^       ^
//       front   end
//
// end 指针指向队尾空位（也可以反过来，front 指向队首前空位）

// 队满：
// h i _ a b c d e f g
//     ^ ^ 

// 一般来说，像这样留置一个空位可以方便实现
// 
// 即判据为：
//  increase(end) == front 为队满
//  front == end 为队空

#include <iostream>
#include <string>

template<typename T>
class Queue {
    T* data;
    size_t len, front, rear;
    auto increasedIndex(size_t i) {
        return (i + 1) % len;
    };
public:
    Queue() = delete;
    Queue(const Queue &) = delete;
    Queue(size_t n) : len(n), data(new T[n]), front(0), rear(0) {}
    Queue & operator==(Queue const & ) = delete;
    ~Queue() { delete[] data; }
    auto empty() { return front == rear; }
    auto full() { return increasedIndex(rear) == front; }
    auto push(const T & a) {
        if (this->full()) return;
        data[rear] = a;
        rear = increasedIndex(rear);
    }
    auto pop() {
        if (this->empty()) return;
        front = increasedIndex(front);
    }
    T& top() {
        return data[front];
    }
    auto capacity() { return len; }

    friend std::ostream& operator<< (std::ostream& os, Queue const & q) {
        auto x1 = q.front;
        auto x2 = q.rear;
        std::string data_line;
        std::string indicator_line;
        std::string front_tag_line, end_tag_line;
        for (int i = 0; i < q.len; i++) {
            auto val = std::to_string(q.data[i]);
            data_line += val + ' ';
            auto blank = std::string(val.length() + 1, ' ');
            if (x1 == i) {
                blank[0] = '^';
                front_tag_line += "front";
            } else {
                front_tag_line += blank;
            }
            if (x2 == i) {
                blank[0] = '^';
                end_tag_line += "end";
            } else {
                end_tag_line += blank;
            }
            indicator_line += blank;
        }
        os << data_line << "\n" << indicator_line << "\n" << front_tag_line << "\n" << end_tag_line;
        return os;
    }
};


// 抑或，改变 end 指针指向为队尾元素

// _ _ _ a b c d _ _ _
//       ^     ^
//       front end

// 队空：
// _ _ _ _ _ _ _ _ _ _
//   ^ ^ front
//   end

// 即判据为：
//  front == end 为队满
//  increase(end) == front 为队空

// 如果要利用空间中的每一个元素，则发现，
// 无法根据 front 和 rear 的相对情况区分队空队满
// 因此需要额外的信息来区分二者

// 比如， end 指针指向为队尾元素，队满时如下
// c d e a b
//     ^ ^
// 则队空时一般如下：
// _ _ _ _ _
//     ^ ^
//   end: 只有一个元素时，等于 front，队空时则应为 front 前一个

// 又比如， end 指针指向队尾空位置，队空队满时皆为 front == end

// 其实，或许使用 front + size 的方法更为巧妙
// 只不过，为了避免极端情况下的整数运算溢出，可能需要在求队尾元素位置时稍作处理

