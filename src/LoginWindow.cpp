#include "LoginWindow.h"
#include "MainWindow.h" // La ventana principal que crearemos despues
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

LoginWindow::LoginWindow(BaseDatos& database, QWidget* parent) : db(database), QWidget(parent) {
    setWindowTitle("Login - Sistema Domotico");
    setFixedSize(350, 220);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);

    QLabel* lblTitulo = new QLabel("<b>CONTROL DOMOTICO - ACCESO</b>", this);
    lblTitulo->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(lblTitulo);

    txtUsuario = new QLineEdit(this);
    txtUsuario->setPlaceholderText("Usuario (ej. admin)");
    layoutPrincipal->addWidget(txtUsuario);

    txtPassword = new QLineEdit(this);
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setPlaceholderText("Contraseña (ej. 1234)");
    layoutPrincipal->addWidget(txtPassword);

    btnIngresar = new QPushButton("Iniciar Sesión", this);
    layoutPrincipal->addWidget(btnIngresar);

    lblMensaje = new QLabel("", this);
    lblMensaje->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(lblMensaje);

    // Conectamos el boton con la funcion de validacion
    connect(btnIngresar, &QPushButton::clicked, this, &LoginWindow::intentarLogin);
}

void LoginWindow::intentarLogin() {
    QString usuario = txtUsuario->text();
    QString password = txtPassword->text();

    if (db.validarUsuario(usuario.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Éxito", "¡Acceso concedido al sistema!");

        // Abrimos la ventana principal domótica y cerramos el login
        MainWindow* ventanaPrincipal = new MainWindow(db);
        ventanaPrincipal->show();
        this->close();
    } else {
        lblMensaje->setStyleSheet("color: red;");
        lblMensaje->setText("Usuario o contraseña incorrectos.");
    }
}
