#include <vector>

class Widget {};

template<typename T> class TD;

template<typename T>
void f(const T& param) {
    TD<T> tType;
    TD<decltype(param)> paramType;
}

std::vector<Widget> createVec() {
    return std::vector<Widget>(1);
}

int main() {
    const auto vw = createVec();
    if (!vw.empty()) f(&vw[0]);
}
