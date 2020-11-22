#include "mapgenerator.h"

MapGenerator::MapGenerator() //technically?
{
    fileParser = new FileParser();
}

MapGenerator::~MapGenerator()
{
    delete fileParser;
}

Map MapGenerator::Generate_map_from_file(QString path)
{
    if(fileParser == nullptr) //error-check if fileparser havent exist for some reason
    {
        fileParser = new FileParser(path);
    }
    else fileParser->read_file_data(path);
    //map generation
    QStringList mapData = fileParser->get_file_data();//error warning
    return Generate_map_from_list(mapData, fileParser->get_length_data(), fileParser->get_height_data());
}

Map MapGenerator::Generate_map_from_list(QStringList map_data, int row , int col)
{
    Map newMap(row, col);
    for(int i = 0; i < map_data.size(); i++)
    {
        for(int j = 0 ; j <  map_data[i].length(); j++)
        {
            newMap.append(map_data[i][j]);
        }
    }
    return newMap;
}
