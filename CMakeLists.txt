cmake_minimum_required(VERSION 3.10)
project(GestorDomotica)

# Usar el estándar C++17 requerido para el proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# Definir el ejecutable y los archivos fuente (.cpp) que va a compilar
add_executable(gestor_domotica
    src/main.cpp
    src/Dispositivo.cpp
    src/Luz.cpp
    src/Persiana.cpp
    src/GestorDomotica.cpp
    src/BaseDatos.cpp
)

target_link_libraries(gestor_domotica PRIVATE sqlite3)
