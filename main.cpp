#include "mainwindow.h"
#include "Network/udp.h"
// START stardust
#include "Network/server.h"
#include "Network/client.h"
// END stardust

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    UDP client;
//    client.read_from_udp();
    w.show();
    // START stardust
    Server server;
    server.show();
    Client client;
    client.show();
    // END stardust
    return a.exec();
}
