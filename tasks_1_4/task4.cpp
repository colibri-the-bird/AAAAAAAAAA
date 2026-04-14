#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Logger {
public:
    virtual void log(const std::string& msg) = 0;
    virtual ~Logger() = default;
};

class ConsoleLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[Консоль] " << msg << '\n';
    }
};

class FileLogger : public Logger {
public:
    explicit FileLogger(std::string fileName) : fileName(std::move(fileName)) {}

    void log(const std::string& msg) override {
        std::ofstream out(fileName, std::ios::app);
        if (!out) {
            throw std::runtime_error("Не удалось открыть файл лога");
        }
        out << "[Файл] " << msg << '\n';
    }

private:
    std::string fileName;
};

class NullLogger : public Logger {
public:
    void log(const std::string&) override {}
};

class LoggerFactory {
public:
    virtual std::unique_ptr<Logger> createLogger() = 0;
    virtual ~LoggerFactory() = default;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    explicit FileLoggerFactory(std::string fileName) : fileName(std::move(fileName)) {}

    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<FileLogger>(fileName);
    }

private:
    std::string fileName;
};

class NullLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<NullLogger>();
    }
};

class Application {
public:
    explicit Application(std::unique_ptr<LoggerFactory> factory) : factory(std::move(factory)) {}

    void run() {
        auto logger = factory->createLogger();
        logger->log("Запуск приложения");
        logger->log("Выполнение работы");
        logger->log("Завершение приложения");
    }

private:
    std::unique_ptr<LoggerFactory> factory;
};

int main() {
    Application app1(std::make_unique<ConsoleLoggerFactory>());
    app1.run();

    Application app2(std::make_unique<FileLoggerFactory>("factory_method_log.txt"));
    app2.run();

    Application app3(std::make_unique<NullLoggerFactory>());
    app3.run();

    return 0;
}
