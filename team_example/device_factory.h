#pragma once
#include "device.h"
#include <memory>
#include <string>

/**
 * Фабрика для создания устройств
 * 
 * Поддерживаемые устройства:
 * - "Lamp" - Лампа
 * - "CoffeeMaker" - Кофеварка  
 * - "RobotVacuum" - Робот-пылесос
 * - "SmartThermostat" - Умный термостат
 * - "SmartSpeaker" - Умная колонка
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
     * @param name Название устройства: "Lamp", "CoffeeMaker", "RobotVacuum", 
     *             "SmartThermostat", "SmartSpeaker"
     */
    static std::unique_ptr<Device> createDeviceByName(const std::string& name);
};