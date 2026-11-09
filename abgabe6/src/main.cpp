#include <cassert>
#include <iostream>

// TODO: define a recursive structure to implement a tuple.
template<class T, class... Rest>
struct Tuple {
    Tuple(T value, Rest... rest) : value(value), rest(rest...) {};
    T value;
    Tuple<Rest...> rest;

    template<int idx>
    auto get() {
        if constexpr (idx == 0) {
            return value;
        } else if constexpr (idx > 0) {
            return rest.template get<idx - 1>();
        } else {
            static_assert(false, "falscher index 1");
        }
    }
};

template<class T>
struct Tuple<T> {
    int value;

    template<int idx>
    T get() {
        static_assert(idx == 0, "wrong index");
        return value;
    }
};

/*int main() {
    Tuple<int, float, int> t(2, 1.2, 9);

    std::cout << t.value << "\n";           // 2
    std::cout << t.rest.value << "\n";      // 1.2
    std::cout << t.rest.rest.value << "\n"; // 9
}*/

// TODO: add a get<idx>() method to your tuple class

int main() {
    Tuple<int, float, int> t(2, 1.2, 9);
    std::cout << t.get<0>() << "\n"; // 2   -- an int, type-safe!
    std::cout << t.get<1>() << "\n"; // 1.2 -- a float, type-safe!
    std::cout << t.get<2>() << "\n"; // 9   -- an int, type-safe!
    // std::cout << t.get<-1>() << "\n"; // 9   -- an int, type-safe!
}
