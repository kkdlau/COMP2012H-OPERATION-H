#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H
#include <QString>
#include <QHash>
#include <QVector>
#include <functional>
#include "KeyState.h"

class KeyboardManager
{
private:

    /**
     * Hash map for storing function pointer corresponding to combo string.
     */
    QHash<const QString, std::function<void(void)>> actionList;

    /**
     * Hash map for storing key state, only keys used by combo are saved in this map.
     */
    QHash<char, KeyState> keyState;

    /**
     * Vector for storing registered combo.
     */
    QVector<QString> comboList;

    /**
     * initialize a key's state.
     *
     * @param key {const char}: key id in char
     */
    void keyInitialize(const char key);


    /**
     * check if all combo keys are pressed.
     *
     * @param combo {const QString&}: constant reference of combo string
     * @return {bool}: is all combo keys pressed or not
     */
    bool isAllKeysPressed(const QString& combo);

public:
    KeyboardManager();

    void addCombo(QString combo, std::function<void(void)> process);

    void deleteCombo(QString action);

    void pressKey(const char key);

    void releaseKey(const char key);
};

#endif // KEYBOARDMANAGER_H
