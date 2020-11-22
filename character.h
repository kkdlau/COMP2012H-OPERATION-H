#ifndef CHARACTER_H
#define CHARACTER_H
#include "qstring.h"
#include "qstringlist.h"

class character
{
public:
    character(QString, int, int);
    character(const QStringList);

    static character* createThirdParty();
    ~character();
    QString get_name() const;
    int get_attack() const;
private:
    QString playerName;
    int attack;
    int health;
};

#endif // CHARACTER_H
