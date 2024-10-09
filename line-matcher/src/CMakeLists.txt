cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
	set(CMAKE_C_STANDARD 99)
	set(CMAKE_C_STANDARD_REQUIRED True)
endif()

if(WIN32)
	add_subdirectory(converter)
endif()

add_subdirectory(core)
add_subdirectory(line-matcher)
