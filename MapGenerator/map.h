#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "qhash.h"
#include "qstring.h"
#include "qvector.h"


class Map //A class that contains the whole map data
{
public:
    /**
     * @brief Constructor for Map. row, col and map_data have not been initialized
     */
    Map();
    Map(int, int);
    ~Map();
    //accessor
    /**
     * @brief return const QCharRef for reference in specific index (row*col_grid + col);
     * @return QCharRef of map_data in specific row & column
     */
    const QCharRef operator[] (const int) const; //read only map_grid_data
    /**
     * @brief get_row returns the map_data row
     * @return int
     */
    int get_row()const;
    /**
     * @brief get_col returns the map_data col
     * @return int
     */
    int get_col()const;
    /**
     * @brief get_index help to generate index based on the row and col data
     * @return index of map_data
     */
    int get_index(int, int)const;
    //mutator
    /**
     * @brief edit the map_data with a specific index
     */
    void edit_data(const int, QCharRef);//idk if i need this if i have the operator
    /**
     * @brief add the map_data
     */
    void append(QCharRef); //to add new data idk
    /**
     * @brief returns a reference QCharRef for read and editing purposes
     * @return QCharRef&
     */
    QCharRef& operator[](const int); //read and write only map_grid_data

private:
    QVector<QCharRef> map_data;
    int row = -1;
    int col = -1;
};


#endif // MAP_H


