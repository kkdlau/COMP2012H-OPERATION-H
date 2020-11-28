#ifndef GRIDINFO_H
#define GRIDINFO_H
#include <QVector>
#include <QString>
#include <QGraphicsRectItem>

class GridInfo
{
private:
    int height;
    const int x;
    const int y;
    QGraphicsRectItem* collidingRect; // this uses for checking collision

    void updateCollidingRect();

public:
    GridInfo(int height, int x, int y);
    GridInfo(const GridInfo& grid);

    /**
     * @brief getHeight get the height of grid
     * @return height
     */
    int getHeight() const;

    QGraphicsRectItem* getCollidingRect() const;

    void registerCollidingRect(QGraphicsRectItem* rect);

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
};

#endif // GRIDINFO_H
