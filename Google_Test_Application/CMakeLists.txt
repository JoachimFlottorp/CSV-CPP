cmake_minimum_required(VERSION 3.22)
project(Tests)

set(Sources 
	Tests.cpp
)

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(${PROJECT_NAME} PRIVATE
	gtest_main
	CSV_Library
)

add_test(
	NAME ${PROJECT_NAME}
	COMMAND ${PROJECT_NAME}
)