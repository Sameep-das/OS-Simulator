#include <iostream>
#include "MemoryManager.h"
#include "Scheduler.h"
#include "FileSystem.h"
#include "Shell.h"
#include "Logger.h"

int main() {
    Logger::getInstance().log(Logger::Level::INFO, "Starting OS Simulator...");

    // Initialize OS Components
    // 1024 bytes total memory, 32 bytes per page
    MemoryManager memMgr(1024, 32);
    
    Scheduler scheduler(memMgr);
    
    FileSystem fs;

    // Start Shell
    Shell shell(memMgr, scheduler, fs);
    shell.run();

    Logger::getInstance().log(Logger::Level::INFO, "OS Simulator Stopped.");
    return 0;
}
