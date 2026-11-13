#include "Luz.h"

Luz::Luz(int id, std::string nombre, double potenciaWatts) 
    : Dispositivo(id, nombre, potenciaWatts) {
    this->nivelBrillo = 100; // Brillo máximo al encender
}

void Luz::setBrillo(int brillo) {
    if (brillo >= 0 && brillo <= 100) {
        this->nivelBrillo = brillo;
    }
}

int Luz::getBrillo() const {
    return this->nivelBrillo;
}
