
#include <iostream>

int main() {
    auto fibbo = [x0 = 0, x1 = 1]() mutable {
        int ret = x0;
        x0 += x1;
        std::swap(x1, x0);
        return ret;
    };

    for (int x = 0; x < 8; x++) { // request 8 numbers
        std::cout << fibbo() << " ";
        // output: 0 1 1 2 3 5 8 13
    }
}