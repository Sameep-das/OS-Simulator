#ifndef SHELL_H
#define SHELL_H

#include "MemoryManager.h"
#include "Scheduler.h"
#include "FileSystem.h"
#include <string>

class Shell {
public:
    Shell(MemoryManager& memMgr, Scheduler& scheduler, FileSystem& fs);
    void run();

private:
    MemoryManager& memMgr;
    Scheduler& scheduler;
    FileSystem& fs;
    int nextPid;

    void processCommand(const std::string& input);
    void showHelp();
};

#endif // SHELL_H
