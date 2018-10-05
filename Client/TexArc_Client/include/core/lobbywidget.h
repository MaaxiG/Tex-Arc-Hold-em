#ifndef LOBBYWIDGET_H
#define LOBBYWIDGET_H

#include <QWidget>
#include <QtWidgets>
class LobbyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LobbyWidget(QWidget *parent = nullptr);
    QPushButton *startBtn;
private:
    QHBoxLayout *mainHB;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;


signals:

public slots:
};

#endif // LOBBYWIDGET_H
