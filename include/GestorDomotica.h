#ifndef GESTOR_DOMOTICA_H
#define GESTOR_DOMOTICA_H

#include <vector>
#include <memory>
#include "Dispositivo.h"

class GestorDomotica {
private:
    // Lista dinámica usando punteros inteligentes para manejar cualquier dispositivo (Luz, Persiana, etc.)
    std::vector<std::shared_ptr<Dispositivo>> dispositivos;

public:
    GestorDomotica();
    ~GestorDomotica();

    void agregarDispositivo(std::shared_ptr<Dispositivo> dispositivo);
    void listarDispositivos() const;
    void apagarTodo();
// estimar consumo energético (kWh) en base a las horas de uso
    double calcularConsumoTotal(double horasUso) const;
};

#endif
