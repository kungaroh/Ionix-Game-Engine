#include "Console.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Console* Console::instance = nullptr;

Console::Console(LogLevel level) : currentLevel(level) { }

Console::~Console() { }

void Console::initialize(LogLevel level) {
    if (instance == nullptr) {
        instance = new Console(level);
    }
}

Console& Console::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("Console not initialized. Call initialize() first.");
    }
    return *instance;
}

std::string Console::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Console::getLevelString(LogLevel level) {
    switch (level) 
    {
        case LogLevel::INFO: return "INFO";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::WARNING: return "WARNING";
        default: return "UNKNOWN";
    }
}

std::string Console::getColorCode(LogLevel level)
{
    switch (level)
    {
    case LogLevel::INFO: return "\033[0;36m";    // Cyan
    case LogLevel::ERROR: return "\033[0;31m";   // Red
    case LogLevel::WARNING: return "\033[0;33m";   // Yellow
    default: return "\033[0m";                   // Reset
    }
}

void Console::log(LogLevel level, const std::string& message)
{
    auto& instance = getInstance();

    std::string colorCode = getColorCode(level);
    std::string levelStr = getLevelString(level);
    std::string timestamp = getTimestamp();
    std::string logMessage = timestamp + " [" + levelStr + "] " + message;
    
    std::cout << colorCode << logMessage << std::endl;    
}

void Console::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Console::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Console::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}
