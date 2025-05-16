cmake_minimum_required(VERSION 3.10)
project(StudentuSkirstymas)

set(CMAKE_CXX_STANDARD 17)

add_executable(studentu_skirstymas
    testavimas.cpp
    testavimoFunkcijos.cpp
)

# Nustatyti, kad .exe būtų pagrindiniame projekto aplanke
set_target_properties(studentu_skirstymas PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")