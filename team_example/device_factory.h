#pragma once
#include "device.h"
#include <memory>
#include <string>

/**
 * Фабрика для создания устройств
 * 
 * TODO: Реализовать функции:
 * 1. createRandomDevice() - создать случайное устройство
 * 2. createDeviceByName(const std::string& name) - создать устройство по названию
 * 
 * Подсказка: Используйте std::make_unique для создания unique_ptr устройств
 * Для random можно использовать С-функции rand()/srand или <random>
 */
class DeviceFactory {
public:
    /**
     * Создать случайное устройство
     * Возвращает unique_ptr на базовый класс Device
     */
    static std::unique_ptr<Device> createRandomDevice();

    /**
     * Создать устройство по названию
     * @param name Название устройства: "Lamp", "CoffeeMaker", "Refrigerator", "HairDryer", "RobotVacuum"
     */
    static std::unique_ptr<Device> createDeviceByName(const std::string& name);
};
