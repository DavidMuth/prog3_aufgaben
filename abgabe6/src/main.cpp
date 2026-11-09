
#include <iostream>
// TODO: define a recursive structure to implement a tuple.
template<class T, class... Rest>
struct Tuple {
    Tuple(T value, Rest... rest) : value(value), rest(rest...) {};
    T value;
    Tuple<Rest...> rest;

    template <int idx>
    auto get() {
        if constexpr(idx == 0) {
            return value;
        } else if constexpr (idx > 0) {
            return rest.get<idx - 1>();
        } else {
            static_assert(false, "Faslcher Index");
        }
    }
};

template<class T>
    struct Tuple<T> {
        template<int idx>
        T get() {
        static_assert(idx == 0, "Falscher index");
        return value;
        }

        T value;
};


    int main() {
        Tuple<int, float, int> t(2, 1.2, 9);
        std::cout << t.get<0>() << "\n"; // 2   -- an int, type-safe!
        std::cout << t.get<1>() << "\n"; // 1.2 -- a float, type-safe!
        std::cout << t.get<2>() << "\n"; // 9   -- an int, type-safe!
    }
