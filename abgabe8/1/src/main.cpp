
#include <iostream>

struct FibonacciIter { // next = current+previous value
    int i;             // this is the index (0,1,2,3,...)
    int x1 = 1;        // this is the next value
    int x0 = 0;        // this is the current value

    bool operator!=(const FibonacciIter& other) const {
        return other.i != i;
    }

    FibonacciIter& operator ++ () {
        i++;
        int n = x1;
        x1 = x0 + x1;
        x0 = n;
        return *this;
    }

    int operator*() {
        return x0;
    }
};

struct Fibonacci {
    int n;
    Fibonacci(int n_) : n(n_) {}
    FibonacciIter begin() {
        return FibonacciIter{ 0 };
    }
    FibonacciIter end() {
        return FibonacciIter{ n };
    }
};

int main() {
    for (auto x : Fibonacci{ 4 }) { // request 4 fibo. numbers
        std::cout << x << " ";      // output: 0 1 1 2
    }
    std::cout << "\n";
    for (auto x : Fibonacci{ 8 }) { // request 8 fibo. numbers
        std::cout << x << " ";      // output: 0 1 1 2 3 5 8 13
    }
}