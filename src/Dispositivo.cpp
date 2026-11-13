#include "Dispositivo.h"

Dispositivo::Dispositivo(int id, std::string nombre, double potenciaWatts) {
    this->id = id;
    this->nombre = nombre;
    this->estado = "apagado";
    this->potenciaWatts = potenciaWatts;
}

Dispositivo::~Dispositivo() {}

void Dispositivo::encender() {
    this->estado = "encendido";
}

void Dispositivo::apagar() {
    this->estado = "apagado";
}

std::string Dispositivo::getEstado() const {
    return this->estado;
}

std::string Dispositivo::getNombre() const {
    return this->nombre;
}

double Dispositivo::getPotencia() const {
    return this->potenciaWatts;
}
