#include <QCoreApplication>
#include "include/gameengine.h"
#include <iostream>
#include <QDebug>

using namespace omp;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameEngine engine;
    engine.dummyGame();
    return a.exec();
}
