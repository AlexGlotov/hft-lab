#include <vector>
#include <cstdio>
#include <typeinfo>

class Widget {};

template<typename T>
void f(T param) {
    std::printf("typeid(T)     = %s\n", typeid(T).name());
    std::printf("typeid(param) = %s\n", typeid(param).name());
}

int main() {
    std::vector<Widget> vw;
    vw.push_back(Widget{});
    f(&vw[0]);
}
