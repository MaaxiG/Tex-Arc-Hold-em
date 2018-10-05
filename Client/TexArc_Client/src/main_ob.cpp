#include <QCoreApplication>
#include <clientnetwork.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ClientNetwork n;
    return a.exec();
}
