#include "keyboardmanager.h"
#include <QDebug>

KeyboardManager::KeyboardManager(QObject *parent): QObject{parent} {

}

void KeyboardManager::keyInitialize(const char key) {
    /**
     * By default, the key is not pressed.
     */
    qDebug() << "initialize key: " << char(key) << "\n";
    keyState[key] = KeyState::RELEASE;
}

KeyboardManager& KeyboardManager::addListeningCombo(QString combo) {
    comboList.push_back(combo);

    for(int i = 0; combo[i] != '\0'; ++i) { // for each combo character
        if (combo[i] == '+') continue;
        keyInitialize(combo[i].unicode());
    }

    return *this;

}

bool KeyboardManager::isAllKeysPressed(const QString& combo) {
    qDebug() << "check isAllKeysPressed" << "\n";

    for(int i = 0; i < combo.length(); ++i) { // for each combo character
        if (combo[i] == '+') continue;
//        qDebug() << "\t check key: " << char(combo[i].unicode()) << ", is pressed: " << (keyState[char(combo[i].unicode())] == KeyState::PRESSED) << "\n";
        if (keyState[char(combo[i].unicode())] != KeyState::PRESSED) return false;
    }

    return true;
}


void KeyboardManager::pressKey(QKeyEvent* k) {
    const char key = k->key();
//    qDebug() << "key pressed: " << key << "\n";
    keyState[key] = KeyState::PRESSED;

    QVector<QString>::iterator ptr;

    for (ptr = comboList.begin(); ptr != comboList.end(); ptr++) {
//        qDebug() << "Checking combo - " << *ptr << "\n";
        if (isAllKeysPressed(*ptr)) {
            emit comboPressed(*ptr);
        }
    }
}

void KeyboardManager::releaseKey(QKeyEvent* k) {
    const char key = k->key();
    keyState[key] = KeyState::RELEASE;
}
