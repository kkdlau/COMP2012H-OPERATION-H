#include "mainwindow.h"
#include "udp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UDP server;
    UDP client;
    QString hi("hji");
    client.say_hello_in_udp(hi);
    w.show();
    return a.exec();
}
