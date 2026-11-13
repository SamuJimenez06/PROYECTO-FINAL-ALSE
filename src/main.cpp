#include <iostream>
#include <memory>
#include "Luz.h"
#include "Persiana.h"
#include "GestorDomotica.h"
#include "BaseDatos.h"

int main() {
    BaseDatos db("../database/domotica.db");
    db.crearTablas();
    db.crearTablaUsuarios();

    std::cout << "\n=======================================" << std::endl;
    std::cout << "   SISTEMA DE GESTION DOMOTICA - LOGIN   " << std::endl;
    std::cout << "=======================================" << std::endl;

    std::string user, pass;
    std::cout << "Usuario: ";
    std::cin >> user;
    std::cout << "Contrasena: ";
    std::cin >> pass;

    if (!db.validarUsuario(user, pass)) {
        std::cout << "\n[Acceso Denegado] Usuario o contrasena incorrectos.\n" << std::endl;
        return 0;
    }

    std::cout << "\n[Acceso Concedido] Bienvenid@ al sistema, " << user << "!\n" << std::endl;

    GestorDomotica miCasa;

    auto sala = std::make_shared<Luz>(1, "Luz Sala", 60.0);
    auto balcon = std::make_shared<Persiana>(2, "Persiana Balcon", 15.0);

    miCasa.agregarDispositivo(sala);
    miCasa.agregarDispositivo(balcon);

    sala->encender();
    db.registrarEvento(sala->getNombre(), sala->getEstado());

    miCasa.listarDispositivos();

    double horas = 5.0;
    double consumoKWh = miCasa.calcularConsumoTotal(horas);
    std::cout << "\n[Estadisticas] Consumo energetico estimado (" << horas << " horas): " 
              << consumoKWh << " kWh" << std::endl;

    return 0;
}
