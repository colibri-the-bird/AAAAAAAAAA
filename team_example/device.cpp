#include "device.h"
#include <iostream>
#include <algorithm>

Device::Device(const std::string& name, 
               double maxBattery,
               double powerConsumption)
    : name{name}, 
      maxBattery{maxBattery}, 
      currentBattery{0.0},
      powerConsumptionPerHour{powerConsumption},
      isRunning{false}{}

void Device::turnOn() {
    if (currentBattery > 0) {
        isRunning = true;
        std::cout << "[" << name << "] включается" << std::endl;
    } else {
        std::cout << "[" << name << "] не может включиться - аккумулятор разряжен!" << std::endl;
    }
}

void Device::turnOff() {
    isRunning = false;
    std::cout << "[" << name << "] выключается" << std::endl;
}

double Device::chargeToFull() {
    if (!isRunning) {
        double chargeNeeded = maxBattery - currentBattery;
        currentBattery = maxBattery;
        std::cout << "[" << name << "] заряжается до полного уровня. Уровень: " << getCurrentBatteryPercent() << "%" << std::endl;
        return chargeNeeded;
    } else {
        std::cout << "[" << name << "] невозможно заряжать во время работы!" << std::endl;
        return 0.0;
    }
}

void Device::work(double hours) {
    if (isRunning && currentBattery > 0) {
        double realHours = currentBattery / powerConsumptionPerHour;
        realHours = std::min(realHours, hours);
        double consumed = powerConsumptionPerHour * realHours;

        std::cout << "[" << name << "] отработало " << realHours << 
            " часов, потреблено: " << consumed << " Вт·ч" << std::endl;

        currentBattery = std::max(0.0, currentBattery - consumed);

        if (realHours < hours) {
            isRunning = false;
            std::cout << "[" << name << "] разрядился и отключился!" << std::endl;
        }
    }
    else
        std::cout << "[" << name << "] не работает. Проверьте включено ли устройство." << std::endl;
}

double Device::getCurrentBattery() const {
    return currentBattery;
}

double Device::getPowerConsumptionPerHour() const {
    return powerConsumptionPerHour;
}

bool Device::isDeviceRunning() const {
    return isRunning;
}

const std::string& Device::getName() const {
    return name;
}

void Device::printStatus() const {
    std::cout << "=== " << getDescription() << " ===" << std::endl;
    std::cout << "  Статус: " << (isRunning ? "РАБОТАЕТ" : "ВЫКЛЮЧЕНО") << std::endl;
    std::cout << "  Заряд батареи: " << getCurrentBatteryPercent() << "% (" 
              << currentBattery << "/" << maxBattery << " Вт·ч)" << std::endl;
    std::cout << "  Потребление: " << powerConsumptionPerHour << " Вт" << std::endl;
}

double Device::getCurrentBatteryPercent() const {
    return (currentBattery / maxBattery) * 100.0;
}

bool Device::needToBeCharged() const {
    return currentBattery < maxBattery * 0.2; // Если заряд меньше 20%, то нужно заряжать
}

