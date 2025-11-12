#pragma once
#include "device.h"

/**
 * Лампа - простое устройство с низким потреблением
 */
class Lamp : public Device {
public:
    Lamp();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};

/**
 * Фен для волос - высокое потребление, работает периодически
 */
class HairDryer : public Device {
public:
    HairDryer();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};

/**
 * Умная кофеварка - высокое потребление при варке кофе
 */
class CoffeeMaker : public Device {
public:
    CoffeeMaker();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};

/**
 * РоБоТ ПыЛеСоС
 */
class RobotVacuum : public Device {
public:
    RobotVacuum();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};

/**
 * Умный термостат - низкое потребление, постоянная работа
 */
class SmartThermostat : public Device {
public:
    SmartThermostat();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};


/**
 * SmartSpeaker
 */
class SmartSpeaker : public Device {
public:
    SmartSpeaker();
    std::string getDescription() const override;
    void printStatus() const override;
    void simulateDay() override;
};

