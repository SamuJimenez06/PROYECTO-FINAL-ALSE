#ifndef LUZ_H
#define LUZ_H

#include "Dispositivo.h"

class Luz : public Dispositivo {
private:
    int nivelBrillo; // Porcentaje de brillo de 0 a 100

public:
    Luz(int id, std::string nombre, double potenciaWatts);
    void setBrillo(int brillo);
    int getBrillo() const;
};

#endif
