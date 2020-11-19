#ifndef KEYSTATE_H
#define KEYSTATE_H

#include <QString>

enum class KeyState { RELEASE, PRESSED, PRESSING };

static QString keyState2Str(KeyState state) {
	switch (state) {
		case KeyState::RELEASE:
			return "KeyState::RELEASE";
		case KeyState::PRESSED:
			return "KeyState::PRESSED";
		case KeyState::PRESSING:
			return "KeyState::PRESSING";
		default:
			return "(unexpected state)";
	}
}

#endif	// KEYSTATE_H
