// device_factory.cpp
// Реализация фабрики устройств
#include "device_factory.h"
#include "lamp_device.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

std::unique_ptr<Device> DeviceFactory::createRandomDevice() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    int choice = std::rand() % 2; // 0 или 1

    switch(choice) {
        case 0:
            return std::make_unique<Lamp>();
        //case 1:
        //    return std::make_unique<HairDryer>();
        default:
            return std::make_unique<Lamp>();
    }
}

std::unique_ptr<Device> DeviceFactory::createDeviceByName(const std::string& name) {
    if (name == "Lamp") {
        return std::make_unique<Lamp>();
    } 
    /*else if (name == "HairDryer") 
    {
        return std::make_unique<HairDryer>();
    }*/
    else {
        std::cerr << "Неизвестное устройство: " << name << ". Создаю лампу по умолчанию." << std::endl;
        return std::make_unique<Lamp>();
    }
}
