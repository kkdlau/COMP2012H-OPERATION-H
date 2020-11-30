#include "mainwindow.h"
#include "Network/udp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UDP client;
    client.read_from_udp();
    w.show();
    return a.exec();
}
