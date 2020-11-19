#ifndef COMBO_H
#define COMBO_H

#include <QString>

#include "KeyState.h"

class Combo {
   private:
	QString str;
	KeyState triggerState;

   public:
	Combo(QString&& strRepresention, KeyState triggerState);

	QString toString();

	QString getComboStr();

	KeyState getTriggerState();
};

#endif	// COMBO_H
