#include <QApplication>
#include "BaseDatos.h"
#include "LoginWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Inicializamos la base de datos y creamos las tablas y usuario por defecto
    BaseDatos db("../database/domotica.db");
    db.crearTablas();
    db.crearTablaUsuarios();

    // Mostramos la ventana de autenticación gráfica
    LoginWindow loginWin(db);
    loginWin.show();

    return app.exec();
}
