#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <unordered_map>

class FileSystem {
public:
    FileSystem();

    bool createFile(const std::string& name, const std::string& content);
    bool readFile(const std::string& name) const;
    bool deleteFile(const std::string& name);
    void listFiles() const;

private:
    std::unordered_map<std::string, std::string> files;
};

#endif // FILESYSTEM_H
