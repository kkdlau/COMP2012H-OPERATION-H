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
    static CharacterManager *getInstance();
    /**
     * @brief generate_random_character create and return a Character*
     * @return Character*
     */
    Character* generate_random_character();
    /**
     * @brief generate_random_enemy create and return an Enemy*
     * @return Enemy*
     */
    Enemy* generate_random_enemy();
    /**
     * @brief dispose_from_map remove a character from the map (not deleting the Character*)
     */
    void dispose_from_map(Character*);
    void temp_function();
    /**
     * @brief set_map set the Map* for the character manager
     * @param map
     */
    void set_map(Map* map);
    /**
     * @brief check_endgame checks if all of the Character* dies
     * @return bool
     */
    bool check_endgame();
private:
    /**
     * Constructor for character_manager()
     */
    CharacterManager();
    /**
    * @brief static variable to hold character_manager
    */
   static CharacterManager *instance;
   /**
    * @brief Hashmap to save the characters.
    */
   QList<Character*> characterDatabase;
   Map* map;
   bool deleting = false;
};

#endif // CHARACTERMANAGER_H
