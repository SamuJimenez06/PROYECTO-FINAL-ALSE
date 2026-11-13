#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "BaseDatos.h"

class LoginWindow : public QWidget {
    Q_OBJECT
private:
    BaseDatos& db;
    QLineEdit* txtUsuario;
    QLineEdit* txtPassword;
    QPushButton* btnIngresar;
    QLabel* lblMensaje;

public:
    LoginWindow(BaseDatos& database, QWidget* parent = nullptr);

private slots:
    void intentarLogin();
};

#endif
