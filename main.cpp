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

//    QSound::play(":assets/footsteps.wav");  // uncomment if u want to hear
    w.show();
    return a.exec();
}
