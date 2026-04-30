#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
public:
    int id;
    std::string name;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int memoryRequired;
    ProcessState state;

    Process(int id, std::string name, int priority, int arrivalTime, int burstTime, int memoryRequired);

    void display() const;
    std::string stateToString() const;
};

#endif // PROCESS_H
