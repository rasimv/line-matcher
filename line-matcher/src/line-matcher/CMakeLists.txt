cmake_minimum_required(VERSION 3.16)

set(SOURCES
	main.cpp
)

add_executable(line-matcher ${SOURCES})

target_link_libraries(line-matcher PRIVATE core)

if(WIN32)
	target_link_libraries(line-matcher PRIVATE converter)
endif()

target_include_directories(line-matcher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set_target_properties(line-matcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
