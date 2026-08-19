#include <cstdio>
#include <typeinfo>

template<typename T>
void f(T param) {
    std::printf("f: typeid(T)     = %s\n", typeid(T).name());
    std::printf("f: typeid(param) = %s\n", typeid(param).name());
}

template<typename T>
void g(T& param) {
    std::printf("g: typeid(T)     = %s\n", typeid(T).name());
    std::printf("g: typeid(param) = %s\n", typeid(param).name());
}

int main() {
    int x = 27;
    const int& rx = x;
    f(rx);
    g(rx);
}
