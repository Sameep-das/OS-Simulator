#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger {
public:
    enum class Level {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    static Logger& getInstance();

    // Delete copy constructor and assignment operator for Singleton
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

    void log(Level level, const std::string& message);

private:
    Logger();
    ~Logger();
    std::ofstream logFile;
    std::string levelToString(Level level);
};

#endif // LOGGER_H
