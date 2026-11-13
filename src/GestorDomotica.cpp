
#include "GestorDomotica.h"
#include <iostream>

GestorDomotica::GestorDomotica() {}

GestorDomotica::~GestorDomotica() {}

void GestorDomotica::agregarDispositivo(std::shared_ptr<Dispositivo> dispositivo) {
    dispositivos.push_back(dispositivo);
}

void GestorDomotica::listarDispositivos() const {
    std::cout << "\n--- LISTA DE DISPOSITIVOS REGISTRADOS ---" << std::endl;
    for (const auto& d : dispositivos) {
        std::cout << "- " << d->getNombre() << " | Estado: " << d->getEstado() 
                  << " | Potencia: " << d->getPotencia() << "W" << std::endl;
    }
}

void GestorDomotica::apagarTodo() {
    for (auto& d : dispositivos) {
        d->apagar();
    }
    std::cout << "\n[!] Alerta: Todos los dispositivos han sido apagados." << std::endl;
}

double GestorDomotica::calcularConsumoTotal(double horasUso) const {
    double potenciaActivaWatts = 0.0;

    // Suma la potencia solo de los dispositivos que estén encendidos
    for (const auto& d : dispositivos) {
        if (d->getEstado() == "encendido") {
            potenciaActivaWatts += d->getPotencia();
        }
    }

    // Fórmula de consumo: (Watts * Horas) / 1000 para obtener kWh
    return (potenciaActivaWatts * horasUso) / 1000.0;
}
