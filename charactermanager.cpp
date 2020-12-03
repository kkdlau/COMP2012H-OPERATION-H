#include "charactermanager.h"
#include "FileParser/fileparser.h"
#include "qdebug.h"

CharacterManager *CharacterManager::instance = nullptr;

CharacterManager::CharacterManager()
{
}

CharacterManager::~CharacterManager()
{
    qDebug()<<"INITIAL "<<characterDatabase.length();
    reset_character_manager();
    instance = nullptr;
    //check leak in instance
}

CharacterManager *CharacterManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new CharacterManager();
    }
    return instance;
}
//Character* character_manager::get_character(QString character_name) const
//{
//    return database.contains(character_name)? database[character_name] : nullptr;
//}

//Character* character_manager::operator[](QString character_name) const
//{
//    return get_character(character_name);
//}

const QList<Character*> CharacterManager::get_all_characters() const
{
    return characterDatabase;
}

bool CharacterManager::is_character_exist(Character* character)
{
    return characterDatabase.contains(character);
}

void CharacterManager::set_map(Map *map)
{
    this->map = map;
}

void CharacterManager::add_character(Character * charData)
{
    if(!is_character_exist(charData) && map != nullptr)
    {
        connect(charData, &Character::deadSignal, this, &CharacterManager::delete_character);
        characterDatabase.append(charData);
        map->addToGroup(charData);
    }
}

void CharacterManager::delete_character(Character* charData)
{
    if(is_character_exist(charData))
    {
        disconnect(charData, &Character::deadSignal, this, &CharacterManager::delete_character);
        map->removeFromGroup(charData);
        delete charData;
        characterDatabase.removeOne(charData);
        qDebug()<<"CHAR LEFT: "<<characterDatabase.length();
        if(characterDatabase.length() <= 1 && !deleting)
        {
            temp_function();
        }
    }
    else
    {
        qCritical()<<"YOU ARE TRYING TO DELETE A NON-EXIST CHARACTER IN THE MANAGER";
    }
}

Character* CharacterManager::generate_random_character()
{
    if(map != nullptr)
    {
        Character* newChar = new Character{5, map};
        add_character(newChar);
        return newChar;

    }
    else
    {
        qCritical()<<"NO MAP DETECTED WHEN CREATING";
        return nullptr;
    }
}
//check tmrw
Enemy* CharacterManager::generate_random_enemy()
{
    if(map != nullptr)
    {
        Enemy* newChar = new Enemy{map};
        add_character(newChar);
        qDebug()<<"NEW CHAR MADE "<<characterDatabase.length();
        return newChar;

    }
    else
    {
        qCritical()<<"NO MAP DETECTED WHEN CREATING";
        return nullptr;
    }
}

void CharacterManager::temp_function()
{
    QMessageBox::aboutQt(nullptr, "HAVE FUN BITCH");
}

void CharacterManager::reset_character_manager()
{
    deleting = true;
    for(int i = characterDatabase.length() - 1; i >= 0; i--)
    {
        delete_character(characterDatabase[i]);
    }
    characterDatabase.clear();
}

bool CharacterManager::check_endgame()
{
    return this->get_all_characters()[0]->get_health() <= 0;
}

