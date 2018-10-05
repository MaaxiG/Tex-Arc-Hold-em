#include "include/core/lobbywidget.h"

LobbyWidget::LobbyWidget(QWidget *parent) : QWidget(parent)
{
    leftVBox = new QVBoxLayout();
    rightVBox = new QVBoxLayout();
    mainHB = new QHBoxLayout();
    mainHB->addLayout(leftVBox);
    mainHB->addLayout(rightVBox);

    startBtn = new QPushButton(tr("Start"));
    leftVBox->addWidget(startBtn);

    this->setLayout(mainHB);
}
