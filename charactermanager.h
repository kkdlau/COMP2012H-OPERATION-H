#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H
#include "character.h"
#include "enemy.h"
#include "qhash.h"
#include "qobject.h"
#include "GameScene/map.h"
#include <QMessageBox>

class CharacterManager : public QObject
{
public:
    /**
     * The character_manager is an singleton class repsonsible for recording
     * all the character initialized in the game. The purpose is to improve
     * accessibility of other functions to access the database (aka the character
     * list) on the game
     */

    /**
     * Constructor for character_manager()
     */
    CharacterManager();
    /**
      *Destructor for chracter_manager(), deleting
      * any *character in the database
      */
    ~CharacterManager();
    /**
     * @brief get specified character in database, return null if character doesnt exist;
     * @param character_name
     * @return character*\/ nullptr if character does not exist
     */
    //Character* get_character() const; ->redundant
    /**
     * @brief operator [] to simplify get_character function
     * @return character*
     */
    //Character* operator[](QString)const; ->redundant
    /**
     * @brief get_all_characters return a constant list of all character
     * @return const QList<Character*>
     */
    const QList<Character*> get_all_characters()const;
    /**
     * @brief Prevent ability to create another instance via copy constructor
     */
    CharacterManager(CharacterManager*) = delete;
    /**
     * @brief prevent ability to create another instance via memberwise assignment
     * @return
     */
    Character* operator=(CharacterManager*) = delete;
    /**
     * @brief check if character is in the database
     * @return bool
     */
    bool is_character_exist(Character*);
    /**
     * @brief add *character to the database
     */
    void add_character(Character*);
    /**
     * @brief delete specified character in database
     */
    void delete_character(Character*);
    /**
     * @brief delete all character in the database
     */
    void reset_character_manager();
    /**
     * @brief return an instance of character_manager.
     * @return *character_manager
     */
    static CharacterManager *get_instance();
    Character* generate_random_character();
    Enemy* generate_random_enemy();
    //delete tmrw
    void temp_function();
    void set_map(Map* map);
private:
    /**
    * @brief static variable to hold character_manager
    */
   static CharacterManager *instance;
   /**
    * @brief Hashmap to save the characters.
    */
   QList<Character*> characterDatabase;
   Map* map;
};

#endif // CHARACTERMANAGER_H
