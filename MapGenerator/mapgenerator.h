#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "map.h"
#include "Parser/FileParser.h"

class MapGenerator
{
public:
    MapGenerator();
    MapGenerator(QString path);
    ~MapGenerator();
    Map Generate_map_from_file(QString path);
    Map Generate_map_from_list(QStringList map_data, int row, int col);
private:
    FileParser *fileParser;
};

#endif // MAPGENERATOR_H
