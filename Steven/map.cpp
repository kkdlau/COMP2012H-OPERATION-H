#include "map.h"
#include "qdebug.h"
Map::Map(){};
Map::Map(int row, int col): row(row), col(col){}
Map::~Map(){};
//accessor
const QCharRef Map::operator[] (const int index) const
{
    return map_data[index];
}
//mutator
void Map::edit_data(const int index, QCharRef newData) //idk if i still need this
{
    map_data[index] = newData;
}

QCharRef& Map::operator[](const int index)
{
    return map_data[index];
}

void Map::append(QCharRef value)
{
    map_data.append(value);
    qDebug()<<"the map inserted " <<  value << "with index of " << map_data.size() - 1;
}

int Map::get_col() const
{
    return col;
}

int Map::get_row() const
{
    return row;
}
