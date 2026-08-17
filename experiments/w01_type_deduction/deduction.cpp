#include <cstddef>
#include <type_traits>
#include <utility>

template <typename ExpectedT, typename ExpectedParam, typename T>
void by_value(T param) {
    static_assert(std::is_same_v<T, ExpectedT> &&
                  std::is_same_v<decltype(param), ExpectedParam>);
}

template <typename ExpectedT, typename ExpectedParam, typename T>
void by_ref(T& param) {
    static_assert(std::is_same_v<T, ExpectedT> &&
                  std::is_same_v<decltype(param), ExpectedParam>);
}

template <typename ExpectedT, typename ExpectedParam, typename T>
void by_uref(T&& param) {
    static_assert(std::is_same_v<T, ExpectedT> &&
                  std::is_same_v<decltype(param), ExpectedParam>);
}

template <typename Expected, typename T>
void check(T&&) {
    static_assert(std::is_same_v<T, Expected>);
}

template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) noexcept {
    return N;
}

namespace {

void run_by_value_checks() {
    int value = 1;
    const int const_value = 2;
    int array[7] = {};

    by_value<int, int>(value);   
    by_value<int, int>(const_value);
    by_value<int*, int*>(array);
}

void run_by_ref_checks() {
    int value = 1;
    const int const_value = 2;
    int array[7] = {};

    by_ref<int, int&>(value);
    by_ref<const int, const int&>(const_value);
    by_ref<int[7], int(&)[7]>(array);
}

void run_array_by_ref_checks() {
    const char name[] = "hft-lab";

    static_assert(array_size(name) == 8);
    static_assert(std::is_same_v<decltype(name), const char[8]>);
    static_assert(std::is_same_v<decltype((name)), const char (&)[8]>);

    by_ref<const char[8], const char (&)[8]>(name);
}

void run_by_uref_checks() {
    int value = 1;
    const int const_value = 2;

    by_uref<int&, int&>(value);
    by_uref<int, int&&>(std::move(value));
    by_uref<const int&, const int&>(const_value);

    check<int&>(value);
    check<int>(std::move(value));
}

}

int main() {
    run_by_value_checks();
    run_by_ref_checks();
    run_array_by_ref_checks();
    run_by_uref_checks();

    int seven[7] = {};
    static_assert(array_size(seven) == 7);

    return 0;
}
