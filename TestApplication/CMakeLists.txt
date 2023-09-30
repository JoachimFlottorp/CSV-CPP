cmake_minimum_required(VERSION 3.8)
project(TestApplication)

add_executable(${PROJECT_NAME}
	TestApplication.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
	CSV_Library
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_SOURCE_DIR}/CSV_Library
)

file(COPY Data DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

