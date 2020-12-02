// DO NOT CHANGE THIS FILE
// This is the new server
// being made by Stardust

#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include "charactermanager.h"
#include "character.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLocalServer;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

private slots:
//    void sendAction();  // assume we only send action commands now
    void sendGamestats();

private:
    QLocalServer *server;
//    QStringList actions;
    QStringList gamestats;
    QString generateGamestats(Character* character);
};

#endif // SERVER_H
