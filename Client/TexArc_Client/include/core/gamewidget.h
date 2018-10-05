#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QtWidgets>

class GameWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

    void addPlayer(QString name, int money, int pos);
    void setPlayerTurn(int turn);
    void nextTurn();
    void nextRound(int pot);
    void showCards(QString c1, QString c2, int pos);
    void hideAllCards();
    void setFlop(QString c1, QString c2, QString c3);
    void setTurn(QString c);
    void setRiver(QString c);
    void setBigCards(QString c1, QString c2);
    void foldPlayer(int pos);
    void setPlayerMoney(int money, int pos);
    void removePlayer(int pos);
    void showCallBtn();
    void showCheckBtn();
    void hideAllBtn();
    void setPlayerSet(int pos, int money);
    void removePlayerSet(int pos);
    void setPot(int money);
    void check(int pos);
    void call(int pos);
    void raise(int pos);
    QString moneyToString(int money);



    void setInfosRaise(int money, int bigBlind){
        this->max = money;
        this->bigBlind = bigBlind;
    }

private:
    QGraphicsScene *scene;
    QVector<QGraphicsPixmapItem*> backplayers;
    QVector<QGraphicsPixmapItem*> firstCards;
    QVector<QGraphicsPixmapItem*> secondCards;
    QVector<QGraphicsTextItem*> playersName;
    QVector<QGraphicsTextItem*> playersMoney;
    QVector<QGraphicsTextItem*> playersSet;
    QVector<QGraphicsPixmapItem*> playersChip;

    QGraphicsRectItem* foldBtn;
    QGraphicsRectItem* callBtn;
    QGraphicsRectItem* raiseBtn;
    QGraphicsRectItem* checkBtn;

    QGraphicsTextItem* foldText;
    QGraphicsTextItem* callText;
    QGraphicsTextItem* raiseText;
    QGraphicsTextItem* checkText;


    QGraphicsTextItem* potText;

    int nbPlayers = 1;
    int turnPlayer;
    int chair;
    QPixmap backplayerPM;
    QPixmap backplayerturnPM;
    QPixmap backCardsPM;
    QPixmap backCardsPM2;

    QPixmap backgroundCardPM;
    QPixmap coeurPM;
    QPixmap piquePM;
    QPixmap treflePM;
    QPixmap carreauPM;

    QPixmap redChip;
    QPixmap blueChip;
    QPixmap greenChip;
    QPixmap yellowChip;

    QGraphicsPixmapItem* bigCard1;
    QGraphicsPixmapItem* bigCard2;

    void generateMiddleCard(QString c, float nb, float m);
    void generateBigCard(QString c, QGraphicsPixmapItem* bigCard);


    // Raise effect
    bool isPressed = false;
    bool mised = false;
    int palier = 100;
    int max = 10000000;
    int bigBlind = 100;
    float lastY;
    int mise = palier;
    bool isUrTurn = false;

    QGraphicsTextItem* raiseNbText;
    QTimer *timer;
    QString nameSaveTimer;
    int posSaveTimer;

signals:
    void raiseClicked(int money);
    void callClicked();
    void foldClicked();
    void checkClicked();
public slots:
    void sliderMove(int nb);
    void hideAction();
protected:
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAMEWIDGET_H
