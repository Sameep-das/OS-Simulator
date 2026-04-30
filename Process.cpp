#include "Process.h"

Process::Process(int id, std::string name, int priority, int arrivalTime, int burstTime, int memoryRequired)
    : id(id), name(name), priority(priority), arrivalTime(arrivalTime), 
      burstTime(burstTime), remainingTime(burstTime), memoryRequired(memoryRequired), 
      state(ProcessState::NEW) {}

std::string Process::stateToString() const {
    switch (state) {
        case ProcessState::NEW: return "NEW";
        case ProcessState::READY: return "READY";
        case ProcessState::RUNNING: return "RUNNING";
        case ProcessState::WAITING: return "WAITING";
        case ProcessState::TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

void Process::display() const {
    std::cout << "Process[" << id << "] " << name 
              << " | Pri: " << priority 
              << " | Burst: " << burstTime 
              << " | Rem: " << remainingTime 
              << " | Mem: " << memoryRequired 
              << " | State: " << stateToString() << std::endl;
}
