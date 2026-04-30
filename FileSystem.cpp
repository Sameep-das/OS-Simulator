#include "FileSystem.h"
#include "Logger.h"
#include <iostream>

FileSystem::FileSystem() {
    Logger::getInstance().log(Logger::Level::INFO, "File System initialized.");
}

bool FileSystem::createFile(const std::string& name, const std::string& content) {
    if (files.find(name) != files.end()) {
        Logger::getInstance().log(Logger::Level::ERROR, "File creation failed. File already exists: " + name);
        return false;
    }
    
    files[name] = content;
    Logger::getInstance().log(Logger::Level::INFO, "Created file: " + name);
    return true;
}

bool FileSystem::readFile(const std::string& name) const {
    auto it = files.find(name);
    if (it == files.end()) {
        Logger::getInstance().log(Logger::Level::ERROR, "File read failed. File not found: " + name);
        return false;
    }

    std::cout << "\n--- Content of " << name << " ---" << std::endl;
    std::cout << it->second << std::endl;
    std::cout << "------------------------\n" << std::endl;
    Logger::getInstance().log(Logger::Level::INFO, "Read file: " + name);
    return true;
}

bool FileSystem::deleteFile(const std::string& name) {
    if (files.erase(name)) {
        Logger::getInstance().log(Logger::Level::INFO, "Deleted file: " + name);
        return true;
    }
    
    Logger::getInstance().log(Logger::Level::ERROR, "File deletion failed. File not found: " + name);
    return false;
}

void FileSystem::listFiles() const {
    std::cout << "\n--- File System ---" << std::endl;
    if (files.empty()) {
        std::cout << "No files found." << std::endl;
    } else {
        for (const auto& pair : files) {
            std::cout << "- " << pair.first << " (" << pair.second.length() << " bytes)" << std::endl;
        }
    }
    std::cout << "-------------------\n" << std::endl;
}
