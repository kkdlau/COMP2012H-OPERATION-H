#include "charactermanager.h"

character_manager *character_manager::instance = nullptr;

character_manager::character_manager()
{
}

character_manager::~character_manager()
{
    reset_character_manager();
}

character_manager *character_manager::get_instance()
{
    if(instance == nullptr)
    {
        instance = new character_manager();
    }
    return instance;
}
Character* character_manager::get_character(QString character_name) const
{
    return database.contains(character_name)? database[character_name] : nullptr;
}

Character* character_manager::operator[](QString character_name) const
{
    return get_character(character_name);
}

const QList<Character*> character_manager::get_all_characters() const
{
    return database.values();
}

bool character_manager::is_character_exist(QString name)
{
    return database.contains(name);
}

void character_manager::add_character(Character * charData)
{
    if(!is_character_exist(charData->get_name()))
    {
        database.insert(charData->get_name(), charData);
    }
}

void character_manager::delete_character(QString charName)
{
    if(is_character_exist(charName))
    {
        delete database[charName];
        database.remove(charName);
    }
}

void character_manager::reset_character_manager()
{
    QStringList key = database.keys();
    for(int i = 0; i < key.count(); i++)
    {
        delete_character(key[i]);
    }
}
