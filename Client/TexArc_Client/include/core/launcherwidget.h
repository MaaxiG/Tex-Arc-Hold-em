#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class LauncherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = nullptr);
    QPushButton *registerButton;
    QPushButton *loginButton;

    QLineEdit *leUserName;
    QLineEdit *lePassword;

private:
    QGroupBox *loginGB;
    QGridLayout *loginGL;
    QHBoxLayout *userNameHBL;
    QHBoxLayout *passwordHBL;
    QVBoxLayout *vBoxLayout;

    QLabel *lblUserName;
    QLabel *lblPassword;



    QHBoxLayout *buttonLayout;


signals:

public slots:
};

#endif // LAUNCHERWIDGET_H
