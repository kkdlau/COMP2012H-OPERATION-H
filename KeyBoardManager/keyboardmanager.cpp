#include "keyboardmanager.h"

#include <QDebug>

KeyboardManager::KeyboardManager(QObject* parent) : QObject{parent} {}

void KeyboardManager::keyInitialize(const char key) {
	/**
	 * By default, the key is not pressed.
	 */
	keyState[key] = KeyState::RELEASE;
}

KeyboardManager& KeyboardManager::addListeningCombo(QString combo) {
	comboList.push_back(combo);

	for (int i = 0; combo[i] != '\0'; ++i) {  // for each combo character
		if (combo[i] == '+') continue;
		keyInitialize(combo[i].unicode());
	}

	return *this;
}

bool KeyboardManager::isAllKeysPressed(const QString& combo) {
	for (int i = 0; i < combo.length(); ++i) {	// for each combo character
		if (combo[i] == '+') continue;
		if (keyState[char(combo[i].unicode())] != KeyState::PRESSED)
			return false;
	}

	return true;
}

void KeyboardManager::pressKey(QKeyEvent* k) {
	const char key = k->key();
	keyState[key] = KeyState::PRESSED;

	QVector<QString>::iterator ptr;

	for (ptr = comboList.begin(); ptr != comboList.end(); ptr++) {
		if (isAllKeysPressed(*ptr)) {
			emit comboPressed(*ptr);
		}
	}
    emit emitKeyboardPressed();
}

void KeyboardManager::releaseKey(QKeyEvent* k) {
	const char key = k->key();
	keyState[key] = KeyState::RELEASE;
}
