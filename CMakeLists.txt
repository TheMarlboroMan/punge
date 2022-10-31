cmake_minimum_required(VERSION 3.5.1)
project(punge)

option(BUILD_DEBUG "Build a debug release" OFF)

#version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

if(${CMAKE_VERSION} VERSION_LESS "3.22.0")

	add_definitions(-DMAJOR_VERSION=${MAJOR_VERSION})
	add_definitions(-DMINOR_VERSION=${MINOR_VERSION})
	add_definitions(-DPATCH_VERSION=${PATCH_VERSION})
else()

	add_compile_definitions(MAJOR_VERSION=${MAJOR_VERSION})
	add_compile_definitions(MINOR_VERSION=${MINOR_VERSION})
	add_compile_definitions(PATCH_VERSION=${PATCH_VERSION})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(${BUILD_DEBUG})
        set(CMAKE_BUILD_TYPE Debug)

else()
        set(CMAKE_BUILD_TYPE Release)
endif()


add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_library(lm SHARED IMPORTED)
add_library(tools SHARED IMPORTED)
add_library(terminal-tools SHARED IMPORTED)
add_library(utf8-tools SHARED IMPORTED)

set_target_properties(lm PROPERTIES IMPORTED_LOCATION /usr/local/lib/liblm.so)
set_target_properties(tools PROPERTIES IMPORTED_LOCATION /usr/local/lib/libtools.so)
set_target_properties(terminal-tools PROPERTIES IMPORTED_LOCATION /usr/local/lib/libterminal-tools.so)
set_target_properties(utf8-tools PROPERTIES IMPORTED_LOCATION /usr/local/lib/libutf8tools.so)

add_library(applib STATIC ${SOURCE})
set_target_properties(applib PROPERTIES OUTPUT_NAME applib)

add_executable(punge src/main.cpp)
target_link_libraries(punge applib tools terminal-tools lm utf8-tools stdc++fs)

#copy files...
add_custom_target(setup_files ALL)
add_custom_command(TARGET setup_files POST_BUILD COMMAND cp -r ../data ./)
