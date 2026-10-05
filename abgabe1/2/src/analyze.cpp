#include <analyze.hpp>

uint32_t analyze(int i) {
    uint32_t count = 0;

    if (i < 0) {
        ++count;
    }

    while (i >= 10 || i <= -10) {
        i /= 10;
        ++count;
    }

    ++count;

    return count;
}

uint32_t analyze(const std::string& string) {
    return string.size();
}
