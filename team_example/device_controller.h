#pragma once
#include "device.h"
#include <vector>
#include <memory>

/**
 * Контроллер для управления всеми устройствами
 */
class DeviceController {
private:
    std::vector<std::unique_ptr<Device>> devices; // список устройств
    double totalEnergyForCharging{0.0}; // Общее потребление энергии на зарядку (Вт·ч)

public:
    DeviceController();

    /**
     * Добавить устройство в контроллер
     * Контроллер принимает право собственности на устройство (unique_ptr)
     */
    void addDevice(std::unique_ptr<Device> device);

    /**
     * Включить устройство по индексу
     */
    void turnOnDevice(size_t index);

    /**
     * Выключить устройство по индексу
     */
    void turnOffDevice(size_t index);

    /**
     * Включить все устройства
     */
    void turnOnAllDevices();

    /**
     * Выключить все устройства
     */
    void turnOffAllDevices();

    /**
     * Зарядить все устройства, которые нуждаются в зарядке
     */
    void chargeDevicesThatNeedIt();

    /**
     * Симулировать работу системы в течение одного дня
     */
    void simulateDayOfWork(int dayNumber);

    /**
     * Вывести статус всех устройств
     */
    void printAllDevicesStatus() const;

    /**
     * Получить общее потребление энергии
     */
    double getTotalEnergyConsumed() const;

    /**
     * Вывести отчет об энергопотреблении
     */
    void printEnergyReport() const;

    /**
     * Получить количество устройств
     */
    size_t getDeviceCount() const;

    /**
     * Вывести описание всех устройств
     */
    void printDevicesDescription() const;
};
