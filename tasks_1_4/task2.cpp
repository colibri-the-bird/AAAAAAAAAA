#include <iostream>
#include <type_traits>

class Animal {
public:
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual ~Animal() = default;
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Кошка: мяу\n";
    }

    void move() const override {
        std::cout << "Кошка двигается тихо\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Собака: гав\n";
    }

    void move() const override {
        std::cout << "Собака бежит\n";
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        std::cout << "Птица: чирик\n";
    }

    void move() const override {
        std::cout << "Птица летит\n";
    }
};

class Car {
public:
    void drive() const {
        std::cout << "Машина едет\n";
    }
};

template <typename T>
void feedAnimal(const T& obj) {
    using U = std::decay_t<T>;

    if constexpr (std::is_base_of_v<Animal, U>) {
        std::cout << "Кормим животное...\n";
        obj.makeSound();
        obj.move();
        std::cout << "Животное накормлено\n\n";
    } else {
        std::cout << "Ошибка: это не животное\n\n";
    }
}

template <typename T>
void checkAnimalType() {
    static_assert(std::is_base_of_v<Animal, T>, "T должен наследоваться от Animal");
    std::cout << "Проверка типа пройдена\n";
}

int main() {
    Cat cat;
    Dog dog;
    Bird bird;
    Car car;

    feedAnimal(cat);
    feedAnimal(dog);
    feedAnimal(bird);
    feedAnimal(car);

    checkAnimalType<Cat>();
    checkAnimalType<Dog>();
    checkAnimalType<Bird>();

    return 0;
}
