cmake_minimum_required(VERSION 3.25)
project(procesador)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(TS/TS_CPP)

add_executable(procesador
    Procesador.cpp
    AnalizadorLexico.cpp
    GestorDeErrores.cpp)

target_link_libraries(procesador TS_CPP)

target_include_directories(procesador PRIVATE
    TS/TS_CPP
    TS/TS_CPP/Include) 
