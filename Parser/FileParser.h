#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "qfile.h"
#include "qstring.h"
#include "qstringlist.h"

class FileParser
{
public:
    /**
     * @brief Construction for FileParser. file_data will be null
     */
    FileParser();
    /**
     * @brief Construction for FileParser with pathstring. When created, it will read and create QStringList data
     * @param path for file;
     */
    FileParser(const QString path);
    /**
      *@brief Destructor for FileParser. Destroy the file_data
      * */
    ~FileParser();
    //accessor
    /**
     * @brief check if file_data contains data
     * @return check via size + nullptr
     */
    bool if_contains_data()const;
    /**
     * @brief Return file_data if file_data contains data
     * @return  QStringList
     */
    QStringList get_file_data()const;
    /**
     * @brief Return data height(Row) if file_data contains data
     * @return int
     */
    int get_height_data() const;
    /**
     * @brief Return data length(Column) if file_data contains data
     * @return int
     */
    int get_length_data() const;
    //mutator
    /**
     * @brief Read and parsing textfile from the path file
     * @param path
     */
    void read_file_data(const QString path);
private:
    QStringList *file_data = new QStringList();
};

#endif // FILEPARSER_H
