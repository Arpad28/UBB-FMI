cmake_minimum_required(VERSION 4.1)
project(TAD_MDO7)

set(CMAKE_CXX_STANDARD 20)

include_directories("Proiect C++" "Teste")
add_executable(TAD_MDO7
        "Proiect C++/App.cpp"
        "Proiect C++/IteratorMDO.cpp"
        "Proiect C++/MDO.cpp"
        "Teste/TestExtins.cpp"
        "Teste/TestScurt.cpp")