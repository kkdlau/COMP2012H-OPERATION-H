#ifndef GRIDINFO_H
#define GRIDINFO_H
#include <QVector>
#include <QString>
#include <QGraphicsRectItem>
#include "../NewWeapon/weapon.h"

#include "qpoint.h"

class GridInfo
{
private:
    int height;
    const int x;
    const int y;
    QGraphicsItemGroup* renderlayer{nullptr};
    Weapon* weapon{nullptr};

public:
    GridInfo(int height, int x, int y,  QGraphicsItemGroup* belongLayer);
    GridInfo(const GridInfo& grid);

    /**
     * @brief getHeight get the height of grid
     * @return height
     */
    int getHeight() const;

    /**
     * @brief heightDiff calculate the height differences between two grids
     * @param grid the grid to compare
     * @return absolute value of height differences
     */
    int heightDiff(const GridInfo& grid) const;

    /**
     * @brief setHeight set the height of grid, it affects the height system
     * @param height height to set, usually ranging from 0 (ground) ~ 15 (Big Wood Box)
     */
    void setHeight(const int height);

    /**
     * @brief operator -: calculate the height differences between two grids
     *
     * @param leftOperand grid for left operand
     * @param rightOperand grid for right operand
     *
     * @return absulote value of height differences
     */
    friend int operator-(const GridInfo& leftOperand, const GridInfo& rightOperand) {
        return leftOperand.heightDiff(rightOperand);
    }

    /**
     * @brief toString get the string representation of GridInfo object
     * @return string representation
     */
    QString toString() const;

    /**
     * @brief getPos Get the position of Grid
     * @return the position
     */
    QPoint getPos() const;

    /**
     * @brief putWeapon Put the weapon on ground
     * @param data
     */
    void putWeapon(Weapon* data);

    /**
     * @brief isWeaponOnGround Check if the grid consist of weapon
     * @return true if the grid consist of weapon
     */
    bool isWeaponOnGround() const;

    /**
     * @brief removeWeapon Remove the weapon from grid.
     */
    void removeWeapon();

    /**
     * @brief popWeapon Pop the Weapon from grid. It transform the ownership of owner.
     * @return weapon pointer
     */
    Weapon* popWeapon();
};

#endif // GRIDINFO_H
