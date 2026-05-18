cmake_minimum_required(VERSION 4.1)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()
add_executable(lab2_4 main.c
        domain/oferta.h
        domain/oferta.c
        repo/repo.h
        repo/repo.c
        service/service.h
        service/service.c
        ui/ui.h
        ui/ui.c
        teste/teste.c
        validator/valideaza.h
        validator/valideaza.c
        vectordinamic/vector.c
        vectordinamic/vector.h)
