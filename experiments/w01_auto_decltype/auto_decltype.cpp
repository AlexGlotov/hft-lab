#include <initializer_list>
#include <type_traits>

template <typename T>
void tf(T);

template <typename T>
void tf_il(std::initializer_list<T>);

auto plain_auto_return() {
    int local = 0;
    return (local);
}

// decltype(auto) применяет к выражению после return правила decltype, а не
// auto. Наивно ожидаешь decltype((local)) == int& (двойные скобки -> lvalue),
// и это действительно так для decltype((local)) как отдельного выражения —
// см. run_decltype_paren_checks. Но C++20 (P1825, "more implicit moves")
// делает так, что имя локальной переменной в return-операторе неявно
// движется, ДАЖЕ в скобках — раньше именно скобки были стандартным приёмом
// это движение отключить. В результате decltype(auto) здесь выводит int&&,
// а не int&: проверено раздельно на g++-14 и clang++-18, оба согласны.
// И то, и другое — ссылка на уничтоженный объект, только разного вида.
// Компилятор при этом НЕ молчит: без диагностической прагмы ниже сборка
// падает на -Wreturn-local-addr (gcc) / -Wreturn-stack-address (clang) под
// -Werror. Прагма отключает предупреждение только для этой функции, чтобы
// сам факт вывода типа остался доказуемым static_assert'ом, а не просто
// заявленным в комментарии.
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#endif
decltype(auto) decltype_auto_return() {
    int local = 0;
    return (local);
}
#pragma GCC diagnostic pop

namespace {

void run_auto_braced_init_checks() {
    auto a = {1, 2, 3};
    auto b{1};
    auto c = {1};

    static_assert(std::is_same_v<decltype(a), std::initializer_list<int>>);

    // Мейерс, "Effective Modern C++" (2014), описывает auto b{1} как
    // std::initializer_list<int> — это было верно для C++11/14. P0091
    // (direct-list-init с одним элементом) сменил правило в C++17: теперь
    // это int. Мы собираем под C++23, поэтому книжное поведение здесь не
    // просто "устарело" — оно физически недостижимо на этом стандарте.
    // Проверяем обе стороны явно, а не только текущую:
    static_assert(std::is_same_v<decltype(b), int>);
    static_assert(!std::is_same_v<decltype(b), std::initializer_list<int>>);

    static_assert(std::is_same_v<decltype(c), std::initializer_list<int>>);
}

void run_template_deduction_checks() {
    static_assert(requires { tf(1); });
    static_assert(requires { tf(std::initializer_list<int>{1, 2, 3}); });
    static_assert(requires { tf_il({1, 2, 3}); });

    // C++14: auto в возвращаемом типе функции и в параметре лямбды выводится
    // по тем же правилам, что и параметр шаблона T (лямбда с auto-параметром
    // — синтаксический сахар над шаблонным operator()). Значит, для голого
    // braced-init-list он ломается ровно как tf({1,2,3}) выше — тот же
    // non-deduced context, и так же не доказывается через requires{}
    // (см. коммит ef29ded): проверено отдельно, auto f() { return {1, 2,
    // 3}; } не компилируется ни на g++-14 ("returning initializer list"),
    // ни на clang++-18 ("cannot deduce return type from initializer list").
    // Встроить эту сломанную функцию в файл нельзя по той же причине, по
    // которой нельзя было встроить !requires{tf({1,2,3})} — рабочая сторона
    // того же правила для лямбда-параметра:
    constexpr auto generic_lambda = [](auto value) { return value; };
    static_assert(std::is_same_v<decltype(generic_lambda(1)), int>);
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

void run_decltype_auto_checks() {
    static_assert(std::is_same_v<decltype(plain_auto_return()), int>);
    static_assert(std::is_same_v<decltype(decltype_auto_return()), int&&>);
}

}  // namespace

int main() {
    run_auto_braced_init_checks();
    run_template_deduction_checks();
    run_decltype_paren_checks();
    run_decltype_auto_checks();
    return 0;
}
