#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include <unordered_map>
#include "Process.h"

class MemoryManager {
public:
    MemoryManager(int totalMemory, int pageSize);

    bool allocateMemory(Process* process);
    void deallocateMemory(Process* process);
    void displayMemoryMap() const;

private:
    int totalMemory;
    int pageSize;
    int totalFrames;
    int freeFrames;

    std::vector<bool> frames; // true if occupied, false if free
    std::unordered_map<int, std::vector<int>> pageTables; // pid -> list of frames
};

#endif // MEMORYMANAGER_H
