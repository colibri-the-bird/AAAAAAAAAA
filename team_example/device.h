#pragma once
#include <string>

/**
 * Базовый класс для электрических устройств умного дома
 * Все устройства должны наследоваться от этого класса
 */
class Device {
protected:
    std::string name{}; // Имя устройства
    double maxBattery{}; // Максимальная ёмкость аккумулятора (Вт·ч)
    double currentBattery{0.0}; // Текущий заряд аккумулятора (Вт·ч)
    double powerConsumptionPerHour{}; // Потребление энергии (Вт) в час
    bool isRunning{false}; // Флаг, указывающий, что устройство работает в данный момент
  
public:
    Device(const std::string& name, 
           double maxBattery,      // Максимальная ёмкость аккумулятора (Вт·ч)
           double powerConsumption); // Потребление энергии (Вт)

    virtual ~Device() = default;

    // Включить устройство
    virtual void turnOn();

    // Выключить устройство
    virtual void turnOff();

    // Зарядить до полного уровня
    // Возвращает энергию в Вт, необходимую для зарядки
    virtual double chargeToFull();

    // Работать в течение указанного времени
    virtual void work(double hours);

    // Получить текущий заряд в Вт·ч
    double getCurrentBattery() const;

    // Получить текущий заряд в процентах (0..100)
    double getCurrentBatteryPercent() const;

    // Получить потребление энергии
    double getPowerConsumptionPerHour() const;

    // Проверить, работает ли устройство
    bool isDeviceRunning() const;

    // Получить имя устройства
    const std::string& getName() const;

    // Получить описание устройства (переопределить в подклассах)
    virtual std::string getDescription() const = 0;

    // Вывести статус устройства
    virtual void printStatus() const;

    // Проверить, нужно ли заряжать устройство
    bool needToBeCharged() const;

    /**
     * Чисто виртуальный метод для симуляции одного дня работы
     * Каждое конкретное устройство должно реализовать свой сценарий работы на день
     */
    virtual void simulateDay() = 0;
};
