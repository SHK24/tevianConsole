cmake_minimum_required(VERSION 3.1.0)
project(tevianConsole)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

set(tevianConsole_SRCS
    jsonparser.cpp
    main.cpp
    tevianexchanger.cpp
)

set (PROJECT_LINK_LIBS ${CMAKE_CURRENT_BINARY_DIR}/libtevianDLL.dll)

message(${CMAKE_CURRENT_BINARY_DIR})

add_executable(tevianConsole ${tevianConsole_SRCS})

target_link_libraries(tevianConsole Qt5::Core Qt5::Network)
target_link_libraries(tevianConsole ${PROJECT_LINK_LIBS})
qt5_use_modules(tevianConsole core network)
