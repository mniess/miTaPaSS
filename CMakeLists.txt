cmake_minimum_required(VERSION 2.8)

PROJECT(miTaPaSS)

set (MITAPASS_VERSION_MAJOR 0)
set (MITAPASS_VERSION_MINOR 1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ )

SET(LIBRARY_OUTPUT_PATH ../lib
CACHE PATH "CMakeLists.txt files optimized for this directory! Please do not change.")

SET(EXECUTABLE_OUTPUT_PATH ../bin
CACHE PATH "CMakeLists.txt files optimized for this directory! Please do not change.")

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_SOURCE_DIR}/bin/config.h"
	)

include_directories(.)

SET(MITAPASS_SRC
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/config.cpp
	${PROJECT_SOURCE_DIR}/bin/config.h
	${RESOURCE_FILE}
)

set(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(miTaPaSS ${MITAPASS_SRC})
