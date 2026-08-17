#include <climits>

int main(int argc, char**) {
    // По той же причине value не константа для компилятора, хотя при
    // обычном запуске (argc == 1) она равна INT_MAX.
    int value = INT_MAX - 1 + argc;
    int overflowed = value + 1;  // signed integer overflow — undefined behavior

    return overflowed;
}
