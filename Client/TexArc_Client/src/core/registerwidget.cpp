#include "include/core/registerwidget.h"

RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent)
{
    registerGL = new QGridLayout();
    this->setLayout(registerGL);
    registerGB = new QGroupBox(tr("Register"));
    userNameHBL = new QHBoxLayout();
    emailHBL = new QHBoxLayout();
    passwordHBL = new QHBoxLayout();
    passwordRepeatHBL = new QHBoxLayout();

    vBoxLayout = new QVBoxLayout(registerGB);

    vBoxLayout->addLayout(userNameHBL);
    vBoxLayout->addLayout(emailHBL);
    vBoxLayout->addLayout(passwordHBL);
    vBoxLayout->addLayout(passwordRepeatHBL);

    registerButton = new QPushButton(tr("Register"));
    vBoxLayout->addWidget(registerButton);


    lblUserName = new QLabel(tr("UserName"));
    lblEmail = new QLabel(tr("Email"));
    lblPassword = new QLabel(tr("Password "));
    lblPasswordRepeat = new QLabel(tr("Confirm password "));
    leUserName = new QLineEdit();
    leEmail = new QLineEdit();
    lePassword = new QLineEdit();
    lePasswordRepeat = new QLineEdit();
    lePassword->setEchoMode(QLineEdit::Password);
    lePasswordRepeat->setEchoMode(QLineEdit::Password);

    userNameHBL->addWidget(lblUserName);
    userNameHBL->addWidget(leUserName);

    emailHBL->addWidget(lblEmail);
    emailHBL->addWidget(leEmail);

    passwordHBL->addWidget(lblPassword);
    passwordHBL->addWidget(lePassword);

    passwordRepeatHBL->addWidget(lblPasswordRepeat);
    passwordRepeatHBL->addWidget(lePasswordRepeat);
    registerGL->addWidget(registerGB);

}
