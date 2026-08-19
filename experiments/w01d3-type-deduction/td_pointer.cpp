template<typename T> class TD;

template<typename T>
void f(T param) {
    TD<T> tType;
    TD<decltype(param)> paramType;
}

template<typename T>
void g(T& param) {
    TD<T> tType;
    TD<decltype(param)> paramType;
}

int main() {
    int x = 27;
    const int* const p = &x;
    f(p);
    g(p);
}
