#include "include/core/gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QGraphicsView(parent)
{
    //Accept hover


    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QColor(50, 50, 50));
    //resize(1100, 800);
    setSceneRect(-width()/2., -height()/2., width(), height());
    // Désactivation des scrollbars
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    backplayerPM = QPixmap(":/images/backplayer.png");
    backplayerturnPM = QPixmap(":/images/backplayer2.png");
    QPixmap tablePM = QPixmap(":/images/table.png");
    QGraphicsPixmapItem* table = new QGraphicsPixmapItem(tablePM);
    QGraphicsPixmapItem* backplayerAI = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP1 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP2 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP3 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP4 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP5 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP6 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP7 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP8 = new QGraphicsPixmapItem(backplayerPM);
    QGraphicsPixmapItem* backplayerP9 = new QGraphicsPixmapItem(backplayerPM);
    table->setPos(-0.5 * tablePM.width(), -0.5 * tablePM.height());
    float dispartionH = tablePM.width() / 5.8;
    float dispartionV = tablePM.height() / 4;
    float marginMonsterV = tablePM.height() / 10;
    float marginMonsterH = tablePM.width() / 10;
    backplayerAI->setPos((-0.5 * backplayerPM.width()) + 1*dispartionH,-0.5 * backplayerPM.height() - 2*dispartionV);
    backplayerP1->setPos((-0.5 * backplayerPM.width()) + 2*dispartionH + marginMonsterH,-0.5 * backplayerPM.height() - dispartionV - marginMonsterV);
    backplayerP2->setPos((-0.5 * backplayerPM.width()) + 3*dispartionH,-0.5 * backplayerPM.height());
    backplayerP3->setPos((-0.5 * backplayerPM.width()) + 2*dispartionH + marginMonsterH,-0.5 * backplayerPM.height() + dispartionV + marginMonsterV);
    backplayerP4->setPos((-0.5 * backplayerPM.width()) + 1*dispartionH,-0.5 * backplayerPM.height() + 2* dispartionV);
    backplayerP5->setPos((-0.5 * backplayerPM.width()) - 1*dispartionH,-0.5 * backplayerPM.height() + 2* dispartionV);
    backplayerP6->setPos((-0.5 * backplayerPM.width()) - 2*dispartionH - marginMonsterH,-0.5 * backplayerPM.height() + dispartionV + marginMonsterV);
    backplayerP7->setPos((-0.5 * backplayerPM.width()) - 3*dispartionH,-0.5 * backplayerPM.height());
    backplayerP8->setPos((-0.5 * backplayerPM.width()) - 2*dispartionH - marginMonsterH,-0.5 * backplayerPM.height() - dispartionV - marginMonsterV);
    backplayerP9->setPos((-0.5 * backplayerPM.width()) - 1*dispartionH,-0.5 * backplayerPM.height() - 2*dispartionV);

    backplayers.append(backplayerAI);
    backplayers.append(backplayerP1);
    backplayers.append(backplayerP2);
    backplayers.append(backplayerP3);
    backplayers.append(backplayerP4);
    backplayers.append(backplayerP5);
    backplayers.append(backplayerP6);
    backplayers.append(backplayerP7);
    backplayers.append(backplayerP8);
    backplayers.append(backplayerP9);

    foreach (QGraphicsPixmapItem* backplayer, backplayers) {
        backplayer->setVisible(false);
    }
    backplayerAI->setVisible(true);

    scene->addItem(table);

    redChip  = QPixmap(":/images/red_chip.png");
    redChip = redChip.scaled(20,20);
    blueChip  = QPixmap(":/images/blue_chip.png");
    blueChip = blueChip.scaled(20,20);
    greenChip  = QPixmap(":/images/green_chip.png");
    greenChip = greenChip.scaled(20,20);
    yellowChip  = QPixmap(":/images/yellow_chip.png");
    yellowChip = yellowChip.scaled(20,20);

    for(int i = 0; i < backplayers.size(); i++) {
        scene->addItem(backplayers.at(i));

        playersName.append(new QGraphicsTextItem(""));
        scene->addItem(playersName.at(i));

        playersName.at(i)->setPos(backplayers.at(i)->pos().x() + 10, backplayers.at(i)->pos().y() + 10);
        playersName.at(i)->setVisible(false);
        playersName.at(i)->setDefaultTextColor(Qt::white);


        playersMoney.append(new QGraphicsTextItem(""));
        scene->addItem(playersMoney.at(i));

        playersMoney.at(i)->setPos(backplayers.at(i)->pos().x() + 10, backplayers.at(i)->pos().y() + 30);
        playersMoney.at(i)->setVisible(false);
        playersMoney.at(i)->setDefaultTextColor(Qt::white);

        //Sets
        playersSet.append(new QGraphicsTextItem("10$"));
        playersSet.at(i)->setDefaultTextColor(Qt::black);


        playersChip.append(new QGraphicsPixmapItem(redChip));
        scene->addItem(playersChip.at(i));
        playersChip.at(i)->setVisible(false);
        scene->addItem(playersSet.at(i));
        playersSet.at(i)->setVisible(false);

    }

    //Sets pos
    playersSet.at(0)->setPos(backplayers.at(0)->pos().x()+50, backplayers.at(0)->pos().y() +75);
    playersSet.at(1)->setPos(backplayers.at(1)->pos().x()-30, backplayers.at(1)->pos().y() +60);
    playersSet.at(2)->setPos(backplayers.at(2)->pos().x()-40, backplayers.at(2)->pos().y() +16);
    playersSet.at(3)->setPos(backplayers.at(3)->pos().x()-30, backplayers.at(3)->pos().y() -44);
    playersSet.at(4)->setPos(backplayers.at(4)->pos().x()+50, backplayers.at(4)->pos().y() -65);
    playersSet.at(5)->setPos(backplayers.at(5)->pos().x()+90, backplayers.at(5)->pos().y() -65);
    playersSet.at(6)->setPos(backplayers.at(6)->pos().x()+190, backplayers.at(6)->pos().y() -44);
    playersSet.at(7)->setPos(backplayers.at(7)->pos().x()+170, backplayers.at(7)->pos().y() +16);
    playersSet.at(8)->setPos(backplayers.at(8)->pos().x()+190, backplayers.at(8)->pos().y() +60);
    playersSet.at(9)->setPos(backplayers.at(9)->pos().x()+90, backplayers.at(9)->pos().y() +75);
    playersName.at(0)->setVisible(true);
    playersName.at(0)->setPlainText("AI");
    playersMoney.at(0)->setVisible(true);
    playersMoney.at(0)->setPlainText(moneyToString(1000));

    //Pos chips
    for(int i = 0; i < playersChip.size(); i++){
        playersChip.at(i)->setPos(playersSet.at(i)->pos().x() - 20, playersSet.at(i)->pos().y() + 2);
    }


    //BACK CARDS
    backCardsPM = QPixmap(":/images/cards/back_simple.png");
    backCardsPM = backCardsPM.scaled(QSize(34.55, 52.8));
    backCardsPM2 = backCardsPM.scaled(QSize(34.55, 52.8));
    QRect rect(0, 0, 34.55, 38);
    QRect rect2(0, 0, 34.55, 39);
    backCardsPM = backCardsPM.copy(rect);
    backCardsPM2 = backCardsPM2.copy(rect2);
    for (int i = 0; i < backplayers.size(); i++){
        firstCards.append(new QGraphicsPixmapItem(backCardsPM));
        firstCards.at(i)->setPos(backplayers.at(i)->pos().x() +70, backplayers.at(i)->y() + 10);
        scene->addItem(firstCards.at(i));
        firstCards.at(i)->setVisible(false);
        secondCards.append(new QGraphicsPixmapItem(backCardsPM2));
        secondCards.at(i)->setPos(backplayers.at(i)->pos().x() +88, backplayers.at(i)->y() + 9);
        scene->addItem(secondCards.at(i));
        secondCards.at(i)->setVisible(false);
    }
    firstCards.at(0)->setVisible(true);
    secondCards.at(0)->setVisible(true);


    //all cards PIXMAP;
    backgroundCardPM = QPixmap(":/images/big_cards/back.png");
    coeurPM = QPixmap(":/images/big_cards/coeur.png");
    piquePM = QPixmap(":/images/big_cards/pique.png");
    treflePM = QPixmap(":/images/big_cards/trefle.png");
    carreauPM = QPixmap(":/images/big_cards/carreau.png");

    //Big background
    QPixmap background(":/images/big_cards/back.png");
    bigCard1 = new QGraphicsPixmapItem(background);
    bigCard2 = new QGraphicsPixmapItem(background);
    bigCard1->setPos(scene->width() / 2 - 3* background.width()+ background.width(), scene->height() / 2);
    bigCard2->setPos(scene->width() / 2 - 3* background.width()+ 1.5 * background.width() + 10, bigCard1->pos().y());
    bigCard1->setVisible(false);
    bigCard2->setVisible(false);
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(50);
    effect->setXOffset(-10);
    bigCard2->setGraphicsEffect(effect);
    scene->addItem(bigCard1);
    scene->addItem(bigCard2);


    //Button fold
    QGraphicsDropShadowEffect * effect2 = new QGraphicsDropShadowEffect();
    foldBtn = new QGraphicsRectItem(0,0,120,40);
    foldBtn->setBrush(QBrush(QColor(212, 0,0)));
    foldBtn->setPen(QPen(QColor(212, 0,0)));
    foldBtn->setPos(-250, bigCard1->pos().y() + 50);
    effect2->setColor(Qt::red);
    effect2->setBlurRadius(100);
    effect2->setXOffset(0);
    foldBtn->setGraphicsEffect(effect2);
    scene->addItem(foldBtn);
    foldText = new QGraphicsTextItem("Fold");
    foldText->setDefaultTextColor(Qt::white);
    foldText->setFont(QFont("Arial", 15));
    foldText->setPos(foldBtn->pos().x()+30, foldBtn->pos().y()+3);
    scene->addItem(foldText);
    foldBtn->setVisible(false);
    foldText->setVisible(false);


    //Button call
    QGraphicsDropShadowEffect * effect3 = new QGraphicsDropShadowEffect();
    callBtn = new QGraphicsRectItem(0,0,120,40);
    callBtn->setBrush(QBrush(QColor(212, 0,0)));
    callBtn->setPen(QPen(QColor(212, 0,0)));
    callBtn->setPos(-60, foldBtn->pos().y());
    effect3->setColor(Qt::red);
    effect3->setBlurRadius(100);
    effect3->setXOffset(0);
    callBtn->setGraphicsEffect(effect3);
    scene->addItem(callBtn);
    callText = new QGraphicsTextItem("Call");
    callText->setDefaultTextColor(Qt::white);
    callText->setFont(QFont("Arial", 15));
    callText->setPos(callBtn->pos().x()+33, callBtn->pos().y()+3);
    scene->addItem(callText);
    callBtn->setVisible(false);
    callText->setVisible(false);

    //Button check
    QGraphicsDropShadowEffect * effect5 = new QGraphicsDropShadowEffect();
    checkBtn = new QGraphicsRectItem(0,0,120,40);
    checkBtn->setBrush(QBrush(QColor(212, 0,0)));
    checkBtn->setPen(QPen(QColor(212, 0,0)));
    checkBtn->setPos(-60, foldBtn->pos().y());
    effect5->setColor(Qt::red);
    effect5->setBlurRadius(100);
    effect5->setXOffset(0);
    checkBtn->setGraphicsEffect(effect5);
    scene->addItem(checkBtn);
    checkText = new QGraphicsTextItem("Check");
    checkText->setDefaultTextColor(Qt::white);
    checkText->setFont(QFont("Arial", 15));
    checkText->setPos(callBtn->pos().x()+23, callBtn->pos().y()+3);
    scene->addItem(checkText);
    checkBtn->setVisible(false);
    checkText->setVisible(false);


    //Button raise
    QGraphicsDropShadowEffect * effect4 = new QGraphicsDropShadowEffect();
    raiseBtn = new QGraphicsRectItem(0,0,120,40);
    raiseBtn->setBrush(QBrush(QColor(212, 0,0)));
    raiseBtn->setPen(QPen(QColor(212, 0,0)));
    raiseBtn->setPos(130, foldBtn->pos().y());
    effect4->setColor(Qt::red);
    effect4->setBlurRadius(100);
    effect4->setXOffset(0);
    raiseBtn->setGraphicsEffect(effect4);
    scene->addItem(raiseBtn);
    raiseText = new QGraphicsTextItem("Raise");
    raiseText->setDefaultTextColor(Qt::white);
    raiseText->setFont(QFont("Arial", 15));
    raiseText->setPos(raiseBtn->pos().x()+25, raiseBtn->pos().y()+3);
    scene->addItem(raiseText);
    raiseBtn->setVisible(false);
    raiseText->setVisible(false);

    // Pot
    potText = new QGraphicsTextItem("Pot: 0$");
    potText->setPos(-20, -80);
    scene->addItem(potText);

    //Raise money
    raiseNbText = new QGraphicsTextItem();
    raiseNbText->setPos(callText->pos().x(), raiseBtn->pos().y() + 3);
    raiseNbText->setFont(QFont("Arial", 15));
    raiseNbText->setDefaultTextColor(Qt::white);
    QGraphicsDropShadowEffect * effect6 = new QGraphicsDropShadowEffect();
    effect6->setColor(Qt::red);
    effect6->setBlurRadius(50);
    effect6->setXOffset(0);
    raiseNbText->setGraphicsEffect(effect6);

    scene->addItem(raiseNbText);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
              this, SLOT(hideAction()));
}

/** Méthode pour ajouter un joueur avec son nom et son solde base
 * @brief GameWidget::addPlayer
 * @param name nom du joueur
 * @param money argent du joueur
 */
void GameWidget::addPlayer(QString name, int money, int pos){
//    int i;
//    for (i = 0; i < backplayers.size(); i++){
//        if (!backplayers.at(i)->isVisible()){
//            break;
//        }
//    }
    backplayers.at(pos)->setVisible(true);
    playersName.at(pos)->setVisible(true);
    playersName.at(pos)->setPlainText(name);
    playersMoney.at(pos)->setVisible(true);
    playersMoney.at(pos)->setPlainText(moneyToString(money));

    firstCards.at(pos)->setVisible(true);
    secondCards.at(pos)->setVisible(true);
    nbPlayers ++;
}

void GameWidget::nextRound(int pot){
    setPot(pot);
    for (int i = 0; i < playersChip.size(); i++){
        playersChip.at(i)->setVisible(false);
        playersSet.at(i)->setVisible(false);
        if (pot == 0){
            firstCards.at(i)->setOpacity(1);
            secondCards.at(i)->setOpacity(1);
            backplayers.at(i)->setOpacity(1);
        }
    }

}

/** Méthode qui force un joueur à jouer
 * @brief GameWidget::setPlayerTurn
 * @param turn (entre 0 et 9)
 */
void GameWidget::setPlayerTurn(int turn){
    foreach (QGraphicsPixmapItem* backplayer, backplayers) {
        backplayer->setPixmap(backplayerPM);
    }
    backplayers.at(turn)->setPixmap(backplayerturnPM);
    turnPlayer = turn;
}
/** Méthode pour passer au tour suivant
 * @brief GameWidget::nextTurn
 */
void GameWidget::nextTurn(){
    int newTurnPlayer = turnPlayer+1;
    while(!backplayers.at(newTurnPlayer)->isVisible()) {
        newTurnPlayer++;
        newTurnPlayer = newTurnPlayer % nbPlayers;
    }
    setPlayerTurn(newTurnPlayer);
}

/** Méthode pour afficher les cartes d'un joueur
 * @brief GameWidget::showCards
 * @param c1 carte 1 (exemple: 10D)
 * @param c2 carte 2
 * @param pos position du joueur sur la table
 */
void GameWidget::showCards(QString c1, QString c2, int pos){
    QPixmap card1 = QPixmap(":/images/cards/" + c1 + ".png");
    QPixmap card2 = QPixmap(":/images/cards/" + c2 + ".png");

    card1 = card1.scaled(QSize(34.55, 52.8));
    card2 = card2.scaled(QSize(34.55, 52.8));
    QRect rect(0, 0, 34.55, 38);
    QRect rect2(0, 0, 34.55, 39);
    card1 = card1.copy(rect);
    card2 = card2.copy(rect2);

    firstCards.at(pos)->setPixmap(card1);
    secondCards.at(pos)->setPixmap(card2);
}
/** Méthode pour retourner toutes les cartes de tous les joueurs
 * @brief GameWidget::hideAllCards
 */
void GameWidget::hideAllCards(){
    for (int i = 0; i < firstCards.size(); i ++){
        firstCards.at(i)->setPixmap(backCardsPM);
        secondCards.at(i)->setPixmap(backCardsPM2);

        //reset opacity
        firstCards.at(i)->setOpacity(1);
        secondCards.at(i)->setOpacity(1);
        backplayers.at(i)->setOpacity(1);
    }
}

/** Méthode pour modifier les deux grande cartes affichées en bas à droite
 * @brief GameWidget::setBigCards
 * @param c1 carte 1 (exemple: 10D)
 * @param c2 carte 2
 */
void GameWidget::setBigCards(QString c1, QString c2){
    generateBigCard(c1, bigCard1);
    generateBigCard(c2, bigCard2);
}

/** Méthode pour afficher le flop
 * @brief GameWidget::setFlop
 * @param c1 carte 1 (exemple: 10D)
 * @param c2 carte 2
 * @param c3 carte 3
 */
void GameWidget::setFlop(QString c1, QString c2, QString c3){
    generateMiddleCard(c1, 0, 0);
    generateMiddleCard(c2, 1, 15);
    generateMiddleCard(c3, 2, 30);
}
/** Méthode pour afficher le turn (4ème carte)
 * @brief GameWidget::setTurn
 * @param c carte
 */
void GameWidget::setTurn(QString c){
     generateMiddleCard(c, 3, 55);
}
/** Méthode pour afficher le river (5ème carte)
 * @brief GameWidget::setRiver
 * @param c carte
 */
void GameWidget::setRiver(QString c){
    generateMiddleCard(c, 4, 70);
}
/** Méthode pour générer et afficher les cartes au milieu
 * @brief GameWidget::generateMiddleCard
 * @param c la carte
 * @param nb la position
 * @param m la marge
 */
void GameWidget::generateMiddleCard(QString c, float nb, float m){
    QPixmap backgroundPMscaled = backgroundCardPM.scaled(QSize(51.8,79.2));
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(backgroundPMscaled);
    background->setPos(-backgroundPMscaled.width()/2 - 2.5*(backgroundPMscaled.width() + 10) + nb*backgroundPMscaled.width() + m, -backgroundPMscaled.height()/2 - 10);
    scene->addItem(background);
    QPixmap cardTypePM = QPixmap(":/images/big_cards/" + c[c.size()-1] + "2.png");
    cardTypePM = cardTypePM.scaled(QSize(22, 22));
    QGraphicsPixmapItem* cardTypeItem = new QGraphicsPixmapItem(cardTypePM);
    cardTypeItem->setPos(background->pos().x()+3, background->pos().y()+30);
    scene->addItem(cardTypeItem);
    QGraphicsTextItem* letter = new QGraphicsTextItem(c[0] + "");
    QFont qFont("Arial", 15);
    qFont.setLetterSpacing(QFont::AbsoluteSpacing, -5);
    QColor color(Qt::black);

    if (c[c.size()-1] + "" == "H" || c[c.size()-1] == "D"){
        color.setRgb(212, 0, 0);
    }
    letter->setDefaultTextColor(color);
    letter->setFont(qFont);
    letter->setPos(background->pos().x()+3, background->pos().y());
    if (c[0] +""== "1"){
        letter->setPlainText("10");
        letter->setPos(background->pos().x(), background->pos().y());
    }
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(25);
    //effect->setXOffset(-10);
    background->setGraphicsEffect(effect);
    scene->addItem(letter);
}

/** Méthode pour générer les grandes cartes en bas à droite
 * @brief GameWidget::generateBigCard
 * @param c
 * @param bigCard
 */
void GameWidget::generateBigCard(QString c, QGraphicsPixmapItem* bigCard){

    bigCard->setVisible(true);
    QPixmap cardTypePM = QPixmap(":/images/big_cards/" + c[c.size()-1] + ".png");
    QGraphicsPixmapItem* cardTypeItem = new QGraphicsPixmapItem(cardTypePM);
    cardTypeItem->setPos(bigCard->pos().x()+6, bigCard->pos().y()+50);
    scene->addItem(cardTypeItem);
    QGraphicsTextItem* letter = new QGraphicsTextItem(c[0] + "");
    QFont qFont("Arial", 25);
    qFont.setLetterSpacing(QFont::AbsoluteSpacing, -5);
    QColor color(Qt::black);;

    if (c[c.size()-1] + "" == "H" || c[c.size()-1] == "D"){
        color.setRgb(212, 0, 0);
    }
    letter->setDefaultTextColor(color);
    letter->setFont(qFont);
    letter->setPos(bigCard->pos().x()+3, bigCard->pos().y());
    if (c[0] +""== "1"){
        letter->setPlainText("10");
        letter->setPos(bigCard->pos().x(), bigCard->pos().y());
    }
    scene->addItem(letter);
}

/** Méthode pour coucher un joueur
 * @brief GameWidget::foldPlayer
 * @param pos position du joueur sur la table
 */
void GameWidget::foldPlayer(int pos){
    firstCards.at(pos)->setOpacity(0.1);
    secondCards.at(pos)->setOpacity(0.1);
    backplayers.at(pos)->setOpacity(0.3);
    nameSaveTimer = playersName.at(pos)->toPlainText();
    posSaveTimer = pos;
//    playersName.at(pos)->setPlainText("FOLD");
//    timer->start(4000);
}
/** Méthode pour modifier l'argent qu'un joueur a
 * @brief GameWidget::setPlayerMoney
 * @param money argent du joueur
 * @param pos position du joueur sur la table
 */
void GameWidget::setPlayerMoney(int money, int pos){
    playersMoney.at(pos)->setPlainText(QString::number(money) + "$");
}
/** Méthode pour supprimer un joueur de la table
 * @brief GameWidget::removePlayer
 * @param pos
 */
void GameWidget::removePlayer(int pos){
    backplayers.at(pos)->setVisible(false);
    firstCards.at(pos)->setVisible(false);
    secondCards.at(pos)->setVisible(false);
    playersName.at(pos)->setVisible(false);
    playersMoney.at(pos)->setVisible(false);
    nbPlayers --;
}
void GameWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    if(items(mouseEvent->pos()).contains(callBtn))
        callBtn->setBrush(QBrush(Qt::black));
    else
        callBtn->setBrush(QBrush(QColor(212, 0,0)));
    if(items(mouseEvent->pos()).contains(foldBtn))
        foldBtn->setBrush(QBrush(Qt::black));
    else
        foldBtn->setBrush(QBrush(QColor(212, 0,0)));
    if(items(mouseEvent->pos()).contains(raiseBtn))
        raiseBtn->setBrush(QBrush(Qt::black));
    else
        raiseBtn->setBrush(QBrush(QColor(212, 0,0)));
    if(items(mouseEvent->pos()).contains(checkBtn))
        checkBtn->setBrush(QBrush(Qt::black));
    else
        checkBtn->setBrush(QBrush(QColor(212, 0,0)));

    if (isPressed){
        if (lastY - mouseEvent->pos().y() > 10){
            if (mise < max){
                if (mise > max-palier){
                    mise = max;
                }
                if (mise == palier *10){
                    palier *= 10;
                }

                mise += palier;

            }

            lastY = mouseEvent->pos().y();
        }
        if (lastY - mouseEvent->pos().y() < -10){
            if (mise > 0){
                if (mise == palier){
                    palier /= 10;
                }
                mise -= palier;
            }
            if (mise < bigBlind) {
                palier = bigBlind;
                mise = 0;
            }
            lastY = mouseEvent->pos().y();
        }
        raiseNbText->setPlainText(moneyToString(mise));
    }

}

/** Méthode pour afficher les boutons: fold, raise et call
 * @brief GameWidget::showCallBtn
 */
void GameWidget::showCallBtn(){
    hideAllBtn();
    foldBtn->setVisible(true);
    foldText->setVisible(true);
    callBtn->setVisible(true);
    callText->setVisible(true);
    raiseBtn->setVisible(true);
    raiseText->setVisible(true);
}
/** Méthode pour afficher les boutons: fold, raise et check
 * @brief GameWidget::showCheckBtn
 */
void GameWidget::showCheckBtn(){
    hideAllBtn();
    foldBtn->setVisible(true);
    foldText->setVisible(true);
    checkBtn->setVisible(true);
    checkText->setVisible(true);
    raiseBtn->setVisible(true);
    raiseText->setVisible(true);
}
/** méthode pour cacher tous les boutons
 * @brief GameWidget::hideAllBtn
 */
void GameWidget::hideAllBtn(){
    foldBtn->setVisible(false);
    foldText->setVisible(false);
    callBtn->setVisible(false);
    callText->setVisible(false);
    checkBtn->setVisible(false);
    checkText->setVisible(false);
    raiseBtn->setVisible(false);
    raiseText->setVisible(false);
}
/** méthode pour modifier le montant du pot
 * @brief GameWidget::setPot
 * @param money argent du pot
 */
void GameWidget::setPot(int money){
    potText->setPlainText("pot: " + moneyToString(money));

}

/** méthode pour afficher la mise d'un joueur
 * @brief GameWidget::setPlayerSet
 * @param pos position du joueur sur la table (0 à 9)
 * @param money argent du joueur
 */
void GameWidget::setPlayerSet(int pos, int money){
    playersSet.at(pos)->setPlainText(moneyToString(money));
    playersChip.at(pos)->setVisible(true);
    playersSet.at(pos)->setVisible(true);

    if (money <= 100)
        playersChip.at(pos)->setPixmap(redChip);
    else if (money <= 200)
        playersChip.at(pos)->setPixmap(blueChip);
    else if (money <= 1000)
        playersChip.at(pos)->setPixmap(greenChip);
    else
        playersChip.at(pos)->setPixmap(yellowChip);
}
/** Supprimer le set d'un joueur
 * @brief GameWidget::removePlayerSet
 * @param pos position du joueur sur la table
 */
void GameWidget::removePlayerSet(int pos){
    playersChip.at(pos)->setVisible(false);
    playersSet.at(pos)->setVisible(false);
}
void GameWidget::mousePressEvent(QMouseEvent *event)
{
    if(items(event->pos()).contains(raiseBtn)){
        foldBtn->setVisible(false);
        foldText->setVisible(false);
        callBtn->setVisible(false);
        callText->setVisible(false);
        checkBtn->setVisible(false);
        checkText->setVisible(false);

        isPressed = true;
        lastY = event->pos().y();
        raiseNbText->setVisible(true);
        raiseNbText->setPlainText(moneyToString(mise));
        if (mised){
            hideAllBtn();
            qDebug() << "confirm mise:" << mise;
            raiseNbText->setVisible(false);
            emit raiseClicked(mise);
        }
    } else {
        if (mised) {
            raiseNbText->setVisible(false);
            mised = false;
            mise = 0;
            if (isUrTurn)
                showCheckBtn();
        }
    }
    if(items(event->pos()).contains(callBtn)){
        emit callClicked();
    }
    if(items(event->pos()).contains(foldBtn)){
        emit foldClicked();
    }
    if(items(event->pos()).contains(checkBtn)){
        emit checkClicked();
    }

}
void GameWidget::mouseReleaseEvent(QMouseEvent *event){
    if (isPressed){
        isPressed = false;
        if (mise == 0){ // Si la mise est à 0 -> réinitialisation
            raiseNbText->setVisible(false);
            mised = false;
            mise = 0;
            showCheckBtn();
        } else {
            mised = true;
        }

    }
}

void GameWidget::sliderMove(int nb){
    qDebug() << nb;
}


/** méthode pour convertir un montant en string (1000 -> 1k)
 * @brief GameWidget::moneyToString
 * @param money
 * @return
 */
QString GameWidget::moneyToString(int money){
    if (money >= 1000 && money < 1000000) {
        int temp = money / 100;
        float result = (float)temp / 10;
            return QString::number(result) + "k $";
    }
    if (money >= 1000000) {
        int temp = money / 100000;
        float result = (float)temp / 10;
            return QString::number(result) + "m $";
    }
    return QString::number(money) + "$";
}

void GameWidget::hideAction(){
    playersName.at(posSaveTimer)->setPlainText(nameSaveTimer);
    timer->stop();
}
void GameWidget::check(int pos){
    nameSaveTimer = playersName.at(pos)->toPlainText();
    posSaveTimer = pos;
    playersName.at(pos)->setPlainText("CHECK");
    timer->start(4000);
}
void GameWidget::call(int pos){
    nameSaveTimer = playersName.at(pos)->toPlainText();
    posSaveTimer = pos;
    playersName.at(pos)->setPlainText("CALL");
    timer->start(4000);
}
void GameWidget::raise(int pos){
    nameSaveTimer = playersName.at(pos)->toPlainText();
    posSaveTimer = pos;
    playersName.at(pos)->setPlainText("RAISE");
    timer->start(4000);
}
