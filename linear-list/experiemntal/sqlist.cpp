#include <iostream>
#include <random>
#include "sqlist.hpp"

template<class T>
auto and_sqlist(const SqList<T>& A, const SqList<T>& B) {
    int idx_a = 0, idx_b = 0;
    SqList<T> C(A.length() + B.length());
    int idx_c = 0;
    while (idx_a < A.length() && idx_b < B.length()) {
        if (A[idx_a] == B[idx_b]) {
            C[idx_c] = A[idx_a];
            idx_c++;
            idx_a++;
            idx_b++;
        }
        else if (A[idx_a] < B[idx_b]) {
            while (A[idx_a] < B[idx_b]) idx_a++;
        } 
        else if (A[idx_a] > B[idx_b]) {
            while (A[idx_a] > B[idx_b]) idx_b++;
        }
    }
    return C;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,100);
    
    SqList<int> A(20), B(20);

    for (int i = 0; i < A.length(); ++i) { A[i] = distrib(gen); }
    for (int i = 0; i < B.length(); ++i) { B[i] = distrib(gen); }

    A.sort();
    B.sort();

    for (int i = 0; i < A.length(); ++i) { std::cout << A[i] << ' '; }
    std::cout << "\n";
    
    for (int i = 0; i < B.length(); ++i) { std::cout << B[i] << ' '; }
    std::cout << "\n";

    // 

    auto C = and_sqlist(A,B);
    for (auto i : C) { std::cout << i << ' '; }
}
