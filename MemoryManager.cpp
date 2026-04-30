#include "MemoryManager.h"
#include "Logger.h"
#include <iostream>

MemoryManager::MemoryManager(int totalMemory, int pageSize) 
    : totalMemory(totalMemory), pageSize(pageSize) {
    totalFrames = totalMemory / pageSize;
    freeFrames = totalFrames;
    frames.resize(totalFrames, false);
    Logger::getInstance().log(Logger::Level::INFO, "Memory Manager initialized: " + std::to_string(totalMemory) + " bytes, " + std::to_string(totalFrames) + " frames.");
}

bool MemoryManager::allocateMemory(Process* process) {
    int pagesNeeded = (process->memoryRequired + pageSize - 1) / pageSize;
    
    if (pagesNeeded > freeFrames) {
        Logger::getInstance().log(Logger::Level::ERROR, "Memory allocation failed for Process " + std::to_string(process->id) + " - Not enough free frames.");
        return false;
    }

    std::vector<int> allocatedFrames;
    for (int i = 0; i < totalFrames && pagesNeeded > 0; ++i) {
        if (!frames[i]) {
            frames[i] = true;
            allocatedFrames.push_back(i);
            pagesNeeded--;
            freeFrames--;
        }
    }

    pageTables[process->id] = allocatedFrames;
    Logger::getInstance().log(Logger::Level::INFO, "Allocated " + std::to_string(allocatedFrames.size()) + " frames for Process " + std::to_string(process->id));
    return true;
}

void MemoryManager::deallocateMemory(Process* process) {
    if (pageTables.find(process->id) == pageTables.end()) {
        return; // Nothing to deallocate
    }

    std::vector<int>& allocatedFrames = pageTables[process->id];
    for (int frame : allocatedFrames) {
        frames[frame] = false;
        freeFrames++;
    }

    Logger::getInstance().log(Logger::Level::INFO, "Deallocated " + std::to_string(allocatedFrames.size()) + " frames from Process " + std::to_string(process->id));
    pageTables.erase(process->id);
}

void MemoryManager::displayMemoryMap() const {
    std::cout << "\n--- Memory Map ---" << std::endl;
    std::cout << "Free Frames: " << freeFrames << " / " << totalFrames << std::endl;
    for (const auto& pair : pageTables) {
        std::cout << "PID " << pair.first << " frames: ";
        for (int frame : pair.second) {
            std::cout << frame << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------\n" << std::endl;
}
