#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename, typename = void>
struct has_less_than : std::false_type {};

template <typename T>
struct has_less_than<T, std::void_t<decltype(std::declval<const T&>() < std::declval<const T&>())>>
    : std::bool_constant<std::is_convertible_v<decltype(std::declval<const T&>() < std::declval<const T&>()), bool>> {};

template <typename, typename = void>
struct has_output : std::false_type {};

template <typename T>
struct has_output<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
class MiniSmartList {
public:
    void push_back(const T& value) {
        data.push_back(value);
    }

    void pop_back() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    std::size_t size() const {
        return data.size();
    }

    void clear() {
        data.clear();
    }

    template <typename U = T, std::enable_if_t<std::is_arithmetic_v<U>, int> = 0>
    U sum() const {
        U result{};
        for (const auto& x : data) {
            result += x;
        }
        return result;
    }

    template <typename U = T, std::enable_if_t<has_less_than<U>::value, int> = 0>
    void sort() {
        std::sort(data.begin(), data.end());
    }

    template <typename U = T, std::enable_if_t<has_output<U>::value, int> = 0>
    void print() const {
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i + 1 < data.size()) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    void debug_print() const {
        for (const auto& x : data) {
            if constexpr (std::is_pointer_v<T>) {
                std::cout << "[адрес] " << static_cast<const void*>(x) << '\n';
            } else {
                std::cout << "[значение] " << x << '\n';
            }
        }
    }

    template <typename U>
    bool contains(U&& value) const {
        using CleanT = std::remove_cv_t<std::remove_reference_t<T>>;
        using CleanU = std::remove_cv_t<std::remove_reference_t<U>>;

        static_assert(std::is_same_v<CleanT, CleanU>, "Несовпадение типов в contains()");

        CleanT target = static_cast<CleanT>(value);
        for (const auto& x : data) {
            if (x == target) {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<T> data;
};

int main() {
    MiniSmartList<int> a;
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);

    std::cout << "Список до сортировки: ";
    a.print();

    std::cout << "Сумма: " << a.sum() << '\n';

    a.sort();
    std::cout << "Список после сортировки: ";
    a.print();

    std::cout << "Отладочный вывод для значений:\n";
    a.debug_print();

    int x = 2;
    const int y = 3;
    std::cout << "Содержит x: " << (a.contains(x) ? "да" : "нет") << '\n';
    std::cout << "Содержит y: " << (a.contains(y) ? "да" : "нет") << '\n';
    std::cout << "Содержит 10: " << (a.contains(10) ? "да" : "нет") << '\n';
    std::cout << "Содержит std::move(x): " << (a.contains(std::move(x)) ? "да" : "нет") << '\n';

    int p = 42;
    MiniSmartList<int*> b;
    b.push_back(&p);

    std::cout << "Отладочный вывод для указателей:\n";
    b.debug_print();

    return 0;
}
