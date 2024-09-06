# Project Setup
cmake_minimum_required(VERSION 3.23)
project(configurator VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json)

# Configurator Library
add_library(${PROJECT_NAME} INTERFACE)
install(FILES include/${PROJECT_NAME}.h DESTINATION include)

# Driver
add_executable(driver src/driver.cpp)
target_include_directories(driver PRIVATE include)
install(TARGETS driver DESTINATION bin)

# Commandline Output
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")


