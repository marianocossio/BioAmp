#include "system.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    System system;

    system.run();

    return a.exec();
}
