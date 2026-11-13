#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QProgressBar>
#include <memory>
#include "GestorDomotica.h"
#include "BaseDatos.h"
#include "Luz.h"
#include "Persiana.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    BaseDatos& db;
    GestorDomotica miCasa;

    std::shared_ptr<Luz> luzSala;
    std::shared_ptr<Persiana> persianaBalcon;

    QListWidget* listaDispositivosUI;
    QProgressBar* barraPotenciaLuz;
    QProgressBar* barraPotenciaPersiana;

public:
    MainWindow(BaseDatos& database, QWidget* parent = nullptr);

private slots:
    void encenderSala();
    void apagarSala();
    void encenderPersiana();
    void apagarPersiana();
    void verConsumoEnergetico();
};

#endif
