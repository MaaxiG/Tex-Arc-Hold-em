#include "include/core/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(tr("Tex'Arc Hold'em"));
    launcherWidget = new LauncherWidget();
    registerWidget = new RegisterWidget();
    lobbyWidget = new LobbyWidget();
    gameWidget = new GameWidget();

    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readyRead);
    socket->connectToHost("127.0.0.1", quint16(65535));

    this->setCentralWidget(launcherWidget);
    //this->setFixedSize(1100, 800);

    connect(launcherWidget->registerButton, &QPushButton::clicked, this, [=]{
        this->setCentralWidget(registerWidget);
    });

    connect(registerWidget->registerButton, &QPushButton::clicked, this, [=]{
        this->sendDataToServer("0", new QList<QString>{registerWidget->leEmail->text(),
                                                       registerWidget->leUserName->text(),
                                                       registerWidget->lePassword->text()});
    });

    connect(launcherWidget->loginButton, &QPushButton::clicked, this, [=]{
        this->sendDataToServer("1", new QList<QString>{launcherWidget->leUserName->text(),
                                                       launcherWidget->lePassword->text()});
    });

    connect(lobbyWidget->startBtn, &QPushButton::clicked, this, [=]{
        this->sendDataToServer("2", new QList<QString>{this->token});
    });

    connect(gameWidget, &GameWidget::raiseClicked, this, [=](int param){
        this->sendDataToServer("4", new QList<QString>{QString::number(param)});
    });

    connect(gameWidget, &GameWidget::checkClicked, this, [=]{
        this->sendDataToServer("3", new QList<QString>{});
    });

    connect(gameWidget, &GameWidget::callClicked, this, [=]{
        this->sendDataToServer("1", new QList<QString>{});
    });

    connect(gameWidget, &GameWidget::foldClicked, this, [=]{
        this->sendDataToServer("2", new QList<QString>{});
    });
}


void MainWindow::readyRead()
{
    QDataStream in(socket);
    qint64 size = 0;

    // When not enough data has been received, stop
    if (socket->bytesAvailable() < sizeof (qint64))
    {
         return;
    }
    in >> size;

    // When not enough data has been received, stop
    if (socket->bytesAvailable() < size)
    {
         return;
    }

    // Get the useful data
    QString state;
    in >> state;

    switch (state.toInt())
    {
        case -1:{
            QString error;
            in >> error;
            //show error
            break;
        }

        case 0:{
            in >> this->token;


            this->setCentralWidget(lobbyWidget);
            break;
        }

        case 1:{
            this->setCentralWidget(gameWidget);
            this->setFixedSize(1100, 800);
            break;
        }

        case 2:{
            //Player info
            break;
        }

        case 3:{
            QString gameState;
            in >> gameState;
            //0: startGame - bigBlindPlayerBet, BigBlindPlayerPlace, bigBlindPlayerBet, BigBlindPlayerPlace
            //1: giveCards -  c1, c2
            //2: nextPlayer - playerPlace
            //3: play - betToEven, currentPlayerBet
            //4: check - playerPlace
            //5: call - playerPlace, bet
            //6: bet - playerPlace, bet
            //7: fold - playerPlace
            //8: nextRound - pot, cards
            //9: newPlayer - PlayerPlace, Playername, Playermoney
            //10: leavePlayer - Playerplace

            //Start game : StartRound > nextPlayer > play(to concerned player) > update > loop > nextRound

            qDebug() << gameState;
            switch (gameState.toInt())
            {
                case 0:{ //START GAME
                    qDebug() << "Start game";
                    QString bigBlindPlayerBet, bigBlindPlayerPlace, smallBlindPlayerBet, smallBlindPlayerPlace;
                    in >> bigBlindPlayerBet;
                    in >> bigBlindPlayerPlace;
                    in >> smallBlindPlayerBet;
                    in >> smallBlindPlayerPlace;

                    gameWidget->nextRound(0);

                    gameWidget->setPlayerSet(bigBlindPlayerPlace.toInt(), bigBlindPlayerBet.toInt());
                    gameWidget->setPlayerSet(smallBlindPlayerPlace.toInt(), smallBlindPlayerBet.toInt());

                    break;
                }

                case 1:{ //GIVE CARDS
                    qDebug() << "Give cards";
                    QString c1, c2;
                    in >> c1;
                    in >> c2;

                    gameWidget->setBigCards(c1, c2);

                    break;
                }

                case 2:{ //NEXT PLAYER
                    qDebug() << "Next player";
                    QString playerPlace;
                    in >> playerPlace;

                    gameWidget->setPlayerTurn(playerPlace.toInt());

                    break;
                }

                case 3:{ //PLAY
                    qDebug() << "Play";
                    QString betToEven, currentBet;
                    in >> betToEven;
                    in >> currentBet;

                    if(betToEven == currentBet)
                        gameWidget->showCheckBtn();
                    else
                        gameWidget->showCallBtn();

                    break;
                }

                case 4:{ //CHECK
                    qDebug() << "check";
                    QString playerPlace;
                    in >> playerPlace;

                    gameWidget->check(playerPlace.toInt());

                    break;
                }

                case 5:{ //CALL
                    qDebug() << "call";
                    QString playerPlace, playerBet;
                    in >> playerPlace;
                    in >> playerBet;

                    gameWidget->call(playerPlace.toInt());
                    gameWidget->setPlayerSet(playerPlace.toInt(), playerBet.toInt());
                    break;
                }

                case 6:{ //BET
                    qDebug() << "bet";
                    QString playerPlace, playerBet;
                    in >> playerPlace;
                    in >> playerBet;

                    gameWidget->raise(playerPlace.toInt());
                    gameWidget->setPlayerSet(playerPlace.toInt(), playerBet.toInt());
                    break;
                }

                case 7:{ //FOLD
                    qDebug() << "fold";
                    QString playerPlace;
                    in >> playerPlace;

                    gameWidget->foldPlayer(playerPlace.toInt());
                    break;
                }

                case 8:{ //NEXT ROUND
                    qDebug() << "next round";
                    QString pot, cards;
                    in >> pot;
                    in >> cards;

                    gameWidget->nextRound(pot.toInt());
                    gameWidget->setFlop("2H", "KH", "4H");
                    break;
                }

                case 9:{ //NEW PLAYER
                    qDebug() << "new player";
                    QString playerPlace, playerName, playerMoney;
                    in >> playerPlace;
                    in >> playerName;
                    in >> playerMoney;

                    gameWidget->addPlayer(playerName, playerMoney.toInt(), playerPlace.toInt());
                    break;
                }

                case 10:{ //LEAVE PLAYER

                    QString playerPlace;
                    in >> playerPlace;

                    gameWidget->removePlayer(playerPlace.toInt());
                    //gameWidget->

                    break;
                }

            }

            break;
        }

        case 4:{ //INITIALIZE UI
            qDebug() << "init ui";
            QString playerName, playerMoney, playerPlace, playerSet, isFolded, gamePot, currentPlayerTurn;

            in >> gamePot;
            in >> currentPlayerTurn;

            gameWidget->setPot(gamePot.toInt());

            for(int i = 0; i < 9; i++)
            {
                in >>playerPlace;
//                qDebug() << "me - " + playerPlace;

                if(playerPlace.toInt() != -1)
                {
                    in >>playerName;
                    in >>playerMoney;
                    in >>playerSet;
                    in >>isFolded;
                    gameWidget->addPlayer(playerName, playerMoney.toInt(), playerPlace.toInt());

                    if(isFolded == "1")
                        gameWidget->foldPlayer(playerPlace.toInt());
                }
            }

            if(currentPlayerTurn.toInt() != -1)
                gameWidget->setPlayerTurn(currentPlayerTurn.toInt());


            break;
        }

        default: break;
    }

    qDebug() << socket->bytesAvailable();
    if(socket->bytesAvailable() != 0)
    {
        readyRead();
    }
}

void MainWindow::sendDataToServer(QString stateNumber, QList<QString> *messages)
{
    /**** DATAGRAMS RECEIVED ********************************************/
    /* SignIn               : |size|0|email|nickname|hashedpassword|    */
    /* LogIn                : |size|1|nickname|hashedpassword|          */
    /* SearchTable          : |size|2|hash|                             */
    /* GetPlayerInfo        : |size|3|hash|                             */
    /*************************************************/
    //Sign in : sendDataToServer("0", new QList<QString>{email, nickname, hashedpassword});
    //Log in : sendDataToServer("1", new QList<QString>{nickname, hashedpassword});
    //searchtable : sendDataToServer("2", new QList<QString>{token});
    //Sign in : sendDataToServer("3", new QList<QString>{token});
    qint32 size = stateNumber.toUtf8().size();

    for(int i = 0; i < messages->length(); i++)
    {
        size += messages->at(i).toUtf8().size();
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << size << stateNumber;

    for(int i = 0; i < messages->length(); i++)
    {
        out << messages->at(i);
    }

    socket->write(block);
    socket->flush();
}



MainWindow::~MainWindow()
{
    delete launcherWidget;
    delete registerWidget;
    delete lobbyWidget;
    delete gameWidget;
}
