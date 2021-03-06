#include "charactermanager.h"
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
        connect(charData, &Character::deadSignal, this, &CharacterManager::dispose_from_map);
        characterDatabase.append(charData);
        map->addToGroup(charData);
    }
}

void CharacterManager::delete_character(Character* charData)
{
    if(is_character_exist(charData))
    {

        delete charData;
        characterDatabase.removeOne(charData);
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
        Character* newChar = new Character{charType::PLAYER,5, map};
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
        for(int i = 0; i < characterDatabase.length();i++)
        {
            if(characterDatabase[i]->getCharacterType() == charType::PLAYER && characterDatabase[i]->is_alive())
            {
                newChar->setDestination(characterDatabase[i]);
            }
        }
        qDebug()<<"NEW CHAR MADE "<<characterDatabase.length();
        return newChar;

    }
    else
    {
        qCritical()<<"NO MAP DETECTED WHEN CREATING";
        return nullptr;
    }
}

void CharacterManager::show_end_game()
{
    QMessageBox::information(nullptr, "Information", "Game Ends");
}

void CharacterManager::dispose_from_map(Character *charData)
{
    if(is_character_exist(charData))
    {
        disconnect(charData, &Character::deadSignal, this, &CharacterManager::dispose_from_map);
        charData->dequipWeapon();
        map->removeFromGroup(charData);
        charData->setVisible(false);
        qDebug()<<"CHAR LEFT: "<<characterDatabase.length();
        int isThereCharacter = false;
        for(int i = 0; i < characterDatabase.length(); i++)
        {
            if(characterDatabase[i]->getCharacterType() == charType::PLAYER && characterDatabase[i]->is_alive())
            {
                isThereCharacter = true;
            }
        }
        if(!isThereCharacter && isOver == false)
        {
            isOver = true;
            show_end_game();
            //TODO: Insert endgame

        }
    }
    else
    {
        qCritical()<<"YOU ARE TRYING TO DELETE A NON-EXIST CHARACTER IN THE MANAGER";
    }
}

void CharacterManager::reset_character_manager()
{
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

