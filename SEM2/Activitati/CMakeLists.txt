cmake_minimum_required(VERSION 4.1)
project(lab6_7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

if (MSVC)
    add_compile_options(/W4 /WX /EHsc)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()
add_executable(lab6_7 maingui.cpp
        domain/activitate.h
        domain/activitate.cpp
        repo/repository.h
        repo/repository.cpp
        service/service.h
        service/service.cpp
        ui/ui.h
        ui/ui.cpp
        teste/teste.h
        teste/teste.cpp
        utils/vector_dinamic.h
        domain/exceptii.h
        domain/lista_activitati.h
        domain/lista_activitati.cpp
        service/undo.h
        ui/ActivitatiGUI.cpp
        ui/ActivitatiGUI.h
        ui/PlanificareGUI.h
        ui/PlanificareGUI.h
        ui/PlanificareGUI.cpp
        ui/PlanificareGUI.h
        ui/Observer.h
        ui/ActivitatiTableModel.h
        ui/CosCRUDGUI.h
        ui/CosReadOnlyGUI.h
)

target_link_libraries(lab6_7 PRIVATE Qt6::Widgets)