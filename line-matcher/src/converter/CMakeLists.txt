cmake_minimum_required(VERSION 3.16)

set(SOURCES
	converter.c
)

add_library(converter STATIC ${SOURCES})
