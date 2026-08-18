#include <initializer_list>
#include <type_traits>

template <typename T>
void tf(T);

template <typename T>
void tf_il(std::initializer_list<T>);

namespace {

void run_auto_braced_init_checks() {
    auto a = {1, 2, 3};
    auto b{1};
    auto c = {1};

    static_assert(std::is_same_v<decltype(a), std::initializer_list<int>>);
    static_assert(std::is_same_v<decltype(b), int>);
    static_assert(std::is_same_v<decltype(c), std::initializer_list<int>>);
}

void run_template_deduction_checks() {
    static_assert(requires { tf(1); });
    static_assert(requires { tf(std::initializer_list<int>{1, 2, 3}); });
    static_assert(requires { tf_il({1, 2, 3}); });
}

void run_decltype_paren_checks() {
    int x = 0;
    const int cx = 1;
    int& rx = x;

    static_assert(std::is_same_v<decltype(x), int>);
    static_assert(std::is_same_v<decltype((x)), int&>);
    static_assert(std::is_same_v<decltype(cx), const int>);
    static_assert(std::is_same_v<decltype((cx)), const int&>);
    static_assert(std::is_same_v<decltype(rx), int&>);
}

}  // namespace

int main() {
    run_auto_braced_init_checks();
    run_template_deduction_checks();
    run_decltype_paren_checks();
    return 0;
}
