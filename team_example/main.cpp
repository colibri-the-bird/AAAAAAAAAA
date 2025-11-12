#include <iostream>
#include <memory>
#include <windows.h>
#include "device_factory.h"
#include "device_controller.h"

int main() {
    // Установка UTF-8 кодировки консоли Windows для вывода кириллицы
    SetConsoleCP(65001);           
    SetConsoleOutputCP(65001);     
    
    std::cout << "\n";
    
    std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║   СИМУЛЯЦИЯ СИСТЕМЫ УМНОГО ДОМА (SMART HOME SYSTEM)        ║" << std::endl;
    std::cout << "║   Демонстрация работы паттерна Factory и полиморфизма      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;

    // Создаем контроллер
    DeviceController controller;

    // ========== СОЗДАНИЕ УСТРОЙСТВ ЧЕРЕЗ ФАБРИКУ ==========
   std::cout << "\n>>> Создание устройств через DeviceFactory::createDeviceByName()..." << std::endl;

// Создаем разнообразные устройства через фабрику
   controller.addDevice(DeviceFactory::createDeviceByName("Lamp"));
   controller.addDevice(DeviceFactory::createDeviceByName("CoffeeMaker"));
   controller.addDevice(DeviceFactory::createDeviceByName("RobotVacuum"));
   controller.addDevice(DeviceFactory::createDeviceByName("SmartThermostat"));
   controller.addDevice(DeviceFactory::createDeviceByName("SmartSpeaker"));

   std::cout << "\n✓ Создано " << controller.getDeviceCount() << " устройств" << std::endl;

    // ========== ВЫВОД ОПИСАНИЯ УСТРОЙСТВ ==========
    controller.printDevicesDescription();

    // ========== НАЧАЛЬНАЯ ЗАРЯДКА ВСЕХ УСТРОЙСТВ ==========
    std::cout << "\n>>> Начальная зарядка всех устройств с 0% до 100%..." << std::endl;
    controller.chargeDevicesThatNeedIt();

    std::cout << "\n✓ Все устройства полностью заряжены!" << std::endl;
    std::cout << "\n>>> Состояние устройств перед симуляцией:" << std::endl;
    controller.printAllDevicesStatus();

    // ========== СИМУЛЯЦИЯ ТРЕХ ДНЕЙ РАБОТЫ ==========
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           СИМУЛЯЦИЯ РАБОТЫ СИСТЕМЫ (3 ДНЯ)                 ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;

    // Симуляция трех дней
    for (int day = 1; day <= 3; ++day) {
        controller.simulateDayOfWork(day);
        
        // Показываем статус в конце дня
        std::cout << "\n--- Статус устройств в конце дня " << day << " ---" << std::endl;
        controller.printAllDevicesStatus();
        controller.chargeDevicesThatNeedIt();
    }

    // ========== ИТОГОВЫЙ ОТЧЕТ ==========
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                      ИТОГОВЫЙ ОТЧЕТ                         ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;

    controller.printEnergyReport();

    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                 СИМУЛЯЦИЯ ЗАВЕРШЕНА                         ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝\n" << std::endl;
    return 0;

    controller.findDeviceByName();
}

/* 
ОБЪЯСНЕНИЕ ДЛЯ СТУДЕНТОВ:

1. ПАТТЕРН FACTORY (Фабрика):
   - DeviceFactory::createDeviceByName() и createRandomDevice() создают объекты разных типов
   - Вместо new используем std::make_unique для автоматического управления памятью
   - Клиент не знает точного типа создаваемого объекта

2. ПОЛИМОРФИЗМ И ВИРТУАЛЬНЫЕ МЕТОДЫ:
   - Все конкретные устройства наследуются от Device
   - DeviceController работает с указателем на Device, но на самом деле работает с нужным типом
   - Вызов virtual функций (включая pure virtual simulateDay) работает через виртуальную таблицу методов
   - Каждый класс устройства реализует свой собственный simulateDay()

3. УМНЫЕ УКАЗАТЕЛИ (std::unique_ptr):
   - unique_ptr автоматически удаляет объект, когда выходит из области видимости
   - std::move передает право собственности на объект
   - Нет утечек памяти, RAII принцип

4. КОНТЕЙНЕРЫ:
   - std::vector<std::unique_ptr<Device>> хранит разнотипные объекты через указатели на базовый класс
   - Можно итерировать по всем устройствам единообразно
   - Автоматическое управление памятью для всех объектов

5. ЛОГИКА СИМУЛЯЦИИ:
   - simulateDayOfWork() симулирует работу всех устройств за один день
   - Каждое устройство знает, сколько энергии оно потребляет в день
   - Если энергии недостаточно, устройство автоматически заряжается до полной емкости
   - Общее энергопотребление включает работу устройств и энергию на их подзарядку

6. РАСШИРЯЕМОСТЬ:
   - Легко добавить новый тип устройства: создать класс, наследующий Device
   - Реализовать виртуальный метод simulateDay()
   - Добавить конструктор в DeviceFactory
   - Контроллер и main не меняются!
*/

