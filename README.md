# OS Simulator

A command-line Operating System Simulator built in C++. This project demonstrates fundamental OS concepts through an interactive shell, allowing users to simulate process scheduling, memory management, and file system operations in a contained environment.

## Features

- **Process Scheduling**: Supports First-Come-First-Serve (FCFS), Round Robin (RR), Priority Scheduling, Shortest Job First (SJF), and Shortest Remaining Time First (SRTF).
- **Memory Management**: Simulates memory allocation using Paging. The system is configured with 1024 bytes of total memory divided into 32-byte frames, handling allocation and deallocation dynamically as processes run.
- **Virtual File System**: An in-memory file system that tracks simulated files and their content, providing basic operations like creation, reading, and deletion.
- **Interactive Shell**: A custom command-line interface to execute commands and interact with the simulated OS components.
- **Logging**: Centralized logging system that records state changes, scheduling actions, and system errors to both the console and an external log file.

## Prerequisites

To build and run this project, you will need:
- A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
- CMake 3.10 or higher (optional, but recommended for building)

## Building the Project

### Using CMake

The project includes a `CMakeLists.txt` file for standard configuration and compilation. 

1. Clone the repository and navigate to the project root:
   ```bash
   git clone https://github.com/Sameep-das/OS-Simulator.git
   cd OS-Simulator
   ```
2. Generate the build files:
   ```bash
   cmake -B build
   ```
3. Compile the project:
   ```bash
   cmake --build build
   ```
4. Run the generated executable (located in the `build` directory).

### Manual Compilation

If you prefer to compile without CMake, you can use `g++` directly from the project root:

```bash
g++ -std=c++17 main.cpp Logger.cpp Process.cpp MemoryManager.cpp Scheduler.cpp FileSystem.cpp Shell.cpp -o os_sim
```

Then, run the executable:
```bash
./os_sim
```

## Usage

Once the simulator is running, it will present an interactive shell prompt `> `. You can use the `help` or `--help` command to see the full list of available operations.

### Available Commands

| Command | Example Usage | Description |
|---------|---------------|-------------|
| `run` | `run p1 1 10 64 2` | Creates a process (name, priority, burst, memory, [arrival time]) |
| `schedule` | `schedule RR 3` | Runs the scheduler (Algorithms: FCFS, RR [quantum], Priority, SJF, SRTF) |
| `create` | `create data.txt "Hello"` | Creates a file with the given content |
| `read` | `read data.txt` | Reads the content of a file |
| `delete` | `delete data.txt` | Deletes a file |
| `ls` | `ls` | Lists all files in the virtual file system |
| `ps` | `ps` | Displays the current ready queue |
| `mem` | `mem` | Shows the memory map and frame allocations |
| `help` | `help` | Shows the help message |
| `exit` | `exit` | Quits the simulator |

### Example Workflow

1. Start the simulator.
2. Create several processes with varying resource requirements:
   ```text
   > run proc1 1 10 64 0
   > run proc2 2 5 32 1
   ```
3. Check the ready queue to see the loaded processes:
   ```text
   > ps
   ```
4. Run a scheduling algorithm to execute the processes:
   ```text
   > schedule SRTF
   ```
5. View the memory map to inspect allocations:
   ```text
   > mem
   ```
