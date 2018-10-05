#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "launcherwidget.h"
#include "registerwidget.h"
#include "lobbywidget.h"
#include "gamewidget.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QList>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void sendDataToServer(QString stateNumber, QList<QString> *messages);
    ~MainWindow();
    QString token;
private:
    LauncherWidget *launcherWidget;
    RegisterWidget *registerWidget;
    LobbyWidget *lobbyWidget;
    GameWidget *gameWidget;

    QTcpSocket* socket;

signals:

public slots:
    void readyRead();
};

#endif // MAINWINDOW_H
