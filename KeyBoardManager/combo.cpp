#include "combo.h"

Combo::Combo(QString&& strRepresention, KeyState triggerState): str(strRepresention), triggerState(triggerState) {

}


QString Combo::toString() {
    return "Combo: " + getComboStr() + ", trigger state: " + keyState2Str(getTriggerState());
}

QString Combo::getComboStr() {
    return str;
}

KeyState Combo::getTriggerState() {
    return triggerState;
}

