#include <climits>
#include <cstdio>

int main(int argc, char**) {
    // argc == 1 в обычном запуске, но компилятор этого не знает — не
    // constant-foldable, поэтому -INT_MIN ниже не ловится статически
    // (-Woverflow), только UBSan в рантайме.
    int tmin = INT_MIN + (argc - 1);

    std::printf("INT_MIN            = %d\n", INT_MIN);
    std::printf("INT_MAX             = %d\n", INT_MAX);
    std::printf("-INT_MIN            = %d\n", -tmin);
    std::printf("(unsigned)INT_MIN   = %u\n", (unsigned)INT_MIN);
    return 0;
}
