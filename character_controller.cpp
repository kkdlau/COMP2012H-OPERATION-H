#include "character.h"
#include <cctype>
const QVector<char> Character::Controller::listenKeyList = {
    'a', 's', 'd', 'w', ' ', 'k', 'm'
};

QHash<char, Character::MOVE_DIRECTION> Character::Controller::KEY2DIRETION = {};

Character::Controller::Controller() {
    keyStateInitialize();
}

void Character::Controller::keyStateInitialize() {
     QVector<char>::const_iterator ptr;

    for (ptr = listenKeyList.begin(); ptr < listenKeyList.end(); ++ptr) {
        keyState[*ptr] = false;
    }

    KEY2DIRETION['a'] = MOVE_DIRECTION::LEFT;
    KEY2DIRETION['s'] = MOVE_DIRECTION::DOWN;
    KEY2DIRETION['w'] = MOVE_DIRECTION::UP;
    KEY2DIRETION['d'] = MOVE_DIRECTION::RIGHT;
}

void Character::Controller::setState(char key, Character::Controller::KeyState state) {
    if (isalpha(key)) key = tolower(key);
    bool oldState = keyState[key];
    keyState[key] = state;
    if (oldState == false && state == true)
        updateKeyPressControl();
//    qDebug() << "set state: " << key << " -> " << pressed;
    updateKeyHoldingControl();
}

void Character::Controller::unControl() {
    toControl = nullptr;
}
void Character::Controller::control(Character *c) {
    toControl = c;
}

void Character::Controller::updateKeyPressControl() {
    if (toControl == nullptr) return;

    if (keyState[' ']) {
        toControl->pickWeapon();
    }

    if (keyState['m']) {
        toControl->attack();
    }
}

void Character::Controller::updateKeyHoldingControl() {
    if (toControl == nullptr) return;
    unsigned controlVector = 0;
    QVector<char>::const_iterator ptr;
    for (ptr = listenKeyList.begin(); ptr < listenKeyList.end(); ++ptr) {
        if (keyState[*ptr] && KEY2DIRETION.keys().contains(*ptr)) {
            controlVector |= KEY2DIRETION[*ptr];
        }
    }


    QVector2D v = toControl->getMovementvector(controlVector);
    if (v.length())
    toControl->moveBy(v.x(), v.y());
}
