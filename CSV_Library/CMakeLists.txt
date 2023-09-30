add_library(CSV_Library
	Src/CSV.cpp
)

target_include_directories(CSV_Library 
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
