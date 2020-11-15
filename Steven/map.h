#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "qhash.h"
#include "qstring.h"
#include "qvector.h"


class Map //A class that contains the whole map data
{
public:
    Map();
    Map(int, int);
    ~Map();
    //accessor
    const QCharRef operator[] (const int) const; //read only map_grid_data
    int get_row()const;
    int get_col()const;
    //mutator
    void edit_data(const int, QCharRef);//idk if i need this if i have the operator
    void append(QCharRef); //to add new data idk
    QCharRef& operator[](const int); //read and write only map_grid_data

private:
    QVector<QCharRef> map_data;
    int row = -1;
    int col = -1;
};


#endif // MAP_H


