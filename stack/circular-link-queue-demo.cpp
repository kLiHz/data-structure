#include "CircularLinkQueue.hpp"
#include <iostream>

int main() {
  CircularLinkQueue<int> q;

  for (int i = 1; i <= 5; ++i) {
    q.push(11 * i);
  }

  std::cout << "原队伍: " << q << "\n";
  std::cout << std::boolalpha;
  std::cout << "是否满队? " << q.full() << "\n";

  for (int i = 1; i <= 5; ++i) {
    q.pop();
    std::cout << "将第 " << i << " 个元素出队伍后: " << q << "\n";
    std::cout << "是否满队? " << q.full() << "\n";
  }
  std::cout << "是否空队? " << q.empty() << "\n";

  for (int i = 6; i <= 10; ++i) {
    q.push(11 * i);
    std::cout << "入队 " << 11 * i << " 后: " << q << "\n";
    std::cout << "是否满队? " << q.full() << "\n";
    std::cout << "是否空队? " << q.empty() << "\n";
  }
}
