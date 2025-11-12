// device_factory.cpp
// Реализация фабрики устройств
#include "device_factory.h"
#include "lamp_device.h"
#include "coffee_maker.h"
#include "robot_vacuum.h"
#include "smart_thermostat.h"
#include "smart_speaker.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

std::unique_ptr<Device> DeviceFactory::createRandomDevice() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    int choice = std::rand() % 5; // 0-4 для 5 устройств

    switch(choice) {
        case 0:
            return std::make_unique<Lamp>();
        case 1:
            return std::make_unique<CoffeeMaker>();
        case 2:
            return std::make_unique<RobotVacuum>();
        case 3:
            return std::make_unique<SmartThermostat>();
        case 4:
            return std::make_unique<SmartSpeaker>();
        default:
            return std::make_unique<Lamp>();
    }
}

std::unique_ptr<Device> DeviceFactory::createDeviceByName(const std::string& name) {
    if (name == "Lamp") {
        return std::make_unique<Lamp>();
    } 
    else if (name == "CoffeeMaker") {
        return std::make_unique<CoffeeMaker>();
    }
    else if (name == "RobotVacuum") {
        return std::make_unique<RobotVacuum>();
    }
    else if (name == "SmartThermostat") {
        return std::make_unique<SmartThermostat>();
    }
    else if (name == "SmartSpeaker") {
        return std::make_unique<SmartSpeaker>();
    }
    else {
        std::cerr << "Неизвестное устройство: " << name << ". Создаю лампу по умолчанию." << std::endl;
        return std::make_unique<Lamp>();
    }
}
