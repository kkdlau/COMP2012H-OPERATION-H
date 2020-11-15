#include "keyboardmanager.h"
 #include <QDebug>
KeyboardManager::KeyboardManager() {

}

void KeyboardManager::keyInitialize(const char key) {
    /**
     * By default, the key is not pressed.
     */
    qDebug() << "initialize key: " << char(key) << "\n";
    keyState[key] = KeyState::RELEASE;
}

void KeyboardManager::addCombo(QString combo, std::function<void(void)> process) {
    comboList.push_back(combo);
    actionList[combo.toUtf8().constData()] = process; //Add the combo to the listener list.

    for(int i = 0; combo[i] != '\0'; ++i) { // for each combo character
        if (combo[i] == '+') continue;
        keyInitialize(combo[i].unicode());
    }

}

bool KeyboardManager::isAllKeysPressed(const QString& combo) {
    qDebug() << "check isAllKeysPressed" << "\n";

    for(int i = 0; i < combo.length(); ++i) { // for each combo character
        if (combo[i] == '+') continue;
        qDebug() << "\t check key: " << char(combo[i].unicode()) << ", is pressed: " << (keyState[char(combo[i].unicode())] == KeyState::PRESSED) << "\n";
        if (keyState[char(combo[i].unicode())] != KeyState::PRESSED) return false;
    }

    return true;
}


void KeyboardManager::pressKey(const char key) {
    qDebug() << "key pressed: " << key << "\n";
    keyState[key] = KeyState::PRESSED;

    QVector<QString>::iterator ptr;

    for (ptr = comboList.begin(); ptr != comboList.end(); ptr++) {
        qDebug() << "Checking combo - " << *ptr << "\n";
        if (isAllKeysPressed(*ptr)) {
            actionList[*ptr]();
        }
    }
}

void KeyboardManager::releaseKey(const char key) {
     keyState[key] = KeyState::RELEASE;
}
