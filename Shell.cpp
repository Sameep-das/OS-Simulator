#include "Shell.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <vector>

Shell::Shell(MemoryManager& memMgr, Scheduler& scheduler, FileSystem& fs) 
    : memMgr(memMgr), scheduler(scheduler), fs(fs), nextPid(1) {}

void Shell::run() {
    std::string input;
    std::cout << "OS Simulator Shell Started. Type 'help' for commands.\n";
    
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;
        
        if (input == "exit" || input == "quit") {
            Logger::getInstance().log(Logger::Level::INFO, "Shutting down OS Simulator...");
            break;
        }

        if (!input.empty()) {
            processCommand(input);
        }
    }
}

void Shell::processCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;

    if (cmd == "help" || cmd == "--help") {
        showHelp();
    } 
    else if (cmd == "run") {
        // Usage: run <name> <priority> <burst> <memory> [arrivalTime]
        std::string name;
        int priority, burst, mem;
        int arrival = 0;
        if (iss >> name >> priority >> burst >> mem) {
            iss >> arrival; // Optional
            Process* p = new Process(nextPid++, name, priority, arrival, burst, mem);
            if (memMgr.allocateMemory(p)) {
                scheduler.addProcess(p);
            } else {
                std::cout << "Failed to allocate memory for process " << name << ".\n";
                delete p;
            }
        } else {
            std::cout << "Usage: run <name> <priority> <burstTime> <memoryRequired> [arrivalTime]\n";
        }
    }
    else if (cmd == "schedule") {
        std::string algo;
        if (iss >> algo) {
            if (algo == "FCFS") {
                scheduler.runFCFS();
            } else if (algo == "RR") {
                int quantum = 2; // Default quantum
                iss >> quantum;
                scheduler.runRR(quantum);
            } else if (algo == "Priority") {
                scheduler.runPriority();
            } else if (algo == "SJF") {
                scheduler.runSJF();
            } else if (algo == "SRTF") {
                scheduler.runSRTF();
            } else {
                std::cout << "Unknown algorithm. Use FCFS, RR [quantum], Priority, SJF, or SRTF.\n";
            }
        } else {
            std::cout << "Usage: schedule <FCFS|RR|Priority|SJF|SRTF> [quantum]\n";
        }
    }
    else if (cmd == "create") {
        std::string name, content, word;
        if (iss >> name) {
            while (iss >> word) {
                content += word + " ";
            }
            if (!content.empty()) content.pop_back(); // Remove trailing space
            fs.createFile(name, content);
        } else {
            std::cout << "Usage: create <filename> <content>\n";
        }
    }
    else if (cmd == "read") {
        std::string name;
        if (iss >> name) {
            fs.readFile(name);
        } else {
            std::cout << "Usage: read <filename>\n";
        }
    }
    else if (cmd == "delete") {
        std::string name;
        if (iss >> name) {
            fs.deleteFile(name);
        } else {
            std::cout << "Usage: delete <filename>\n";
        }
    }
    else if (cmd == "ls") {
        fs.listFiles();
    }
    else if (cmd == "ps") {
        scheduler.displayQueue();
    }
    else if (cmd == "mem") {
        memMgr.displayMemoryMap();
    }
    else {
        std::cout << "Unknown command: " << cmd << "\n";
    }
}

void Shell::showHelp() {
    std::cout << "\n============================= Available Commands =============================\n";
    std::cout << "Command      | Example Usage                    | Description\n";
    std::cout << "-------------|----------------------------------|-----------------------------\n";
    std::cout << "run          | run p1 1 10 64 2                 | Creates a process (name, pri, burst, mem, [arrival])\n";
    std::cout << "schedule     | schedule RR 3                    | Runs scheduler (FCFS, RR [quantum], Priority, SJF, SRTF)\n";
    std::cout << "create       | create data.txt \"Hello World\"    | Creates a file with content\n";
    std::cout << "read         | read data.txt                    | Reads content of a file\n";
    std::cout << "delete       | delete data.txt                  | Deletes a file\n";
    std::cout << "ls           | ls                               | Lists all files\n";
    std::cout << "ps           | ps                               | Shows the ready queue\n";
    std::cout << "mem          | mem                              | Shows memory map and allocations\n";
    std::cout << "help/--help  | --help                           | Shows this help message\n";
    std::cout << "exit/quit    | exit                             | Quits the simulator\n";
    std::cout << "==============================================================================\n";
}
