cmake_minimum_required(VERSION 2.8)

PROJECT(de.mniess.miTaPaSS)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ )

SET(LIBRARY_OUTPUT_PATH ./lib
CACHE PATH "CMakeLists.txt files optimized for this directory! Please do not change.")

SET(EXECUTABLE_OUTPUT_PATH ./bin
CACHE PATH "CMakeLists.txt files optimized for this directory! Please do not change.")

#find dependencies
#find_package(Threads)#gets pthread (also on other platforms)

find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

#include
include_directories(${RAPIDJSON_INCLUDE_DIRS})

# Hier können zusätzliche Quelldateien eingtragen werden, die dann automatisch dem Projekt hinzugefügt werden
SET(MITAPASS_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
	${RESOURCE_FILE}
)

set(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(miTaPaSS ${MITAPASS_SRC})

#target_link_libraries(miTaPaSS ${CMAKE_THREAD_LIBS_INIT})#(links pthread)
