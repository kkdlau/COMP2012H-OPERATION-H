#include "mainwindow.h"
// START stardust
#include "Network/server.h"
#include "Network/client.h"
// END stardust

#include <QSound>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
