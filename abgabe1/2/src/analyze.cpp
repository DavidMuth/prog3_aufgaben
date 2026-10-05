#include <analyze.hpp>

uint32_t analyze(int i) {
    return analyze(std::to_string(i));
}

uint32_t analyze(const std::string& string) {
    return string.size();
}
