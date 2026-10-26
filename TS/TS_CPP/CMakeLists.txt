cmake_minimum_required(VERSION 3.25)
project(TS_CPP)

set(CMAKE_CXX_STANDARD 23)

MACRO(SOURCE_FILES sources_dir_list sources_return_list extension)
    MESSAGE(STATUS "Processing Source Files")
    SET(sources_list "")
    FOREACH(dir ${${sources_dir_list}})
        MESSAGE(STATUS "Processing source directory: " ${dir})
        SET(new_list "")
        FILE(GLOB_RECURSE new_list ${dir}/*${extension})
        SET(sources_list ${sources_list} ${new_list})
    ENDFOREACH()
    SET(${sources_return_list} ${sources_list})
    MESSAGE(STATUS "DONE")
ENDMACRO()

set(source_dir_list Include)

include_directories(Include)

SOURCE_FILES(source_dir_list source_files_list .cpp)
SOURCE_FILES(source_dir_list header_files_list .h)

list(LENGTH source_files_list source_files_list_count)
message(STATUS "[INFO] Found ${source_files_list_count} source files. (${source_files_list})\n")

list(LENGTH header_files_list header_files_list_count)
message(STATUS "[INFO] Found ${header_files_list_count} header files. (${header_files_list})\n")

add_library(TS_CPP TSManager.cpp ${header_files_list} ${source_files_list})


# GoogleTest
add_subdirectory(Tests)
