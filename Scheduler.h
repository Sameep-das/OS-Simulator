#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include "Process.h"
#include "MemoryManager.h"

class Scheduler {
public:
    Scheduler(MemoryManager& memMgr);

    void addProcess(Process* process);
    void runFCFS();
    void runRR(int quantum);
    void runPriority();
    void runSJF();
    void runSRTF();
    void displayQueue() const;

private:
    std::vector<Process*> readyQueue;
    MemoryManager& memMgr;

    void executeProcess(Process* process, int time);
};

#endif // SCHEDULER_H
