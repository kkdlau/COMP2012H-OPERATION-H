#ifndef CHARACTER_H
#define CHARACTER_H
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"

class Character : public QGraphicsItem
{
public:
    Character(QString, int, int);
    Character(const QStringList);

    static Character* createThirdParty();
    ~Character();
    QString get_name() const;
    int get_health() const;
    void set_name();
    void set_health();

private:
    QString playerName;
    int health;
};

#endif // CHARACTER_H
