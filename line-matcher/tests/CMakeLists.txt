cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
	set(CMAKE_C_STANDARD 99)
	set(CMAKE_C_STANDARD_REQUIRED True)
endif()

set(SOURCES
	main.cpp
)

add_executable(unit-tests ${SOURCES})

target_compile_definitions(unit-tests PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(unit-tests PRIVATE
	${PROJECT_SOURCE_DIR}/line-matcher/include
	${PROJECT_SOURCE_DIR}/googletest/googletest/include
	${PROJECT_SOURCE_DIR}/googletest/googlemock/include
)

target_link_directories(unit-tests PRIVATE ${PROJECT_SOURCE_DIR}/googletest/build/lib)

target_link_libraries(unit-tests PRIVATE core gtest gtest_main gmock gmock_main)

set_target_properties(unit-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
