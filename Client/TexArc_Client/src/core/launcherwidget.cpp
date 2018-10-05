#include "include/core/launcherwidget.h"

LauncherWidget::LauncherWidget(QWidget *parent) : QWidget(parent)
{
    loginGL = new QGridLayout();
    this->setLayout(loginGL);
    loginGB = new QGroupBox(tr("Login"));
    userNameHBL = new QHBoxLayout();
    passwordHBL = new QHBoxLayout();
    vBoxLayout = new QVBoxLayout(loginGB);
    vBoxLayout->addLayout(userNameHBL);
    vBoxLayout->addLayout(passwordHBL);
    buttonLayout = new QHBoxLayout();
    vBoxLayout->addLayout(buttonLayout);
    loginButton = new QPushButton(tr("Login"));
    registerButton = new QPushButton(tr("Register"));
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(loginButton);
    lblUserName = new QLabel(tr("UserName"));
    lblPassword = new QLabel(tr("Password "));
    leUserName = new QLineEdit();
    lePassword = new QLineEdit();
    lePassword->setEchoMode(QLineEdit::Password);
    userNameHBL->addWidget(lblUserName);
    userNameHBL->addWidget(leUserName);
    passwordHBL->addWidget(lblPassword);
    passwordHBL->addWidget(lePassword);
    loginGL->addWidget(loginGB);
}
