#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H
#include "character.h"
#include "qhash.h"

class character_manager
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
    character_manager();
    /**
      *Destructor for chracter_manager(), deleting
      * any *character in the database
      */
    ~character_manager();
    /**
     * @brief get specified character in database, return null if character doesnt exist;
     * @param character_name
     * @return character*\/ nullptr if character does not exist
     */
    Character* get_character(QString character_name) const;
    /**
     * @brief operator [] to simplify get_character function
     * @return character*
     */
    Character* operator[](QString)const;
    /**
     * @brief Prevent ability to create another instance via copy constructor
     */
    character_manager(character_manager&) = delete;
    /**
     * @brief prevent ability to create another instance via memberwise assignment
     * @return
     */
    Character* operator=(const character_manager*) = delete;
    /**
     * @brief check if character is in the database
     * @return bool
     */
    bool is_character_exist(QString);
    /**
     * @brief add *character to the database
     */
    void add_character(Character*);
    /**
     * @brief delete specified character name in database
     */
    void delete_character(QString);
    /**
     * @brief delete all character in the database
     */
    void reset_character_manager();
    /**
     * @brief return an instance of character_manager.
     * @return *character_manager
     */
    static character_manager *get_instance();
private:
    /**
    * @brief static variable to hold character_manager
    */
   static character_manager *instance;
   /**
    * @brief Hashmap to save the characters.
    */
   QHash<QString, Character*> database;
};

#endif // CHARACTER_MANAGER_H
