#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>

class Dispositivo {
protected:
    int id;
    std::string nombre;
    std::string estado; // "encendido", "apagado" o "fallo"
    double potenciaWatts;

public:
    Dispositivo(int id, std::string nombre, double potenciaWatts);
    virtual ~Dispositivo();

    virtual void encender();
    virtual void apagar();
    
    std::string getEstado() const;
    std::string getNombre() const;
    double getPotencia() const;
};

#endif
