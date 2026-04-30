#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>

Logger::Logger() {
    logFile.open("os_sim.log", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case Level::INFO: return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR: return "ERROR";
        case Level::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

void Logger::log(Level level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::string levelStr = levelToString(level);
    
    // Write to console
    if (level == Level::ERROR) {
        std::cerr << "[" << levelStr << "] " << message << std::endl;
    } else {
        std::cout << "[" << levelStr << "] " << message << std::endl;
    }

    // Write to file
    if (logFile.is_open()) {
        logFile << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") 
                << " [" << levelStr << "] " << message << "\n";
        logFile.flush();
    }
}
