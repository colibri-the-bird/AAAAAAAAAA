#include <iostream>

template <typename T>
class Printer {
public:
    void print(const T& value) const {
        std::cout << "Значение: " << value << '\n';
    }
};

template <>
class Printer<bool> {
public:
    void print(const bool& value) const {
        std::cout << "Логическое значение: " << (value ? "true" : "false") << '\n';
    }
};

template <typename T>
class Printer<T*> {
public:
    void print(T* ptr) const {
        std::cout << "Адрес: " << static_cast<const void*>(ptr)
                  << ", значение: " << *ptr << '\n';
    }
};

int main() {
    Printer<int> p1;
    p1.print(42);

    Printer<bool> p2;
    p2.print(true);

    int x = 100;
    Printer<int*> p3;
    p3.print(&x);

    return 0;
}
