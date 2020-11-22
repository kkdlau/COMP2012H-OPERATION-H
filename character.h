#ifndef CHARACTER_H
#define CHARACTER_H
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"

class Character : public QGraphicsItem
{
public:
    Character(QString, int);
    Character(const QStringList);

    static Character* createThirdParty();
    ~Character();
    QString get_name() const;
    int get_health() const;
    bool is_alive() const;
    void set_name(QString name);
    void set_health(int health);

private:
    QString characterName;
    int characterHealth;
};

#endif // CHARACTER_H
