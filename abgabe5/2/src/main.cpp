#include <optional>
#include <type_traits>

template<typename T>
struct IsOptional : std::false_type {};

template<typename T>
struct IsOptional<std::optional<T>> : std::true_type {};

template<typename T>
constexpr bool IsOptionalV = IsOptional<T>::value;

int main() {
    static_assert(!IsOptionalV<int>);
    static_assert(IsOptionalV<std::optional<int>>);
}
