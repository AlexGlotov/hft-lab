#include <vector>

class Widget {};

template<typename T> class TD;

template<typename T>
void f(T param) {
    TD<T> tType;
    TD<decltype(param)> paramType;
}

int main() {
    std::vector<Widget> vw;
    vw.push_back(Widget{});
    f(&vw[0]);
}
