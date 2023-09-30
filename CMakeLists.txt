cmake_minimum_required(VERSION 3.22)
project(CSV)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(./external)
add_subdirectory(./CSV_Library)

add_subdirectory(./TestApplication)
add_subdirectory(./Google_Test_Application)
