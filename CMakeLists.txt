cmake_minimum_required(VERSION 3.10)
project(GestorDomotica)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

include_directories(include)

add_executable(gestor_domotica
    src/main.cpp
    src/Dispositivo.cpp
    src/Luz.cpp
    src/Persiana.cpp
    src/GestorDomotica.cpp
    src/BaseDatos.cpp
    src/LoginWindow.cpp
    src/MainWindow.cpp
    include/LoginWindow.h
    include/MainWindow.h
)


target_link_libraries(gestor_domotica PRIVATE sqlite3 Qt5::Widgets Qt5::Sql)
