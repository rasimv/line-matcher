cmake_minimum_required(VERSION 3.16)

set(SOURCES
	LineMatcher.cpp
)

add_library(core STATIC ${SOURCES})
