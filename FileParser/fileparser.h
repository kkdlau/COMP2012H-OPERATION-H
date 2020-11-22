#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "qfile.h"
#include "qstring.h"
#include "qstringlist.h"

class FileParser
{
public:
    FileParser();
    FileParser(const QString path);
    ~FileParser();
    //accessor
    bool if_contains_data()const;
    QStringList get_file_data()const;
    int get_height_data() const;
    int get_length_data() const;
    //mutator
    void read_file_data(const QString path);
private:
    QStringList file_data;
};
#endif // FILEPARSER_H
