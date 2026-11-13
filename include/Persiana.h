#ifndef PERSIANA_H
#define PERSIANA_H

#include "Dispositivo.h"

class Persiana : public Dispositivo {
private:
    int porcentajeApertura; // 0 (cerrada) a 100 (abierta)

public:
    Persiana(int id, std::string nombre, double potenciaWatts);

    void setApertura(int porcentaje);
    int getApertura() const;
};

#endif
