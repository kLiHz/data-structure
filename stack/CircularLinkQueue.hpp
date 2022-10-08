/*
 * 请设计一个队列, 要求满足:
 * 1. 初始时队列为空;
 * 2. 入队时, 允许增加队列占用空间;
 * 3. 出队后, 出队元素所占用的空间可重复使用, 即整个队列所占用的空间只增不减;
 * 4. 入队操作和出队操作的时间复杂度始终保持为 O(1).
 *
 * 请回答下列问题:
 * 1. 该队列是应选择链式存储结构, 还是应选择顺序存储结构?
 * 2. 画出队列的初始状态, 并给出判断队空和队满的条件;
 * 3. 试编写算法分别实现队列初始化, 入队列和出队列操作.
 *
 * */

#include <iostream>
#include <sstream>

template <typename T> class CircularLinkQueue {

  struct Node {
    T data;
    Node *next;
  }; // 数据结点

  Node *head, *rear;

public:
  // 空队列: 将 rear 置空表示空队列
  // 队列初始化后有 1 个空间
  //
  //       front
  //       | rear = nullptr
  //       |
  //       -----
  //   --->| / |---
  //   |   -----  |
  //   ------------

  // 空队列
  bool empty() const { return this->rear == nullptr; }

  // 初始化队列
  CircularLinkQueue() {
    Node *s = new Node;
    s->next = s;
    this->head = s;
    this->rear = nullptr;
  }

  // 队列空间满的情况 / 没有空余空间
  // 情况 1:
  //
  //       front           rear
  //       |               |
  //       -----   -----   -----
  //   --->| E |-->| E |-->| E |---
  //   |   -----   -----   -----  |
  //   ----------------------------
  //
  //  情况 2:
  //
  //       front
  //       | rear
  //       | |
  //       -----
  //   --->| E |---
  //   |   -----  |
  //   ------------

  // 队列有空余空间的情况:
  //
  //       front
  //       | rear
  //       | |
  //       -----   -----   -----
  //   --->| E |-->| / |-->| / |---
  //   |   -----   -----   -----  |
  //   ----------------------------

  // 队列没有空余空间
  bool full() const {
    return this->rear != nullptr && (this->rear->next == this->head);
  }

  // 释放队列
  ~CircularLinkQueue() {
    Node *i = this->head->next;
    while (i != this->head) {
      // cout << "Freeing " << i->data << "\n";
      Node *t = i;
      i = i->next;
      delete t;
    }
    // cout << "Freeing " << i->data << "\n";
    delete i;
  }

  // 入队
  void push(T&& e) {
    if (this->rear == nullptr) { // 空队列
      this->head->data = std::move(e);
      this->rear = this->head;
    } else if (this->rear->next == this->head) { // 队列满则开辟一个空间
      Node *s = new Node;
      s->data = std::move(e);
      s->next = this->rear->next;
      this->rear->next = s;
      this->rear = s;
    } else { // 有空结点
      this->rear = this->rear->next;
      this->rear->data = std::move(e);
    }
  }

  // 入队
  void push(T const& e) {
    if (this->rear == nullptr) { // 空队列
      this->head->data = e;
      this->rear = this->head;
    } else if (this->rear->next == this->head) { // 队列满则开辟一个空间
      Node *s = new Node;
      s->data = e;
      s->next = this->rear->next;
      this->rear->next = s;
      this->rear = s;
    } else { // 有空结点
      this->rear = this->rear->next;
      this->rear->data = e;
    }
  }

  // 出队
  void pop() {
    if (this->head == this->rear) { // 一个元素的情况
      // e = q->rear->data;
      this->rear = nullptr;
    } else {
      // e = q->front->data;
      this->head = this->head->next;
    }
  }

  auto front() const { return this->head->data; }

  auto to_string() const {
    std::ostringstream ss;
    Node *i = this->head;
    if (!this->empty()) {
      do {
        ss << i->data << " ";
        i = i->next;
      } while (i != this->rear->next);
    }
    return ss.str();
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, CircularLinkQueue<T> const& q) {
  os << q.to_string();
  return os;
}
