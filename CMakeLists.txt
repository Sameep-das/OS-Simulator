cmake_minimum_required(VERSION 3.10)
project(OS_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
set(SOURCES
    main.cpp
    Logger.cpp
    Process.cpp
    MemoryManager.cpp
    Scheduler.cpp
    FileSystem.cpp
    Shell.cpp
)

add_executable(os_sim ${SOURCES})
