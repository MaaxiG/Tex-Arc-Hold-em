#include <QCoreApplication>
#include <include\network\masternetwork.h>
#include "include/network/dbhandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MasterNetwork m;
    return a.exec();
}

