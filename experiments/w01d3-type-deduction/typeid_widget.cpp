#include <vector>
#include <cstdio>
#include <typeinfo>

class Widget {};

template<typename T>
void f(const T& param) {
    std::printf("typeid(T)     = %s\n", typeid(T).name());
    std::printf("typeid(param) = %s\n", typeid(param).name());
}

std::vector<Widget> createVec() {
    return std::vector<Widget>(1);
}

int main() {
    const auto vw = createVec();
    if (!vw.empty()) f(&vw[0]);
}
