#include "Persiana.h"

Persiana::Persiana(int id, std::string nombre, double potenciaWatts) 
    : Dispositivo(id, nombre, potenciaWatts) {
    this->porcentajeApertura = 0; // Por defecto cerrada al iniciar
}

void Persiana::setApertura(int porcentaje) {
    if (porcentaje >= 0 && porcentaje <= 100) {
        this->porcentajeApertura = porcentaje;
    }
}

int Persiana::getApertura() const {
    return this->porcentajeApertura;
}
