#include <boost/type_index.hpp>
#include <iostream>

template<typename T>
void f(T param) {
    std::cout << "f: type_id_with_cvr<T>()               = "
              << boost::typeindex::type_id_with_cvr<T>().pretty_name() << '\n';
    std::cout << "f: type_id_with_cvr<decltype(param)>() = "
              << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template<typename T>
void g(T& param) {
    std::cout << "g: type_id_with_cvr<T>()               = "
              << boost::typeindex::type_id_with_cvr<T>().pretty_name() << '\n';
    std::cout << "g: type_id_with_cvr<decltype(param)>() = "
              << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

int main() {
    int x = 27;
    const int& rx = x;
    f(rx);
    g(rx);
}
