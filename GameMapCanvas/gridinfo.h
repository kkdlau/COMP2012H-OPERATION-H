#ifndef GRIDINFO_H
#define GRIDINFO_H
#include <QVector>
#include <QString>
#include "Weapons/weapon.h"

class GridInfo
{
private:
    float height;
    const unsigned int x;
    const unsigned int y;
//    QVector<Weapon> weapons;
public:
    GridInfo(float height, unsigned int x, unsigned int y /*, QVector<Weapon>&& weapons*/);

    float getHeight() const;
    void setHeight(const float height);

    QString toString() const;

//    const QVector<Weapon>& getWeapons() const;
//    QVector<Weapon>& getWeapons();
};

#endif // GRIDINFO_H
