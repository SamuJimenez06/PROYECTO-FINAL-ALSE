#include "BaseDatos.h"
#include <iostream>

BaseDatos::BaseDatos(const std::string& nombreArchivo) {
    db = nullptr;
    errMsg = nullptr;
    rc = sqlite3_open(nombreArchivo.c_str(), &db);
    if (rc) {
        std::cerr << "[Error] No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "[Info] Base de datos SQLite conectada con exito." << std::endl;
    }
}

BaseDatos::~BaseDatos() {
    cerrarConexion();
}

bool BaseDatos::abrirConexion() {
    return db != nullptr;
}

void BaseDatos::crearTablas() {
    const char* sql = "CREATE TABLE IF NOT EXISTS Eventos ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "dispositivo TEXT NOT NULL, "
                      "estado TEXT NOT NULL, "
                      "fecha_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "[Error SQL] Error al crear la tabla: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "[Info] Tabla 'Eventos' verificada/creada correctamente." << std::endl;
    }
}

void BaseDatos::registrarEvento(const std::string& dispositivo, const std::string& estado) {
    std::string sql = "INSERT INTO Eventos (dispositivo, estado) VALUES ('" + dispositivo + "', '" + estado + "');";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "[Error SQL] No se pudo registrar el evento: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "[DB Log] Evento guardado: " << dispositivo << " -> " << estado << std::endl;
    }
}

void BaseDatos::cerrarConexion() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "[Info] Conexión a la base de datos cerrada." << std::endl;
    }
}

void BaseDatos::crearTablaUsuarios() {
    const char* sql = "CREATE TABLE IF NOT EXISTS Usuarios ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "[Error SQL] Error al crear tabla Usuarios: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        const char* insertDefault = "INSERT OR IGNORE INTO Usuarios (username, password) VALUES ('admin', '1234');";
        sqlite3_exec(db, insertDefault, 0, 0, &errMsg);
        std::cout << "[Info] Tabla 'Usuarios' verificada (Usuario por defecto: admin / 1234)." << std::endl;
    }
}

bool BaseDatos::validarUsuario(const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM Usuarios WHERE username = ? AND password = ?;";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "[Error SQL] Fallo al preparar consulta de login." << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    bool accesoConcedido = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        accesoConcedido = true;
    }

    sqlite3_finalize(stmt);
    return accesoConcedido;
}
