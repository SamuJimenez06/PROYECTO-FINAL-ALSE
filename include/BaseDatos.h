#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include <string>
#include <sqlite3.h>

class BaseDatos {
private:
    sqlite3* db;
    char* errMsg;
    int rc;

public:
    BaseDatos(const std::string& nombreArchivo);
    ~BaseDatos();

    bool abrirConexion();
    void crearTablas();
    void registrarEvento(const std::string& dispositivo, const std::string& estado);

    // Nuevos métodos para autenticación de usuarios
    void crearTablaUsuarios();
    bool validarUsuario(const std::string& username, const std::string& password);

    void cerrarConexion();
};

#endif

