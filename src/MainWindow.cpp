#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(BaseDatos& database, QWidget* parent) : db(database), QMainWindow(parent) {
    setWindowTitle("Panel de Control Domótico - GUI");
    setFixedSize(500, 450);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Inicializamos los dispositivos como miembros de la clase
    luzSala = std::make_shared<Luz>(1, "Luz Sala", 60.0);
    persianaBalcon = std::make_shared<Persiana>(2, "Persiana Balcon", 15.0);

    miCasa.agregarDispositivo(luzSala);
    miCasa.agregarDispositivo(persianaBalcon);

    layout->addWidget(new QLabel("<b>Dispositivos Registrados en el Hogar:</b>", this));
    listaDispositivosUI = new QListWidget(this);
    listaDispositivosUI->addItem("Luz Sala | Estado: apagado | Potencia: 60W");
    listaDispositivosUI->addItem("Persiana Balcon | Estado: apagado | Potencia: 15W");
    layout->addWidget(listaDispositivosUI);

    QHBoxLayout* layoutBotonesLuz = new QHBoxLayout();
    QPushButton* btnEncenderLuz = new QPushButton("Encender Luz Sala", this);
    QPushButton* btnApagarLuz = new QPushButton("Apagar Luz Sala", this);
    layoutBotonesLuz->addWidget(btnEncenderLuz);
    layoutBotonesLuz->addWidget(btnApagarLuz);
    layout->addLayout(layoutBotonesLuz);

    QHBoxLayout* layoutBotonesPersiana = new QHBoxLayout();
    QPushButton* btnEncenderPersiana = new QPushButton("Abrir Persiana", this);
    QPushButton* btnApagarPersiana = new QPushButton("Cerrar Persiana", this);
    layoutBotonesPersiana->addWidget(btnEncenderPersiana);
    layoutBotonesPersiana->addWidget(btnApagarPersiana);
    layout->addLayout(layoutBotonesPersiana);

    layout->addWidget(new QLabel("<b>Panel Gráfico de Potencia (W):</b>", this));

    layout->addWidget(new QLabel("Luz Sala (60W):", this));
    barraPotenciaLuz = new QProgressBar(this);
    barraPotenciaLuz->setRange(0, 100);
    barraPotenciaLuz->setValue(0);
    layout->addWidget(barraPotenciaLuz);

    layout->addWidget(new QLabel("Persiana Balcon (15W):", this));
    barraPotenciaPersiana = new QProgressBar(this);
    barraPotenciaPersiana->setRange(0, 100);
    barraPotenciaPersiana->setValue(0);
    layout->addWidget(barraPotenciaPersiana);

    QPushButton* btnEstadisticas = new QPushButton("Calcular Consumo Energético Total (kWh)", this);
    layout->addWidget(btnEstadisticas);

    setCentralWidget(centralWidget);

    connect(btnEncenderLuz, &QPushButton::clicked, this, &MainWindow::encenderSala);
    connect(btnApagarLuz, &QPushButton::clicked, this, &MainWindow::apagarSala);
    connect(btnEncenderPersiana, &QPushButton::clicked, this, &MainWindow::encenderPersiana);
    connect(btnApagarPersiana, &QPushButton::clicked, this, &MainWindow::apagarPersiana);
    connect(btnEstadisticas, &QPushButton::clicked, this, &MainWindow::verConsumoEnergetico);
}

void MainWindow::encenderSala() {
    luzSala->encender();
    barraPotenciaLuz->setValue(60);
    db.registrarEvento("Luz Sala", "encendido");
    QMessageBox::information(this, "Control", "Luz de la Sala encendida y registrada en SQLite.");
}

void MainWindow::apagarSala() {
    luzSala->apagar();
    barraPotenciaLuz->setValue(0);
    db.registrarEvento("Luz Sala", "apagado");
}

void MainWindow::encenderPersiana() {
    persianaBalcon->encender();
    barraPotenciaPersiana->setValue(30);
    db.registrarEvento("Persiana Balcon", "abierto");
    QMessageBox::information(this, "Control", "Persiana abierta y registrada en SQLite.");
}

void MainWindow::apagarPersiana() {
    persianaBalcon->apagar(); 
    barraPotenciaPersiana->setValue(0);
    db.registrarEvento("Persiana Balcon", "cerrado");
}

void MainWindow::verConsumoEnergetico() {

    double consumo = miCasa.calcularConsumoTotal(5.0);
    QString mensaje = QString("Consumo energético estimado (5 horas): %1 kWh").arg(consumo);
    QMessageBox::information(this, "Estadísticas de Consumo", mensaje);
}
