#include "include/core/ai.h"
#include <QDebug>

AI::AI(quint64 money) : Player("bank", money, "ai")
{
    st = new Stats();
    nbPlayers = 2;
    srand(time(nullptr));
}

QString AI::playPreFlop(){
    PlayerAction action = PlayerAction::Fold;
    int raise = 0;
    int maxPercent = 70;
    if (nbPlayers > 4){
        maxPercent = 65;
    }
    if (nbPlayers > 7){
        maxPercent = 60;
    }
    float probaWin = st->getProbaPreflop(playerGame->cards.at(0)->getCardName() + playerGame->cards.at(1)->getCardName(), sameColor, nbPlayers);
    qDebug() << probaWin << "%";
    if (probaWin >= maxPercent){
        if (shouldI(40)) {// Si il faut augmenter la mise
            action = PlayerAction::Bet;
            raise = randomRaise(2, 4) * mise;
        }else{
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (probaWin >= maxPercent-20 && mise <= bigBlind * 2.5){
        if (shouldI(15)){ // Si il faut augmenter la mise
            action = PlayerAction::Bet;
            raise = randomRaise(2, 3) * mise;
        }else{
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (probaWin >= maxPercent-40 && mise <= bigBlind * 1.2){
        if (shouldI(10)){
            action = PlayerAction::Bet;
            raise = 2 * mise;
        }if (shouldI(95)){
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (probaWin >= maxPercent-50 && mise == bigBlind) {
        if (shouldI(50)){// Si il faut suivre
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (probaWin >= maxPercent-55 && shouldI(20) && mise == bigBlind){
        action = PlayerAction::Call;
        raise = mise;
    }
    if (shouldI(2)){ // bluff ultime
        action = PlayerAction::Bet;
        raise = randomRaise(2, 6) * mise;
    }
    if (action == PlayerAction::Call && mise == maMise)
        action = PlayerAction::Check;
    return QString::number(action) + " " + QString::number(raise) + "$";
}



QString AI::playAfterFlop(){

    PlayerAction action = PlayerAction::Fold;
    int raise = 0;
    omp::Hand hand = omp::Hand::empty();
    omp::HandEvaluator evaluator;

    for(Card *card : openCards)
        hand += card->getCardID();
    int evaluationFlop = evaluator.evaluate(hand);
    for(Card *card : playerGame->cards)
        hand += card->getCardID();
    int evaluation = evaluator.evaluate(hand);
    int diff = evaluation - evaluationFlop;
    int max = 9*4096;
    float amelioration = (float)diff / (float)max;

    float maxMoneyTemp = (bigBlind*amelioration*1000*amelioration * evaluation / max);
    float maxMoney = qRound(maxMoneyTemp /10) * 10;



    qDebug() << "MaxMoneyIWillPutPussy:"<< maxMoney << "$";

    if (maxMoney == mise){
        if (shouldI(3)) {
            action = PlayerAction::Bet;
            raise = 2*mise;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    } else if (maxMoney == 0 && mise == bigBlind){
        if (shouldI(10)){
            action = PlayerAction::Call;
            raise = mise;
        } else {
            if (maMise == mise)
                action = PlayerAction::Check;
            else
                action = PlayerAction::Fold;
            raise = 0;
        }
    }

    if (maxMoney > mise * 5){
        if (shouldI(90)){
            action = PlayerAction::Bet;
            raise = randomRaise(2,5) * mise;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (maxMoney > mise * 4){
        if (shouldI(80)) {
            action = PlayerAction::Bet;
            raise = randomRaise(2,5) * mise;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (maxMoney > mise * 3){
        if (shouldI(70)) {
            action = PlayerAction::Bet;
            raise = randomRaise(2,4) * mise;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (maxMoney > mise * 2){
        if (shouldI(50)) {
            action = PlayerAction::Bet;
            raise = randomRaise(2,3) * mise;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    }
    if (maxMoney < mise){
        if(shouldI(97)) {
            if (maMise == mise)
                action = PlayerAction::Check;
            else
                action = PlayerAction::Fold;
            raise = 0;
        } else {
            action = PlayerAction::Call;
            raise = mise;
        }
    }

    if (action == PlayerAction::Call && mise == maMise)
        action = PlayerAction::Check;

    //MANQUE UN EMIT ICI
    return QString::number(action) + " " + QString::number(raise) + "$";
}

QString AI::playAfterTurn(){
    return playPreFlop();
}
QString AI::playAfterRiver(){
    return playPreFlop();
}

QString AI::play(){
    switch(openCards.size()) {

    case 3:
        return playAfterFlop();
        break;
    case 4:
        return playAfterTurn();
        break;
    case 5:
        return playAfterRiver();
        break;
    default:
        return playPreFlop();
        break;
    }
}

bool AI::shouldI(int chance){

    int randNum = rand()%(101);
    qDebug() << randNum;
    if (randNum <= chance){
        return true;
    }
    return false;
}
int AI::randomRaise(int min, int max){
    int randRaise =  rand()%(max-min + 1) + min;
    if (randRaise > getMoney()){
        return getMoney();
    }
    return randRaise;

}
