#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class ClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetwork(QObject *parent = nullptr);
    void networkQuit();
    void sendDataToServer(QString stateNumber, QList<QString> *messages);
    void debugSendMessage();
    QString token;
private:
    QTcpSocket *socket;
signals:

public slots:
    void readyRead();
};

#endif // CLIENTNETWORK_H
