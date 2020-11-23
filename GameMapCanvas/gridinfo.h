#ifndef GRIDINFO_H
#define GRIDINFO_H
#include <QVector>
#include <QString>

class GridInfo
{
private:
    int height;
    const int x;
    const int y;
//    QVector<Weapon> weapons;
public:
    GridInfo(int height, int x, int y /*, QVector<Weapon>&& weapons*/);

    int getHeight() const;
    int heightDiff(const GridInfo& grid) const;
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
        return abs(leftOperand.height - rightOperand.height);
    }

    QString toString() const;

//    const QVector<Weapon>& getWeapons() const;
//    QVector<Weapon>& getWeapons();
};

#endif // GRIDINFO_H
