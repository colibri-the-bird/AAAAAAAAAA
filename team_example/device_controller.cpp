// device_controller.cpp
// Реализация контроллера устройств
#include "device_controller.h"
#include <iostream>
#include <iomanip>
#include <cmath>

DeviceController::DeviceController() 
    : totalEnergyForCharging(0.0) {}

void DeviceController::addDevice(std::unique_ptr<Device> device) {
    if (device) {
        devices.push_back(std::move(device));
    }
}

void DeviceController::turnOnDevice(size_t index) {
    if (index < devices.size()) {
        devices[index]->turnOn();
    }
}

void DeviceController::turnOffDevice(size_t index) {
    if (index < devices.size()) {
        devices[index]->turnOff();
    }
}

void DeviceController::turnOnAllDevices() {
    std::cout << "\n>>> Включаю все устройства..." << std::endl;
    for (auto& device : devices) {
        device->turnOn();
    }
}

void DeviceController::turnOffAllDevices() {
    std::cout << "\n>>> Выключаю все устройства..." << std::endl;
    for (auto& device : devices) {
        device->turnOff();
    }
}

void DeviceController::chargeDevicesThatNeedIt() {
    std::cout << "\n>>> Заряжаю устройства, которые нуждаются в зарядке..." << std::endl;
    for (auto& device : devices) {
        if (device->needToBeCharged()) {
            totalEnergyForCharging += device->chargeToFull();
        }
    }
}

void DeviceController::simulateDayOfWork(int dayNumber) {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                       ДЕНЬ " << dayNumber << "                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    
    for (auto& device : devices) {
        // Симулируем день — устройство возвращает сколько энергии потребовалось для зарядки
        device->simulateDay();
    }
}

void DeviceController::printAllDevicesStatus() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║      СТАТУС ВСЕХ УСТРОЙСТВ               ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << "\n[Устройство " << i << "]" << std::endl;
        devices[i]->printStatus();
    }
}

void DeviceController::printEnergyReport() const {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║      ИТОГОВЫЙ ОТЧЕТ ОБ ЭНЕРГОПОТРЕБЛЕНИИ                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    
    // Общее потребление энергии
    std::cout << "\n📊 ПОТРЕБЛЕНИЕ ЭНЕРГИИ на зарядку устройств:" << std::endl;
    std::cout << totalEnergyForCharging << " Вт·ч" << std::endl;
    
    // Перевод в кВт·ч
    double kwh = totalEnergyForCharging / 1000.0;
    std::cout << "  В кВт·ч:                              " << kwh << " кВт·ч" << std::endl;
    
    // Расчет стоимости в рублях
    double costPerKwh = 30.0; // рубли за кВт·ч
    double totalCostRubles = kwh * costPerKwh;
    std::cout << "\n💰 ФИНАНСОВЫЕ РАСХОДЫ:" << std::endl;
    std::cout << "─────────────────────────────────────────" << std::endl;
    std::cout << "  Тариф:                                " << costPerKwh << " руб/кВт·ч" << std::endl;
    std::cout << "  Общая стоимость электроэнергии:       " << totalCostRubles << " рублей" << std::endl;
    
    // Перевод в килокаллории (ккал)
    // 1 ккал/ч ≈ 1.163 Вт
    // Обратно: Энергия в ккал = Энергия в Вт·ч / 1.163
    double kcalPerWattHour = 1.0 / 1.163;
    double totalKcal = totalEnergyForCharging * kcalPerWattHour;
    
    std::cout << "\n🔥 ЭНЕРГЕТИЧЕСКАЯ ЦЕННОСТЬ:" << std::endl;
    std::cout << "─────────────────────────────────────────" << std::endl;
    std::cout << "  Коэффициент пересчета:                1 ккал/ч ≈ 1.163 Вт" << std::endl;
    std::cout << "  Общая энергия в килокалориях:        " << totalKcal << " ккал" << std::endl;
    
    // Перевод в "сосиски в тесте"
    // 1 сосиска в тесте = 280 ккал
    double kcalPerSausage = 280.0;
    int sausageCount = static_cast<int>(totalKcal / kcalPerSausage);
    double remainingKcal = std::fmod(totalKcal, kcalPerSausage);
    
    std::cout << "\n🌭 ЭКВИВАЛЕНТ В СОСИСКАХ В ТЕСТЕ:" << std::endl;
    std::cout << "─────────────────────────────────────────" << std::endl;
    std::cout << "  1 сосиска в тесте содержит:           " << kcalPerSausage << " ккал" << std::endl;
    std::cout << "  Количество полных сосисок:           " << sausageCount << " сосисок" << std::endl;
    std::cout << "  Плюс еще:                             " << remainingKcal << " ккал" << std::endl;
    std::cout << "\n  🎉 Итого: " << sausageCount << " сосисок в тесте" << std::endl;
}

size_t DeviceController::getDeviceCount() const {
    return devices.size();
}

void DeviceController::printDevicesDescription() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║      ОПИСАНИЕ УСТРОЙСТВ                  ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << "[" << i << "] " << devices[i]->getDescription() << std::endl;
    }
}
