#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    QPushButton *registerButton;



    QLineEdit *leEmail;
    QLineEdit *leUserName;
    QLineEdit *lePassword;
    QLineEdit *lePasswordRepeat;
private:
    QGridLayout *registerGL;
    QGroupBox *registerGB;
    QHBoxLayout *userNameHBL;
    QHBoxLayout *emailHBL;
    QHBoxLayout *passwordHBL;
    QHBoxLayout *passwordRepeatHBL;
    QVBoxLayout *vBoxLayout;

    QLabel *lblEmail;
    QLabel *lblUserName;
    QLabel *lblPassword;
    QLabel *lblPasswordRepeat;


signals:

public slots:
};

#endif // REGISTERWIDGET_H
