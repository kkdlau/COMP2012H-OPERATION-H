#include "fileparser.h"
#include "QtDebug"
#include "qtextstream.h"
#include "qcoreapplication.h"
FileParser::FileParser()
{

}

FileParser::FileParser(const QString fileName) //constructor that instantly produce the text
{
    read_file_data(fileName);
}

FileParser::~FileParser()
{
}

void FileParser::read_file_data(const QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    if(if_contains_data()) file_data.clear();
    QTextStream in(&file);
       while (!in.atEnd()) {
           QString line = in.readLine();
           file_data.append(line);
       }
}
bool FileParser::if_contains_data() const
{
    return !file_data.isEmpty();
}

QStringList FileParser::get_file_data() const //returns a copy
{
    QStringList null;
    if(if_contains_data()) return file_data;
    else return null;
}

int FileParser::get_height_data() const
{
    return if_contains_data() ? file_data.size() : -1;
}

int FileParser::get_length_data() const
{
    if(if_contains_data())
    {
        int initial_length = file_data[0].length();
        int height = get_height_data();
        for(int i = 0; i < height; i++)
        {
            if(file_data[i].length() != initial_length)
            {
                return -1 ;//indicate that there is no similar length
            }
        }
        return initial_length;
    }
    return -2 ;//indicate null
}
