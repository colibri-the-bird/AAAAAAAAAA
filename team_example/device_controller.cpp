
#include "device_controller.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>  // важно для std::sort / std::stable_sort

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
    std::vector<std::pair<size_t, int>> devicesToCharge;
    for (size_t i = 0; i < devices.size(); ++i) {
        auto& device = devices[i];
        double batteryPercent = device->getCurrentBatteryPercent();
        
        // ИЗМЕНЕНИЕ: Новый порог зарядки: 50% вместо 20%
        if (batteryPercent < 50.0) {
            // НОВОЕ: Определяем приоритет устройства
            int priority = 0;
            std::string deviceType = device->getName();
            
            // НОВОЕ: Критичные устройства (высший приоритет)
            if (deviceType == "Умный термостат" || deviceType == "Холодильник") {
                priority = 3;
            }
            // НОВОЕ: Важные устройства (средний приоритет)
            else if (deviceType == "Кофеварка" || deviceType == "Робот-пылесос") {
                priority = 2;
            }
            // НОВОЕ: Обычные устройства (низкий приоритет)
            else {
                priority = 1;
            }
            
            devicesToCharge.emplace_back(i, priority);
            
            // НОВОЕ: Выводим информацию о том, какие устройства требуют зарядки и почему
            std::cout << "  📋 Устройство \"" << device->getName() 
                      << "\" требует зарядки (" << std::fixed << std::setprecision(1) 
                      << batteryPercent << "%), приоритет: " << priority << std::endl;
        }
    }
    
    // НОВОЕ: Проверяем, есть ли устройства для зарядки
    if (devicesToCharge.empty()) {
        std::cout << "  ✅ Все устройства имеют достаточный заряд (>50%)" << std::endl;
        return;
    }
    
    // НОВОЕ: Сортируем устройства по приоритету (от высокого к низкому)
    // Используем stable_sort, чтобы сохранить исходный порядок у одинаковых приоритетов.
    std::stable_sort(devicesToCharge.begin(), devicesToCharge.end(), 
        [](const std::pair<size_t,int>& a, const std::pair<size_t,int>& b) {
            return a.second > b.second; // Сортировка по убыванию приоритета
        });
    
    // НОВОЕ: Показываем порядок зарядки
    std::cout << "\n  🔄 Порядок зарядки (по приоритету):" << std::endl;
    
    // НОВОЕ: Заряжаем устройства в порядке приоритета
    for (const auto& pr : devicesToCharge) {
        size_t index = pr.first;
        int priority = pr.second;

        auto& device = devices[index];
        double batteryBefore = device->getCurrentBatteryPercent();
        
        if (device->needToBeCharged()) {
            double energyUsed = device->chargeToFull();
            totalEnergyForCharging += energyUsed;
            
            double batteryAfter = device->getCurrentBatteryPercent();
            
            // НОВОЕ: Детальная информация о процессе зарядки
            std::cout << "  ⚡ Заряжено: \"" << device->getName() 
                      << "\" (приоритет " << priority << ") - "
                      << std::fixed << std::setprecision(1) << batteryBefore 
                      << "% → " << batteryAfter << "%"
                      << ", использовано энергии: " << energyUsed << " Вт·ч" << std::endl;
        }
    }
    
    std::cout << "  ✅ Зарядка завершена!" << std::endl;
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

void DeviceController::findDeviceByName() {
    string name;
    cout << "Введите имя устройства: ";
    cin >> name;
    for (size_t i = 0; i < devices.size(); ++i) {
        if name == devices[i]->getName(){
            cout << "Статус устройства '" << name << "':/n " <<devices[i]->printStatus<< endl;
            return;
        }
        else{
            cout << "Устройство '" << name << "' не найдено" << endl;
            return;
        }
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