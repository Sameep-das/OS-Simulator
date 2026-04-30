#include "Scheduler.h"
#include "Logger.h"
#include <algorithm>
#include <iostream>

Scheduler::Scheduler(MemoryManager& memMgr) : memMgr(memMgr) {}

void Scheduler::addProcess(Process* process) {
    if (process) {
        process->state = ProcessState::READY;
        readyQueue.push_back(process);
        Logger::getInstance().log(Logger::Level::INFO, "Process " + std::to_string(process->id) + " added to Ready Queue.");
    }
}

void Scheduler::executeProcess(Process* process, int time) {
    process->state = ProcessState::RUNNING;
    Logger::getInstance().log(Logger::Level::INFO, "Process " + std::to_string(process->id) + " is RUNNING for " + std::to_string(time) + " units.");
    
    process->remainingTime -= time;
    if (process->remainingTime <= 0) {
        process->remainingTime = 0;
        process->state = ProcessState::TERMINATED;
        Logger::getInstance().log(Logger::Level::INFO, "Process " + std::to_string(process->id) + " TERMINATED.");
        memMgr.deallocateMemory(process);
    } else {
        process->state = ProcessState::READY;
    }
}

void Scheduler::runFCFS() {
    Logger::getInstance().log(Logger::Level::INFO, "Starting FCFS Scheduling.");
    
    // Sort by arrival time just in case, assuming added in order for now
    for (Process* p : readyQueue) {
        if (p->state == ProcessState::READY) {
            executeProcess(p, p->remainingTime);
        }
    }
    
    // Clear queue after execution for simplicity
    readyQueue.erase(
        std::remove_if(readyQueue.begin(), readyQueue.end(),
            [](Process* p) { return p->state == ProcessState::TERMINATED; }),
        readyQueue.end()
    );
}

void Scheduler::runRR(int quantum) {
    Logger::getInstance().log(Logger::Level::INFO, "Starting Round Robin Scheduling with quantum " + std::to_string(quantum));
    
    std::queue<Process*> rq;
    for (Process* p : readyQueue) {
        if (p->state == ProcessState::READY) {
            rq.push(p);
        }
    }

    while (!rq.empty()) {
        Process* p = rq.front();
        rq.pop();

        int timeToRun = std::min(quantum, p->remainingTime);
        executeProcess(p, timeToRun);

        if (p->state != ProcessState::TERMINATED) {
            rq.push(p);
        }
    }

    readyQueue.erase(
        std::remove_if(readyQueue.begin(), readyQueue.end(),
            [](Process* p) { return p->state == ProcessState::TERMINATED; }),
        readyQueue.end()
    );
}

void Scheduler::runPriority() {
    Logger::getInstance().log(Logger::Level::INFO, "Starting Priority Scheduling.");
    
    // Sort by priority (higher priority number = executes first, or lower number? Let's say lower number is higher priority)
    std::sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
        return a->priority < b->priority;
    });

    for (Process* p : readyQueue) {
        if (p->state == ProcessState::READY) {
            executeProcess(p, p->remainingTime);
        }
    }

    readyQueue.erase(
        std::remove_if(readyQueue.begin(), readyQueue.end(),
            [](Process* p) { return p->state == ProcessState::TERMINATED; }),
        readyQueue.end()
    );
}

void Scheduler::runSJF() {
    Logger::getInstance().log(Logger::Level::INFO, "Starting SJF Scheduling.");
    
    // Sort by burst time
    std::sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
        return a->burstTime < b->burstTime;
    });

    for (Process* p : readyQueue) {
        if (p->state == ProcessState::READY) {
            executeProcess(p, p->remainingTime);
        }
    }

    readyQueue.erase(
        std::remove_if(readyQueue.begin(), readyQueue.end(),
            [](Process* p) { return p->state == ProcessState::TERMINATED; }),
        readyQueue.end()
    );
}

void Scheduler::runSRTF() {
    Logger::getInstance().log(Logger::Level::INFO, "Starting SRTF Scheduling.");
    
    int currentTime = 0;
    int completed = 0;
    int n = readyQueue.size();
    
    while (completed != n) {
        Process* shortest = nullptr;
        int minRemaining = 1e9;
        
        for (Process* p : readyQueue) {
            if (p->state != ProcessState::TERMINATED && p->arrivalTime <= currentTime) {
                if (p->remainingTime < minRemaining) {
                    minRemaining = p->remainingTime;
                    shortest = p;
                }
            }
        }
        
        if (shortest == nullptr) {
            currentTime++; // CPU idle
        } else {
            executeProcess(shortest, 1);
            currentTime++;
            if (shortest->state == ProcessState::TERMINATED) {
                completed++;
            }
        }
    }

    readyQueue.erase(
        std::remove_if(readyQueue.begin(), readyQueue.end(),
            [](Process* p) { return p->state == ProcessState::TERMINATED; }),
        readyQueue.end()
    );
}

void Scheduler::displayQueue() const {
    std::cout << "\n--- Ready Queue ---" << std::endl;
    if (readyQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        for (const Process* p : readyQueue) {
            p->display();
        }
    }
    std::cout << "-------------------\n" << std::endl;
}
