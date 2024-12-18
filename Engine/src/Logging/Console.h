#pragma once
#include <string>
#include "Architecture/Macros.h"

enum class LogLevel {
    INFO,
    ERROR,
    WARNING
};

class ENGINE_API Console {
private:
    static Console* instance;
    Console(LogLevel level);
    ~Console();

    LogLevel currentLevel;

    static std::string getTimestamp();
    static std::string getLevelString(LogLevel level);
    static std::string getColorCode(LogLevel level);

public:

    Console(const Console&) = delete;
    Console& operator=(const Console&) = delete;

    static void initialize(LogLevel level = LogLevel::INFO);

    static Console& getInstance();

    static void log(LogLevel level, const std::string& message);
    static void info(const std::string& message);
    static void error(const std::string& message);
    static void warning(const std::string& message);
};