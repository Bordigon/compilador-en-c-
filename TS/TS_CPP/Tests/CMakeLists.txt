project(Google_tests)
add_subdirectory(googletest-lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

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

set(test_dir_list .)
SOURCE_FILES(test_dir_list test_files_list .cpp)

list(LENGTH test_files_list test_files_list_count)
message(STATUS "[INFO] Found ${test_files_list_count} test files. (${test_files_list})\n")

add_executable(Google_Tests_run ${test_files_list})

# Mark the test directory to be excluded from all target
set_property(TARGET Google_Tests_run PROPERTY EXCLUDE_FROM_ALL TRUE)

target_link_libraries(Google_Tests_run TS_CPP)

target_link_libraries(Google_Tests_run gtest gtest_main)
